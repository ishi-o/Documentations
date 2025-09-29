package demo.beans;

import java.io.IOException;
import java.io.InputStream;
import java.nio.channels.ReadableByteChannel;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.io.Resource;
import org.springframework.core.io.ResourceLoader;
import org.springframework.stereotype.Component;

@Component
public class ResourceDemo {
	private final ResourceLoader resourceLoader;

	@Autowired
	public ResourceDemo(ResourceLoader resourceLoader) {
		this.resourceLoader = resourceLoader;
	}

	public void resourceDemo() {
		Resource res = resourceLoader.getResource("https://www.baidu.com/");
		if (res.exists() && res.isReadable()) {
			try (InputStream is = res.getInputStream(); ReadableByteChannel bc = res.readableChannel();) {
				// use bio or nio
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}