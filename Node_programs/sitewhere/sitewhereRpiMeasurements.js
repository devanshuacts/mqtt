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

var now = new Date().toISOString();
var fval = parseInt(Math.random() * (100 - 50) + 50);
var tval = parseInt(Math.random()* (200 - 100) + 100);

var obj = 
{
    hardwareId: "RPITEST",
    type: "DeviceMeasurements",
    request: {
        measurements: { 
        	fuel_level: fval,
        	engine_temp: tval
        },
        updateState: true,
        eventDate: now
     }
};

var jobj = JSON.stringify(obj);


client.on('connect', function(){
	var t3=setInterval( function() {
		client.publish('SiteWhere/input/json', jobj);
		console.log("Measurements published", now)
	},1000);
	setTimeout( function() {
		clearInterval(t3);
		client.end();
	},12000);
			
});



