const mqtt = require('/home/devanshu/node-v6.10.0/lib/node_modules/mqtt');
var client = mqtt.connect("mqtt://127.0.0.1:1883");

client.on('connect', function(){
	client.publish('hello', 'my second message');
	client.end();
	//client.end(true, function(){
		//console.log("client exited");
	//});
});

