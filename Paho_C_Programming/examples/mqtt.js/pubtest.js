var mqtt = require('mqtt')
//var conn_opts = require('url').parse('mqtt://localhost:1883');
var conn_opts = {
	protocol : 'mqtt',
	host : 'localhost',
	port :1883,	
	protocolId: 'MQTT', //'MQIsdp',
  	protocolVersion: 4,   //3
	keepalive: 60,
	clean: true,
	clientId: 'pub.1',
	reconnectPeriod: 1000,
        connectTimeout: 30000
	//username:'xxxx',
	//password:'xxxx'
};
var client  = mqtt.connect(conn_opts);	//var client=mqtt.connect('mqtt://localhost:1883');
var pub_opts = {
	qos:1,
	retain:false
};
console.log(client);
client.on('connect', function () {
	console.log('connected');
	var timer = setInterval(function() {
		client.publish('simple', 'Hello mqtt',pub_opts);
	},1000);
	setTimeout(function() {
		clearTimeout(timer);
		client.end();
	},15000);		
});
