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
	
	
	if(isset($_POST['start_script'])){
		$scriptid = $_POST['start_script'];
		$stmt = $conn->prepare('UPDATE users_scripts SET status = ? WHERE id = ? AND status = ?');
		if($stmt->execute(array('start', $scriptid, 'wait'))){
			http_response_code(200);
		}else{
			echo $stmt->errorInfo();
			http_response_code(400);
		}
		exit;
	}
	
	if(isset($_POST['stop_script'])){
		$scriptid = $_POST['stop_script'];
		$ti = $_POST['time'];
		$res = $_POST['result'];
		$stmt = $conn->prepare('UPDATE users_scripts SET status = ?, time_exec = ?, result = ?  WHERE id = ? AND status = ?');
		if($stmt->execute(array('finish', $ti, $res, $scriptid, 'start'))){
			http_response_code(200);
		}else{
			echo print_r($stmt->errorInfo());
			http_response_code(400);
		}
		exit;
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
		<script type="text/javascript" src="js/sopovrobotics.js"></script>

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
				<li class="active"><a href="./">User Scripts</a></li>
				<li><a href="admin_settings.php">Settings</a></li>
				<li><a href="admin_users.php">Users</a></li>
			  </ul>
			  <ul class="nav navbar-nav navbar-right">
				<li><a href="logout.php">Logout (<?php echo $username; ?>)</a></li>
			  </ul>
			</div><!--/.nav-collapse -->
		  </div>
		</nav>
			
	<div class="container">
		
		<?php
			$stmt = $conn->prepare('SELECT * FROM settings WHERE name = ?');
			if($stmt->execute(array('secret_robot'))){
				if($row = $stmt->fetch()){
					$secret_robot = htmlspecialchars($row['value']);
				}
			}
			
			if($stmt->execute(array('ipaddress_robot'))){
				if($row = $stmt->fetch()){
					$ipaddress_robot = htmlspecialchars($row['value']);
				}
			}
			
		?>
		<div class="form-group row">
			<div class="col-xs-6">
				<label for="ipaddress_robot">IP Address (robot)</label>
				<input name="ipaddress_robot" id="ipaddress_robot" readonly value="<?php echo $ipaddress_robot; ?>" class="form-control">
			</div>
			<div class="col-xs-6">
				<label for="secret_robot">Secret (robot)</label>
				<input name="secret_robot" id="secret_robot" readonly value="<?php echo $secret_robot; ?>" class="form-control">
			</div>
		</div>
		Status connection: {<div style="display: inline-block" id="status_connection"></div>}
		<div class="table-responsive">
		  <table class="table">
			 <thead>
			  <tr>
				<th>Script ID</th>
				<th>Code</th>
				<th>Status</th>
				<th>Time</th>
				<th>Result</th>
			  </tr>
			</thead>
			<tbody>
		
		<?php

			$stmt = $conn->prepare('SELECT users_scripts.* FROM users_scripts INNER JOIN users ON users.id = users_scripts.userid WHERE users_scripts.status = ? ORDER BY users_scripts.id ASC LIMIT 0,20');
			if($stmt->execute(array('wait'))){
				while($row = $stmt->fetch()){
					$scriptid = $row['id'];
					$code = htmlspecialchars($row['script']);
					echo '
						<tr>
							<td>'.$scriptid.'</td>
							<td>'.htmlspecialchars($row['status']).'</td>
							<td>'.htmlspecialchars($row['time_exec']).'</td>
							<td>'.htmlspecialchars($row['result']).'</td>
							<td>
								<textarea id="scriptcode_'.$scriptid.'" style="display: none">'.$code.'</textarea>';
							echo '<button scriptid="'.$scriptid.'" class="btn btn-danger start-script">Start</button>' ;
						echo '</td>
						</tr>
					';
				}
			}
		?>
		
			</tbody>
		  </table>
		</div>
    </div>
    
    <div id="modalDialog" class="modal fade in" role="dialog" tabindex="-1" style="padding-right: 15px;">
		<div class="modal-dialog" style="width: 80%;">
			<div class="modal-content">
				<div class="modal-header">
					<h4 class="modal-title">Run script</h4>
				</div>
				<div class="modal-body">
					<div class="form-group row">
						<div class="col-xs-12">
							<label for="script_id_for_save">ScriptID</label>
							<input id="script_id_for_save" type="number" readonly style="font-size: medium;" class="form-control"></input>
						</div>
					</div>
					<div class="form-group row">
						<div class="col-xs-12">
							<label for="script_time">Time (<font id="count_down_time">00:00</font>)</label>
							<input id="script_time" type="number" readonly style="font-size: medium;" class="form-control"></input>
						</div>
					</div>
					<div class="form-group row" id="script_result_input" style="display: none">
						<div class="col-xs-12">
							<label for="script_result">Result</label>
							<input id="script_result" type="number" style="font-size: medium;" value="0" class="form-control"></input>
						</div>
					</div>
				</div>
				
				<div class="modal-footer">
					<button type="button" id="stop_script" class="btn btn-danger">STOP</button>
					<button type="button" id="save_script_result" style="display: none" class="btn btn-danger">Save</button>
				</div>
			</div>
		</div>
	</div>
    
    <script>
		
			var ipaddress = $('#ipaddress_robot').val();
			sopovrobotics.secret = $('#secret_robot').val();
			var settings_cache = {};
			function try_connect(){
				$('#status_connection').html('Connecting...');
				
				sopovrobotics.ws_opened = function() {
					$('#status_connection').html('ws connected');
				}
				sopovrobotics.receive_info = function(data){
					if(data.name == "ForKeva"){
						$('#status_connection').html('OK');
						// sopovrobotics.cmd_settings();
					}else{
						$('#status_connection').html('Wrong device, expected model ForKeva');
						window.socket.close();
					}
				}
				
				sopovrobotics.connect(ipaddress);

				sopovrobotics.ws_error = function(error) {
					console.error("Error " + error.message);
					$('#status_connection').html('WS failed connect');
				};
			}
			sopovrobotics.receive_error = function(error){
				console.log(error);
				$('#status_connection').html(error);
				
			}
			var time_start = new Date().getTime();
			
			function call_stop(){
				clearInterval(window.count_down);
				var time_end = new Date().getTime();
				var t = time_end - time_start;
				$('#script_time').val(t);
				$('#stop_script').hide();
				$('#save_script_result').show();
				$('#script_result_input').show();
			}
			
			sopovrobotics.receive_auto_stopped = function(){
				call_stop();
			}
			
			try_connect();
			
			$('.start-script').unbind().bind('click', function(){
				var scriptid = $(this).attr('scriptid');
				$.ajax({ url: 'admin.php', type: 'POST', data: { 'start_script': scriptid } }).done(function(){
				});
				
				var script = $('#scriptcode_' + scriptid).val();
				$('#script_id_for_save').val(scriptid);
				$('#modalDialog').modal('show');
				$('.start-script').hide();
				time_start = new Date().getTime();
				sopovrobotics.cmd_start_auto(script);
				var count_down_t = 0; 
				window.count_down = setInterval(function(){
					count_down_t++;
					var sec = count_down_t % 60;
					var m = Math.floor((count_down_t - sec) / 60);
					$('#count_down_time').html(("00" + m).slice(-2) + ":" + ("00" + sec).slice(-2));
					if(count_down_t > 90){
						sopovrobotics.cmd_stop_auto();
						call_stop();
					}
				},1000);
			});
			
			$('#stop_script').unbind().bind('click', function(){
				sopovrobotics.cmd_stop_auto();
				call_stop();
			});
			
			$('#save_script_result').unbind().bind('click', function(){
				var scriptid = $('#script_id_for_save').val();
				var script_t = $('#script_time').val();
				var script_r = $('#script_result').val();
				
				$.ajax({ url: 'admin.php', type: 'POST', data: { 'stop_script': scriptid, 'time': script_t, 'result': script_r } }).done(function(){
					window.location.reload();
				});
			});
			
		</script>
		<br> <br>
	</body>
</html>


