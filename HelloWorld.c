#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 5
typedef struct {
	int startState;
	char readInput;
	char writeOutput;
	char shiftTape;
	int nextState;

} Transition;

typedef Transition *transitionPointer;
typedef transitionPointer *arrayOfTransitionPointer;
typedef arrayOfTransitionPointer *listOfStatePointer;



Transition acquireTransition();



int main() {
	Transition temporaryTransition;
	char phantomString[10];
	arrayOfTransitionPointer inputCharacters[256] = {NULL};
	int tempchar;
	scanf("%s", phantomString);
	printf("%s\n", phantomString);

	while(temporaryTransition.startState!= -1){
	temporaryTransition = acquireTransition();
	printf("%d", temporaryTransition.startState);
	if(temporaryTransition.startState!= -1){
	printf("%c", temporaryTransition.readInput);
	printf("%c", temporaryTransition.writeOutput);
	printf("%c", temporaryTransition.shiftTape);
	printf("%d\n", temporaryTransition.nextState);

	tempchar = (int) temporaryTransition.readInput;
	printf("%d\n", tempchar);
	printf("%p", inputCharacters[tempchar]);






	}




	}


    

    return 0;
}

Transition acquireTransition(){
	Transition transition;
	char *start = NULL;
    char *end = NULL;
    char in, out, shift;
    int firstState;
    int secondState;

    
        if ( start) {
            free ( start);
            start = NULL;
        }
        printf("before start: ");
        fflush ( stdout);
        scanf("%ms", &start);
        

        if(strcmp(start, "acc") != 0) {
            if ( end) {
                free ( end);
                end = NULL;
            }
            printf("in if: ");
            fflush ( stdout);
            scanf(" %c %c %c %ms", &in, &out, &shift, &end);
            printf("%s", start);
            printf("%c", in);
            printf("%c", out);
            printf("%c", shift);
            printf("%s\n", end);
            //Now i insert the read data into a Transition Node

            firstState = atoi(start);
    		secondState = atoi(end);

    		transition.startState = firstState;
    		transition.readInput = in;
    		transition.writeOutput = out;
    		transition.shiftTape = shift;
    		transition.nextState = secondState;

        }
        else {
        	transition.startState= -1;
        }
    
    
    if ( start) {
        free ( start);
        start = NULL;
    }
    if ( end) {
        free ( end);
        end = NULL;
    }

    return transition;
}
