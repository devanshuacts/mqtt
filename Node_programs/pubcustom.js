const mqtt = require('/home/devanshu/node-v6.10.0/lib/node_modules/mqtt');

var conn_opts = {
	host: 'localhost',
	port: 1883,
	protocolId: 'MQTT',
	protocolVersion: 4,
	clean: true,
	qos: 1,
	retain: true,
	clientId: 'pubdemo.1234',
	will: {
		topic: 'killed',
		payload: 'pub terminated'
	}
};

var client = mqtt.connect(conn_opts);

client.on('connect', function(){
	var t3=setInterval( function() {
		client.publish('hello', 'my custom message with qos 1');
	},1000);
	
	setTimeout( function() {
		clearInterval(t3);
		client.end();
	},12000);
});

