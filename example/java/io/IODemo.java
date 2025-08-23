package example.java.io;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.URI;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.nio.charset.CharsetEncoder;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.LinkOption;
import java.nio.file.Path;
import java.nio.file.PathMatcher;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.nio.file.StandardOpenOption;
import java.nio.file.attribute.BasicFileAttributes;
import java.nio.file.attribute.PosixFileAttributes;
import java.nio.file.attribute.UserDefinedFileAttributeView;

/**
 */
public class IODemo {

    public static void bioDemo() {
        // copy demo using bio
        File fsrc = new File("./s"), fdst = new File("./o");
        try {
            if (!fsrc.exists()) {
                fsrc.createNewFile();
            }
            if (!fdst.exists()) {
                fdst.createNewFile();
            }
            if (fsrc.isFile() && fsrc.canRead() && fdst.isFile() && fdst.canWrite()) {
                try (FileInputStream fin = new FileInputStream(fsrc); BufferedInputStream bin = new BufferedInputStream(fin); FileOutputStream fout = new FileOutputStream(fdst); BufferedOutputStream bout = new BufferedOutputStream(fout);) {
                    byte[] buf = new byte[1024];
                    int readlen;
                    while ((readlen = bin.read(buf, 0, 1024)) != -1) {
                        bout.write(buf, 0, readlen);
                    }
                }
            }
        } catch (IOException e) {
        }
    }

    public static void nioDemo() {
        Path src = Path.of("./a"), dst = Path.of("./o");
        ByteBuffer buf = ByteBuffer.allocate(1024);
        try {
            FileChannel fin = FileChannel.open(src, StandardOpenOption.READ), fout = FileChannel.open(dst, StandardOpenOption.WRITE);
            while (fin.read(buf) != -1) {
                buf.flip();
                fout.write(buf);
                buf.flip();
            }
        } catch (IOException e) {
        }
    }

    public static void pathDemo() {
        // Path API
        Path pp = Paths.get("");
        Path p = Path.of(URI.create("file://www.baidu.com/index.html"));    // 静态方法, 替代Paths的所有作用 根为classpath
        System.out.println(p);                  // 输出p.getFileName()
        System.out.println(p.getFileName());    // 返回String文件名
        System.out.println(p.getFileSystem());  // 返回FileSystem
        System.out.println(p.getNameCount());   // 返回路径的层级
        System.out.println(p.getName(0));   // 返回第index层的Path对象
        System.out.println(p.getParent());  // 相对路径则返回null
        System.out.println(p.getRoot());    // 相对路径返回null
        System.out.println(p.isAbsolute()); // 绝对路径返回true
        System.out.println(p.iterator().hasNext());   // 返回从小到大遍历所有层的迭代器
        System.out.println(p.normalize());  // 规范化路径, 去除所有.和..
        System.out.println(p.relativize(p.getName(0)));    // 返回它们之间的相对路径
        System.out.println(p.resolve(p.getName(0)));   // 解析路径, 若为绝对路径则返回, 否则在this后拼接并返回
        System.out.println(p.resolveSibling(p.getName(0))); // 解析路径, 若为绝对路径则返回, 否则在this.parent后拼接并返回
        // startsWith和endsWith
        System.out.println(p.toAbsolutePath());
        System.out.println(p.toUri()); // toUri   file://{p.getFilePath()}
    }

    public static void charsetDemo() {
        // 枚举: StandardCharsets
        // 类: Charset
        // get a charset
        Charset cs = Charset.forName("UTF-8");
        // get a decoder or encoder
        CharsetDecoder decoder = cs.newDecoder();
        CharsetEncoder encoder = cs.newEncoder();
        // bytebuffer <-> charbuffer
        ByteBuffer bbuf = ByteBuffer.allocate(1024);
        try {
            var cbuf = decoder.decode(bbuf);
            decoder.reset();
            var bytebuf = encoder.encode(cbuf);
            encoder.reset();
        } catch (Exception e) {
        }
    }

    public static void fileAttributeDemo() {
        Path src = Path.of("./LICENSE");
        try {
            BasicFileAttributes basicAttr = Files.readAttributes(src, BasicFileAttributes.class, LinkOption.NOFOLLOW_LINKS);
            PosixFileAttributes posixAttr = Files.readAttributes(src, PosixFileAttributes.class);
            UserDefinedFileAttributeView userDefinedAttrView = Files.getFileAttributeView(src, UserDefinedFileAttributeView.class);
        } catch (Exception e) {
        }

    }

    public static void fileFilterDemo() {
        Path src = Path.of("");
        PathMatcher globMatcher = FileSystems.getDefault().getPathMatcher("glob:");
        PathMatcher regexMatcher = FileSystems.getDefault().getPathMatcher("regex:");
        globMatcher.matches(src);
        regexMatcher.matches(src);
    }

    public static void filesDemo() {
        Path src = Path.of("./LICENSE"), dst = Path.of("./a.txt");
        try {
            Files.copy(src, dst, StandardCopyOption.COPY_ATTRIBUTES);
            Files.move(src, dst, StandardCopyOption.ATOMIC_MOVE);
            Files.createDirectories(dst);
            Files.createFile(dst);
            Files.createLink(Path.of("link"), dst);
            Files.delete(dst);
            Files.deleteIfExists(dst);
            Files.exists(dst, LinkOption.NOFOLLOW_LINKS);
            Files.getAttribute(dst, "attr_name", LinkOption.NOFOLLOW_LINKS);
            // Files.setAttribute(dst, attribute, dst, options);
            // Files.isXxx();
            Files.list(dst);
        } catch (Exception e) {
        }
    }

}
