/***********************************************************************
name: Vivian Duong
	assignment4 -- acts as a pipe using ":" to seperate programs.
description:	
	See CS 360 Processes and Exec/Pipes lecture for helpful tips.
***********************************************************************/

/* Includes and definitions */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>

/**********************************************************************
./assignment4 <arg1> : <arg2>

    Where: <arg1> and <arg2> are optional parameters that specify the programs
    to be run. If <arg1> is specified but <arg2> is not, then <arg1> should be
    run as though there was not a colon. Same for if <arg2> is specified but
    <arg1> is not.
**********************************************************************/


int main(int argc, char *argv[]){
	int fd[2];

	// check if there is any argument entered
	if (argc < 2) {
		printf("%s\n", strerror(errno));
		exit(0);
	}

	//get number of arguments on the left side of :
	int i = 1;
	while ((strcmp(argv[i], ":") != 0)) {
		i++;
		if (i >= argc){
			break;
		}
	}
	
	int leftCount = i; 		// number of arguments on left 
	int rightCount = i + 1; // number of arguments on right

	char *left[argc]; 	// array to store args on the left
	char *right[argc];	// array to store args on the right

	// add the arguments on the left of the pipe to an array
	i = 1;
	int j = 0;
	for (; i < leftCount; i++) {
		left[j] = argv[i];
		j++;
	}
	// null terminate the array
	left[j] = NULL;
	
	// add the arguments on the right of the pipe to an array
	int k = 0;
	i = rightCount;
	for (; i < argc; i++) {
		right[k] = argv[i];
		k++;
	}
	// null terminate the array
	right[k] = NULL;

	//if no right args, execute left
	if (right[0] == NULL) {
		execvp(left[0], left);
		printf("%s\n", strerror(errno));
		exit(1);
	} else if (left[0] == NULL) { 	// if no left arguments, execute right
		execvp(right[0], right);
		printf("%s\n", strerror(errno));
		exit(1);
	}

	pipe(fd);
	int pid;
	if((pid = fork()) == 0) { // execute parent process
		close(fd[0]); 	// close parent's access to read end
		if (dup2(fd[1], 1) == -1) {
			printf("%s\n", strerror(errno));
			exit(1);
		}
		close(fd[1]);
		execvp(left[0], left);
		printf("%s\n", strerror(errno));
		exit(1);
	} else { // execute child process
		close(fd[1]); // close child's access to write end
		if (dup2(fd[0], 0)) {
			printf("%s\n", strerror(errno));
			exit(1);
		}
		close(fd[0]);
		execvp(right[0], right);
		printf("%s\n", strerror(errno));
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	return 0;
}