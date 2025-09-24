package demo.beans;

/**
 * A POJO
 */
public class User {
	private Integer uid;
	private String username;

	public User() {
	}

	public User(Integer uid, String username) {
		this.uid = uid;
		this.username = username;
	}

	public Integer getUid() {
		return uid;
	}

	public String getUsername() {
		return username;
	}

	public void setUid(Integer uid) {
		this.uid = uid;
	}

	public void setUsername(String username) {
		this.username = username;
	}
}
