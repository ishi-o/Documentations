package demo.io;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

/**
 */
public class FileChannelByBio implements AutoCloseable {

    private FileInputStream fin;
    private FileOutputStream fout;
    private BufferedInputStream bin;
    private BufferedOutputStream bout;

    public FileChannelByBio(File f) throws IOException {
        fin = new FileInputStream(f);
        fout = new FileOutputStream(f);
        bin = new BufferedInputStream(fin);
        bout = new BufferedOutputStream(fout);
    }

    @Override
    public void close() throws IOException {
        bin.close();
        bout.close();
        fin.close();
        fout.close();
    }

    public int read(BufferByBio dst) throws IOException {
        int tmp, cap = dst.capacity(), pos = dst.position(), it = pos;
        while (it < cap && (tmp = bin.read()) != -1) {
            dst.put((byte) tmp);
            ++it;
        }
        return it - pos;
    }

    public int write(BufferByBio src) throws IOException {
        int pos = src.position(), lim = src.limit(), it = pos;
        while (it < lim) {
            bout.write(src.get());
        }
        return it - pos;
    }

}
