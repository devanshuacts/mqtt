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
var pub_opts = {
	qos:0,
	retain:false
};
console.log(client);
var topic='iot-2/type/nodered-version0.15.1/id/0022647cf3b8/evt/status/fmt/json';
var payload = {
		d: { 
			myName: 'pidemo', 
			data: 
			{ 
			   temperature: 0, 
			   humidity: 0
			} 
		}
};
client.on('connect', function () {
	console.log('connected');
	var timer = setInterval(function() {
		payload.d.data.temperature=18+parseInt(Math.random()*22);
		payload.d.data.humidity=50+parseInt(Math.random()*50)
		client.publish(topic, JSON.stringify(payload),pub_opts);
	},5000);
	setTimeout(function() {
		//clearTimeout(timer);
		//client.end();
	},15000);		
});
