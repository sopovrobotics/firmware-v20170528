/*$(document).ready(function(){
	setInterval(function(){
		image1.src="webcam.php?t=" + Date.now();
	}, 1000);
});*/

var type = "stop";
var connected = false;
$(document).keydown(function(e){
	// console.log("keydown ", e.keyCode);
	if(e.keyCode == 38){
		type = "forward";
	}else if(e.keyCode == 40){
		type = "backward";
	}else if(e.keyCode == 37){
		type = "turnleft";
	}else if(e.keyCode == 39){
		type = "turnright";
	}else{
		type = "stop";
	}
});

$(document).keyup(function(e){
	// console.log("keyup ", e.keyCode);
	type = "stop";
});

setInterval(function(){
	if(connected == false)
		return;

	if(type == "forward"){
		$('#forward_').show();
		drive("forward");
	}else{
		$('#forward_').hide();
	}
	
	if(type == "backward"){
		$('#backward_').show();
		drive("backward");
	}else{
		$('#backward_').hide();
	}
	
	if(type == "turnleft"){
		$('#turnleft_').show();
		drive("turnleft");
	}else{
		$('#turnleft_').hide();
	}
	
	if(type == "turnright"){
		$('#turnright_').show();
		drive("turnright");
	}else{
		$('#turnright_').hide();
	}
	
	if(type == "stop"){
		stop();
	}
	
}, 200);

function takevideo0(){
	if(connected == false)
		return;
	//window.socket.send(JSON.stringify({'cmd':'takevideo0'}));
}

var lastSendedCommand = ''; 

function drive(cmd){
	if(connected == false)
		return;
	if(lastSendedCommand != cmd){
		lastSendedCommand = cmd;
		window.socket.send(JSON.stringify({'cmd':cmd}));
	}
}

function stop(){
	if(connected == false)
		return;
	if(lastSendedCommand != 'stop'){
		lastSendedCommand = 'stop';
		window.socket.send(JSON.stringify({'cmd':'stop'}));
	}
}

setInterval(function(){
	if(connected == false)
		return;
	takevideo0();
}, 2000);


if(window.localStorage.getItem('roboscript') == null){
	window.localStorage.setItem('roboscript', ""
		+ "function main(){\n"
		+ "  turnleft(); sleep(1000); stop();\n"
		+ "  forward(); sleep(1000); stop();\n"
		+ "  backward(); sleep(1000); stop();\n"
		+ "  turnright(); sleep(1000); stop();\n"
		+ "}"
	)
}


$(document).ready(function(){
	$('#connect').click(function(){
		$('.connectionform').hide();
		window.socket = new WebSocket($('#address_ws').val());
		window.socket.onopen = function() {
			$('.controlpanel').css({'display': 'table'});
			connected = true;
			takevideo0();
		};

		window.socket.onclose = function(event) {
			$('.controlpanel').hide();
			$('.connectionform').show();
			
			if (event.wasClean) {
				console.log('Disconnected');
			} else {
				console.log('Connection refused');
			}
			console.log('Code: ' + event.code + ' Reason: ' + event.reason);
			connected = false;
		};

		window.socket.onmessage = function(event) {
			
			if(event.data instanceof Blob){
				
				/*var ctx = document.getElementById('canvas').getContext('2d');
				var img = new Image;
				img.onload = function() {
					ctx.drawImage(img, 20,20);
					alert('the image is drawn');
				}
				img.src = URL.createObjectURL(e.target.files[0]);*/

				// $('.controlpanel').css({'display': 'table'});
				// $('#webcam').attr({'src' : URL.createObjectURL(event.data)})
			}else{
				console.log("Recieved data " + event.data);
			}
			
		};

		window.socket.onerror = function(error) {
			console.log("Error " + error.message);
			// $('.connectionform').hide();
			// $('#status').hide();
			// $('#webcam').hide();
			// connected = false;
		};
	});

	$('#roboscript').html(window.localStorage.getItem('roboscript'));
})
