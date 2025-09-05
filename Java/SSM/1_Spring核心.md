## `Spring`容器核心

### `IoC`容器与依赖注入

- `IoC`(`Inversion of Control`，控制反转)容器的原则是使原本有相互依赖的各个部分解耦，实现松耦合地运作

  在传统的组合中，上层的模块在内部定义某些对象的类型，控制权在上层的模块中，如果需要修改内部的业务逻辑则会违反开闭原则

  而`IoC`的思想则是使上层的模块将控制权“反转”给一个第三方，例如开发者自己或者一个`IoC`容器，由外部来控制并决定向上层模块提供什么样的实现类

- `IoC`容器的常见的实现方法是`DI`(`Dependency Injection`，依赖注入)，即上层模块所依赖的其它对象仅通过**构造方法**或**工厂方法**或**`setter`**方法暴露注入入口，容器在创建对象时控制注入对象的实现类

- 例子：

  ```java
  class Person {
      private Eye e = new BlackEye();	// 在后续改动时违反开闭原则
  }
  
  class Person {
      private Eye e;
      
      public Person(Eye e) {
          this.e = e;
      }
  }
  Person = new Person(new BlackEye());	// 在外部注入
  ```

- 而在`Spring`框架中，这个“外部注入”不需要由开发者手动地注入，而是通过声明式注解由`Spring`内置的`IoC`容器**自动注入**