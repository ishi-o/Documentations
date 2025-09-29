package demo;

import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import demo.config.BeansConfiguration;

public class Main {
	public static void main(String[] args) {
		ApplicationContext ctx = new AnnotationConfigApplicationContext(BeansConfiguration.class);
		ApplicationContext ctx2 = new ClassPathXmlApplicationContext("main/resources/bean.xml");
	}
}