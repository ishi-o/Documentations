package demo.oobase.heap;

import java.util.Comparator;

/**
 */
public class AbstractRankHeap<T> extends AbstractHeap<T> implements RankHeap<T> {

    int rank;

    public AbstractRankHeap(int rank, Comparator<T> comp, boolean compType) {
        super(comp, compType);
        this.rank = rank;
    }

    @Override
    public void setRank(int k) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public int getRank() {
        return rank;
    }

}
