#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "MQTTClient.h"
#include <json/json.h>

#define ADDR 		"tcp://localhost:1883"
#define TIMEOUT     10000L
#define TOPIC       "SiteWhere/input/json"
#define CLIENTID	"pubdemo.101"

int main() {
	
	int rx;
	MQTTClient client;
	
	MQTTClient_create(&client, ADDR, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
	
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	
	MQTTClient_connect(client, &conn_opts);
	MQTTClient_message pubmesg = MQTTClient_message_initializer;
	
	/*
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
	*/
	
	//char *jptr;
	json_object *job1 = json_object_new_object();
	json_object *hardwareId = json_object_new_string("RPITEST");
	json_object *type = json_object_new_string("DeviceMeasurements");
	json_object_object_add(job1, "hardwareId", hardwareId);
	json_object_object_add(job1, "type", type);
	
	json_object *request = json_object_new_object(); 
	
	json_object *measurements = json_object_new_object();
	json_object *fuel_level = json_object_new_int(30);
	json_object *engine_temp = json_object_new_int(40);
	json_object_object_add(measurements, "fuel_level", fuel_level);
	json_object_object_add(measurements, "engine_temp", engine_temp);
	
	json_object *updateState = json_object_new_boolean(10);
	json_object *eventDate = json_object_new_string("2017-05-26 23:31:46");	
	json_object_object_add(request, "measurements", measurements);
	json_object_object_add(request, "updateState", updateState);
	//json_object_object_add(request, "eventDate", eventDate);
	
	json_object_object_add(job1, "request", request);
	
	const char *jptr = json_object_to_json_string(job1);
	
	printf("%s\n", jptr);
	
	pubmesg.payload = jptr;
	pubmesg.payloadlen = strlen(jptr);
	pubmesg.qos = 1;
	pubmesg.retained = 0;
	
	MQTTClient_deliveryToken token;
	MQTTClient_publishMessage(client, TOPIC, &pubmesg, &token);
	rx = MQTTClient_waitForCompletion(client, token, 10000L);
	//printf("%d\n", rx);
	MQTTClient_disconnect(client, 10000L);
	MQTTClient_destroy(&client);

	return 0;
	
}
