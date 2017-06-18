#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "MQTTClient.h"
#include "MQTTAsync.h"

#define ADDR 		"tcp://localhost:1883"
#define TIMEOUT     10000L
#define TOPIC       "hello"
#define PAYLOAD		"hello from paho synchronous"
#define CLIENTID	"pub_async_exa"
#define QOS         1

void onPublishFailure(void* context, MQTTAsync_failureData* response)
{
	printf("publish failure\n");
}
void onPublish(void* context, MQTTAsync_successData* response)
{
	printf("payload published\n");
}

int main(){
	MQTTAsync client;
	int rtcode, rc;
	
	MQTTAsync_createOptions create_opts = MQTTAsync_createOptions_initializer;
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	MQTTAsync_responseOptions pub_opts = MQTTAsync_responseOptions_initializer;
	MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
	
	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;
	MQTTAsync_createWithOptions(&client, ADDR, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL,&create_opts);
	
	MQTTAsync_setCallbacks(client, NULL, NULL, NULL, NULL);
	
	rtcode = MQTTAsync_connect(client, &conn_opts);
	if(rtcode != MQTTCLIENT_SUCCESS){
		printf("not able to connect\n");
		exit(1);
	}
	
	pub_opts.onSuccess = onPublish;
	pub_opts.onFailure = onPublishFailure;
	
	do{
		rc = MQTTAsync_send(client, TOPIC, strlen(PAYLOAD), PAYLOAD, QOS, 0,&pub_opts);
	}while(rc != MQTTASYNC_SUCCESS);
	
	//disc_opts.onSuccess = onDisconnect;
	MQTTAsync_disconnect(client, &disc_opts);
	MQTTAsync_destroy(&client);
	
	return 0;
}












