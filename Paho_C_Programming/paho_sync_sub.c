#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "MQTTClient.h"

#define ADDR 		"tcp://localhost:1883"
#define TIMEOUT     10000L
#define TOPIC       "hello"
#define QOS			1
#define CLIENTID	"sub.sync.demo"

int msgarrvd(void *context, char *topicName, int topiLen, MQTTClient_message *message){

	char *ploadptr;
	printf("call back entered: message arrived\n");
	ploadptr = message->payload;
	for(int i = 0; i < message->payloadlen; i++){
		printf("%c", *ploadptr);
		ploadptr++;
	}
	MQTTClient_freeMessage(&message);
	MQTTClient_free(topicName);
	return 1;
}

/*void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}*/

int main() {
	char ch;
	int rtcode;
	MQTTClient client;
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	
	MQTTClient_create(&client, ADDR, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
	conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
	
	MQTTClient_setCallbacks(client, NULL, NULL, msgarrvd, NULL);
	
	rtcode = MQTTClient_connect(client, &conn_opts);
	if(rtcode != MQTTCLIENT_SUCCESS){
		printf("not able to connect\n");
		exit(1);
	}
	
	MQTTClient_subscribe(client, TOPIC, QOS);
	
	while(1) {
		ch = getchar();
		if(ch == 'q' || ch == 'Q'){
			break;
		}
	}
	
	MQTTClient_disconnect(client, 10000L);
	MQTTClient_destroy(&client);
	
	return 0;
}
