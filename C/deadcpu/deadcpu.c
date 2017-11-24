#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <time.h>
#include <pthread.h>

int cpu_usage(void){

long double a[4], b[4], loadavg;
	FILE *fp;

	fp = fopen("/proc/stat","r");
	fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&a[0],&a[1],&a[2],&a[3]);
	fclose(fp);
	sleep(1);

	fp = fopen("/proc/stat","r");
	fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&b[0],&b[1],&b[2],&b[3]);
	fclose(fp);

	loadavg = ((b[0]+b[1]+b[2]) - (a[0]+a[1]+a[2])) / ((b[0]+b[1]+b[2]+b[3]) - (a[0]+a[1]+a[2]+a[3]));
	printf("CPU: %Lf\n",loadavg);


	return 0;

}

void *calc(void *arg){

	srand((unsigned int)time(NULL));
	float res, a = 5.0;

	while(1){

		res = (float)rand()/(float)(7.9) * a;
	}
}

int main(int argc, char *argv[])
{	
	if (argc < 2){
		printf("Syntax: <max thread number>\n");
		return 0;
	}

	int result, max;

	max = atoi(argv[1]);

	pthread_t threads[max];

	for (int i = 0; i < max; ++i)
	{
		result = pthread_create(&threads[i], NULL, calc, 0);
		if (result != 0) {
			perror("Error creating the first thread");
			return EXIT_FAILURE;
		}

		printf("THREAD: %d\t", i);
		cpu_usage();

	}

	return 0;
}
