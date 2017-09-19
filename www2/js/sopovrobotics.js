window.sopovrobotics = {};
window.sopovrobotics.secret = "";
window.sopovrobotics.ws_opened = function(){};
window.sopovrobotics.ws_error = function(){};
window.sopovrobotics.receive_settings = function(data){}
window.sopovrobotics.receive_info = function(data){}
window.sopovrobotics.receive_error = function(data){}
window.sopovrobotics.receive_updated_settings = function(data){}

window.sopovrobotics.connect = function(ipaddressport){
	var self = window.sopovrobotics;
	
	self.socket = new WebSocket("ws://" + ipaddressport);
	self.socket.onopen = function() {
		self.ws_opened();
	};
	
	self.socket.onmessage = function(event) {
		var data = JSON.parse(event.data);
		if(data.error){
			console.error(data);
			self.receive_error(data.error);
		}else if(data.msg == "info"){
			self.receive_info(data);
		}else if(data.cmd == "settings"){
			self.receive_settings(data.data);
		}else if(data.cmd == "update_settings"){
			self.receive_updated_settings(data.data);
		}else{
			console.warn(data);
		}
	};

	self.socket.onerror = function(error) {
		console.error("Error " + error.message);
		$('#status_connection').html('WS failed connect');
		self.ws_error();
	};
}

window.sopovrobotics.cmd_stop = function(){
	var self = window.sopovrobotics;
	self.socket.send(JSON.stringify({
		'cmd':'stop',
		'secret': self.secret
	}));
}

window.sopovrobotics.cmd_settings = function(){
	var self = window.sopovrobotics;
	self.socket.send(JSON.stringify({
		'cmd':'settings',
		'secret': self.secret
	}));
}

window.sopovrobotics.cmd_update_settings = function(data){
	var self = window.sopovrobotics;
	self.socket.send(JSON.stringify({
		'cmd':'update_settings',
		'secret': self.secret,
		'data': data
	}));
}


window.sopovrobotics.cmd_comb_up = function(){
	var self = window.sopovrobotics;
	self.socket.send(JSON.stringify({
		'cmd':'comb_up',
		'secret': self.secret
	}));
}

window.sopovrobotics.cmd_comb_down = function(){
	var self = window.sopovrobotics;
	self.socket.send(JSON.stringify({
		'cmd':'comb_down',
		'secret': self.secret
	}));
}

window.sopovrobotics.cmd_forward = function(){
	var self = window.sopovrobotics;
	self.socket.send(JSON.stringify({
		'cmd':'forward',
		'secret': self.secret
	}));
}

window.sopovrobotics.cmd_backward = function(){
	var self = window.sopovrobotics;
	self.socket.send(JSON.stringify({
		'cmd':'backward',
		'secret': self.secret
	}));
}

window.sopovrobotics.cmd_turnleft = function(){
	var self = window.sopovrobotics;
	self.socket.send(JSON.stringify({
		'cmd':'turnleft',
		'secret': self.secret
	}));
}

window.sopovrobotics.cmd_turnright = function(){
	var self = window.sopovrobotics;
	self.socket.send(JSON.stringify({
		'cmd':'turnright',
		'secret': self.secret
	}));
}

window.sopovrobotics.cmd_stop = function(){
	var self = window.sopovrobotics;
	self.socket.send(JSON.stringify({
		'cmd':'stop',
		'secret': self.secret
	}));
}

window.sopovrobotics.cmd_start_auto = function(script){
	var self = window.sopovrobotics;
	self.socket.send(JSON.stringify({
		'cmd':'start_auto',
		'secret': self.secret,
		'script': script
	}));
}

window.sopovrobotics.cmd_stop_auto = function(){
	var self = window.sopovrobotics;
	self.socket.send(JSON.stringify({
		'cmd':'stop_auto',
		'secret': self.secret
	}));
}
