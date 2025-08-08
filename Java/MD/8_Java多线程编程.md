# `Java`多线程编程

## 传统多线程编程

### `Runnable`接口

- 所有类，如果希望让它单独作为一个线程运行，可以**继承**`Thread`类并重写`void run()`方法
- 所有类，如果希望让它单独作为一个线程运行，更常用的方法是**实现**`Runnable`**接口**以便用多态特性被调用
- `Runnable`接口要求实现`void run()`方法，当这个类作为线程运行时，运行的就是这个`run()`方法

  使用这种方法，实现了`Runnable`接口的类称为线程任务对象，传递给`Thread`运行，创建的`Thread`对象称为线程对象

### `Thread`类

- `Thread`的常用构造器：
  - `Thread()`

  - `Thread(Runnable task, String name)`：将实现了`Runnable`接口的对象引用传递给它，并命名为`name`
- `start()`
- 

### 线程同步

