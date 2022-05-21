// MAX-MIN HEAP

typedef struct heapNode {
    int priority;
    int data;
} heapNode;

typedef char boolean;

int parent(int i) {return (i - 1) / 2;}
int left_child(int i) {return 2*i + 1;}
int right_child(int i) {return 2*i + 2;}

void swap(heapNode* x, heapNode* y) {
    heapNode temp = *x;
    *x = *y;
    *y = temp;
}

void max_heap_insert(heapNode heap[], heapNode node, int* n, int max_dim) {
    if (max_dim == *n) {
        if (heap[*n].priority < node.priority)
            heap[*n] = node;
    } else {
        heap[*n] = node;
    }

    int i = *n;
    while(i != 0 && heap[parent(i)].priority < heap[i].priority) {
        swap(&heap[parent(i)], &heap[i]);
        i = parent(i);
    }

    if (max_dim != *n)
        *n += 1;
}

void min_heap_insert(heapNode heap[], heapNode node, int* n) {
    //    if(node.data == 399)
    //        printf("\n\n INSERISCO 399 \n");

    heap[*n] = node;

    int i = *n;
    while(i != 0 && heap[parent(i)].priority > heap[i].priority) {
        swap(&heap[parent(i)], &heap[i]);
        i = parent(i);
    }

    *n += 1;
}

void max_heapify(heapNode heap[], int i, int n) {
    int left = left_child(i);
    int right = right_child(i);
    int largest = i;

    if(left <= n && heap[left].priority > heap[largest].priority)
        largest = left;

    if(right <= n && heap[right].priority > heap[largest].priority)
        largest = right;

    if (largest != i) {
        heapNode temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;
        max_heapify(heap, largest, n);
    }
}

void min_heapify(heapNode heap[], int i, int n) {
    int left = left_child(i);
    int right = right_child(i);
    int lower = i;

    if(left < n && heap[left].priority < heap[lower].priority)
        lower = left;

    if(right < n && heap[right].priority < heap[lower].priority)
        lower = right;

    if (lower != i) {
        heapNode temp = heap[i];
        heap[i] = heap[lower];
        heap[lower] = temp;
        min_heapify(heap, lower, n);
    }
}

void build_max_heap(heapNode heap[], int n) {
    for (int i = n/2; i >= 0; i--) {
        max_heapify(heap, i, n);
    }
}

void build_min_heap(heapNode heap[], int n) {
    for (int i = n/2; i >= 0; i--) {
        min_heapify(heap, i, n);
    }
}

heapNode get_maxmin(heapNode heap[]) {
    return heap[0];
}

heapNode delete_max(heapNode heap[], int* n) {
    heapNode max = heap[0];

    heap[0] = heap[*n - 1];
    *n -= 1;

    max_heapify(heap, 0, *n);
    return max;
}

heapNode delete_min(heapNode heap[], int* n) {
    heapNode min = heap[0];

    heap[0] = heap[*n - 1];
    *n -= 1;

    min_heapify(heap, 0, *n);
    return min;
}

void updatePriority(heapNode h[], int n, int i, int new_priority) {
    if (new_priority == h[i].priority)
        return;

    if(new_priority > h[i].priority) {
        h[i].priority = new_priority;
        min_heapify(h, i, n);
    } else {
        h[i].priority = new_priority;

        if (i == 0)
            return;

        while (parent(i) >= 0 && h[i].priority < h[parent(i)].priority) {
            swap(&h[parent(i)], &h[i]);
            i = parent(i);
        }
    }
}

void print_heap(heapNode heap[], int n) {
    printf("\n------ heap ------");
    for (int i = 0; i < n; i++) {
        printf("\nPri: %d, Data: %d", heap[i].priority, heap[i].data);
    }
    printf("\n-------------------");
}
