#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MQTTAsync.h"
#include "MQTTClient.h"

#define ADDRESS     "tcp://localhost:1883"
#define CLIENTID    "ExampleClientPub"
#define TOPIC       "pahotest"
#define PAYLOAD     "Hello World!"
#define QOS         2
#define TIMEOUT     10000L

int messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* m)
{
	//Nothing to Do in publish
}
void onDisconnect(void* context, MQTTAsync_successData* response)
{
}
void onConnect(void* context, MQTTAsync_successData* response)
{
}
void onConnectFailure(void* context, MQTTAsync_failureData* response)
{

}
void connectionLost(void* context, char* cause)
{
}
void onPublishFailure(void* context, MQTTAsync_failureData* response)
{
}
void onPublish(void* context, MQTTAsync_successData* response)
{
}

int main(int argc, char* argv[])
{
	MQTTAsync client;
	MQTTAsync_createOptions create_opts = MQTTAsync_createOptions_initializer;
	MQTTAsync_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	MQTTAsync_responseOptions pub_opts = MQTTAsync_responseOptions_initializer;
	MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;	
	//MQTTClient_message pubmsg = MQTTClient_message_initializer;
	//MQTTClient_deliveryToken token;
	int rc;

	MQTTAsync_createWithOptions(&client, ADDRESS, CLIENTID,MQTTCLIENT_PERSISTENCE_NONE, NULL,&create_opts);
	MQTTAsync_setCallbacks(client, client, connectionLost, messageArrived, NULL);

	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;
	//conn_opts.username = opts.username;
	//conn_opts.password = opts.password;
	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	conn_opts.context = client;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
	{
		printf("Failed to connect, return code %d\n", rc);
		exit(-1);
	}
	/*pubmsg.payload = PAYLOAD;
	pubmsg.payloadlen = strlen(PAYLOAD);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;*/
	pub_opts.onSuccess = onPublish;
	pub_opts.onFailure = onPublishFailure;
	//MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
	do {
		rc=MQTTAsync_send(client,TOPIC,strlen(PAYLOAD),PAYLOAD,QOS, 0,&pub_opts);
	}while (rc != MQTTASYNC_SUCCESS);
	//usleep(1000);
	disc_opts.onSuccess = onDisconnect;
	MQTTAsync_disconnect(client, &disc_opts);
	MQTTAsync_destroy(&client);
	return rc;
}

