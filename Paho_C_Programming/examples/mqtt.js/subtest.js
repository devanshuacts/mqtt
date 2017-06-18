var mqtt = require('mqtt')
var hosturl= 'mqtt://localhost:1883';
var conn_opts={};
conn_opts.clean=true;
conn_opts.clientId='sub.1';
conn_opts.keepalive=60;
//conn_opts.protocolId=MQTT'; //MQIsdp
//conn_opts.protocolVersion=4;//3
//reconnectPeriod: 1000,
//connectTimeout: 30000
//username:'xxxx',
//password:'xxxx'
var client  = mqtt.connect(hosturl,conn_opts);	//var client=mqtt.connect('mqtt://localhost:1883');
var sub_opts = {
	qos:1,	
};
//console.log(client);
//client.subscribe('simple');
//client.subscribe(['simple','jstest']);
//client.subscribe({'simple':2});
client.subscribe({'simple':1,'jstest':2});
client.on('message', function (topic,message) {
	console.log("Got a message,topic=",topic,"message=",message.toString());
	if(message.toString()==="stop")
		client.end();
});
