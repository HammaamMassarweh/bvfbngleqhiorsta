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

int main(int argc, char** argv) {

	if (!argc != 1 && argc != 5 && argc != 9) {
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
	printf("max = %d\nduration = %d\nramp = %f\ntear = %f\n",max,duration,ramp,tear);


	return 0;
}

