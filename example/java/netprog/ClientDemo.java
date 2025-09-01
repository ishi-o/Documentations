package example.java.netprog;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.Authenticator;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.ProxySelector;
import java.net.Socket;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpClient.Redirect;
import java.net.http.HttpClient.Version;
import java.net.http.HttpHeaders;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.nio.charset.StandardCharsets;
import java.time.Duration;

/**
 */
public class ClientDemo {

    public static void BioTCPClientDemo() {
        try (Socket s = new Socket("localhost", 8080); InputStream in = s.getInputStream(); OutputStream out = s.getOutputStream(); BufferedReader bin = new BufferedReader(new InputStreamReader(in, StandardCharsets.UTF_8)); BufferedWriter bout = new BufferedWriter(new OutputStreamWriter(out, StandardCharsets.UTF_8))) {
            bout.write("Hello\n");
            bout.flush();
            System.out.println(bin.readLine());
        } catch (IOException e) {
        }
    }

    public static void BioUDPClientDemo() {
        try (DatagramSocket ds = new DatagramSocket();) {
            byte[] buf = new byte[1024];
            DatagramPacket dp = new DatagramPacket(buf, buf.length);
            ds.connect(InetAddress.getByName("localhost"), 8080);
            ds.send(dp);
            ds.disconnect();
        } catch (IOException e) {
        }
    }

    public static void BioHTTPClientDemo() {
        HttpClient hc = HttpClient.newBuilder()
                .version(Version.HTTP_2) // HTTP版本
                .followRedirects(Redirect.NORMAL) // 重定向策略
                .connectTimeout(Duration.ofSeconds(20)) // 超时时长
                .proxy(ProxySelector.of(new InetSocketAddress("proxy.example.com", 80))) // 代理
                .authenticator(Authenticator.getDefault())
                .build();
        HttpRequest hr = HttpRequest.newBuilder()
                .uri(URI.create("https://www.baidu.com/"))
                .header("Content-Type", "application/json")
                .POST(HttpRequest.BodyPublishers.ofString(""))
                .timeout(Duration.ofSeconds(10))
                .build();
        try {
            HttpResponse<String> resp = hc.send(hr, HttpResponse.BodyHandlers.ofString());
            int code = resp.statusCode();
            HttpHeaders headers = resp.headers();
            String body = resp.body();
        } catch (Exception e) {
        }
    }

}
