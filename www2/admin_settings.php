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

	$settings = array();
	$settings['ipaddress_robot'] = '';
	$settings['secret_robot'] = '';
	$settings['default_script_robot'] = '';

	if(isset($_POST['update_settings'])){
		$stmt = $conn->prepare('SELECT * FROM settings');
		$settings_current = array();
		
		if($stmt->execute()){
			while($row = $stmt->fetch()){
				$name = htmlspecialchars($row['name']);
				$value = htmlspecialchars($row['value']);
				$settings_current[$name] = $value;
			}
		}	
		
		foreach($settings as $k => $v){
			if(isset($_POST[$k])){
				if(isset($settings_current[$k])){
					$conn->prepare('UPDATE settings SET value = ? WHERE name = ?')->execute(array($_POST[$k],$k));
				}else{
					$conn->prepare('INSERT INTO settings(name,value) VALUES(?,?)')->execute(array($k,$_POST[$k]));
				}
			}
		}
		header("Location: admin_settings.php");
		exit;
	}
	
	
?>
<html>
	<link href="css/bootstrap.min.css" rel="stylesheet" />
		<link href="css/bootstrap-grid.min.css" rel="stylesheet" />
		<script type="text/javascript" src="js/jquery-3.1.0.min.js"></script>
		<script type="text/javascript" src="js/bootstrap.min.js"></script>
		<script type="text/javascript" src="js/sopovrobotics.js"></script>
		
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
				<li class="active"><a href="admin_settings.php">Settings</a></li>
				<li><a href="admin_users.php">Users</a></li>
			  </ul>
			  <ul class="nav navbar-nav navbar-right">
				<li><a href="logout.php">Logout (<?php echo $username; ?>)</a></li>
			  </ul>
			</div><!--/.nav-collapse -->
		  </div>
		</nav>
			
	<div class="container">
		
		<!-- server settings -->
		<?php

			$stmt = $conn->prepare('SELECT * FROM settings');
			if($stmt->execute()){
				while($row = $stmt->fetch()){
					$name = htmlspecialchars($row['name']);
					$value = htmlspecialchars($row['value']);
					if(!isset($settings[$name])){
						echo "Warn: not found: ".$name."<br>";
						continue;
					}
					$settings[$name] = $value;
				}
			}
		?>

		<div class="form-group row">
			<div class="col-xs-6">
				<label for="ipaddress_robot">IP Address (robot)</label>
				<input name="ipaddress_robot" id="ipaddress_robot"  value="<?php echo $settings['ipaddress_robot']; ?>" class="form-control">
			</div>
			<div class="col-xs-6">
				<label for="secret_robot">Secret (robot)</label>
				<input name="secret_robot" id="secret_robot"  value="<?php echo $settings['secret_robot']; ?>" class="form-control">
			</div>
		</div>
		<div class="form-group row">
			<div class="col-xs-12">
				<label for="default_script_robot">Default Script Robot</label>
				<textarea id="default_script_robot" class="form-control"><?php echo $settings['default_script_robot']; ?></textarea>
			</div>
		</div>
	
		<button id="update_settings" class="btn btn-danger">Update</button>
		
		<script  type="text/javascript">
			// new scriptcode
			var el = $('#default_script_robot')[0];
			window.cm = CodeMirror(function(elt) {
			  el.parentNode.replaceChild(elt, el);
			}, {
				value: el.value,
				readOnly: false,
				theme: 'cobalt',
				viewportMargin: 50,
				mode:  "javascript",
				lineNumbers: true,
				lineWrapping: false
			});
			
			height = cm.defaultTextHeight() * (20);
			cm.setSize("", height);
			
			$('#update_settings').click(function(){
				var post_data = {};
				post_data.update_settings = '';
				post_data.ipaddress_robot = $('#ipaddress_robot').val();
				post_data.secret_robot = $('#secret_robot').val();
				post_data.default_script_robot = cm.getValue();
				
				$.ajax({
					url: './admin_settings.php',
					type: 'POST',
					data: post_data
				}).done(function(){
					window.location.reload();
				})
			})
			
		</script>
		
		<!-- robot settings -->
		
		<button id="check_connection" class="btn btn-success">Check Conenction To Robot (<?php echo $settings['ipaddress_robot']; ?>)</button> 
		Status connection: {<div style="display: inline-block" id="status_connection"></div>}
		
		<h1>Robot Settings</h1>
		<h3>Drivers</h3>
		<div class="form-group row">
			<div class="col-xs-2">
				<label class="control-label col-sm-2" for="pwd">Drivers:</label>
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_pin_A1">Pin A1</label>
				<input id="robot_drivers_pin_A1" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_pin_A2">Pin A2</label>
				<input id="robot_drivers_pin_A2" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_pin_B1">Pin B1</label>
				<input id="robot_drivers_pin_B1" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_pin_B2">Pin B2</label>
				<input id="robot_drivers_pin_B2" value="" class="form-control">
			</div>
		</div>
		<hr>
		<div class="form-group row">
			<div class="col-xs-2">
				<label class="control-label col-sm-2">Forward:</label>
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_forward_A1">Value A1</label>
				<input id="robot_drivers_forward_A1" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_forward_A2">Value A2</label>
				<input id="robot_drivers_forward_A2" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_forward_B1">Value B1</label>
				<input id="robot_drivers_forward_B1" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_forward_B2">Value B2</label>
				<input id="robot_drivers_forward_B2" value="" class="form-control">
			</div>
		</div>
		<hr>
		<div class="form-group row">
			<div class="col-xs-2">
				<label class="control-label col-sm-2">Backward:</label>
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_backward_A1">Value A1</label>
				<input id="robot_drivers_backward_A1" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_backward_A2">Value A2</label>
				<input id="robot_drivers_backward_A2" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_backward_B1">Value B1</label>
				<input id="robot_drivers_backward_B1" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_backward_B2">Value B2</label>
				<input id="robot_drivers_backward_B2" value="" class="form-control">
			</div>
		</div>
		<hr>
		<div class="form-group row">
			<div class="col-xs-2">
				<label class="control-label col-sm-2">Turnleft:</label>
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_turnleft_A1">Value A1</label>
				<input id="robot_drivers_turnleft_A1" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_turnleft_A2">Value A2</label>
				<input id="robot_drivers_turnleft_A2" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_turnleft_B1">Value B1</label>
				<input id="robot_drivers_turnleft_B1" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_turnleft_B2">Value B2</label>
				<input id="robot_drivers_turnleft_B2" value="" class="form-control">
			</div>
		</div>
		<hr>
		<div class="form-group row">
			<div class="col-xs-2">
				<label class="control-label col-sm-2">Turnright:</label>
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_turnright_A1">Value A1</label>
				<input id="robot_drivers_turnright_A1" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_turnright_A2">Value A2</label>
				<input id="robot_drivers_turnright_A2" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_turnright_B1">Value B1</label>
				<input id="robot_drivers_turnright_B1" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_drivers_turnright_B2">Value B2</label>
				<input id="robot_drivers_turnright_B2" value="" class="form-control">
			</div>
		</div>
		<hr>
		<div class="form-group row">
			<div class="col-xs-2">
				<label class="control-label col-sm-2">Servo Comb:</label>
			</div>
			<div class="col-xs-2">
				<label for="robot_servo_pin_comb">Pin</label>
				<input id="robot_servo_pin_comb" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_servo_pin_comb_value_up">Value Up</label>
				<input id="robot_servo_pin_comb_value_up" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_servo_pin_comb_value_down">Value Down</label>
				<input id="robot_servo_pin_comb_value_down" value="" class="form-control">
			</div>
		</div>
		<hr>
		<div class="form-group row">
			<div class="col-xs-2">
				<label class="control-label col-sm-2">Main:</label>
			</div>
			<div class="col-xs-4">
				<label for="robot_secret">Secret</label>
				<input id="robot_secret" value="" class="form-control">
			</div>
			<div class="col-xs-2">
				<label for="robot_port">Port</label>
				<input id="robot_port" value="" class="form-control">
			</div>
		</div>
		<hr>
		<button id="update_robot_settings" class="btn btn-danger">Update settings on robot</button> <br><br>
		
		<h1>Robot commands</h1>
		<button id="cmd_comb_up" class="btn btn-success">Comb up</button>
		<button id="cmd_comb_down" class="btn btn-success">Comb down</button>
		<button id="cmd_forward" class="btn btn-success">Forward</button>
		<button id="cmd_backward" class="btn btn-success">Backward</button>
		<button id="cmd_turnleft" class="btn btn-success">Turnleft</button>
		<button id="cmd_turnright" class="btn btn-success">Turnright</button>
		<button id="cmd_stop" class="btn btn-success">Stop</button>
		<button id="cmd_start_auto" class="btn btn-success">Start auto</button>
		<button id="cmd_stop_auto" class="btn btn-success">Stop auto</button>

		<script>
			var ipaddress = "<?php echo $settings['ipaddress_robot']; ?>";
			sopovrobotics.secret = "<?php echo $settings['secret_robot']; ?>";
			var settings_cache = {};
			function try_connect(){
				$('#status_connection').html('Connecting...');
				
				sopovrobotics.ws_opened = function() {
					$('#status_connection').html('ws connected');
				}
				sopovrobotics.receive_info = function(data){
					if(data.name == "ForKeva"){
						$('#status_connection').html('OK');
						sopovrobotics.cmd_settings();
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
			
			sopovrobotics.receive_settings = function(settings){
				settings_cache = settings;
				for(var i in settings){
					$('#robot_' + i).val(settings[i]);
				}
			}
			
			sopovrobotics.receive_updated_settings = function(new_settings){
				// console.warn(new_settings);
				window.location.reload();
			}
			
			$('#check_connection').click(try_connect);
			
			try_connect();
			
			$('#update_robot_settings').click(function(){
				var data = {};
				var count = 0;
				for(var i in settings_cache){
					var v = $('#robot_' + i).val();
					if(v != settings_cache[i]){
						data[i] = v;
						count++;
					}
				}
				if(count > 0){
					sopovrobotics.cmd_update_settings(data);
				}
			});

			$('#cmd_comb_up').click(sopovrobotics.cmd_comb_up);
			$('#cmd_comb_down').click(sopovrobotics.cmd_comb_down);
			$('#cmd_forward').click(sopovrobotics.cmd_forward);
			$('#cmd_backward').click(sopovrobotics.cmd_backward);
			$('#cmd_turnleft').click(sopovrobotics.cmd_turnleft);
			$('#cmd_turnright').click(sopovrobotics.cmd_turnright);
			$('#cmd_stop').click(sopovrobotics.cmd_stop);
			$('#cmd_stop_auto').click(sopovrobotics.cmd_stop_auto);
			$('#cmd_start_auto').click(function(){
				sopovrobotics.cmd_start_auto(window.cm.getValue());
			});
			
		</script>
		<br> <br>
    </div>
	</body>
</html>


