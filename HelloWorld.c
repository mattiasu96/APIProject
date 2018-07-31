#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 5
#define SIZE 256
typedef struct T{
	int startState;
	char readInput;
	char writeOutput;
	char shiftTape;
	int nextState;
	struct T *prox;


} Transition;

Transition *acquireTransition();
int calculateHashMap(int stateNumber);
void scantr();



int main() {
	Transition *temporaryTransition=NULL;
	Transition **inputCharacters[256] = {NULL};
	int tempchar;
	int hashmapIndex;
	Transition **p=NULL;

	//Stringa usata per scartare il tr
	scantr();
	
	do{
		//Ricevo puntatore alla transition creata
		temporaryTransition = acquireTransition();
		printf("%d", temporaryTransition->startState);
		if(temporaryTransition->startState!= -1){
			printf("%c", temporaryTransition->readInput);
			printf("%c", temporaryTransition->writeOutput);
			printf("%c", temporaryTransition->shiftTape);
			printf("%d\n", temporaryTransition->nextState);

			//Fast check of conversion from ASCII to number, in order to insert in the right index
			tempchar = (int) temporaryTransition->readInput;
			printf("%d\n", tempchar);

			//Creo un singolo puntatore dello stesso di inputCharacters e gli alloco la hashmap
			
		 	printf("%p\n",p );
		 	if(inputCharacters[tempchar]==NULL){
				inputCharacters[tempchar]=(Transition **)calloc(SIZE,sizeof(Transition*));;
			}
            
			hashmapIndex = calculateHashMap(temporaryTransition->startState);
			if(inputCharacters[tempchar][hashmapIndex]==0){
				inputCharacters[tempchar][hashmapIndex]=temporaryTransition;
			}
			else
				//Inserire elemento nella coda e scompare anche l'errore di memoria
				printf("Elemento già inserito in questa posizione: accodare\n");
			printf("printo valore dell'hashmap index: %d\n", hashmapIndex);
			
			printf("Prima del test\n");
			
			printf("Printo valore in inputCharacters: %d\n",inputCharacters[tempchar][hashmapIndex]->startState);
		

		}

	}while(temporaryTransition->startState!= -1);
	free(temporaryTransition);

    

    return 0;
}

Transition *acquireTransition(){
	Transition *transition=NULL;
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
        
        transition=malloc(sizeof(Transition));
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

    		transition->startState = firstState;
    		transition->readInput = in;
    		transition->writeOutput = out;
    		transition->shiftTape = shift;
    		transition->nextState = secondState;
    		transition->prox = NULL;

        }
        else {
        	transition->startState= -1;
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


int calculateHashMap(int stateNumber){
	return stateNumber%256;
}
void scantr(){
	char phantomString[10];
	scanf("%s", phantomString);
	printf("%s\n", phantomString);
}
