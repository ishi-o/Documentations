package example.java.io;

/**
 */
public class BufferByBio {

    private final byte[] buf;
    private int pos, mark, limit;

    private final int size;

    public BufferByBio(int size) {
        this.size = size;
        this.pos = 0;
        this.mark = -1;
        this.limit = this.size;
        this.buf = new byte[this.size];
    }

    public int position() {
        return pos;
    }

    public void position(int pos) {
        if (pos < mark) {
            throw new IllegalArgumentException();
        }
        this.pos = pos;
    }

    public void mark() {
        mark = pos;
    }

    public int limit() {
        return limit;
    }

    public void limit(int limit) {
        if (limit < pos) {
            throw new IllegalArgumentException();
        }
        this.limit = limit;
    }

    public void reset() {
        if (pos < mark || mark < 0) {
            throw new IllegalArgumentException();
        }
        pos = mark;
    }

    public void flip() {
        limit = pos;
        pos = 0;
    }

    public byte get() {
        if (pos == limit) {
            throw new IllegalArgumentException();
        }
        return buf[pos++];
    }

    public void put(byte b) {
        if (pos == size) {
            throw new IllegalArgumentException();
        }
        buf[pos++] = b;
    }

    public int capacity() {
        return size;
    }
}
