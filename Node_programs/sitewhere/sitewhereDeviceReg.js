const mqtt = require('/home/devanshu/node-v6.10.0/lib/node_modules/mqtt');

var conn_opts = {
	host: 'localhost',
	port: 1883,
	protocolId: 'MQTT',
	protocolVersion: 4,
	clean: true,
	qos: 1,
	retain: true,
	clientId: 'pubdemo.101',
	will: {
		topic: 'killed',
		payload: 'pub terminated'
	}
};

var client = mqtt.connect(conn_opts);

var mypayload = 
{
	hardwareId: "RPITEST",
	type: "RegisterDevice",
	request: {
		hardwareId: "RPITEST",
		specificationToken: "7dfd6d63-5e8d-4380-be04-fc5c73801dfb",
		siteToken: "227639cd-8fe0-4f18-a2d0-4e88d1589190"
	}
}

//topic:- SiteWhere/input/json
var jload = JSON.stringify(mypayload);
//publish it then


client.on('connect', function(){
	client.publish('SiteWhere/input/json', jload);
	client.end();
});	
	
	
	
	


