## `Tomcat`

### 依赖

```xml
<dependency>
    <groupId>org.apache.tomcat.embed</groupId>
    <artifactId>tomcat-embed-core</artifactId>
    <version>11.0.10</version>
</dependency>

<!-- 若用到jsp技术 -->
<dependency>
    <groupId>org.apache.tomcat.embed</groupId>
    <artifactId>tomcat-embed-jasper</artifactId>
    <version>11.0.10</version>
</dependency>
```

### 结构介绍

- `Tomcat`是`Apache`开发的开源`Servlet`容器，其根目录一定是某个名为**`webapps`**的目录

- 其中，`WEB-INF`目录是受保护的，客户端无法访问这个目录下的资源，保存应用的信息

  这个目录下面还有`classes/`、`lib/`以及`web.xml`

  `classes/`存放`Java`程序的编译结果、`lib/`存放一系列第三方`jar`包

  其余应是一系列静态资源，例如`js/`、`css/`、`views/`等常见的命名

- 传统部署：指`Tomcat`服务器包含开发者开发的`.war`包这样的`Web`应用，`Servlet`应用开发好后打包成`.war`包并复制到`Tomcat`服务器中，然后启动服务器

  只有在传统部署中，会出现`classes/`与`lib/`，由`Tomcat`解包`.war`并存放于`classes/`下

### `web.xml`映射

- 这是一种比较传统的映射方式，仅了解即可

- `web.xml`应位于`webapps/WEB-INF`目录下，其中所有的配置会**覆盖注解形式的映射**

- 声明为`webapp`：

  ```xml
  <web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
		xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
		xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
		http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd" id="WebApp_ID" version="4.0">

  </web-app>
  ```

- 声明一个`Servlet`：

  ```xml
  <servlet>
      <servlet-name>Servlet_name</servlet-name>
      <servlet-class>类路径</servlet-class>
      <init-param>
  </servlet>
  ```

- 将`Servlet`映射到某个路径上：

  ```xml
  <servlet-mapping>
      <servlet-name>Servlet_name</servlet-name>
      <url-pattern>/路径</url-pattern>
  </servlet-mapping>
  ```

- 初始化某个`Servlet`或某个`Filter`的参数：

  ```xml
  <init-param>
    <param-name>param_name</param-name>
    <param-value>xml文件、字符串等</param-value>
  </init-param>
  ```

- 设置欢迎文件：

  ```xml
  <welcome-file-list>
    <welcome-file>index.html</welcome-file>
  </welcome-file-list>
  ```

- 设置`session`的生效时间

  ```xml
  <session-config>
    <session-timeout>30</session-timeout>
  </session-config>
  ```

### 注解映射

- `@WebServlet`注解：在`Servlet 3.0`前，需要在`web.xml`中配置大量信息，在`WebServlet`注解出现后，所有的配置被分散到各个服务类上，最重要且必要的属性是`urlPatterns`，是`String`集合，表示这些`URI`均映射到这个`Servlet`类上

  在传统部署时，它们的解析是全自动的

### 内嵌`Tomcat`

- 内嵌部署`Tomcat`显得更加灵活，由开发者完全控制`Tomcat`的配置，但因此**注解映射、静态资源需要由开发者亲自解析、引入**

- 由`new Tomcat()`直接构造一个`Tomcat`实例，调用`start()`启动该服务器(会抛出`LifecycleException`受检异常)，调用`getServer().await()`使该服务器不断地等待请求

- `Tomcat`实例方法：

  - `setHostname(String)`：设置服务器地址

  - `setPort(int)`：设置服务器端口

  - `setBaseDir(String)`：设置基准目录，表示`Tomcat`实例工作时，临时文件等存放的根目录

    推荐设置为`target/`下的某个目录

  - `getConnector()`：获取其绑定的连接器

  - **`Context addWebapp(String contextPath, String docBase)`**：添加`Web`应用并获取它的上下文实例

    `contextPath`指上下文的根所**映射的`URL`路径**，例如传入`""`则该上下文会映射到`"/"`

    `docBase`指要引入的**资源的本地路径**，提供的路径下必须含有`WEB-INF`目录及`web.xml`文件

    等价于将整个`Web`应用加载到服务器上，使用`addWebapp()`会自动生成并注册一个默认的`Servlet`服务，当客户端访问那些在用户自定义`Servlet`服务中找不到的服务时，会转向这个默认服务

    默认服务会试图在`docBase`下的静态资源中查询是否有对应的资源，若找到则返回，否则返回`404`响应

  - `Context addContext(String contextPath, String docBase)`：添加一个**空白的上下文**实例，参数意义同上

  - **`addServlet(String contextPath, String servletName, Servlet serv)`**：登记一个名为`servletName`的微服务，对应到路径为`contextPath`的上下文

    有静态方法的版本，其中`contextPath`应替换为`Context`对象

    同时需要使用`Context`实例的`addServletMappingDecoded(String pattern, String name)`将微服务映射到`URL`的某个路径上

    这两步等价于在`web.xml`中声明`Servlet`服务和映射

- 上下文类`Context`的实例方法：

  - `addWelcomeFile(String)`：设置当客户端访问根路径时，返回的资源文件
  
    即将`String`指向的资源文件映射到`"/"`
  
  - **`addServletMappingDecoded(String pattern, String name)`**：将微服务映射到某个`URL`上
  
  - `addFilterDef(FilterDef)`：登记一个`Filter`，由`FilterDef`封装其信息
  
    `FilterDef`常用方法：`setFilter(Filter)`、`setFilterName(String)`、`addInitParameter(String, Object)`
  
    分别为登记`Filter`对象、登记`Filter`服务名、初始化`Filter`参数
  
  - `addFilterMap(FilterMap)`：登记从`Filter`到`URL`的映射，由`FilterMap`封装映射信息
  
    `FilterMap`常用方法：`addURLPatternDecoded(String)`、`addServletName(String)`、`setFilterName(String)`
  
    分别为登记其应用的`URL`、登记其应用的`Servlet`、设置其绑定的`Filter`服务名

