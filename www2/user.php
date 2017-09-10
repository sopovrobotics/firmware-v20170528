<?php
	session_start();
	$curdir = dirname(__FILE__);
	include_once ($curdir."/slib.php");
	
	if(!isset($_SESSION['userid']) && !isset($_SESSION['role'])){
		header("Location: index.php");
		exit;
	}
	
	if(isset($_SESSION['userid']) && isset($_SESSION['role'])){
		$role = $_SESSION['role'];
		if($role != 'user' && $role == 'admin'){
			header("Location: admin.php");
			exit;
		}
	}
?>
<html>
	<head>
		<link href="css/bootstrap.min.css" rel="stylesheet" />
	</head>
	<body>
	<div class="container">
		<h1>User page</h1>
		<form method="GET" action="logout.php"><input type="hidden" name="logout"/><button class="btn btn-success">Logout</button></form>
		
		
		
    </div>
	</body>
</html>


