<?php
	session_start();
	$curdir = dirname(__FILE__);
	include_once ($curdir."/slib.php");

	$conn = SLib::db_connection();
	
?>
<html>
	<link href="css/bootstrap.min.css" rel="stylesheet" />
		<!-- link href="css/bootstrap-grid.min.css" rel="stylesheet" / -->
	<body>
			
	<div class="container">

		<div class="table-responsive">
		  <table class="table">
			 <thead>
			  <tr>
				<th>User</th>
				<th>ScriptID</th>
				<th>Time</th>
				<th>Result</th>
			  </tr>
			</thead>
			<tbody>
		
		<?php

			$stmt = $conn->prepare('SELECT users_scripts.*, users.login 
				FROM users_scripts 
				INNER JOIN users ON users.id = users_scripts.userid
				WHERE users_scripts.status = ?
				ORDER BY users_scripts.id DESC LIMIT 0,20');
			if($stmt->execute(array('start'))){
				while($row = $stmt->fetch()){
					$scriptid = $row['id'];
					$status = $row['status'];
					echo '
						<tr class="danger">
							<td>'.htmlspecialchars($row['login']).'</td>
							<td>'.$scriptid.'</td>
							<td></td>
							<td></td>
						</tr>
					';
				}
			}
			
			echo '
				<tr>
					<td>--</td>
					<td>--</td>
					<td>--</td>
					<td>--</td>
				</tr>
			';

			$stmt = $conn->prepare('SELECT users_scripts.*, users.login 
				FROM users_scripts 
				INNER JOIN users ON users.id = users_scripts.userid
				WHERE users_scripts.status = ?
				ORDER BY users_scripts.time_exec ASC, users_scripts.result DESC, users_scripts.id ASC LIMIT 0,20');
			if($stmt->execute(array('finish'))){
				while($row = $stmt->fetch()){
					$scriptid = $row['id'];
					$status = $row['status'];
					echo '
						<tr '.($status == 'finish' ? 'class="success"' : 'class="error"').'>
							<td>'.htmlspecialchars($row['login']).'</td>
							<td>'.$scriptid.'</td>
							<td>'.htmlspecialchars($row['time_exec']).'</td>
							<td>'.htmlspecialchars($row['result']).'</td>
						</tr>
					';
				}
			}
		?>
		
			</tbody>
		  </table>
		</div>
    </div>
    <script>
			setTimeout(function(){
				window.location.reload();
			},1000)
			
		</script>
	</body>
</html>


