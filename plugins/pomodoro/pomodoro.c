#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(int argc, char *argv[]){
	
	// initialize variables
	int mins = 0, secs = 0;
	char min_string[4], sec_string[4];

	// declare files
	FILE *mins_file;
	FILE *secs_file;

	// initialize time from command line arguments
	if(argc > 1) {
		mins = atoi(argv[1]);
		if (argc == 3) secs = atoi(argv[2]);
	}

	// case distinction: if resume: read time from file , 
	// if new start: write from file
	if( argc == 1){
		// read initial time from file
		mins_file = fopen("minutes", "r");
		secs_file = fopen("seconds", "r");
		fgets(min_string, 4, mins_file);
		fgets(sec_string, 4, secs_file);
		fclose(mins_file);
		fclose(secs_file);
		mins = atoi(min_string);
		secs = atoi(sec_string);
	} else {
		// write initial time to file
		mins_file = fopen("minutes", "w");
		secs_file = fopen("seconds", "w");
		fprintf(mins_file, "%d", mins);
		fprintf(secs_file, "%d", secs);
		fclose(mins_file);
		fclose(secs_file);
	}

	// start timer
	while (mins >= 0){
		while (secs > 0){
			sleep(1);
			secs_file = fopen("seconds", "w");
			fprintf(secs_file, "%d", --secs);
			fclose(secs_file);
		}
		sleep(1);
		secs = 59;
		secs_file = fopen("seconds", "w");
		fprintf(secs_file, "%d", secs);
		fclose(secs_file);
		if( --mins >= 0) {
			mins_file = fopen("minutes", "w");
			fprintf(mins_file, "%d", mins);
			fclose(mins_file);
		}
	}

}
