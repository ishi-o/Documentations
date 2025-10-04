package demo.entity;

import java.io.Serializable;

import jakarta.persistence.AttributeOverride;
import jakarta.persistence.AttributeOverrides;
import jakarta.persistence.Column;
import jakarta.persistence.Embeddable;
import jakarta.persistence.Embedded;
import jakarta.persistence.EmbeddedId;
import jakarta.persistence.Entity;
import jakarta.persistence.Table;

/**
 */
@Entity
@Table(name = "embed_demo", schema = "demo")
public class EmbedEntity {
	@Embeddable
	public static class EmbedId implements Serializable {
		private Long uid;
		private String username;

		@Override
		public boolean equals(Object obj) {
			if (obj.getClass() == EmbedId.class) {
				EmbedId eid = (EmbedId) obj;
				return uid.equals(eid.uid) && username.equals(eid.username);
			} else {
				return false;
			}
		}

		@Override
		public int hashCode() {
			return Integer.hashCode(uid.hashCode() + username.hashCode());
		}
	}

	@EmbeddedId
	@AttributeOverrides({
			@AttributeOverride(name = "uid", column = @Column(name = "uid" /** 其它约束 */
			)),
			@AttributeOverride(name = "username", column = @Column(name = "username"))
	})
	private EmbedId id;

	@Embedded
	@AttributeOverrides({
			@AttributeOverride(name = "uid", column = @Column(name = "parent_uid" /** 其它约束 */
			)),
			@AttributeOverride(name = "username", column = @Column(name = "parent_username"))
	})
	private EmbedId pid;
}
