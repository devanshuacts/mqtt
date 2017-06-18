#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <mosquitto.h>
#define MESSAGE_MAX_SIZE 128
int completed;
void my_connect_callback(struct mosquitto *mosq, void *obj, int rc)
{
	printf("Conencted::rc: %d\n", rc);
	//TODO
}

void my_disconnect_callback(struct mosquitto *mosq, void *obj, int result)
{
	printf("Disconnected\n");
}

void my_subscribe_callback(struct mosquitto *mosq, void *obj, int mid)
{
	printf("subscribed....\n");
}
void my_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
	//char buf[MESSAGE_MAX_SIZE];
	//strncpy(buf,msg->payload,msg->payloadlen+1 );
	//buf[msg->payloadlen]=0;
	printf("Got a message::topic=%s,payload=%s\n",msg->topic,msg->payload);
}

int main()
{
	struct mosquitto *mosq;
	int i,rc = 0,major,minor,rev;
	mosquitto_lib_version(&major,&minor,&rev);
	printf("lib version:%d.%d.%d\n",major,minor,rev);
	mosquitto_lib_init();
	mosq = mosquitto_new("pubtest", true, NULL);
	mosquitto_connect_callback_set(mosq, my_connect_callback);
	mosquitto_disconnect_callback_set(mosq, my_disconnect_callback);
	//mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);
	mosquitto_message_callback_set(mosq, my_message_callback);
	//mosquitto_opts_set
	mosquitto_connect(mosq, "127.0.0.1", 1883, 600);
	//mosquitto_connect_bind
	mosquitto_subscribe(mosq, NULL, "mqtest",2); 
	mosquitto_loop_forever(mosq, 0, 1);
	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
	return 0;
	

}
