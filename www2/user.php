<?php
	session_start();
	$curdir = dirname(__FILE__);
	include_once ($curdir."/slib.php");
	include_once ($curdir."/JShrink_Minifier.php");
	
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

	$userid = $_SESSION['userid'];
	$conn = SLib::db_connection();
	
	$stmt = $conn->prepare('SELECT * FROM users WHERE id = ?');
	if($stmt->execute(array($userid))){
		if($row = $stmt->fetch()){
			$username = htmlspecialchars($row['login']);
		}
	}

	if(isset($_POST['new_code_script'])){
		$code = $_POST['new_code_script'];
		
		$minifier_code = JShrink_Minifier::minify($code);
		$script_hash = md5($minifier_code);
		
		$stmt = $conn->prepare('INSERT INTO users_scripts(userid,script,minifier_script,md5_script,status,time_exec,result) VALUES(?,?,?,?,?,?,?)');
		if($stmt->execute(array($userid, $code, $minifier_code, $script_hash, 'wait', 0, 0))){
			http_response_code(200);
		}else{
			http_response_code(400);
			print_r($stmt->errorInfo());
		}
		exit;
	}
	
	if(isset($_POST['revoke_script'])){
		$scriptid = $_POST['revoke_script'];
		$stmt = $conn->prepare('UPDATE users_scripts SET status = ? WHERE userid = ? AND id = ?');
		if($stmt->execute(array('revoke', $userid, $scriptid))){
			http_response_code(200);
		}else{
			echo $stmt->errorInfo();
			http_response_code(400);
		}
		exit;
	}

?>
<html>
	<head>
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

	</head>
	<body>
	<div class="container">
		<h1>Welcome user, <?php echo $username; ?> !
			<form style="display: inline-block;" method="GET" action="logout.php"><input type="hidden" name="logout"/><button class="btn btn-success">Logout</button></form>
		</h1>
		
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
				$stmt = $conn->prepare('SELECT * FROM users_scripts WHERE userid = ?');
				if($stmt->execute(array($userid))){
					$i = 0;
					while($row = $stmt->fetch()){
						$scriptid = htmlspecialchars($row['id']);
						$status = $row['status'];
						$code = htmlspecialchars($row['script']);
						echo '
							<tr>
								<td>'.$scriptid.'</td>
								<td>'.htmlspecialchars($row['status']).'</td>
								<td>'.htmlspecialchars($row['time_exec']).'</td>
								<td>'.htmlspecialchars($row['result']).'</td>
								<td>
									<textarea id="scriptcode_'.$scriptid.'" style="display: none">'.$code.'</textarea>
									<button scriptid="'.$scriptid.'" class="btn btn-info show-code">Show</button>
									'.($status == 'wait' ? '<button scriptid='.$scriptid.' class="btn btn-danger revoke">Revoke the script</button>' : '').'
								</td>
							</tr>
						';
						$i++;
					}
					if($i == 0){
						echo '<tr>';
						echo '<td>...</td>';
						echo '<td>...</td>';
						echo '<td>...</td>';
						echo '<td>...</td>';
						echo '<td>...</td>';
						echo '</tr>';
					}
				}
			?>
			</tbody>
		  </table>
		</div>

		<div class="form-group row">
			<div class="col-xs-12">
				<label for="new_script_code">New script</label>
				<textarea id="new_script_code" style="font-size: medium;" class="form-control">
forward(100); // forward 100ms
backward(200); // backward 200ms
turnleft(400); // turn to the left 400ms
turnright(400); // turn to the right 400ms
				</textarea>
			</div>
		</div>
		<button class="btn btn-success" id="send_new_script">Send</button>
		<hr>
		
		
    </div>

<div id="modalDialog" class="modal fade in" role="dialog" style="padding-right: 15px;">
	<div class="modal-dialog" style="width: 80%;">
		<div class="modal-content">
			<div class="modal-header">
				<button type="button" class="close" data-dismiss="modal">×</button>
				<h4 class="modal-title">...</h4>
			</div>
			<div class="modal-body">
				<div class="form-group row">
					<div class="col-xs-12">
						<label for="script_code">Script</label>
						<textarea id="script_code" style="font-size: medium;" class="form-control"></textarea>
					</div>
				</div>
			</div>
			<div class="modal-footer">
				<button type="button" id="modalButton_1" class="btn btn-default" data-dismiss="modal">Close</button>
			</div>
		</div>
	</div>
</div>

<script  type="text/javascript">
	
	
	
	// new scriptcode
	var el = $('#new_script_code')[0];
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
	
	console.log(cm.getValue());
	
	$('#send_new_script').unbind().bind('click', function(){
		$.ajax({
			url: 'user.php',
			type: 'POST',
			data: {
				'new_code_script': cm.getValue()
			}
		}).done(function(){
			window.location.reload();
		}).fail(function(err){
			console.error(err);
			if(err.responseText){
				alert(err.responseText);
			}else{
				alert("Wrong script");
			}
		});
	});
	
	// old scriptcode
	var el2 = $('#script_code')[0];
	window.cm2 = CodeMirror(function(elt) {
	  el2.parentNode.replaceChild(elt, el2);
	}, {
		value: el.value,
		readOnly: true,
		theme: 'cobalt',
		viewportMargin: 50,
		mode:  "javascript",
		lineNumbers: false,
		lineWrapping: false
	});

	cm2.setSize("", height);

	$('.revoke').unbind().bind('click',function(){
		var scriptid = $(this).attr('scriptid');
		$.ajax({
			url: 'user.php',
			type: 'POST',
			data: {
				'revoke_script': scriptid
			}
		}).done(function(){
			window.location.reload();
		}).fail(function(err){
			console.error(err);
		});
	})
	
	$('.show-code').unbind().bind('click', function(){
		var scriptid = $(this).attr('scriptid');
		var sc = $('#scriptcode_' + scriptid).val();
		$('#modalDialog .modal-title').html('Script #' + scriptid);
		
		$('#modalDialog').modal('show');
		setTimeout(function(){
			cm2.setValue(sc);
		},500);
	});
			
</script>
		<!--
		
		by SopovRobotics 20170528
		
		Hardware

Motor-reducer Gekko MR12-100 (2 pieces)
Track Pololu 30T
Pololu 5v Step-Up/Step-Down Voltage Regulator S7V7F5
DRV8833 Dual Motor Driver Carrier
OprangePi Zero
Case for accumulator 18650
Accumulator 18650
Switcher
		
		 -->
	</body>
</html>


