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
		if($role != 'admin' && $role == 'user'){
			header("Location: user.php");
			exit;
		}
	}
	
	$userid = $_SESSION['userid'];
	$conn = SLib::db_connection();
	
	$stmt = $conn->prepare('SELECT * FROM users WHERE id = ?');
	if($stmt->execute(array($userid))){
		if($row = $stmt->fetch()){
			$username = htmlspecialchars($row['login']);
		}
	}
?>
<html>
	<link href="css/bootstrap.min.css" rel="stylesheet" />
		<link href="css/bootstrap-grid.min.css" rel="stylesheet" />
		<link href="css/bootstrap-reboot.min.css" rel="stylesheet" />
		<script type="text/javascript" src="js/jquery-3.1.0.min.js"></script>
		<script type="text/javascript" src="js/bootstrap.min.js"></script>
		
		<script type="text/javascript" src="CodeMirror/codemirror.js"></script>
		<link href="CodeMirror/codemirror.css" rel="stylesheet" />
		<link href="CodeMirror/theme/cobalt.css" rel="stylesheet" />
		<script type="text/javascript" src="CodeMirror/mode/javascript/javascript.js"></script>

		<style>
			.CodeMirror{
				font-size: large;
			}
		</style>

	<body>
	<div class="container">
	
		<h1>Welcome admin, <?php echo $username; ?> ! 
			<form style="display: inline-block;" method="GET" action="logout.php"><input type="hidden" name="logout"/><button class="btn btn-success">Logout</button></form>
		</h1>
		
    </div>
	</body>
</html>


