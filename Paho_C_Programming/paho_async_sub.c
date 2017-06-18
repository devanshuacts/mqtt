#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "MQTTClient.h"
#include "MQTTAsync.h"

#define ADDR 		"tcp://localhost:1883"
#define TIMEOUT     10000L
#define TOPIC       "hello"
#define QOS			1
#define CLIENTID	"sub_async_exa"

void onDisconnect(void* context, MQTTAsync_successData* response)
{
}
void onSubscribeFailure(void* context, MQTTAsync_failureData* response)
{
}
void onSubscribe(void* context, MQTTAsync_successData* response)
{
}
void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
	//TODO:reconnect
}
void connectionLost(void* context, char* cause)
{
	//TODO:reconnect
}

void onConnect(void* context, MQTTAsync_successData* response){
	int rc;
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_responseOptions sub_opts = MQTTAsync_responseOptions_initializer;
	sub_opts.onSuccess = onSubscribe;
	sub_opts.onFailure = onSubscribeFailure;
	rc = MQTTAsync_subscribe(client, TOPIC, QOS, &sub_opts);
	if(rc!=MQTTASYNC_SUCCESS)
	{
		printf("Failed to start subscribe, return code %d\n", rc);
	}
	else printf("connected and subscribed\n");
}

int messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* message)
{
	printf("topic:%s\t", topicName);
	char payloadbuf[message->payloadlen+1];
	strncpy(payloadbuf,message->payload,message->payloadlen+1);
	printf("payload:%s\n", payloadbuf);
	//printf("%.*s", message->payloadlen, (char*)message->payload);
	fflush(stdout);
	MQTTAsync_freeMessage(&message);
	MQTTAsync_free(topicName);
	return 1;
}

int main(){
	MQTTAsync client;
	int rtcode;
	char ch;
	
	MQTTAsync_createOptions create_opts = MQTTAsync_createOptions_initializer;
	MQTTAsync_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;	

	MQTTAsync_createWithOptions(&client, ADDR, CLIENTID,MQTTCLIENT_PERSISTENCE_NONE, NULL,&create_opts);
	MQTTAsync_setCallbacks(client, client, NULL, messageArrived, NULL);

	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;	
	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	conn_opts.context = client;
	
	rtcode = MQTTAsync_connect(client, &conn_opts);
	if(rtcode != MQTTCLIENT_SUCCESS){
		printf("not able to connect\n");
		exit(1);
	}
	
	while(1) {
		ch = getchar();
		if(ch == 'q' || ch == 'Q'){
			break;
		}
	}
	
	disc_opts.onSuccess = onDisconnect;
	MQTTAsync_disconnect(client, &disc_opts);
	MQTTAsync_destroy(&client);
	return 0;
}











