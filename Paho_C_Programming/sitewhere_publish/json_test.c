#include <json/json.h>
#include <stdio.h>


int main() {
	char *jptr;
	json_object *job1 = json_object_new_object();
	json_object *jvalue = json_object_new_string("rpi");
	json_object_object_add(job1, "device", jvalue);
	
	json_object *job2 = json_object_new_object(); 
	json_object *jvalue1 = json_object_new_int(24);
	json_object *jvalue2 = json_object_new_int(72);
	json_object_object_add(job2, "temp", jvalue1);
	json_object_object_add(job2, "humidity", jvalue2);
	json_object_object_add(job1, "measurements", job2);
	
	jptr = json_object_to_json_string(job1);
	
	printf("%s\n", jptr);

	
	return 0;
	
}
