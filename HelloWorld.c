#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 5
#define SIZE 256
#define acceptNumber 5
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
void inserisciCoda(Transition *element,Transition *position);
int checkMaxStates(Transition *element, int currentMax);
int *acquireAcceptStates();



int main() {
	Transition *temporaryTransition=NULL;
	Transition **inputCharacters[256] = {NULL};
	int tempchar;
	int hashmapIndex;
	Transition *p=NULL;
	int *acceptStates=NULL;
	int numberOfStates=0;

	//Stringa usata per scartare il tr
	scantr();
	
	do{
		//Ricevo puntatore alla transition creata
		temporaryTransition = acquireTransition();
		if(temporaryTransition->startState!= -1){
			printf("%c", temporaryTransition->readInput);
			printf("%c", temporaryTransition->writeOutput);
			printf("%c", temporaryTransition->shiftTape);
			printf("%d\n", temporaryTransition->nextState);

			numberOfStates = checkMaxStates(temporaryTransition, numberOfStates);
			printf("Printo numero di stati max: %d\n", numberOfStates);
			//Fast check of conversion from ASCII to number, in order to insert in the right index
			tempchar = (int) temporaryTransition->readInput;
			printf("%d\n", tempchar);

			//Creo un singolo puntatore dello stesso di inputCharacters e gli alloco la hashmap
			
		 	if(inputCharacters[tempchar]==NULL){
				inputCharacters[tempchar]=(Transition **)calloc(SIZE,sizeof(Transition*));;
			}
            
			hashmapIndex = calculateHashMap(temporaryTransition->startState);
			if(inputCharacters[tempchar][hashmapIndex]==0){
				inputCharacters[tempchar][hashmapIndex]=temporaryTransition;
			}
			else{
				//Inserire elemento nella coda e scompare anche l'errore di memoria
				inserisciCoda(temporaryTransition,inputCharacters[tempchar][hashmapIndex]);
				printf("Elemento già inserito in questa posizione: sto accodando\n");
			}
			printf("printo valore dell'hashmap index: %d\n", hashmapIndex);
			
			printf("Prima del test\n");
			p=inputCharacters[tempchar][hashmapIndex];
			while (p->prox!=NULL){
				
				printf("Printo valore in inputCharacters: %d\n",p->startState);	
				printf("Printo valore in inputCharacters: %c\n",p->writeOutput);	
				p = p-> prox;	
			} 
			
			
		

		}

	}while(temporaryTransition->startState!= -1);
	free(temporaryTransition);


	acceptStates = acquireAcceptStates();

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

void inserisciCoda(Transition *element,Transition *position){
	Transition *scanner = NULL;
	scanner = position;
	while(scanner->prox!=NULL){
		scanner=scanner->prox;
	}
	scanner->prox = element;


}

int checkMaxStates(Transition *element,int currentMax){
	int max=currentMax;

	if(max<element->startState)
		max = element->startState;
	if(max<element->nextState)
		max = element->nextState;

	return max;


}

int *acquireAcceptStates(){
	int *p=NULL;
	int counter=0;
	int counter2=1;
	int number=0;
	char *c=NULL;
	

  	p=malloc(sizeof(int)*acceptNumber);


	while(c==NULL || strcmp(c,"max")!=0){
		if(c){
			free(c);
			c=NULL;
		}
		scanf("%ms", &c);
		if(strcmp(c,"max")!=0){
		number=atoi(c);
		p[counter]=number;
		counter++;
		if(counter>acceptNumber){
			p=realloc(p,sizeof(int)*acceptNumber+counter2);
			counter2++;
		}
		}

	}
	free(c);

	return p;

}