#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mosquitto.h>
#define MESSAGE_SIZE 40
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

void my_publish_callback(struct mosquitto *mosq, void *obj, int mid)
{
	printf("published....\n");
}

int main(int argc,char* argv[])
{
	struct mosquitto *mosq;
	int i,rc = 0,msglen,major,minor,rev;
	char *buf,*topic;
	if(argc>2)
	{
		topic=argv[1];
		buf=argv[2];
		msglen=strlen(buf);
	}
	else if(argc==2)
	{
		topic="mosqpub/test";
		buf=argv[1];
		msglen=strlen(buf);
	}
	else
	{
		topic="mosqpub/test";
		buf="hello mosquitto!!";
		msglen=18;
	}
	mosquitto_lib_version(&major,&minor,&rev);
	printf("lib version:%d.%d.%d\n",major,minor,rev);
	mosquitto_lib_init();
	mosq = mosquitto_new("pubtest", true, NULL);
	mosquitto_connect_callback_set(mosq, my_connect_callback);
	mosquitto_disconnect_callback_set(mosq, my_disconnect_callback);
	mosquitto_publish_callback_set(mosq, my_publish_callback);
	//mosquitto_opts_set
	mosquitto_connect(mosq, "127.0.0.1", 1883, 600);
	//mosquitto_connect_bind
	//srand(time(0));
	//for(i=0;i<MESSAGE_SIZE;i++)
		//buf[i]=64+rand()%26;
	if(!mosquitto_loop(mosq, 0, 1))
		mosquitto_publish(mosq, NULL, topic, msglen, buf, 0, false);
	usleep(1000);		//TODO
	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
	return 0;
	

}
