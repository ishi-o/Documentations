package demo.functionalprog;

import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

/**
 */
public class Orders {

    public static List<Order> filterState(List<Order> os, Order.State stat) {
        return os.stream()
                .parallel()
                .filter(x -> x.getState().equals(stat))
                .toList();
    }

    public static Map<String, Double> getCustomerFee(List<Order> os) {
        return os.stream()
                .parallel()
                .collect(Collectors.groupingBy(x -> x.getCname()))
                .entrySet()
                .stream()
                .parallel()
                .collect(Collectors.toMap(
                        x -> x.getKey(),
                        x -> x.getValue()
                                .stream()
                                .parallel()
                                .collect(Collectors.summingDouble(
                                        d -> d.getAmount()
                                ))));
    }

    public static List<String> maxLimit(List<Order> os, int lim) {
        return getCustomerFee(os)
                .entrySet()
                .stream()
                .parallel()
                .sorted((lhs, rhs) -> {
                    return -lhs.getValue().compareTo(rhs.getValue());
                })
                .limit(lim)
                .map(x -> x.getKey())
                .toList();
    }
}
