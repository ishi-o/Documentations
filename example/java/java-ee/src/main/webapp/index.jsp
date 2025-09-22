<html>

<head>
	<%@ page import="java.util.*, java.net.*" %>
</head>

<body>
	<h1>
		$ { title }
	</h1>
	<% if (request.getParameter("name")==null) { %>
		<div>Error</div>
		<% } else { %>
			<div>request.getParameter("name")</div>
			<% } %>
</body>

</html>