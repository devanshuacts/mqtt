var mqtt = require('mqtt')
//var client  = mqtt.connect('tcp://localhost:1883')
var client=mqtt.connect('ws://192.168.7.109:8883/mqtt');

client.on('connect', function () {
  client.subscribe('presence')
  client.publish('presence', 'Hello mqtt')
})

client.on('message', function (topic, message) {
  // message is Buffer
  console.log(message.toString())
  client.end()
})
