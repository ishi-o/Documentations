package demo.oobase.heap;

import java.util.Comparator;
import java.util.NoSuchElementException;

/**
 * @author Ishi_O
 * @since
 */
public abstract class AbstractHeap<T> implements Heap<T> {

    int _size = 0;

    private final Comparator<T> comp;

    private final boolean compType;

    public AbstractHeap(Comparator<T> comp, boolean compType) {
        this.comp = comp;
        this.compType = compType;
    }

    @SuppressWarnings("unchecked")
    int __compare(T lhs, T rhs) {
        if (comp == null) {
            return (compType ? -1 : 1) * ((Comparable<T>) lhs).compareTo(rhs);
        } else {
            return (compType ? -1 : 1) * comp.compare(lhs, rhs);
        }
    }

    void __checkIndex(int idx) {
        if (idx < 1 || idx > _size) {
            throw new NoSuchElementException();
        }
    }

    @Override
    public T top() {
        throw new UnsupportedOperationException();
    }

    @Override
    public T pop() {
        throw new UnsupportedOperationException();
    }

    @Override
    public void push(T e) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void clear() {
        _size = 0;
    }

    @Override
    public boolean isEmpty() {
        return _size == 0;
    }

    @Override
    public int size() {
        return _size;
    }
}
