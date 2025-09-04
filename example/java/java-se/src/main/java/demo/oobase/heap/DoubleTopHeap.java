package demo.oobase.heap;

import java.util.Comparator;
import java.util.NoSuchElementException;

public class DoubleTopHeap<T> extends AbstractRankHeap<T> {

    private final Heap<T> kheap, oheap;

    public DoubleTopHeap(int rank) {
        this(rank, null, false);
    }

    public DoubleTopHeap(int rank, boolean compType) {
        this(rank, null, compType);
    }

    public DoubleTopHeap(int rank, Comparator<T> comp) {
        this(rank, comp, false);
    }

    /**
     *
     * @param rank
     * @param comp
     * @param compType true: 求第rank大元素, false: 求第rank小元素
     */
    public DoubleTopHeap(int rank, Comparator<T> comp, boolean compType) {
        super(rank, comp, compType);
        Comparator<T> c = (T o1, T o2) -> __compare(o1, o2);
        kheap = new BinaryHeap<>(c);
        oheap = new BinaryHeap<>(c, true);
    }

    void __checkRank() {
        if (rank > _size) {
            throw new NoSuchElementException();
        }
    }

    void __fillKheap() {
        while (!oheap.isEmpty() && kheap.size() < rank) {
            kheap.push(oheap.pop());
        }
        while (kheap.size() > rank) {
            oheap.push(kheap.pop());
        }
    }

    @Override
    public T top() {
        __checkRank();
        return kheap.top();
    }

    @Override
    public T pop() {
        __checkRank();
        --_size;
        if (!oheap.isEmpty()) {
            T tmp = kheap.pop();
            kheap.push(oheap.pop());
            return tmp;
        } else {
            return kheap.pop();
        }
    }

    @Override
    public void push(T e) {
        ++_size;
        if (!kheap.isEmpty() && __compare(e, kheap.top()) > 0) {
            oheap.push(e);
        } else {
            kheap.push(e);
        }
        __fillKheap();
    }

    @Override
    public void setRank(int k) {
        if (k < 1) {
            throw new IllegalArgumentException();
        }
        rank = k;
        __fillKheap();
    }

    @Override
    public void clear() {
        _size = 0;
        kheap.clear();
        oheap.clear();
    }

}
