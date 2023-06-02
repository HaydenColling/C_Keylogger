#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>

int main(int argc,char* argv[]) {

	printf("***Creating log file***\n");

	FILE* fp;
	fp = fopen("log","w");
	char buffer[1024];

	// Get time
	struct timeval tv;
	time_t t;
	struct tm *info;

	gettimeofday(&tv,NULL);
	t = tv.tv_sec;
	info = localtime(&t);
	strftime(buffer,sizeof(buffer), "%A %B %d %I:%M %P\n",info);
	printf("%s", buffer);

	// Write start for signify beggining of log
	// Write current time of day

	fprintf(fp,"start\t",sizeof("start"));
	fprintf(fp,buffer,sizeof(buffer));

}