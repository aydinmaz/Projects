<%@ taglib prefix="spring" uri="http://www.springframework.org/tags" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Resrveation</title>
     <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
      <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
<%--      <script src="${contextPath}/resources/js/utils.js"></script> --%>
    
    <!--    <link href="${contextPath}/resources/css/bootstrap.min.css" rel="stylesheet">   -->
    <!--   <link href="${contextPath}/resources/css/common.css" rel="stylesheet">          -->

    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!--[if lt IE 9]>
    <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
    <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
    
  

    <style type="text/css">
    
    
    td{
      /* width:auto; */
      vertical-align:middle;
      font :bold;
      color: black;
      border: 2px solid black;
      
     /*   #idtr{
    background: red;
    } */
     
     .style1{
    background-color:black;
    color:black;
    font-size:44px;
         }
     
     
     
     
      </style>
      
    
</head>

<body>

<div  class="container" align="center">


			<c:forEach items= "${rooms1}" var="x" step="25"  varStatus="varstat_x">
	        
	         <h1>${x.name} </h1>   
	         <table id="caio1" class="table table-bordered"  >
			 <thead>
			    <tr style="background-color:#b3b3ff; font-weight:bold;font-family: italic" >
				  <td style="background-color: #8080ff  ">\Days \Hours</td>  <td>8 - 10</td>   
				  <td >10 - 12</td> <td >12 - 14</td> 
				  <td >14 - 16</td> <td >16 - 18</td> 
			    </tr>
			 </thead>
			    <tbody>
			<c:forEach items= "${rooms1}" var="i" step="5" begin="${varstat_x.index}" end="${varstat_x.index+24}" varStatus="varSt">
				
				<tr>
				 <td style="background-color:#b3b3ff;font-weight:bold;font-family:inherit; ">${i.day},${varSt.index}</td>
			     <c:forEach items= "${rooms1}" var="m" begin="${varSt.index}" end="${varSt.index+4}" varStatus="mSta">
			     
			     <c:choose>
			     	<c:when test="${m.confirm==false}">
			     	  <td style="background-color:#d8ecf3 " id="${m.id}" onclick="content(id)">free,${mSta.index+1} </td>
			     	</c:when>
			     	<c:when test="${m.user.username==currentuser.username}">
			     	  <td style="background-color: LimeGreen " id="${m.id}" onclick="content(id)">reserved by you ${m.user.name},${mSta.index+1}</td> 
			     	</c:when>
			     <c:otherwise> <td style="background-color:#ff4d4d" id="${m.id}" onclick="content2()">reserved by ${m.user.name},${mSta.index+1}</td> 
			     </c:otherwise>
			     </c:choose>
			    </c:forEach>    
			    </tr>
			</c:forEach>				    
			    </tbody>
		  </table>
		    <br>
		 </c:forEach>
		
			
		  
		  
    
<!-- 			 <button type="button" onclick="sendRoomID()">Invia</button> -->
<%-- 	    </form:form> --%>
		<h2> <a href="welcome">finished</a></h2>
		<button onclick="location.href='welcome'" type="button">Finish</button>
		<a href="welcome"> <button>Click me</button> </a>

       

</div>
<br>
<script >


function content2()
{alert("I am sorry ,this hour is reserved by another person,please choose another hour ")}


function content(id)
 {  
	console.log(id);
	var cosa = '${currentuser.name}';
	var backcolor=document.getElementById(id).style.backgroundColor;
	console.log(backcolor);
// 	var parentId = document.getElementById(id).parentNode.parentNode.parentNode.id;
// 	alert(parentId);

	if (backcolor == 'rgb(216, 236, 243)' )
	{  document.getElementById(id).style = 'background-color: olivedrab ';
	document.getElementById(id).innerHTML =id+'   reserveed by you '+cosa;}
	else {document.getElementById(id).style = 'background-color: #d8ecf3';
	document.getElementById(id).innerHTML =id+'  free'
	}
	
	$.ajax
	({  method : 'GET',
	    url : 'reservationTest?room_id='+id})
	
  }			


</script>
  

</body> 


</html>