package demo.entity;

import java.util.List;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.ForeignKey;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.OneToMany;

/**
 */
@Entity
public class Employee {
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	@Column(name = "eid")
	private Integer eid;

	@JoinColumn(name = "manager", referencedColumnName = "eid", foreignKey = @ForeignKey(name = "fk_EmpManager_EmpEid"))
	@ManyToOne(optional = true)
	private Employee manager;

	@OneToMany(mappedBy = "manager")
	private List<Employee> emps;
}
