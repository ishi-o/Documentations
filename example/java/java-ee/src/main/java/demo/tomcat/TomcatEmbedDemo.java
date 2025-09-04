package demo.tomcat;

import java.nio.file.Path;

import org.apache.catalina.Context;
import org.apache.catalina.LifecycleException;
import org.apache.catalina.startup.Tomcat;
import org.apache.tomcat.util.descriptor.web.FilterDef;
import org.apache.tomcat.util.descriptor.web.FilterMap;

import demo.servlet.ServletDemo;

/**
 */
public class TomcatEmbedDemo {

    public static void tomcatEmbedDemo() throws LifecycleException {
        Tomcat tomcat = new Tomcat();

        tomcat.setHostname("localhost");
        tomcat.setPort(8080);
        tomcat.getConnector();

        tomcat.setBaseDir("/target/tomcat/");

        String contextPath = "";
        // String docBase = new File("/src/main/webapp").getAbsolutePath();
        String docBase = Path.of("/src/main/webapp").toAbsolutePath().toString();
        Context context = tomcat.addContext(contextPath, docBase);

        String servletName = "ServletDemo";
        tomcat.addServlet(contextPath, servletName, new ServletDemo());
        context.addServletMappingDecoded("/api/*", servletName);

        FilterDef filterDef = new FilterDef();
        filterDef.setFilter((req, resp, chain) -> {
            // 过滤 ...
            // 链式处理
            chain.doFilter(req, resp);
        });
        filterDef.setFilterName("FilterDemo");

        FilterMap filterMap = new FilterMap();
        filterMap.addURLPatternDecoded("/*");
        filterMap.addServletName(servletName);
        filterMap.setFilterName("FilterDemo");

        context.addFilterDef(filterDef);
        context.addFilterMap(filterMap);

        tomcat.init();
        tomcat.start();
        tomcat.getServer().await();
    }
}
