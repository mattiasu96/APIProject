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




Transition *acquireTransition();
int calculateHashMap(int stateNumber);



int main() {
	Transition *temporaryTransition=NULL;
	char phantomString[10];
	//int arraySize = 256;
	Transition **inputCharacters[256] = {NULL};
	int tempchar;
	int hashmapIndex;
	//arrayOfTransitionPointer tempPointer;

	//Stringa usata per scartare il tr
	scanf("%s", phantomString);
	printf("%s\n", phantomString);
	//NB PROVA A INIZIALIZZARE TEMPORARY TRANSITION A NULL! PRIMA HO FATTO UN CONTROLLO SU IF SU UN PUNTATORE NON ANCORA INIZIALIZZATO! 
	//PUO' ESSERE QUELLO IL PROBLEMA DEL SEGMENTATION FAULT
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
			Transition **p=NULL;
		 	printf("%p\n",p );
			p= (Transition **)calloc(256,sizeof(Transition*));

			//Creo il puntatore alla singola struct Transition
		 	Transition *p2=NULL;
			p2=temporaryTransition;

		 	//Qui metto il puntatore della hashmap uguale a quello che punta alla singola struct, così ottengo il riferimento ad essa.
		 	//L'indice è dato dalla funzione di hashing
			hashmapIndex = calculateHashMap(p2->startState);
			printf("%d\n", hashmapIndex);
			p[hashmapIndex]=p2;
			printf("Prima del test\n");
			//printf("%d\n",p[0]->startState );

			//Qui inserisco il il puntatore alla hashmap i-esima nel inputCharacter i-esimo. La cella dove inserirla mi è data dalla lettera di ingresso.
			// ERRORE: NON STO GESTENDO I DUE INDICI! COSI' STO DICENDO SOLO INDICE DI INPUT CHAR, MA POI NON SPECIFICO QUELLO DELL'HASHMAP
			inputCharacters[tempchar]=p;
			printf("%d\n",inputCharacters[tempchar][hashmapIndex]->startState);
		

		}

	}while(temporaryTransition->startState!= -1);


    

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
