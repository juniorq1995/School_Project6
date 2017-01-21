#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <memory.h>

// This holds the total number of successful operations
int succ_ops = 0;

// This handler catches the exception thrown when the user types CONTROL-C
// The total number of successful operations is printed to the console and the program is exited
void exit_handler(){
	printf("\nTotal number of operations successfully completed: %i\n",succ_ops);
	printf("The program wil be halted.\n");
	exit(0);
}

// This handler catches the exception thrown when the user inputs a non-integer or 0 for the second input query
// The user is then informed that they attempted to illegally divide by 0 and outptus the total number of successful operations before exiting the program
void zero_handler(){
	printf("Error: a division by 0 operation was attempted.\n");
	printf("Total number of operations completed: %i\nThe program will be stopped.\n",succ_ops);	
	exit(0);
}

//In this main() function the user will be prompted for 2 integers and dsplay the result of division an the remainder separately.
// Any incorrect user inputs will be handled accordingly by the handlers above
int main(){
	// Vars for the first and second user inputs
	int one,two;
	// This struct will hold the information for which handler to invoke
	struct sigaction z_action,e_action;
	
	// Initialize the struct
	memset(&z_action,0,sizeof(z_action));
	memset(&e_action,0,sizeof(e_action));
	
	// Set the elements
	e_action.sa_handler = exit_handler;
	z_action.sa_handler = zero_handler;
	
	// Check that the handler binds while attempting to bind the handler
	if(sigaction(SIGINT,&e_action,NULL) == -1){
		printf("Failed to bind to the handler\n");
	}
	
	if(sigaction(SIGFPE,&z_action,NULL) == -1){
		printf("Failed to bind to the handler.\n");
		}
	// Prompt user for inputs and display results of operations
	while(1){
		//Prompt user for first input
		printf("Enter first integer: ");
		int check1 = scanf("%i",&one);
		// Check that input is of correct data type
		if(!check1){
			// If the user input is incorrect then set the input var to 0 and clear scanf
			one = 0;
			scanf("%*[^\n]");
		}
		
		// Prompt user for second input
		printf("Enter second integer: ");
		int check2 = scanf("%i",&two);
		// Check if second input has correct data type
		if(!check2){
			// If the input type is incorrect then set the second input var to a default 0 and clear scanf
			two = 0;
			scanf("%*[^\n]");
		}
		
		// Calculate the operations
		// Caclulate the result of dividing var one by var two
		int fraction = one/two;
		// Calculate one modulus two, akathe remainder from the above division operation
		int remainder = one%two;

		// Output the result of the operation to the console
		printf("%i / %i is %i with a remainder of %i\n",one,two,fraction,remainder);
		// Increment the number of successive operations
		succ_ops++;
	}
	return 0;
}
