<%@ taglib prefix="spring" uri="http://www.springframework.org/tags" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<c:set var="contextPath" value="${pageContext.request.contextPath}"/>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Welcome</title>

    <link href="${contextPath}/resources/css/bootstrap.min.css" rel="stylesheet">
    <link href="${contextPath}/resources/css/common.css" rel="stylesheet">
    
<style>
body {background-color: bisque;}
h3   {font-family: verdana;
    font-size: 100%;
    text-align:center;}
p    {color: red;}
ul {
    list-style-type: none;
    margin: 0;
    padding: 50;
    overflow: hidden;
    background-color: #333333;
}

li {
    float: left;
}

li a {
    display: block;
    color: white;
    text-align: center;
    padding: 16px;
    text-decoration: none;
}

li a:hover {
    background-color: #111111;
}
</style>


</head>
<body >
<h1 style="color:DodgerBlue;text-align: center;" >Welcome to Finsoft ${currentuser.name}  </h1>
            <h3>Please choose from Menu, your action</h3>
            <hr>
            <ul>
			  <li><a href="reservation">Reserve Room</a></li>
			  <li><a href="#news">Order food</a></li>
			  <li><a href="#contact">Send Request</a></li>
			  <li><a href="#about">Mi Suggeriscono</a></li>
           </ul>
<div style="text-align:center;" class="container">

<!-- 		<h2 ><a href="reservation"> Reserve Room </a></h2> -->
    
    <c:if test="${pageContext.request.userPrincipal.name != null}"> 
        <form style="height: 100px" id="logoutForm" method="POST" action="${contextPath}/logout"> 
             <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/> 
       </form> 
		<a onclick="document.forms['logoutForm'].submit()">
		<button  style="background-color:powderblue;width: 10%;height: 40px" >Logout</button></a>
		 
     </c:if> 

</div>
<!-- /container -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
<script src="${contextPath}/resources/js/bootstrap.min.js"></script>
</body>
</html>