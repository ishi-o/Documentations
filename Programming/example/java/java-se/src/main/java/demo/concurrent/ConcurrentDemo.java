package demo.concurrent;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.ThreadPoolExecutor;

public class ConcurrentDemo {

    public static void traditionThreadDemo() {
        Thread t1 = new Thread() {
            @Override
            public void run() {
                while (!isInterrupted()) {  // 循环检测是否中断
                    try {
                        sleep(100);
                    } catch (InterruptedException e) {
                        break;
                    }
                }
            }
        };
        t1.setDaemon(true);
        t1.start();
        t1.interrupt();

    }

    public static void concurrentThreadDemo() {
        ExecutorService es = new ThreadPoolExecutor(0, 0, 0, null, null);

    }
}
