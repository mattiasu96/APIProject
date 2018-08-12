#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 10
#define ASCII 256
#define acceptNumber 5
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



int main() {
    Transition *temporaryTransition=NULL;
    Transition ***inputStatesArray = {NULL};
    Transition ***check = {NULL};
    int maxInputSize;
    int tempchar;
    int tempstate;
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

            maxInputState = checkMaxStates(temporaryTransition, maxInputState);
            maxInputSize= maxInputState+1;
            
            tempchar = (int) temporaryTransition->readInput;
            tempstate = temporaryTransition ->startState;
       
            if(maxInputSize>currentIndex){
                printf("Sto reallocando\n");
                check = realloc(inputStatesArray, sizeof(Transition**)*(maxInputSize));
                if(check!=NULL)
                    inputStatesArray=check;
             
                for(i=currentIndex;i<maxInputSize;i++){
                    inputStatesArray[i]=NULL;
                }
                currentIndex=maxInputSize;


            }
            

            if(inputStatesArray[tempstate]==NULL){

                inputStatesArray[tempstate] = calloc(ASCII,sizeof(Transition*));

            }
           
            if(inputStatesArray[tempstate][tempchar]==0){
                inputStatesArray[tempstate][tempchar]=temporaryTransition;
            }
            else{
                inserisciCoda(temporaryTransition,inputStatesArray[tempstate][tempchar]);
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
    /*free(acceptStates);
    free(inputStatesArray[15][97]);
    free(inputStatesArray[15]);
    free(inputStatesArray);*/



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