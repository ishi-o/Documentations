package demo.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.EnableWebMvc;
import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

import demo.filter.LogInterceptor;

/**
 */
@Configuration
@EnableWebMvc
@ComponentScan({ "demo.controller", "demo.filter" })
public class WebConfig implements WebMvcConfigurer {
	private final LogInterceptor logInterceptor;

	public WebConfig(LogInterceptor logInterceptor) {
		this.logInterceptor = logInterceptor;
	}

	@Override
	public void addInterceptors(InterceptorRegistry registry) {
		registry.addInterceptor(logInterceptor)
				.addPathPatterns("/api/**")
				.excludePathPatterns("/api/noIntercept")
				.order(0);
	}
}
