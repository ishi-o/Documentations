---
related:
  - "[[./4_Spring Validation.md|Spring Validation Note]]"
---

# `Spring Security`

## `PasswordEncoder`接口

- `PasswordEncoder`是一个单向加密的接口，不适用于双向加密，如单向加密的缺点那样，只能用于验证，而不能用于隐私数据存储(未来有需要读取的场景)
- `String encode(CharSequence raw)`：加密方法
- `boolean matches(CharSequence raw, String encoded)`：判断上交的`raw`经过`encode()`加密后是否和`encoded`一致
- `boolean upgradeEncoding(String encoded)`：判断加密后的密码是否需要再次加密，默认实现会返回`false`
- 它的实现有：
  - `NoOpPasswordEncoder`：已弃用
  - `BCryptPasswordEncoder`：使用`BCrypt`强哈希加密，可指定加密强度，越大则复杂度呈指数级增长，默认为`10`
  - `Pbkdf2PasswordEncoder`
  - `SCryptPasswordEncoder`
  - `DelegatingPasswordEncoder`：基于前缀标识符来代表其它`PasswordEncoder`的实现类，默认代表`BCryptPasswordEncoder`

    如其简介所说的那样，可简单理解为内部是一个`Map<String, PasswordEncoder>`，生成的密文将是类似`{bcrypt}encoded`的密文，通过`PasswordEncoderFactories`工厂创建的实例默认使用`BCryptPasswordEncoder`

## 在`Servlet`应用中使用`Spring Security`

- `Spring Security`依靠代理模式和委托模式，有一个`DelegatingFilterProxy`，它缝合了`Servlet`应用和`Spring`的`IoC`容器之间的鸿沟，使得我们编写的标准`Filter`能作为`Bean`而存在(并在其中注入其它`Bean`)

  `Servlet`容器会先找到`DelegatingFilterProxy`，由它找到`IoC`容器上下文中的`Filter Bean`，并调用它的`doFilter()`

  这种`Filter`的配置不是传统的`Servlet`容器那样的配置，而是需要在`Spring`配置类中注册`SecurityFilterChain`这个`Bean`，其方法应该接受一个`HttpSecurity`建造者，使用`HttpSecurity`往里加自定义`Filter Bean`然后构建成`SecurityFilterChain`对象
