package demo.config;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;

import demo.beans.User;

/**
 */
@Configuration
@ComponentScan(basePackages = { "demo.service", "demo.repository" })
public class BeansConfiguration {
	@Bean
	public User user() {
		return new User();
	}

	@Bean
	@Primary
	public User user(@Value("1") Integer uid, @Value("aaa") String username) {
		return new User(uid, username);
	}
}
