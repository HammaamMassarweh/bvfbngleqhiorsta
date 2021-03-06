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
#include <unistd.h>
//-D_FILE_OFFSET_BITS == 64

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y));
#define SECONDS_IN_MIN 60
#define STRING_LENGTH 128
#define NUM_OF_CHARS 136
#define CHARS_START '!'
#define MAX_TIMESTAMP_LENGTH 22
//#define NUM_OF_LETTERS 52

int main(int argc, char** argv) {

	printf("=> process ID : %d\n", getpid());	//print procces id

	if (!argc != 1 && argc != 5 && argc != 9) { //todo ask if less or more parameters can be passed
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
	printf("=> Starting test...\n");

	time_t begin;
	time(&begin);

	//specifies the log file name and creats it
	unsigned long mytime = (unsigned long) begin;
	char filename[sizeof(mytime) + strlen("output_.log") + 1];
	sprintf(filename, "output_%lu.log", mytime);
	FILE* output = fopen(filename, "a");
	printf("=> %s log file is now opened\n", filename);

	double upacc = max / ramp;
	double downacc = max / tear;

	//this function works for a duration amount of minutes
	int passedTime = 0;
	while (passedTime < duration) {
		clock_t launch = clock();

		passedTime++;
		//here we calculate the number of events we can execute in this certain minute
		int toPrintEvents;
		int rampEvents = (int) (passedTime * upacc);
		int tearEvents = (int) ((duration - passedTime) * downacc);
		if (ramp > passedTime && tear > (duration - passedTime)) {
			toPrintEvents = MIN(rampEvents, tearEvents)
			;
		} else {
			if (ramp > passedTime) {
				toPrintEvents = rampEvents;
			} else {
				toPrintEvents = MIN(max, tearEvents)
				;
			}
		}

		printf("--> minute %d running another %d events\n", passedTime,
				toPrintEvents);
		for (int j = 0; j < toPrintEvents; j++) {
			//get the time and convert it to "struct tm" so we can extract time data.
			time_t shemde;
			time(&shemde);
			struct tm timeStruct;
			timeStruct = *(localtime(&shemde));

			// generates a random LOG LEVEL
			int randLogLevel = rand() % 3;
			char* logLevel;
			switch (randLogLevel) {
			case 0:
				logLevel = "INFO";
				break;
			case 1:
				logLevel = "DEBUG";
				break;
			case 2:
				logLevel = "ERROR";
				break;
			default:
				break;
			}

			// generates a string of random 128 ASCII chars
			char randString[STRING_LENGTH];
			for (int i = 0; i < STRING_LENGTH; i++) {
				int randChar = rand() % NUM_OF_CHARS;
				randString[i] = randChar + CHARS_START;
//				int randChar = rand() % NUM_OF_LETTERS;
//				randString[i]=letters[randChar];
			}

			//puts the log string into the log file (only dateTime meanwhile).
			char printNow[MAX_TIMESTAMP_LENGTH];
			snprintf(printNow, MAX_TIMESTAMP_LENGTH, "%d-%d-%dT%d:%d:%dZ",
					(timeStruct.tm_year) + 1900, timeStruct.tm_mon + 1,
					timeStruct.tm_mday, timeStruct.tm_hour, timeStruct.tm_min,
					timeStruct.tm_sec);
			int lineLen = MAX_TIMESTAMP_LENGTH + strlen(randString)
					+ strlen(logLevel) + 1 + 1 + 1 + 1;
			char printLogLine[lineLen];
			snprintf(printLogLine, lineLen, "%s %s %s\n", printNow, logLevel,
					randString);
			fputs(printLogLine, output);
		}

		/// let the process sleep for the rest of the minute.
		clock_t done = clock();
		double diff = (done - launch) / CLOCKS_PER_SEC;
		if (SECONDS_IN_MIN - (int) diff > 0) {
			sleep(SECONDS_IN_MIN - (int) diff);
		}
	}

	if (!output) {
		printf("# Files problem was discovered\n");
		return 0;
	}
	if (!fclose(output)) {
		printf("=> %s is now closed\n", filename);
	}

	return 0;
}

