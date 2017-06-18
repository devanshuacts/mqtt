var mqtt = require('mqtt')
//var conn_opts = require('url').parse('mqtt://localhost:1883');
var conn_opts = {
	protocol : 'mqtt',
	host : 'quickstart.messaging.internetofthings.ibmcloud.com',
	port :1883,	
	protocolId: 'MQTT', //'MQIsdp',
  	protocolVersion: 4,   //3
	keepalive: 60,
	clean: true,
	//clientId: 'a:quickstart:44d8c70a553c',
	reconnectPeriod: 1000,
    connectTimeout: 30000
	//username:'xxxx',
	//password:'xxxx'
};
function s4() {
return Math.floor((1 + Math.random()) * 0x10000).toString(16).substring(1);
}
function util_guid() {
        return s4() + s4() + s4();    
};
conn_opts.clientId='a:quickstart:'+util_guid();
var client  = mqtt.connect(conn_opts);	//var client=mqtt.connect('mqtt://localhost:1883');
console.log(client);
var topic='iot-2/type/nodered-version0.15.1/id/0022647cf3b8/evt/status/fmt/json';
client.on('connect', function () {
	console.log('connected');
	client.subscribe(topic);	
});
client.on('message',function(topic,payload) {
	console.log("topic:"+topic);
	var message=JSON.parse(payload);
	console.log(message);
	//console.log("device:"+message.d.myName);
	//console.log(message.d.data);
});
