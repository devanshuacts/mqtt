#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <MQTTClient.h>

#define ADDRESS     "tcp://localhost:1883"
#define CLIENTID    "ExampleClientSub"
#define TOPIC       "pahotest"
#define PAYLOAD     "Hello World!"
#define QOS         2
#define TIMEOUT     10000L

MQTTClient_deliveryToken deliveredtoken;
void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    char* payloadptr;
    int i;

    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");

    payloadptr = message->payload;
    for(i=0; i<message->payloadlen; i++)
    {
        putchar(*payloadptr++);
    }
    putchar('\n');
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}
void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}


int main(int argc, char* argv[])
{
    MQTTClient client;
    char *topic=TOPIC;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message submsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    MQTTClient_create(&client, ADDRESS, CLIENTID,MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }
    rc=MQTTClient_subscribe(client, topic, QOS);
    /*while(1) 	//true synchronous
    {
	char* topicName = NULL;
	//char pbuf[128],tbuf[32];
	int topicLen=0;
	MQTTClient_message* message = NULL;
	rc = MQTTClient_receive(client, &topicName, &topicLen, &message, 1000);
	if(message) {
		//strncpy(tbuf,topicName,topicLen+1);
		//strncpy(pbuf,message->payload,message->payloadlen+1);
		printf("Got a message::topic:%s,payload:%s\n",topicName,message->payload);
		MQTTClient_freeMessage(&message);
		MQTTClient_free(topicName);
	}
	//else
		//printf("no message at this point\n");
    }*/
    while(1)
    pause();	//wait for signal (or) sigsuspend in callback mode
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}

