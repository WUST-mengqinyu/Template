template<class T = int>
struct BinaryHeap {
    vector<T> Heap;
    int sz;
    BinaryHeap(int s = 0) { Heap.resize(s), sz = 0; }
    void init(int s) { Heap.resize(s), sz = 0; }
    bool less(T a, T b) { return a > b; }
    void up(int p) {
        while (p > 1) {
            if (less(Heap[p / 2], Heap[p])) {
                swap(Heap[p], Heap[p / 2]);
                p /= 2;
            } else break;
        }
    }
    void down(int p) {
        int s = p * 2;
        while (s <= sz) {
            if (s < sz && less(Heap[s], Heap[s + 1])) s++;
            if (less(Heap[p], Heap[s])) {
                swap(Heap[s], Heap[p]);
                p = s, s = p * 2;
            } else break;
        }
    }
    void insert(int val) {
        Heap[++sz] = val;
        up(sz);
    }
    void removeTop() {
        Heap[1] = Heap[sz--];
        down(1);
    }
    void remove(int pos) {
        Heap[pos] = Heap[sz--];
        up(pos), down(pos);
    }
    int getTop() {
       assert(sz > 0);
       return Heap[1];
    }
};