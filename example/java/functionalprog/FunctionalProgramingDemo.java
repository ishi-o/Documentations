package example.java.functionalprog;

import java.util.Comparator;
import java.util.function.BiConsumer;
import java.util.function.Consumer;
import java.util.function.IntSupplier;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 */
public class FunctionalProgramingDemo {

    // 自定义需要添加FunctionalInterface注解
    @FunctionalInterface
    public static interface UserDefinedFunctionalInterface {

        void func(Integer a);

        static void func2(Integer a) {
        }
    }

    public static void methodRefDemo(BiConsumer<UserDefinedFunctionalInterface, Integer> c) {
    }

    public static void methodRefDemo2(Consumer<Integer> c) {
    }

    public static void lambdaDemo() {
        // no lambda
        Comparator<Integer> comp = new Comparator<>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o1.compareTo(o2);
            }
        };
        // using lambda
        Comparator<Integer> compWithLambda = (o1, o2) -> {
            return o1.compareTo(o2);
        };
        methodRefDemo(UserDefinedFunctionalInterface::func);
        methodRefDemo2(UserDefinedFunctionalInterface::func2);
    }

    public static void streamDemo() {
        // 相比Stream<Integer>不用装箱, 但不能使用收集器
        IntStream evenPositiveIntStream = IntStream.generate(new IntSupplier() {
            int n = 0;

            @Override
            public int getAsInt() {
                return n += 2;
            }

        }).parallel().skip(50).limit(50);   // 第50~100项
        evenPositiveIntStream.allMatch(x -> (x % 4) == 0);
        // 等价于 !evenPositiveIntStream.anyMatch(x -> !((x % 4) == 0));
        evenPositiveIntStream.filter(x -> (x % 4) == 0);
        evenPositiveIntStream.distinct();
        evenPositiveIntStream.count();
        evenPositiveIntStream = evenPositiveIntStream.map(x -> x * x);
        // 等价于 evenPositiveIntStream.forEach(x -> x *= x);
        // 来自Files.lines()等IO的Stream对象必须close()
        evenPositiveIntStream.boxed().toList();
        evenPositiveIntStream.boxed().collect(Collectors.toList());
        evenPositiveIntStream.boxed().collect(Collectors.toMap(e -> e, e -> e * e));
        var s = evenPositiveIntStream.boxed().collect(Collectors.groupingBy(e -> e % 4));   // 通过K将e分类, 得到Map<K, List<T>>
    }
}
