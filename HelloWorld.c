#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 10
#define ASCII 75

char accettazione = 'N';
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
TM *iterateListTM(TM *headTM,Transition ***transizioni, int maxInputState,int *listaAccettazione, int dimensoniLista);
void lastCheck(TM *headTM,Transition ***transizioni,int maxInputState,int *listaAccettazione,int dimensoniListaAcc);
TM *cleanAll(TM *headTM);


int main() {
    char *inputTape;
    TM *headTM=NULL;
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
    unsigned int numpassi=0;
    unsigned int counterPassi=0;

    //Stringa usata per scartare il tr
    phantomScan();

    
    inputStatesArray = malloc(sizeof(Transition**)*MAX);
    for (int i = 0; i < currentIndex; ++i)
    {
        inputStatesArray[i]=NULL;
    }
            
    do{
        //Ricevo puntatore alla transition creata
        temporaryTransition = acquireTransition();
        if(temporaryTransition->startState!= -1){
    

            maxInputState = checkMaxStates(temporaryTransition, maxInputState);
            maxInputSize= maxInputState+1;
           
            //Fast check of conversion from ASCII to number, in order to insert in the right index
            tempchar = (int) (temporaryTransition->readInput)-48;
            // FORSE QUA DEVO CAMBIARE GLI ORDINI, POTREBBE ESSER QUI IL PROBLEMA
            tempstate = temporaryTransition ->startState;
         
            //ERRORE QUI
            if(maxInputSize>currentIndex){
                check = realloc(inputStatesArray, sizeof(Transition**)*(maxInputSize));
                //FIN QUI HA SENSO
                if(check!=NULL)
                    inputStatesArray=check;
                //FORSE ALTRO BUG QUI, NON INIZIALIZZO L'ULTIMO!!
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

    
    scanf("%u", &numpassi);
    phantomScan();

    
    //INIZIO PARTE DI SIMULAZIONE 
    while(scanf("%ms",&inputTape)!=EOF){
        //INIZIALIZZAZIONE
        accettazione='N';
        counterPassi=0;
        headTM = initializeSimulation(inputTape);
        free(inputTape);

        //SIMULAZIONE
        //QUI DEVO METTERE UN WHILE AMPIO SU FINE COMPUTAZIONI O LISTA VUOTA O ACCETTAZIONE TROVATA.
        while(counterPassi<numpassi && accettazione== 'N' && headTM!=NULL){
        headTM = iterateListTM(headTM,inputStatesArray,maxInputState,acceptStates,numberofAcceptStates);
        
        //INSERIRE INCREMENTO CONTATORE 
        counterPassi++;
    }
    //INSERIRE LAST CHECK QUI

    if(headTM==NULL && accettazione=='N'){
        accettazione='0';
    }
    else
        if(accettazione=='N'){
            //DICHIARARE IL FUNZIONAMENTO DI lastCheck
            lastCheck(headTM,inputStatesArray,maxInputState,acceptStates,numberofAcceptStates);
        }
    if(accettazione=='N'){
        accettazione='0';
        printf("%c\n", accettazione);
    }
    else
        printf("%c\n", accettazione);
    //PULIRE TUTTO QUI
    if(headTM!=NULL){
        headTM= cleanAll(headTM);
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
        fflush ( stdout);
        scanf("%ms", &start);
        
        transition=malloc(sizeof(Transition));
        if(strcmp(start, "acc") != 0) {
            if ( end) {
                free ( end);
                end = NULL;
            }
            fflush ( stdout);
            scanf(" %c %c %c %ms", &in, &out, &shift, &end);
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
        max=element->nextState;
    

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
    //Inserire memcpy
    strcpy(p->tape,tape);
    p->prox=NULL;
    p->prec=NULL;
    return p;
}


TM *iterateListTM(TM *headTM,Transition ***transizioni,int maxInputState,int *listaAccettazione,int dimensoniListaAcc){
    int blankLenght = 6000;
    TM *scannerTM = NULL;
    TM *newTM = NULL;
    scannerTM =headTM;
    Transition *p=NULL;
    int i=0;
    int rimossoInTesta=0;
    while(scannerTM!=NULL && accettazione=='N'){
            rimossoInTesta=0;
            int tempchar =(int) (scannerTM->tape[scannerTM->tapePosition])-48;
            //Checko se sto accedendo a transizioni esistenti, altrimenti verifico se è da terminare
            if(transizioni[scannerTM->currentState]!=NULL && transizioni[scannerTM->currentState][tempchar]!=NULL){
                p=transizioni[scannerTM->currentState][tempchar];
                while(p->prox!=NULL){
                    newTM = malloc(sizeof(TM));
                    //Inserisco i valori
                    newTM->currentState = p->nextState;
                    //QUI COPIO LA STRINGA
                    newTM->tapesize = scannerTM->tapesize;
                    newTM->tapePosition=scannerTM->tapePosition;
                    newTM->tape=malloc(sizeof(char)*((scannerTM->tapesize)+1));
                    memcpy(newTM->tape,scannerTM->tape,((scannerTM->tapesize)+1));
                    newTM->tape[newTM->tapePosition] = p->writeOutput;

                    //Qui è da inserire il check per la realloc
                    //CHECK DESTRO
                    if((newTM->tapePosition)+(p->shiftTape)==newTM->tapesize){
                        newTM->tape=realloc(newTM->tape,blankLenght+1+newTM->tapesize);
                        //memcpy(&newTM->tape[newTM->tapesize],blank,blankLenght+1);
                        memset(&newTM->tape[newTM->tapesize],'_',blankLenght);
                        newTM->tapesize=newTM->tapesize+blankLenght;
                        newTM->tape[newTM->tapesize]='\0';


                    }
                    //CHECK A SINISTRA
                    if(newTM->tapePosition+p->shiftTape==-1){
                        newTM->tape=realloc(newTM->tape,newTM->tapesize+blankLenght+1);
                        memmove(&newTM->tape[blankLenght],newTM->tape,newTM->tapesize+1);
                        //memcpy(newTM->tape,blank,blankLenght);
                        memset(newTM->tape,'_',blankLenght);
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
                scannerTM->tape[scannerTM->tapePosition] = p->writeOutput;
                //ESTENSIONE A DESTRA
                if(scannerTM->tapePosition+p->shiftTape==scannerTM->tapesize){
                        scannerTM->tape=realloc(scannerTM->tape,scannerTM->tapesize+blankLenght+1);
                        //memcpy(&scannerTM->tape[scannerTM->tapesize],blank,blankLenght+1);
                        memset(&scannerTM->tape[scannerTM->tapesize],'_',blankLenght);
                        scannerTM->tapesize=scannerTM->tapesize+blankLenght;
                        scannerTM->tape[scannerTM->tapesize]='\0';                        


                    }
                    //ESTENSIONE A SINISTRA
                if(scannerTM->tapePosition+p->shiftTape==-1){
                        scannerTM->tape=realloc(scannerTM->tape,scannerTM->tapesize+blankLenght+1);

                        memmove(&scannerTM->tape[blankLenght],scannerTM->tape,scannerTM->tapesize+1);

                        //memcpy(scannerTM->tape,blank,blankLenght);
                        memset(scannerTM->tape,'_',blankLenght);

                        scannerTM->tapesize=scannerTM->tapesize+blankLenght;
                        scannerTM->tapePosition=scannerTM->tapePosition+blankLenght;


                }


                scannerTM->tapePosition = scannerTM->tapePosition+p->shiftTape;
                p=NULL;


            }else {
                //QUI E' DA INSERIRE L'EVENTUALE CHECK PER ACCETTAZIONE O STATO POZZO (NON HO PIU' TRANSIZIONI)
                for(i=0;i<dimensoniListaAcc;i++){
                    //RICERCA ACCETTAZIONE
                    if(scannerTM->currentState==listaAccettazione[i]){
                        accettazione='1';
                        break;
                    }

                }
                if(accettazione=='N'){
                    //Eliminazione in testa
                    if(scannerTM->prec==NULL){
                        headTM=scannerTM->prox;
                        if(headTM!=NULL){
                            headTM->prec=NULL;

                        }
                        free(scannerTM->tape);
                        free(scannerTM);
                        scannerTM=headTM;
                        rimossoInTesta=1;

                    }
                    else
                        if(scannerTM->prox==NULL){

                            scannerTM=scannerTM->prec;
                            free(scannerTM->prox->tape);
                            free(scannerTM->prox);
                            scannerTM->prox=NULL;


                        }
                        else{
                            scannerTM=scannerTM->prec;
                            scannerTM->prox=scannerTM->prox->prox;
                            //FREE DEL NODO
                            free(scannerTM->prox->prec->tape);
                            free(scannerTM->prox->prec);
                            scannerTM->prox->prec=scannerTM;
                            }
                        }




            }
            if(rimossoInTesta!=1){
            scannerTM=scannerTM->prox;
            }   

        }



    return headTM;
}

void lastCheck(TM *headTM,Transition ***transizioni,int maxInputState,int *listaAccettazione,int dimensoniListaAcc){
    TM *scannerTM=NULL;
    scannerTM=headTM;
    int i=0;
    while(scannerTM!=NULL && accettazione!='1'){
            int tempchar =(int) (scannerTM->tape[scannerTM->tapePosition])-48;
            //Checko se sto accedendo a transizioni esistenti, altrimenti verifico se è da terminare
            if(transizioni[scannerTM->currentState]!=NULL && transizioni[scannerTM->currentState][tempchar]!=NULL){
                accettazione='U';


            }
            else
                for(i=0;i<dimensoniListaAcc;i++){
                    //RICERCA ACCETTAZIONE
                    if(scannerTM->currentState==listaAccettazione[i]){
                        accettazione='1';
                        break;
                    }

                }
            scannerTM=scannerTM->prox;


        }




}

TM *cleanAll(TM *headTM){
    TM *scannerTM = NULL;
    scannerTM=headTM;
    while(headTM!=NULL){
        headTM=scannerTM->prox;
        free(scannerTM->tape);
        free(scannerTM);
        scannerTM=headTM;
    }
    return headTM;
}


