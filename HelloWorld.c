#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 10
#define ASCII 128
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
	int tapesize;
	int tapePosition;
	char *tape;
	struct turing *prox;
	struct turing *prec;
} TM;

Transition *acquireTransition();
void phantomScan();
void inserisciCoda(Transition *element,Transition *position);
int checkMaxStates(Transition *element, int currentMax);
int *acquireAcceptStates(int *NacceptState);
TM *initializeSimulation(char *tape);
TM *iterateListTM(TM *headTM,Transition ***transizioni, int maxInputState);




int main() {
	char *inputTape;
	TM *headTM=NULL;
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
    unsigned int numpassi=0;
    unsigned int counterPassi=0;

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
    
    scanf("%u", &numpassi);
    printf("%u", numpassi);
    phantomScan();

    
    //INIZIO PARTE DI SIMULAZIONE 
    while(scanf("%ms",&inputTape)!=EOF){
    	printf("Tape originale: %s\n",inputTape);
    	printf("%ld\n", strlen(inputTape));
    	//INIZIALIZZAZIONE
    	headTM = initializeSimulation(inputTape);
    	printf("Stato iniziale: %d\n",headTM->currentState);
    	printf("Printo contenuto del tape copiato inizialmente:%s\n",headTM->tape);
    	printf("Dimensioni del mio array: %d\n", headTM->tapesize);
		free(inputTape);

		//SIMULAZIONE
		//QUI DEVO METTERE UN WHILE AMPIO SU FINE COMPUTAZIONI O LISTA VUOTA O ACCETTAZIONE TROVATA.
		while(counterPassi<numpassi){
		headTM = iterateListTM(headTM,inputStatesArray,maxInputState);
		
		//INSERIRE INCREMENTO CONTATORE 
		counterPassi++;
	}



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

TM *initializeSimulation(char *tape){
	TM *p=NULL;
	p=malloc(sizeof(TM));
	p->currentState=0;
	p->tapePosition=0;
	p->tapesize=strlen(tape);
	p->tape=malloc(sizeof(char)*((p->tapesize)+1));
	printf("Dimensione inizializzato: %d\n",p->tapesize);
	//Inserire memcpy
	strcpy(p->tape,tape);
	printf("Strlen inizializzato: %d\n",p->tapesize);
	printf("Posizione testina inizializzato: %d\n",p->tapePosition);
	printf("Contenuto tape inizializzato: %s\n",p->tape);



	p->prox=NULL;
	p->prec=NULL;
	return p;
}


TM *iterateListTM(TM *headTM,Transition ***transizioni,int maxInputState){
	char blank[]="___";
	int blankLenght = strlen(blank);
	TM *scannerTM = NULL;
	TM *newTM = NULL;
	scannerTM =headTM;
	Transition *p=NULL;
	while(scannerTM!=NULL){
			int tempchar =(int) scannerTM->tape[scannerTM->tapePosition];
			//Checko se sto accedendo a transizioni esistenti, altrimenti verifico se è da terminare
			if(scannerTM->currentState<=maxInputState && transizioni[scannerTM->currentState]!=NULL && transizioni[scannerTM->currentState][tempchar]!=NULL){
				p=transizioni[scannerTM->currentState][tempchar];
				printf("Stato prossimo della prima transizione letta %d\n", p->nextState);
				while(p->prox!=NULL){
					newTM = malloc(sizeof(TM));
					//Inserisco i valori
					newTM->currentState = p->nextState;
					//QUI COPIO LA STRINGA
					newTM->tapesize = scannerTM->tapesize;
					newTM->tapePosition=scannerTM->tapePosition;
					// PROBABILMENE MANCA INIZIALIZZAZIONE DI TAPE POSITION. CONTROLLA CHE NELLA COPIA ASSEGNO TUTTE LEVARIABILI!!!!!!
					newTM->tape=malloc(sizeof(char)*((scannerTM->tapesize)+1));
					memcpy(newTM->tape,scannerTM->tape,((scannerTM->tapesize)+1));
					newTM->tape[newTM->tapePosition] = p->writeOutput;

					//Qui è da inserire il check per la realloc
					//CHECK DESTRO
					if((newTM->tapePosition)+(p->shiftTape)==newTM->tapesize){
						newTM->tape=realloc(newTM->tape,blankLenght+1+newTM->tapesize);
						memcpy(&newTM->tape[newTM->tapesize],blank,blankLenght+1);
						newTM->tapesize=newTM->tapesize+blankLenght;
						printf("Sforo gli indici\n");


					}
					if(newTM->tapePosition+p->shiftTape==-1){
						newTM->tape=realloc(newTM->tape,newTM->tapesize+blankLenght+1);
						memmove(&newTM->tape[blankLenght],newTM->tape,newTM->tapesize+1);
						memcpy(newTM->tape,blank,blankLenght);
						newTM->tapesize=newTM->tapesize+blankLenght;
						newTM->tapePosition=newTM->tapePosition+blankLenght;


				}

					newTM->tapePosition = newTM->tapePosition+p->shiftTape;
					//Ora devo inserire in testa la nuova copia
					newTM->prox = headTM;
					newTM->prec =NULL;
					headTM->prec = newTM;
					headTM = newTM;
					p=p->prox;
					}
					//Inserisco i valori
				scannerTM->currentState = p->nextState;
				printf("Cambiato stato: %d\n", scannerTM->currentState);
				scannerTM->tape[scannerTM->tapePosition] = p->writeOutput;
				printf("Contenuto nastro dopo modifica: %s\n",scannerTM->tape);
				//ESTENSIONE A DESTRA
				if(scannerTM->tapePosition+p->shiftTape==scannerTM->tapesize){
						scannerTM->tape=realloc(scannerTM->tape,scannerTM->tapesize+blankLenght+1);
						memcpy(&scannerTM->tape[scannerTM->tapesize],blank,blankLenght+1);

						scannerTM->tapesize=scannerTM->tapesize+blankLenght;
						printf("Sforo gli indici\n");
						int i=0;
						for(i=0;i<scannerTM->tapesize;i++){
							printf("Printo carattere: %c\n", scannerTM->tape[i]);
						}


					}
					//ESTENSIONE A SINISTRA
				if(scannerTM->tapePosition+p->shiftTape==-1){
						scannerTM->tape=realloc(scannerTM->tape,scannerTM->tapesize+blankLenght+1);
						printf("Contenuto nastro dopo realloc: %s\n",scannerTM->tape);

						memmove(&scannerTM->tape[blankLenght],scannerTM->tape,scannerTM->tapesize+1);
						printf("Contenuto nastro dopo memmove: %s\n",scannerTM->tape);

						memcpy(scannerTM->tape,blank,blankLenght);
						scannerTM->tapesize=scannerTM->tapesize+blankLenght;
						scannerTM->tapePosition=scannerTM->tapePosition+blankLenght;


				}


				scannerTM->tapePosition = scannerTM->tapePosition+p->shiftTape;
				printf("Contenuto nastro dopo modifica: %s\n",scannerTM->tape);

				printf("Posizione testina dopo modifica: %d\n",scannerTM->tapePosition);
				printf("strlen del nastro: %d\n",scannerTM->tapesize);

				p=NULL;


			}else {
				printf("Sono nel caso di transizioni finite\n");
				//QUI E' DA INSERIRE L'EVENTUALE CHECK PER ACCETTAZIONE O STATO POZZO (NON HO PIU' TRANSIZIONI)
				//POI E' DA GESTIRE LA FREE E RICONCATENAMENTO

			}
			scannerTM=scannerTM->prox;

		}



	return headTM;
}
