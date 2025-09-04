package demo.io;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Arrays;
import java.util.stream.Stream;

/**
 */
public class FilesByBio {

    public static void copy(File src, File dst) {
        if (!src.exists() || dst.exists()) {
            throw new IllegalArgumentException();
        } else {
            try {
                dst.createNewFile();
            } catch (IOException e) {
            }
        }
        if (src.isFile()) {
            try (FileInputStream fin = new FileInputStream(src); BufferedInputStream bin = new BufferedInputStream(fin); FileOutputStream fout = new FileOutputStream(dst); BufferedOutputStream bout = new BufferedOutputStream(fout);) {
                byte[] buf = new byte[1024];
                int off;
                while ((off = bin.read(buf, 0, 1024)) != -1) {
                    bout.write(buf, 0, off);
                }
            } catch (IOException e) {
            }
        } else {
            dst.mkdir();
            for (File f : src.listFiles()) {
                copy(f, new File(dst, f.toString()));
            }
        }
    }

    public static void move(File src, File dst) {
        src.renameTo(dst);
    }

    public static void createDirectories(File d) {
        d.mkdirs();
    }

    public static Stream<File> list(File d) {
        return (Arrays.asList(d.listFiles())).stream();
    }

}
