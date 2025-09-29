package demo.config;

import org.jspecify.annotations.Nullable;
import org.springframework.web.servlet.support.AbstractAnnotationConfigDispatcherServletInitializer;

/**
 */
public class WebApplicationContextInitializer extends AbstractAnnotationConfigDispatcherServletInitializer {
	@Override
	protected Class<?> @Nullable [] getRootConfigClasses() {
		return null;
	}

	@Override
	protected Class<?>[] getServletConfigClasses() {
		return new Class<?>[] { WebConfig.class };
	}

	@Override
	protected String[] getServletMappings() {
		return new String[] { "/api/**" };
	}

}
