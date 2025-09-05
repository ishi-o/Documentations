## `javax.servlet`

### `Java EE`介绍

- 在`Java EE 8`及之前，这个企业版是由`Oracle`开发的闭源项目，包括一系列大型或中小型的商业软件包，但由于`Spring`等框架的流行，`Java EE`开始力不从心

  于是在之后，`Oracle`将整个`Java EE`移交给`Eclipse`开源基金会维护，并强制要求`Eclipse`不能继续使用`Java EE`的项目名以及`javax`的命名空间，因此在`Eclipse`接手这个项目后迫不得已将`javax`改为`jakarta`，并将大版本号提升至`5`，表示不再向下兼容

  总而言之，`javax`命名空间适用于`4.0`及之前的企业版项目，`jakarta`适用于`5.0`及之后的企业版

- `Servlet`源于`Server Applet`，即在服务端上运行的小程序

  在`SE`的网络编程中对于`Http`的处理只介绍了`HttpClient`，即客户端的编写，是因为服务端需要考虑的东西过多

  而`Servlet`项目致力于高效而安全地开发服务器

- `Servlet`本质可用于任意通信协议，但主要用于`HTTP`

  它内部封装了线程池，通过多线程的方式处理请求，因此比起此前的方案性能更高

- `Servlet`需要部署到专用的`Web`服务器上，称作`Servlet`容器，例如`Apache`的`Tomcat`项目、`Eclipse`的`Jetty`项目

  因为`Servlet`本质是一个`Web`应用，是`Servlet`容器向开发者暴露的规范接口，`Servlet`容器是更复杂的应用

### `servlet`依赖

```xml
<dependency>
    <groupId>javax.servlet</groupId>
    <artifactId>javax.servlet-api</artifactId>
    <version>4.0.1</version>
</dependency>

<dependency>
    <groupId>jakarta.servlet</groupId>
    <artifactId>jakarta.servlet-api</artifactId>
    <version>6.1.0</version>
</dependency>
```

### `Servlet`接口与`HttpServlet`实现类

- `Servlet`有三个重要方法：`init()`、`service()`、`destroy()`，由`Servlet`容器调用进行生命周期管理

  `service()`含有两个参数`HttpServletRequest`与`HttpServletResponse`

- `HttpServlet`是最常用的实现类，有四个重要方法：`doGet()`、`doPost()`、`doPut()`、`doDelete()`

  它们也均含有两个参数：`HttpServletRequest`与`HttpServletResponse`

  重写它们来自定义处理逻辑

  一般不需要重写`service()`，由`HttpServlet`已经实现好了，他会自动解析请求方法并调用`doXxx()`

  除非需要使用`HttpServlet`处理其它通信协议

- `HttpServletRequest`接口表示一个`HTTP`请求报文，常用方法如下：

  - `setCharsetEncoding(String)`：设置解析的编码集
  - `String getParameter(String name)`：获取某个请求参数
  - `String getHeader(String name)`：获取某个请求头
  - `getRequestDispatcher(String location)`：获取一个请求分发器，指向内部的另一个`URI`，通常会继续调用`RequestDispatcher`接口的`forward(req, resp)`内部转发

- `HttpServletResponse`接口表示一个`HTTP`响应报文，常用方法如下：

  - `setCharsetEncoding(String)`：设置解析的编码集
  - `setContentType(String type)`：设置响应体的类型
  - `PrintWriter getWriter()`：获取绑定的字符输出流
  - `ServletOutputStream getOutputStream()`：获取绑定的字节输出流
  - `setStatus(int)`：设置状态码
  - `setHeader(String name, String value)`：设置响应头
  - **`sendRedirect(String)`**：`302`临时重定向到另一个`URI`

- 一个服务器的所有`Servlet`实现类只会有一个实例，因此遇到多个请求时会用同一个实例来处理

  因此实现类的实例属性的所有访问需要保证线程安全

### `Session`与`Cookie`

- `Session`用于存储客户端的某种状态，能保证每个`Session`唯一，内部类似于一个`Map<String, Object>`

- `HttpServletRequest`对象的`getSession()`方法会创建并返回一个`HttpSession`对象

  `getSession(false)`则不会创建，而只是返回已有的对象，若无则返回`null`

- `HttpSession`实例的常用方法为`setAttribute(String, Object)`和`Object getAttribute(Stirng)`

  分别为设置、获取其存储的对象数据

### `JSP`技术

- `JSP`技术比较落后，了解即可

- 由于`Servlet`本质是内嵌`HTML`的`Java`微服务程序，大量的`HTML`文本由一行行的输出流打印比较麻烦，因此`JSP`技术出现

  `JSP`本质也是一个`Servlet`应用，由`Web`服务器在启动时自动将其编译成`Servlet`程序并在服务器上运行

### `Filter`

### `Listener`
