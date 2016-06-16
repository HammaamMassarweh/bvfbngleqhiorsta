/*
 * main.c
 *
 *  Created on: May 27, 2015
 *      Author: hussen
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {

	if (!argc != 1 && argc != 5 && argc != 9) {  //todo ask if less or more parameters can be passed
		printf("Invalid input");
		return 0;
	}

	//default values
	int max = 1000, duration = 1;
	double ramp = 0.2, tear = 0.2;

//	for(int i=0;i<argc;i++){
//		printf("%s\n",argv[i]);
//	}

	switch (argc) {
	case 5:
		// in case parameters were passed without a word before each parameter
		max = atoi(argv[1]);
		duration = atoi(argv[2]);
		ramp = atof(argv[3]);
		tear = atof(argv[4]);
		break;
	case 9:
		// in case parameters were passed with a word before each parameter
		max = atoi(argv[2]);
		duration = atoi(argv[4]);
		ramp = atof(argv[6]);
		tear = atof(argv[8]);
		break;
	default:
		break;
	}

	// print parameters
	printf("=> Starting test with:\nmax = %d\nduration = %d\nramp = %f\ntear = %f\n",max,duration,ramp,tear);

	unsigned long mytime = (unsigned long)time(NULL);	//todo check if timestamp is accurate

//	printf("my size:%d\n",sizeof(mytime));

	char filename[sizeof(mytime)];				//todo check if size is good that way

	sprintf(filename, "output_%lu.log", mytime);

//	printf("%lu\n", mytime);
//	printf("TS:=%s\n",filename);

	FILE* output = fopen(filename,"a");
	printf("=> %s log file is now opened\n",filename);

	if(!output){
		printf("# Files problem was discovered\n");
		return 0;
	}
	if(!fclose(output)){
		printf("=> %s is now closed\n",filename);
	}

	return 0;
}

