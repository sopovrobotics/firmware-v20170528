<?php
	session_start();
	$curdir = dirname(__FILE__);
	include_once ($curdir."/slib.php");
	
	if(isset($_POST['login']) && isset($_POST['password']) && isset($_POST['password2'])){

		$login = $_POST['login'];
		$password = $_POST['password'];
		$password2 = $_POST['password2'];
		
		if($password != $password2){
			$error_msg = "Passwords do not match";
		}else{
			$conn = SLib::db_connection();
			$stmt = $conn->prepare('SELECT * FROM users WHERE login = ?');
			
			if($stmt->execute(array(strtolower($login)))){
				if($row = $stmt->fetch()){
					$error_msg = "User with this login already registered";
				}else{
					$stmt = $conn->prepare('INSERT INTO users(login,password,role,dt) VALUES(?,?,?,NOW())');
					$stmt->execute(array(strtolower($login), sha1($password), 'user'));
					header("Location: index.php");
					exit;
				}
			}else{
				$error_msg = "error 500";
			}
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
							<label for="inputLogin">Login:</label>
							<input type="text" id="inputLogin" name="login" value="<?php echo isset($login) ? htmlspecialchars($login) : ''; ?>" class="form-control" placeholder="Login" required autofocus>
						</div>
					</div>

					<div class="form-group">
						<div class="col-xs-12">
							<label for="inputPassword">Password:</label>
							<input type="password" id="inputPassword" name="password" class="form-control" placeholder="Password" required>
						</div>
					</div>
					
					<div class="form-group">
						<div class="col-xs-12">
							<label for="inputPassword2">Password (reply):</label>
							<input type="password" id="inputPassword2" name="password2" class="form-control" placeholder="Password (reply)" required>
						</div>
					</div>
					
					<button class="btn btn-primary" type="submit">Sign up</button><br><br>
					<?php 
						if(isset($error_msg)){
							echo '<div class="alert alert-danger" role="alert">
								<strong>Fail!</strong> '.$error_msg.'
							</div>';
						}
					?>
					
					</form>
					<a href="index.php">Login page</a>
				</td>
			</tr>
        </table>
    </div>
	</body>
</html>


