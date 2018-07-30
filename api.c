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
//Pointer to single struct
typedef Transition *transitionPointer;
//Pointer to the array of transitions (grouped by state)
typedef Transition **arrayOfTransitionPointer;




Transition acquireTransition();



int main() {
    Transition temporaryTransition;
    char phantomString[10];
    //int arraySize = 256;
    arrayOfTransitionPointer inputCharacters[256] = {NULL};
    int tempchar;
    //arrayOfTransitionPointer tempPointer;
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

    //Fast check of conversion from ASCII to number, in order to insert in the right index
    tempchar = (int) temporaryTransition.readInput;
    printf("%d\n", tempchar);

    arrayOfTransitionPointer p=NULL;
    printf("%p\n",p );
    //p= (transitionPointer *)calloc(256,sizeof(transitionPointer));
    transitionPointer p2=NULL;

    p2=(Transition *) malloc(sizeof(Transition));
    p2->startState = 10;

    p= (transitionPointer *)calloc(256,sizeof(transitionPointer));
    p[0]=p2;
    printf("Prima del test\n");
    printf("%d\n",p[0]->startState );

    inputCharacters[0]=p;
    printf("%d\n", (**inputCharacters[0]).startState  );

    
/*
    printf("%p\n",p[0]);
    printf("prima di\n");
    printf("%p\n",p );
    inputCharacters[tempchar] = p;
    printf("%p\n", inputCharacters[tempchar]  );*/
    


    

    








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
