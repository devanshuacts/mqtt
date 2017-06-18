const mqtt = require('/home/devanshu/node-v6.10.0/lib/node_modules/mqtt');

var conn_opts = {
	host: 'localhost',
	port: 1883,
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
