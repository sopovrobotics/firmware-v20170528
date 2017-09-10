<?php
	session_start();
	$curdir = dirname(__FILE__);
	include_once ($curdir."/slib.php");
	
	if(isset($_SESSION['userid']) && isset($_SESSION['role'])){
		if($_SESSION['role'] == 'admin'){
			header("Location: admin.php");
		}else{
			header("Location: user.php");
		}
		exit;
	}
	
	if(isset($_POST['login']) && isset($_POST['password'])){
		
		$login = $_POST['login'];
		$password = $_POST['password'];
		
		$conn = SLib::db_connection();
		$stmt = $conn->prepare('SELECT * FROM users WHERE login = ? AND password = ?');
		if($stmt->execute(array(strtolower($login), sha1($password)))){
			if($row = $stmt->fetch()){
				$_SESSION['userid'] = $row['id'];
				$_SESSION['role'] = $row['role'];
				header("Location: index.php");
				exit;
			}else{
				$error_msg = "Login or password incorrect";
			}
		}else{
			echo "fail";
		}
	}
?>
<html>
	<head>
		<link href="css/bootstrap.min.css" rel="stylesheet" />
	</head>
	<body>
	<div class="container">
		
		
		<table width=100% height=100%>
			<tr>
				<td align="center">
					
					<h1>Stand up "Control Me"</h1>
					<form method="POST" style="width: 450px">
						
					<div class="form-group">
						<div class="col-xs-12">
							<label for="inputEmail">Login:</label>
							<input type="text" id="inputEmail" name="login" class="form-control" placeholder="Login" required autofocus>
						</div>
					</div>

					<div class="form-group">
						<div class="col-xs-12">
							<label for="inputPassword">Password:</label>
							<input type="password" id="inputPassword" name="password" class="form-control" placeholder="Password" required>
						</div>
					</div>
					
					<button class="btn btn-primary" type="submit">Sign in</button><br><br>
					<?php 
						if(isset($error_msg)){
							echo '<div class="alert alert-danger" role="alert">
								<strong>Fail!</strong> '.$error_msg.'
							</div>';
						}
					?>
					
					</form>
					<a href="registration.php">Registration</a>
				</td>
			</tr>
        </table>
    </div>
	</body>
</html>


