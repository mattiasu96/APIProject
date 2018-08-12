#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 10
#define ASCII 256
typedef struct T{
    int startState;
    char readInput;
    char writeOutput;
    int shiftTape;
    int nextState;
    struct T *prox;


} Transition;


// Controlla Strlen come funzione, potrebbe essere utile
typedef struct turing{
	int currentState;
	int tapePosition;
	int remainingSteps;
	char subtapeType;
	char *contentRight;
	char *contentLeft;
	struct turing *prox;
} TM;

Transition *acquireTransition();
void phantomScan();
void inserisciCoda(Transition *element,Transition *position);
int checkMaxStates(Transition *element, int currentMax);
int *acquireAcceptStates(int *NacceptState);
TM *initializeSimulation(char *tape, int numberOfSteps);



int main() {
	char *inputTape;
	TM *headTM=NULL;
	TM *taleTM=NULL;
	//TM *scannerTM=NULL;
    Transition *temporaryTransition=NULL;
    Transition ***inputStatesArray = {NULL};
    Transition ***check = {NULL};
    int maxInputSize;
    int tempchar;
    int tempstate;
    Transition *p=NULL;
    int *acceptStates=NULL;
    int maxInputState=0;
    int numberofAcceptStates=0;
    int currentIndex=MAX;
	int i=0;
    unsigned long int numpassi=0;

    //Stringa usata per scartare il tr
    phantomScan();

    
    inputStatesArray = malloc(sizeof(Transition**)*MAX);
    for (int i = 0; i < currentIndex; ++i)
    {
  		inputStatesArray[i]=NULL;
  		printf("%p",inputStatesArray[i] );
    }
            
    do{
        //Ricevo puntatore alla transition creata
        temporaryTransition = acquireTransition();
        if(temporaryTransition->startState!= -1){
            printf("%d", temporaryTransition->startState);
            printf("%c", temporaryTransition->readInput);
            printf("%c", temporaryTransition->writeOutput);
            printf("%d", temporaryTransition->shiftTape);
            printf("%d\n", temporaryTransition->nextState);

            maxInputState = checkMaxStates(temporaryTransition, maxInputState);
            maxInputSize= maxInputState+1;
            printf("Printo numero di stati max: %d\n", maxInputState);
            printf("Printo dimensiona massima di stati di ingresso di stati max: %d\n", maxInputSize);

            //Fast check of conversion from ASCII to number, in order to insert in the right index
            tempchar = (int) temporaryTransition->readInput;
            // FORSE QUA DEVO CAMBIARE GLI ORDINI, POTREBBE ESSER QUI IL PROBLEMA
            tempstate = temporaryTransition ->startState;
            printf("%d\n",tempstate);
            printf("%d\n", tempchar);
            //ERRORE QUI
            if(maxInputSize>currentIndex){
            	printf("Sto reallocando\n");
            	check = realloc(inputStatesArray, sizeof(Transition**)*(maxInputSize));
            	//FIN QUI HA SENSO
            	if(check!=NULL)
            		inputStatesArray=check;
            	printf("Prima ciclo if\n");
            	//FORSE ALTRO BUG QUI, NON INIZIALIZZO L'ULTIMO!!
            	for(i=currentIndex;i<maxInputSize;i++){
            		printf("Metto a null\n");
					inputStatesArray[i]=NULL;
            	}
            	currentIndex=maxInputSize;
            	printf("Dopo ciclo if\n");


            }
            for (int i = 0; i < currentIndex; ++i)
    		{
  				printf("%p ",inputStatesArray[i] );
    		}
            printf("Prima dell'errore Puntaotre a: %p\n",inputStatesArray[tempstate] );

            if(inputStatesArray[tempstate]==NULL){
            	printf("Dentro if calloc\n");

            	inputStatesArray[tempstate] = calloc(ASCII,sizeof(Transition*));

            }
            printf("Dopo Check if\n");
            printf("Puntaotre a: %p\n",inputStatesArray[tempstate] );


            
            printf("Printo valore del puntatore: %p\n", inputStatesArray[tempstate][tempchar]);
            if(inputStatesArray[tempstate][tempchar]==0){

                inputStatesArray[tempstate][tempchar]=temporaryTransition;
            }
            else{
 				 // BUG QUI
                 printf("Possibile bug nell'accodamento?\n");

                inserisciCoda(temporaryTransition,inputStatesArray[tempstate][tempchar]);
                printf("Elemento già inserito in questa posizione: sto accodando\n");
            }
            
            printf("Prima del test\n");
            p=inputStatesArray[tempstate][tempchar];
            while (p->prox!=NULL){
                
                printf("Printo valore in inputStatesArray: %d\n",p->startState); 
                printf("Printo valore in inputStatesArray: %c\n",p->writeOutput);    
                p = p-> prox;   
            } 
            

        

        }

    }while(temporaryTransition->startState!= -1);
    free(temporaryTransition);


    acceptStates = acquireAcceptStates(&numberofAcceptStates);
    printf("Numero di stati di accettazione: %d\n", numberofAcceptStates);
    for(i=0;i<numberofAcceptStates;i++)
        printf("Valore stato di accettazione i-esimo: %d\n", acceptStates[i]);
    
    scanf("%lu", &numpassi);
    printf("%lu", numpassi);
    phantomScan();
    
    //INIZIO PARTE DI SIMULAZIONE 
    while(scanf("%ms",&inputTape)!=EOF){
    	printf("%s\n",inputTape);
    	printf("%ld\n", strlen(inputTape));
    	headTM = initializeSimulation(inputTape,numpassi);
    	printf("Stato iniziale: %d\n",headTM->currentState);
    	taleTM =headTM;
    	
		free(inputTape);
		free(headTM->contentRight);
		free(headTM);

    }





    return 0;
}

Transition *acquireTransition(){
    Transition *transition=NULL;
    char *start = NULL;
    char *end = NULL;
    char in, out, shift;
    int shiftInt;
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
            switch (shift){
                case 'L':
                    shiftInt = -1;
                    break;
                case 'S':
                    shiftInt = 0;
                    break;
                case 'R':
                    shiftInt = 1;
                    break;
            }
            printf("Valore di shift int: %d\n", shiftInt);
            transition->shiftTape = shiftInt;
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

void phantomScan(){
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
    

    return max;


}
// CONTROLLARE CHE FUNZIONI CORRETTAMENTE
int *acquireAcceptStates(int *NacceptState){
    int *p=NULL;
    int counter=0;
    char *c=NULL;
    int *p2=NULL;


    while(c==NULL || strcmp(c,"max")!=0){
        

        if(c){
            free(c);
            c=NULL;
        }
        scanf("%ms", &c);
        if(strcmp(c,"max")!=0){
            counter++;
            p2 = (int *)realloc(p,sizeof(int)*counter);
            if(p2!=NULL){
                p=p2;
                p[counter-1]=atoi(c);
            }
            else 
                printf("Errore nella realloc\n");
            
            
    }

    }
    if(c){
        free(c);
    }
    *NacceptState = counter;



    return p;

}

TM *initializeSimulation(char *tape, int numberOfSteps){
	TM *p=NULL;
	p=malloc(sizeof(TM));
	p->currentState=0;
	p->tapePosition=0;
	p->remainingSteps=numberOfSteps;
	p->subtapeType='R';
	p->contentLeft=NULL;
	p->contentRight=malloc(sizeof(char)*(strlen(tape)+1));
	p->contentRight[0]='\0';
	strcpy(p->contentRight,tape);
	printf("Printo contenuto di contentRight: %s\n",p->contentRight);
	p->prox=NULL;
	return p;
}

