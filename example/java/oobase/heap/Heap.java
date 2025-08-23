package example.java.oobase.heap;

/**
 *
 */
public interface Heap<T> {

    T top();

    T pop();

    void push(T e);

    void clear();

    boolean isEmpty();

    int size();
}
