#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "MQTTClient.h"

#define ADDR 		"tcp://localhost:1883"
#define TIMEOUT     10000L
#define TOPIC       "hello"
#define PAYLOAD		"hello from paho"
#define CLIENTID	"pub_sync_exa"

int main(){
	int rx;
	MQTTClient client;
	
	MQTTClient_create(&client, ADDR, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
	
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	
	MQTTClient_connect(client, &conn_opts);
	MQTTClient_message pubmesg = MQTTClient_message_initializer;
	
	//char str[] = "hello from paho";
	pubmesg.payload = PAYLOAD;
	pubmesg.payloadlen = strlen(PAYLOAD);
	pubmesg.qos = 1;
	pubmesg.retained = 0;
	
	MQTTClient_deliveryToken token;
	MQTTClient_publishMessage(client, TOPIC, &pubmesg, &token);
	rx = MQTTClient_waitForCompletion(client, token, 10000L);
	printf("%d\n", rx);
	MQTTClient_disconnect(client, 10000L);
	MQTTClient_destroy(&client);
	return rx;
}

