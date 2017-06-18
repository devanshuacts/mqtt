const mqtt = require('/home/devanshu/node-v6.10.0/lib/node_modules/mqtt');

var conn_opts = {
	host: 'localhost',
	port: 1883,
	protocolId: 'MQTT',
	protocolVersion: 4,
	clean: true,
	qos: 1,
	retain: true,
	clientId: 'subdemo.1234',
	will: {
		topic: 'killed',
		payload: 'sub terminated'
	}
};

var client = mqtt.connect(conn_opts);

client.on('connect', function(){
	console.log('connected');
	client.subscribe('hello');
});

client.on('message', function(topic, message){
	console.log('got a message, topic:'+topic);
	console.log('payload:'+message);
});
