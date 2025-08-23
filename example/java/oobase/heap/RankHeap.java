package example.java.oobase.heap;

public interface RankHeap<T> extends Heap<T> {

    void setRank(int k);

    int getRank();
}
