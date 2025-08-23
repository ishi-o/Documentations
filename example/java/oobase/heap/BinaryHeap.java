package example.java.oobase.heap;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

/**
 *
 */
public class BinaryHeap<T> extends AbstractHeap<T> implements Cloneable {

    private final ArrayList<T> heap;

    public BinaryHeap() {
        this(null, false);
    }

    public BinaryHeap(boolean compType) {
        this(null, compType);
    }

    public BinaryHeap(Comparator<T> comp) {
        this(comp, false);
    }

    public BinaryHeap(Comparator<T> comp, boolean compType) {
        super(comp, compType);
        heap = new ArrayList<>();
        heap.addLast(null);
    }

    void __upward(int idx) {
        if (idx <= _size) {
            while (idx > 1 && __compare(heap.get(idx), heap.get(idx >> 1)) > 0) {
                Collections.swap(heap, idx, idx >> 1);
                idx >>= 1;
            }
        }
    }

    void __downward(int idx) {
        if (idx >= 1) {
            int tmp;
            while ((idx << 1) <= _size) {
                tmp = idx << 1;
                if ((idx << 1 | 1) <= _size && __compare(heap.get(idx << 1 | 1), heap.get(idx << 1)) > 0) {
                    tmp = idx << 1 | 1;
                }
                if (__compare(heap.get(tmp), heap.get(idx)) > 0) {
                    Collections.swap(heap, tmp, idx);
                    idx = tmp;
                } else {
                    break;
                }
            }
        }
    }

    @Override
    public T top() {
        __checkIndex(1);
        return heap.get(1);
    }

    @Override
    public T pop() {
        __checkIndex(1);
        Collections.swap(heap, 1, _size);
        --_size;
        __downward(1);
        return heap.removeLast();
    }

    @Override
    public void push(T e) {
        heap.addLast(e);
        __upward(++_size);
    }

    @Override
    public void clear() {
        _size = 0;
        heap.clear();
        heap.addLast(null);
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

}
