---
related:
  - "[[./4_Spring Validation.md|Spring Validation Note]]"
---

# `Spring Security`

## 介绍

- `Spring Security`是一套很老也很复杂的安全框架，它的大多数功能可能并不适合每一个项目，但适当了解有好处
- 其保证安全的本质是设置一大串过滤器链，涵盖各种方面，并隐藏其细节

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

## 用户管理

### `UserDetailsService`与`UserDetailsManager`

- `UserDetailsService`接口仅有一个方法：`UserDetails loadUserByUsername(String name)`，它提供该方法供`AuthenticationManager`调用，由该类委托其它类自动验证密码字段
- `UserDetailsManager`继承了`UserDetailsService`，包含一些创建、更新、销毁用户等方法，但并不常用
- 实践中一般实现`UserDetailsService`，来使用`AuthenticationManager`提供的功能

### `UserDetails`接口

- `UserDetails`包含七个方法，是`Spring Security`暴露出的关于用户信息的核心接口
  - `Collection<? extends GrantedAuthority> getAuthorities()`：获取用户的权限
  - `String getPassword()`和`String getUsername()`：获取用户的密码和用户名
  - `isAccountNonExpired()`：判断用户账号是否过期，可用于临时账户分发，有默认实现
  - `isAccountNonLocked()`：判断用户账号是否被封禁，有默认实现
  - `isCredentialsNonExpired()`：判断用户凭证(例如密码)是否过期，可用于指定一段时间后必须修改密码，有默认实现
  - `isEnabled()`：判断用户是否登录，有默认实现
- `Spring Security`提供了默认实现类`User`，但这扩展性差，一般不常用，而是自己实现
  - 可以直接实现`UserDetails`
  - 可以使用适配器模式，实现`UserDetails`，内部使用项目之前设计的`User`类

### `GrantedAuthority`接口

- `GrantedAuthority`包含一个方法，`String getAuthority()`，以`String`形式表示一个权限/角色，一般来说权限可自定义，角色以`ROLE_`开头
- `SimpleGrantedAuthority`是其提供的实现类，构造方法包含一个`String`表示权限/角色
- 一般来说，使用自定义的权限类和角色类就够用了，在自定义过滤器或拦截器中检查它们即可，一定要使用`Spring Security`框架时实现`getAuthorities()`即可

## 在`Servlet`应用中使用`Spring Security`

- `Spring Security`依靠代理模式和委托模式，有一个`DelegatingFilterProxy`，它缝合了`Servlet`应用和`Spring`的`IoC`容器之间的鸿沟，使得我们编写的标准`Filter`能作为`Bean`而存在(并在其中注入其它`Bean`)

  `Servlet`容器会先找到`DelegatingFilterProxy`，由它找到`IoC`容器上下文中的`Filter Bean`，并调用它的`doFilter()`

  这种`Filter`的配置不是传统的`Servlet`容器那样的配置，而是需要在`Spring`配置类中注册`SecurityFilterChain`这个`Bean`，其方法应该接受一个`HttpSecurity`建造者，使用`HttpSecurity`往里加自定义`Filter Bean`然后构建成`SecurityFilterChain`对象
