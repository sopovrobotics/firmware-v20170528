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
		
		<!-- Static navbar -->
		<nav class="navbar navbar-default navbar-static-top">
		  <div class="container">
			<div class="navbar-header">
			  <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
				<span class="sr-only">Toggle navigation</span>
				<span class="icon-bar"></span>
				<span class="icon-bar"></span>
				<span class="icon-bar"></span>
			  </button>
			  <a class="navbar-brand" href="#">Control Me</a>
			</div>
			<div id="navbar" class="navbar-collapse collapse">
			  <ul class="nav navbar-nav">
				<li><a href="./">User Scripts</a></li>
				<li><a href="admin_settings.php">Settings</a></li>
				<li class="active"><a href="admin_users.php">Users</a></li>
			  </ul>
			  <ul class="nav navbar-nav navbar-right">
				<li><a href="logout.php">Logout (<?php echo $username; ?>)</a></li>
			  </ul>
			</div><!--/.nav-collapse -->
		  </div>
		</nav>
			
	<div class="container">
		
    </div>
	</body>
</html>


