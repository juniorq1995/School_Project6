#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <memory.h>

// Gobal vars
// sec is the number of seconds to set the alarm() function
int sec = 3;
// count holds the total number of CONTROL-C commands needed before the program exits
int count = 5;

// This function is a handler that catches the SIGINT exception thrown when the user types CONTROL-C
// When the handler is invoked it displays the total number of CONTROL-C commands needed before the program exits
// If the global var count is 0, then the function carries out the exit of the program
void exit_handler(){
	count--;
	// Finally exits program
	if(count == 0){
		printf("\nFinal control-c caught. Exiting.\n");
		exit(0);
	}
	// Display number of CONTROL-C commands left before program exits
	else{
		printf("\nControl-c caught. %i more before program ends.\n",count);
	}
}

// This function is a handler that catches the SIGALRM exception thrown when the alarm() function reaches 0
// When this handler is invoked, it gets the current time from the computer and siplays it to the console
void alarm_handler(){
	// Get current date and time from computer
	time_t curr_time;
	char* time_string;
	curr_time = time(NULL);

	time_string = ctime(&curr_time);
	// Display current date and time to the console for the user
	printf("current time is %s", time_string);
	// Reset the alarm so this function will be invoked in sec seconds
	alarm(sec);
}

// In this main() function the user is informed that the current date/time will be printed to the console every 3 seconds in an infinite loop
// In order to break out of this loop the user must exit the program by typing CONTROL-C 5 times
// Each time the user types CONTROL-C a meesage is displayed with the current count of CONTROL-C needed to exit the program left 
int main(){
	// The struct that will hold the info for the handler to be invoked
	struct sigaction al_action,ex_action;

	// Setting aside memory and initializing the struct
	memset(&al_action,0, sizeof(al_action));
	memset(&ex_action,0,sizeof(ex_action));

	// Setting the elements
	al_action.sa_handler = alarm_handler;
	ex_action.sa_handler = exit_handler;	

	// Display message for user
	printf("Date will be printed every 3 seconds\nEnter ^C 5 times to end the program:\n");
	
	// Bind handler and check that it binded successfully
	if(sigaction(SIGALRM,&al_action,NULL) == -1){
		printf("Failed to bind handler\n");
	}
	// Bind handler and check that it binded successfully
	if(sigaction(SIGINT,&ex_action,NULL) == -1){
		printf("Failed to bind handler\n");
	}	
	// Set the initial alarm
	alarm(sec);
	// Enter infinite loop
	while(1);

	return 0;
}
