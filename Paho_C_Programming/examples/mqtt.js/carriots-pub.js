var mqtt = require('mqtt')
//var conn_opts = require('url').parse('mqtt://localhost:1883');
var conn_opts = {
	protocol : 'mqtt',
	host : 'mqtt.carriots.com',
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
//conn_opts.clientId='a:quickstart:'+util_guid();
var client  = mqtt.connect(conn_opts);	//var client=mqtt.connect('mqtt://localhost:1883');
var pub_opts = {
	qos:0,
	retain:false
};
//console.log(client);
var api_key='97ac26df3c72bf2b79919137dc11eec3283941e1cf442ba26e25d9c92b3de7f2';
var topic=api_key+'/streams';
var payload = {
        protocol:"v2",
        at:"now",
        device:"cityweather@rajeshsola.rajeshsola",
        data:{
                temperature:0,
        },
        checksum:""
};
client.on('connect', function () {
	console.log('connected,topic='+topic);
	var timer = setInterval(function() {
		payload.data.temperature=18+parseInt(Math.random()*22);
		client.publish(topic, JSON.stringify(payload),pub_opts);
		console.log(payload);
	},5000);
	setTimeout(function() {
		//clearTimeout(timer);
		//client.end();
	},15000);		
});
