# `IoC`容器

## 简介

- `IoC`(`Inversion of Control`，控制反转)容器的原则是使原本有相互依赖的各个部分解耦，实现松耦合地运作

  在传统的组合中，上层的模块在内部定义某些对象的类型，控制权在上层的模块中，如果需要修改内部的业务逻辑则会违反开闭原则

  而`IoC`的思想则是使上层的模块将控制权“反转”给一个第三方，例如开发者自己或者一个`IoC`容器，由外部来控制并决定向上层模块提供什么样的实现类

- `IoC`容器的常见的实现方法是`DI`(`Dependency Injection`，依赖注入)，即上层模块所依赖的其它对象仅通过**构造方法**或**工厂方法**或**`setter`**方法暴露注入入口，容器在创建对象时控制注入对象的实现类

- 例子：

  ```java
  class Person {
      private Eye e = new BlackEye(); // 在后续改动时违反开闭原则
  }
  
  class Person {
      private Eye e;
      
      public Person(Eye e) {
          this.e = e;
      }
  }
  Person = new Person(new BlackEye()); // 在外部注入
  ```

- 而在`Spring`框架中，这个“外部注入”不需要由开发者手动地注入，而是通过声明式注解由`Spring`内置的`IoC`容器**自动注入**
- `org.springframework.beans`与`org.springframework.context`是`IoC`容器的核心

## 元数据配置

### 上下文

- `Spring`的`IoC`容器通过解析元数据来管理`Bean`

  元数据通常包括以下内容：
  - `Bean`的类型
  - `Bean`的`id`
  - `Bean`的依赖注入
  - `Bean`的作用域
  - `Bean`的生命周期行为(以回调形式存在)
  - `Bean`的懒加载、协作者等其它元数据
- `ApplicationContext`：应用上下文接口的实例表示一个`IoC`容器，它会自动创建、配置、组装所有的`Bean`
  - 继承`BeanFactory`接口：该接口提供一系列和`Bean`有关的方法

  `T getBean(String name, Class<T> clazz)`：获取它管理的类型为`T`、名字为`name`的`Bean`
  - 继承`MessageSource`接口：该接口提供国际化处理信息的能力

  `String getMessage(String msg, Object[] args, Locale locale)`：根据`locale`以及可选的选项`args`解析`msg`
- 创建一个`ApplicationContext`实例：

  创建`ApplicationContext`实例同时意味着许多配置，在**不依靠外部框架**(如`Spring Boot`和`Tomcat`)的情况下，`ApplicationContext`只能通过`new`创建
  
  `Spring`提供了三种初始化配置的方式，分别为基于`XML`的配置、基于注解的配置、基于`Java`的配置
  - 基于`XML`的配置：实现类为`ClassPathXmlApplicationContext`，构造方法需要的参数是`String...`，即一系列`xml`配置文件的路径
  - 基于`Java`的配置：实现类为`AnnotationConfigApplicationContext`，构造方法需要的参数是`Class<?>...`，即一系列由`@Configuration`注解的配置类
- 基于`XML`、基于注解、基于`Java`的区别
