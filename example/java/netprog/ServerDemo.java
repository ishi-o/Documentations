package example.java.netprog;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

/**
 */
public class ServerDemo {

    public static void BioTCPServerDemo() {
        try (ServerSocket ss = new ServerSocket(8080);) {
            while (true) {
                Socket sock = ss.accept();
                Thread t = new Thread() {
                    Socket s = sock;

                    @Override
                    public void run() {
                        try (InputStream in = s.getInputStream(); OutputStream out = s.getOutputStream(); BufferedReader bin = new BufferedReader(new InputStreamReader(in, StandardCharsets.UTF_8)); BufferedWriter bout = new BufferedWriter(new OutputStreamWriter(out, StandardCharsets.UTF_8))) {
                            String line;
                            int readlen;
                            while ((line = bin.readLine()) != null) {
                                // 解析请求报文
                            }
                            // 输出响应报文
                            bout.write("Bye!\n");
                            bout.flush();
                        } catch (IOException e) {
                        }
                    }
                };
                t.start();
            }
        } catch (IOException e) {
        }
    }

    public static void BioUDPServerDemo() {
        try (DatagramSocket ds = new DatagramSocket(8080);) {
            byte[] buf = new byte[1024];
            DatagramPacket dp = new DatagramPacket(buf, buf.length);
            while (true) {
                ds.receive(dp);
                String msg = new String(dp.getData(), dp.getOffset(), dp.getLength(), StandardCharsets.UTF_8);
                // 处理 msg ... 
                byte[] senddata = "Hello!\n".getBytes(StandardCharsets.UTF_8);
                dp.setData(senddata);
                ds.send(dp);
            }
        } catch (IOException e) {
        }

    }

}
