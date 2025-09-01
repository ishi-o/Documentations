package example.java.functionalprog;

import java.time.LocalDate;

/**
 */
public class Order {

    public static enum State {
        CREATED,
        PAID,
        SHIPPED,
        COMPLETED,
        CANCELLED
    }

    private Long oid;
    private State stat;
    private String cname;
    private Double amount;
    private LocalDate date;

    public State getState() {
        return stat;
    }

    public Long getOid() {
        return oid;
    }

    public String getCname() {
        return cname;
    }

    public Double getAmount() {
        return amount;
    }

    public LocalDate getDate() {
        return date;
    }

}
