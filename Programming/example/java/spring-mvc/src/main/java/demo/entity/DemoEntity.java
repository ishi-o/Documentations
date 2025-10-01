package demo.entity;

import jakarta.persistence.CheckConstraint;
import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.Index;
import jakarta.persistence.Table;
import jakarta.persistence.UniqueConstraint;

/**
 */
@Entity
@Table(name = "demoTable", schema = "demo", uniqueConstraints = {
		@UniqueConstraint(name = "uniq_username", columnNames = { "username" })
}, indexes = {
		@Index(name = "idx_user_cnt", columnList = "count")
}, check = {
		@CheckConstraint(name = "chk_username", constraint = "username ~ ^[0-9a-zA-Z]{8, 20}$")
})
public class DemoEntity {
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	@Column(name = "id")
	private Long id;

	@Column(name = "user_name", nullable = false)
	private String userName;

	@Column(name = "count")
	private Integer count;
}
