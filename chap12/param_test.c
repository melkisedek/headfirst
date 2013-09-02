/*
Thread functions can accept a single void pointer parameter and return
a single void pointer value. Quite often, you will want to pass and
return integer values to a thread, and one trick is to use long values.
longs can be stored in void pointers because they are the same size.
*/
#include <stdio.h>
#include <pthread.h>
//a thread can accept a single void pointer parameter
void* do_stuff(void* param){
	long thread_no = (long)param;
	printf("Thread number %ld\n", thread_no);
	return (void*)(thread_no + 1);
}

int main(int argc, char const *argv[])
{
	pthread_t threads[20];
	long t;
	for(t = 0; t < 3; t++){
		pthread_create(&threads[t], NULL, do_stuff, (void*)t);
	}

	void* result;
	for(t = 0; t < 3; t++){
		pthread_join(threads[t], &result);
		printf("Thread %ld returned %ld\n", t, (long)result );
	}
	return 0;
}