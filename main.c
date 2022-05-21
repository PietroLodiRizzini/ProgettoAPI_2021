#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.c"

int d = 0; // numero nodi
int k = 0;
char* comando;

#define INF 2000000000

int addGraphAndComputeRank();
void topK();
void dijkstraQueue(int G[d][d], int s, int pred[], int dist[]);

int main() {
    char continua = 1;
    char buffer[21];
    char d_str[10];
    char k_str[10];
    boolean costruisci_heap = 0;

    if (fgets(buffer, 21, stdin)) {}

    int i = 0, j = 0;
    do {
        d_str[i] = buffer[i];
        i++;
    } while (buffer[i] != ' ');
    do {
        i++;
        k_str[j] = buffer[i];
        j++;
    } while (buffer[i] != '\0');

    d = atoi(d_str);
    k = atoi(k_str);

    int dim_classifica = 0;
    heapNode classifica[k];

    int indiceGrafo = 0;
    char comando[20];
    do {
        memset(comando, '\0', 20);
        if(fgets(comando, 20, stdin)) {} else continua = 0;

        if(comando[0] == 'A') {
            heapNode newnode;
            newnode.data = indiceGrafo;
            newnode.priority = addGraphAndComputeRank();
            indiceGrafo++;
            if (dim_classifica < k) {
                classifica[dim_classifica] = newnode;
                dim_classifica++;
            } else {
                if (! costruisci_heap) {
                    build_max_heap(classifica, dim_classifica);
                    costruisci_heap = 1;
                }

                if(get_maxmin(classifica).priority > newnode.priority) {
                    classifica[0] = newnode;
                    max_heapify(classifica, 0, dim_classifica);
                }
            }
        } else if(comando[0] == 'T') {
            for (int l = 0; l < dim_classifica; ++l) {
                printf("%d", classifica[l].data);
                if (l != dim_classifica - 1)
                    printf(" ");
            }
            printf("\n");
        }
    } while(continua);

    return 0;
}

int addGraphAndComputeRank() {
    char str[11];
    int G[d][d];
    int k = 0, j = 0, l = 0;
    char buffer[10*d];

    for (int i = 0; i < d; i++) {
        memset(buffer, '\0', 10*d);

        if (fgets(buffer, 10*d, stdin)) {}
        do {
            str[j] = buffer[k];
            k++;
            j++;
            if (buffer[k] == ',' || buffer[k] == '\n') {
                G[i][l] = atoi(str);
                memset(str, '\0', 11);
                l++;
                k++;
                j = 0;
            }
        } while (buffer[k] != '\0');
        l = 0;
        j = 0;
        k = 0;
    }

    int parent[d];
    int dist[d];

    dijkstraQueue(G, 0, parent, dist);

    int metrica = 0;
    for (int i = 0; i < d; ++i)
        if(dist[i] != INF)
            metrica += dist[i];

    return metrica;
}

void dijkstraQueue(int G[d][d], int s, int pred[], int dist[]) {
    int n = 0;
    heapNode Q[d];
    dist[s] = 0;

    for (int i = 0; i < d; i++) {
        if(i != s) {
            dist[i] = INF;
        }
        heapNode node;
        node.priority = dist[i];
        node.data = i;
        min_heap_insert(Q, node, &n);
    }

    int i = 0;

    while (n != 0) {
        heapNode u = delete_min(Q, &n);

        for (int j = 0; j < d; ++j) {
            if (G[u.data][j] != 0 && u.data != j) {
                int ndis = dist[u.data] + G[u.data][j];

                if (dist[j] > ndis) {
                    dist[j] = ndis;
                    pred[j] = u.data;

                    int l;
                    for (l = 0; l < n; ++l) {
                        if (Q[l].data == j) {
                            updatePriority(Q, n, l, ndis);
                        }
                    }
                }
            }
        }

        i++;
    }
}