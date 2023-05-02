#include <stdio.h>
#include <stdlib.h>
#include <string.h> //Funzioni stringa
#include <stdbool.h> //Tipo booleano

#define MAXSTRINGSIZE 50 //Dimensione massima stringhe

//Structs
struct studente{
    char matricola[MAXSTRINGSIZE]; //Matricola dello studente
    struct libro* primoLibro; //Testa della lista dei libri in possesso di questo studente
    struct studente* studenteSuccessivo; //Collegamento allo studente successivo
};

struct libro{
    char nome[MAXSTRINGSIZE]; //Nome libro
    char possessore[MAXSTRINGSIZE]; //Matricola del possessore (o libreria)
    struct libro* libroSuccessivo; //Collegamento al libro successivo
};

struct richiesta{
    bool tipoRichiesta; //Tipo di richiesta, 0 = Richiedi libro; 1 = Restituisci libro
    char nomeLibro[MAXSTRINGSIZE]; //Nome del libro da restituire/prendere in prestito
    char matricola[MAXSTRINGSIZE]; //Matricola che ha fatto la richiesta
    struct richiesta* richiestaSuccessiva; //Collegamento alla richiesta successiva
};

//Dichiarazione funzioni

//Libri
struct libro* inserisciPrimoLibro(char nome[], char possessore[]); //Inserisce il primo libro nella lista di uno studente
void inserisciLibro(struct libro* testa, char nome[], char possessore[]); //Inserisce un libro nella lista di uno studente
struct libro* trovaLibro(struct libro* testa, char nome[], char possessore[]); //Trova un libro nella lista di uno studente e lo restituisce
struct libro* rimuoviLibro(struct libro* testa, char nome[]); //Rimuove un libro dalla lista di uno studente
void stampaListaLibri(struct libro* testa); //Stampa la lista dei libri di uno studente
struct libro* creaLibreria(int numeroLibri); //Inizializzazione array libreria
void stampaLibreria(); //Stampa l'array libreria
bool libroPresente(struct libro* testa, char nome[]); //Controlla se un libro è nella lista dei libri di uno studente
bool libroPresenteInLibreria(char nome[]); //Controlla se un libro è nell' array libreria
int trovaLibroId(char nome[], char possessore[]); //Cerca l'id di un particolare libro dell'array della libreria e ne restituisce l'indice

//Studenti
struct studente* inserisciPrimoStudente(char matricola[]); //Inserisce il primo studente nella lista studenti
void inserisciStudente(struct studente* testa, char matricola[]); //Inserisce studente nella lista studenti
struct studente* trovaStudente(struct studente* testa, char matricola[]); //Trova uno studente e lo restituisce

//Richieste
struct richiesta* inserisciPrimaRichiesta(bool tipo, char matricola[], char nomeLibro[]); //Inserisce prima richiesta nella lista richieste
void inserisciRichiesta(struct richiesta* testa, bool tipo, char matricola[], char nomeLibro[]); //Inserisce una richiesta nella lista richieste
void stampaListaRichieste(struct richiesta* testa); //Stampa la lista delle richieste
struct richiesta* rimuoviRichiesta(struct richiesta* testa, struct richiesta* richiesta); //Elimina richiesta dalla lista delle richieste
struct richiesta* richiestaTipo1(struct richiesta* testa, struct richiesta* richiesta); //Prova a soddisfare una richiesta di tipo 0, inserimento
struct richiesta* richiestaTipo2(struct richiesta* testa, struct richiesta* richiesta); //Prova a soddisfare una richiesta di tipo 1, restituzione
struct richiesta* soddisfaRichieste(struct richiesta* testa, struct richiesta* richiesta); //Discrimina tra i 2 tipi di richieste
bool richiestaPresente(struct richiesta* testa, bool tipoRichiesta, char nomeLibro[], char matricola[]); //Controlla se una certa richiesta è presente nella lista delle richieste



//Variabili globali

struct studente* testaStudenti = NULL; //Primo studente della lista degli studenti
int numeroLibri = 15; //Numero dei libri nella libreria
struct libro* libreria; //Puntatore all'array della libreria



//Funzioni

//Libri
struct libro* inserisciPrimoLibro(char nome[], char possessore[]){

    //Inserimento primo elemento nella lista

    struct libro* nuovoLibro;

    //Alloca memoria al nuovo nodo
    nuovoLibro = (struct libro*)malloc(sizeof(struct libro));
    //La testa della lista sarà proprio questo nodo
    //Il nuovo nodo, essendo l'unico punta a null
    nuovoLibro->libroSuccessivo = NULL;
    //Inserisco data nel nuovo nodo
    strcpy(nuovoLibro->nome, nome);
    strcpy(nuovoLibro->possessore, possessore);

    //Restituisce testa della lista se avevo inserito il primo nodo
    return nuovoLibro;

}

void inserisciLibro(struct libro* testa, char nome[], char possessore[]){

    //Inserimento in fondo alla lista

    struct libro* nuovoLibro;
    struct libro* temp;

    //Alloca memoria al nuovo nodo
    nuovoLibro = (struct libro*)malloc(sizeof(struct libro));

    //Inserisco puntatore testa in un puntatore temporaneo (per non perdere il valore della testa)
    temp = testa;
    //Il nuovo nodo è messo in fondo quindi punta a null
    nuovoLibro->libroSuccessivo = NULL;

    //Scorri lista finchè non arrivo all'ultimo elemento della lista (quello che punta a null)
    while(temp->libroSuccessivo != NULL){
        //Scorri lista
        temp=temp->libroSuccessivo;
    }
    //Il nuovo nodo viene collegato al precedentemente ultimo nodo della lista
    temp->libroSuccessivo=nuovoLibro;
    //Inserisco data nel nuovo nodo
    strcpy(nuovoLibro->nome, nome);
    strcpy(nuovoLibro->possessore, possessore);

}

struct libro* trovaLibro(struct libro* testa, char nome[], char possessore[]){

    //Metto la testa in un puntatore temporaneo per non perdere il valore della testa
    struct libro* tmp = testa;


    //Scorro la lista fino alla sua terminazione
    while(tmp != NULL){
        //Libro trovato, lo restituisco
        if(!strcmp(tmp->nome, nome) && !strcmp(tmp->possessore, possessore)){
            return tmp;
        }
        //Scorro la lista
        tmp = tmp->libroSuccessivo;
    }

    return tmp;

};

struct libro* rimuoviLibro(struct libro* testa, char nome[]){

    struct libro* temp = testa;
    struct libro* nuovaTesta = NULL;
    struct libro* precedente = NULL;

    //Se la testa è il nodo da eliminare
    if (temp != NULL && !strcmp(temp->nome, nome)){
        nuovaTesta = temp->libroSuccessivo;   //Cambia la testa con il nodo successivo
        return nuovaTesta; //Termina
    }

    //Cerco il nodo da cancellare
    while (temp != NULL && strcmp(temp->nome, nome)){
        precedente = temp; //Salvo il precedente per collegare il precedente del nodo da eliminare col suo successivo
        temp = temp->libroSuccessivo; //Scorri lista
    }

    //Se il nodo non è trovato
    if (temp == NULL){
            return NULL;
    }

    //Collego il precedente del nodo da eliminare col suo successivo
    precedente->libroSuccessivo = temp->libroSuccessivo;

    return testa;

}

void stampaListaLibri(struct libro* testa){

    //Metto la testa in un puntatore temporaneo per non perdere il valore della testa
    struct libro* tmp = testa;
    int c = 1;

    //Scorro la lista fino alla sua terminazione
    while(tmp != NULL){
        printf("Libro[%d]: %s, possessore: %s\n", c++, tmp->nome, tmp->possessore);
        //Scorro la lista
        tmp = tmp->libroSuccessivo;
    }

}

struct libro* creaLibreria(int numeroLibri){

    struct libro *libreria;
    libreria = malloc(sizeof(struct libro)*numeroLibri);

    //Popola libreria
    strcpy(libreria[0].nome, "Moby dick");
    strcpy(libreria[1].nome, "1984");
    strcpy(libreria[2].nome, "Il Decamerone");
    strcpy(libreria[3].nome, "Odissea");
    strcpy(libreria[4].nome, "Guerra e pace");
    strcpy(libreria[5].nome, "A sangue freddo");
    strcpy(libreria[6].nome, "La coscienza di Zeno");
    strcpy(libreria[7].nome, "Faust");
    strcpy(libreria[8].nome, "La Divina Commedia");
    strcpy(libreria[9].nome, "Furore");
    strcpy(libreria[10].nome, "Ulisse");
    strcpy(libreria[11].nome, "Lolita");
    strcpy(libreria[12].nome, "Il piccolo principe");
    strcpy(libreria[13].nome, "I miserabili");
    strcpy(libreria[14].nome, "I promessi sposi");

    //Imposta il campo possessore dei libri a "Libreria"
    int i;
    for(i = 0; i < numeroLibri; i++){
        strcpy(libreria[i].possessore, "Libreria");
    }

    return libreria;

};

void stampaLibreria(){
    int i;
    for(i = 0; i<numeroLibri; i++){
        printf("Libro[%d]: %s, possessore: %s\n", i+1, libreria[i].nome, libreria[i].possessore);
    }

}

bool libroPresente(struct libro* testa, char nome[]){

    //Metto la testa in un puntatore temporaneo per non perdere il valore della testa
    struct libro* tmp = testa;

    //Scorro la lista fino alla sua terminazione
    while(tmp != NULL){
        //Libro trovato
        if(!strcmp(tmp->nome, nome)){
            return true;
        }
        //Scorro la lista
        tmp = tmp->libroSuccessivo;
    }

    return false; //Libro non trovato

}

bool libroPresenteInLibreria(char nome[]){

    //Scorro libreria
    int i;
    for(i = 0; i<numeroLibri; i++){
        //Libro trovato
        if(!strcmp(libreria[i].nome, nome)){
            return true;
        }
    }

    return false; //Libro non trovato

}

int trovaLibroId(char nome[], char possessore[]){
    int i;
    for(i = 0; i < numeroLibri; i++){
        if(!strcmp(libreria[i].nome, nome) && !strcmp(libreria[i].possessore, possessore)){
            return i; //Libro trovato, restituisco la sua posizione nell'array libreria
        }
    }

    return -1; //Libro non trovato

}


//Studenti
struct studente* inserisciPrimoStudente(char matricola[]){

    //Inserimento primo elemento nella lista

    struct studente* nuovoStudente;

    //Alloca memoria al nuovo nodo
    nuovoStudente = (struct studente*)malloc(sizeof(struct studente));
    //La testa della lista sarà proprio questo nodo
    //Il nuovo nodo, essendo l'unico punta a null
    nuovoStudente->studenteSuccessivo = NULL;
    //Inserisco data nel nuovo nodo
    strcpy(nuovoStudente->matricola, matricola);

    //Restituisce testa della lista se avevo inserito il primo nodo
    return nuovoStudente;

}

void inserisciStudente(struct studente* testa, char matricola[]){

    //Inserimento in fondo alla lista

    struct studente* nuovoStudente;
    struct studente* temp;

    //Alloca memoria al nuovo nodo
    nuovoStudente = (struct studente*)malloc(sizeof(struct studente));

    //Inserisco puntatore testa in un puntatore temporaneo (per non perdere il valore della testa)
    temp = testa;
    //Il nuovo nodo è messo in fondo quindi punta a null
    nuovoStudente->studenteSuccessivo = NULL;

    //Scorri lista finchè non arrivo all'ultimo elemento della lista (quello che punta a null)
    while(temp->studenteSuccessivo != NULL){
        //Scorri lista
        temp=temp->studenteSuccessivo;
    }
    //Il nuovo nodo viene collegato al precedentemente ultimo nodo della lista
    temp->studenteSuccessivo=nuovoStudente;
    //Inserisco data nel nuovo nodo
    strcpy(nuovoStudente->matricola, matricola);

}

struct studente* trovaStudente(struct studente* testa, char matricola[]){

    struct studente* ret = NULL; //Valore di return
    struct studente* tmp = testa;

    //Finchè non raggiungo la fine della lista o trovo lo studente
    while(tmp != NULL && ret == NULL){
        if(!strcmp(matricola, tmp->matricola)){
            ret = tmp; //Studente trovato, metto il suo puntatore in ret
        }
        //Scorro lista
        tmp = tmp->studenteSuccessivo;
    }

    return ret;

};


//Richieste
struct richiesta* inserisciPrimaRichiesta(bool tipo, char matricola[], char nomeLibro[]){

    //Inserimento primo elemento nella lista

    struct richiesta* nuovaRichiesta;

    //Alloca memoria al nuovo nodo
    nuovaRichiesta = (struct richiesta*)malloc(sizeof(struct richiesta));
    //La testa della lista sarà proprio questo nodo
    //Il nuovo nodo, essendo l'unico punta a null
    nuovaRichiesta->richiestaSuccessiva = NULL;
    //Inserisco data nel nuovo nodo
    strcpy(nuovaRichiesta->nomeLibro, nomeLibro);
    strcpy(nuovaRichiesta->matricola, matricola);
    nuovaRichiesta->tipoRichiesta = tipo;

    //Restituisce testa della lista se avevo inserito il primo nodo
    return nuovaRichiesta;

};

void inserisciRichiesta(struct richiesta* testa, bool tipo, char matricola[], char nomeLibro[]){

    //Inserimento in fondo alla lista

    struct richiesta* nuovaRichiesta;
    struct richiesta* temp;

    //Alloca memoria al nuovo nodo
    nuovaRichiesta = (struct richiesta*)malloc(sizeof(struct richiesta));

    //Inserisco puntatore testa in un puntatore temporaneo (per non perdere il valore della testa)
    temp = testa;
    //Il nuovo nodo è messo in fondo quindi punta a null
    nuovaRichiesta->richiestaSuccessiva = NULL;

    //Scorri lista finchè non arrivo all'ultimo elemento della lista (quello che punta a null)
    while(temp->richiestaSuccessiva != NULL){
        //Scorri lista
        temp=temp->richiestaSuccessiva;
    }
    //Il nuovo nodo viene collegato al precedentemente ultimo nodo della lista
    temp->richiestaSuccessiva=nuovaRichiesta;
    //Inserisco data nel nuovo nodo
    strcpy(nuovaRichiesta->nomeLibro, nomeLibro);
    strcpy(nuovaRichiesta->matricola, matricola);
    nuovaRichiesta->tipoRichiesta = tipo;

}

void stampaListaRichieste(struct richiesta* testa){

    //Metto la testa in un puntatore temporaneo per non perdere il valore della testa
    struct richiesta* tmp = testa;


    //Scorro la lista fino alla sua terminazione
    while(tmp != NULL){
        //Discrimina i 2 tipi di richiesta
        if(tmp->tipoRichiesta == 0){
            printf("Richiesta libro, richiesta da: %s, libro in questione: %s\n", tmp->matricola, tmp->nomeLibro);
        }else{
            printf("Restituzione libro, richiesta da: %s, libro in questione: %s\n", tmp->matricola, tmp->nomeLibro);
        }
        //Scorro la lista
        tmp = tmp->richiestaSuccessiva;
    }

}

struct richiesta* rimuoviRichiesta(struct richiesta* testa, struct richiesta* richiesta){

    struct richiesta* temp = testa;
    struct richiesta* nuovaTesta = NULL;
    struct richiesta* precedente = NULL;

    //Se la testa è il nodo da eliminare
    if (temp != NULL && !strcmp(temp->matricola, richiesta->matricola) && !strcmp(temp->nomeLibro, richiesta->nomeLibro) && temp->tipoRichiesta == richiesta->tipoRichiesta){
        nuovaTesta = temp->richiestaSuccessiva;   //Cambia la testa con il nodo successivo
        return nuovaTesta; //Termina
    }

    //Cerco il nodo da cancellare
    while (temp != NULL && !(!strcmp(temp->matricola, richiesta->matricola) && !strcmp(temp->nomeLibro, richiesta->nomeLibro) && temp->tipoRichiesta == richiesta->tipoRichiesta)){
        precedente = temp; //Salvo il precedente per collegare il precedente del nodo da eliminare col suo successivo
        temp = temp->richiestaSuccessiva; //Scorri lista
    }

    //Se il nodo non è trovato
    if (temp == NULL){
            return NULL;
    }

    //Collego il precedente del nodo da eliminare col suo successivo
    precedente->richiestaSuccessiva = temp->richiestaSuccessiva;

    return testa;

}

struct richiesta* richiestaTipo1(struct richiesta* testa, struct richiesta* richiesta){

    struct richiesta* nuovaTesta = testa;

    //Controlla se nella libreria è presente il libro che è stato richiesto
    int libroID = trovaLibroId(richiesta->nomeLibro, "Libreria");

    if(libroID != -1){
        //Libro trovato in libreria
        strcpy(libreria[libroID].possessore, richiesta->matricola); //Cambia possessore
        //Inserisci nuovo libro nella lista dello studente

        struct studente* studente = trovaStudente(testaStudenti, richiesta->matricola);
        if(studente->primoLibro == NULL){
            studente->primoLibro = inserisciPrimoLibro(richiesta->nomeLibro, richiesta->matricola);
        }else{
            inserisciLibro(studente->primoLibro, richiesta->nomeLibro, richiesta->matricola);
        }

        //Richiesta restituzione completata, elimina
        nuovaTesta = rimuoviRichiesta(nuovaTesta, richiesta);

    }

    return nuovaTesta; //Se il nodo che elimina è il primo, rimpiazza la testa

}

struct richiesta* richiestaTipo2(struct richiesta* testa, struct richiesta* richiesta){

    struct richiesta* nuovaTesta = testa;

    //Controlla se nella lista dei libri dello studente ho quel libro
    struct libro* libro = trovaLibro(trovaStudente(testaStudenti, richiesta->matricola)->primoLibro, richiesta->nomeLibro, richiesta->matricola);

    //Libro trovato nella lista
    if(libro != NULL){
        //Rimuovi libro nella lista dello studente
        struct studente* studente = trovaStudente(testaStudenti, richiesta->matricola);

        studente->primoLibro = rimuoviLibro(studente->primoLibro, libro->nome);

        //Cambia il possessore nel libro della lista della libreria
        int libroID = trovaLibroId(richiesta->nomeLibro, richiesta->matricola);
        strcpy(libreria[libroID].possessore, "Libreria"); //Cambia possessore

        //Richiesta completata, elimina
        nuovaTesta = rimuoviRichiesta(testa, richiesta);

        //Controllo se qualcuno aveva richiesto il libro appena restituito
        //Scorri lista richieste
        struct richiesta* tmp = nuovaTesta;

        while(tmp != NULL){

            nuovaTesta = soddisfaRichieste(nuovaTesta, tmp);
            tmp = tmp->richiestaSuccessiva;

        }
    }

    return nuovaTesta; //Se il nodo che elimina è il primo, rimpiazza la testa

}

struct richiesta* soddisfaRichieste(struct richiesta* testa, struct richiesta* richiesta){

    struct richiesta* nuovaTesta;

    //Discrimina i tipi di richiesta
    if(richiesta->tipoRichiesta == 0){
        nuovaTesta = richiestaTipo1(testa, richiesta); //Richiesta libro
    }else{
        nuovaTesta = richiestaTipo2(testa, richiesta); //Restituzione libro
    }

    return nuovaTesta;

}

bool richiestaPresente(struct richiesta* testa, bool tipoRichiesta, char nomeLibro[], char matricola[]){

    //Metto la testa in un puntatore temporaneo per non perdere il valore della testa
    struct richiesta* tmp = testa;

    //Se la lista è vuota restituisci sempre true
    if(tmp == NULL){
        return false;
    }


    //Scorro la lista fino alla sua terminazione
    while(tmp != NULL){
        //Richiesta trovata, la restituisco
        if(!strcmp(tmp->matricola, matricola) && !strcmp(tmp->nomeLibro, nomeLibro) && tmp->tipoRichiesta == tipoRichiesta){
            return true;
        }
        //Scorro la lista
        tmp = tmp->richiestaSuccessiva;
    }

    return false;

}



//Main

int main(){

    libreria = creaLibreria(numeroLibri); //Libreria
    struct richiesta* testaRichieste = NULL; //Prima richiesta della lista delle richieste

    stampaLibreria();

    char matricola[MAXSTRINGSIZE]; //Buffer matricola
    char libroScelto[MAXSTRINGSIZE]; //Buffer libro scelto

    struct studente* studente;

    int op;
    int valoriLetti; //Variabile per controllare il tipo di input inserito dall'utente

    do{

        //"Login studente"
        printf("\nInserire matricola per eseguire nuova richiesta:\n");
        fgets(matricola, MAXSTRINGSIZE, stdin);

        //Controlla che la lunghezza della stringa inserita sia minore di MAXSTRINGSIZE
        while(matricola[strlen(matricola)-1] != '\n'){
            fflush(stdin); //Libera stream input
            system("cls");
            stampaLibreria();

            printf("\n\aLa matricola inserita e' troppo lunga, riprova (Lunghezza max 50 caratteri\n");
            printf("\nInserire matricola per eseguire nuova richiesta:\n");
            fgets(matricola, MAXSTRINGSIZE, stdin);
        }

        //Controlla se almeno un carattere è stato inserito
        while(!strcmp(matricola, "\n")){
            system("cls");
            stampaLibreria();

            printf("\n\aInserire almeno un carattere per la matricola\n");
            printf("\nInserire matricola per eseguire nuova richiesta:\n");
            fgets(matricola, MAXSTRINGSIZE, stdin);
        }

        //Rimuovi \n dalla string
        strtok(matricola, "\n");


        //Primo studente della lista
        if(testaStudenti == NULL){
            //Pulisci schermo e ristampa libreria
            system("cls");
            stampaLibreria();
            if(testaRichieste != NULL){
                //Se ho delle richieste in sospeso
                printf("\nLista richieste in sospeso:\n");
                stampaListaRichieste(testaRichieste);
            }
            testaStudenti = inserisciPrimoStudente(matricola); //Inserisci il primo studente
            studente = testaStudenti; //Essendo l'unico studente, la testa è lo studente che sta facendo la richiesta
            studente->primoLibro = NULL; //Studente appena aggiunto, non ha libri
        //Aggiungo alla lista
        }else{
            //Se lo studente è già nella lista lo metto nella variabile studente
            studente = trovaStudente(testaStudenti, matricola);
            //Se lo studente non è stato trovato
            if(studente == NULL){
                inserisciStudente(testaStudenti, matricola); //Inserisci nuovo studente nella lista
                studente = trovaStudente(testaStudenti, matricola); //Trova lo studente appena inserito
                studente->primoLibro = NULL; //Studente appena aggiunto, non ha libri
            }
        }

        //Pulisci schermo e ristampa libri
        system("cls");
        stampaLibreria();
        if(testaRichieste != NULL){
                //Se ho delle richieste in sospeso
                printf("\nLista richieste in sospeso:\n");
                stampaListaRichieste(testaRichieste);
        }

        //Stampa lista libri dello studente
        printf("\nLibri attualmente in possesso dello studente con matricola %s:\n", studente->matricola);
        if(studente->primoLibro != NULL){
           stampaListaLibri(studente->primoLibro);
        }else{
            printf("\nNessun libro\n");
        }

        //Fai scegliere tipo richiesta
        printf ("\n1. Richiedi libro\n");
        printf ("2. Restituisci libro\n");
        printf ("0. Termina programma\n");


        valoriLetti = scanf("%d", &op);
        getchar(); //Per evitare che il prossimo input venga saltato

        system("cls");
        stampaLibreria();

        //Si Assicura che l'input sia valido
        while((op != 0 && op != 1 && op != 2) || valoriLetti != 1){
            system("cls");
            stampaLibreria();
            //Stampa lista libri dello studente
            printf("\nLibri attualmente in possesso dello studente con matricola %s:\n", studente->matricola);
            if(studente->primoLibro != NULL){
               stampaListaLibri(studente->primoLibro);
            }else{
                printf("\nNessun libro\n");
            }

            //Fai scegliere tipo richiesta
            printf ("\n1. Richiedi libro\n");
            printf ("2. Restituisci libro\n");
            printf ("0. Termina programma\n");

            printf("\aInserire una richiesta valida!\n");

            valoriLetti = scanf("%d", &op);
            getchar(); //Per evitare che il prossimo input venga saltato

        }

        system("cls");
        stampaLibreria();

        if(testaRichieste != NULL){
                //Se ho delle richieste in sospeso
                printf("\nLista richieste in sospeso:\n");
                stampaListaRichieste(testaRichieste);
        }
        printf("\nLibri attualmente in possesso dello studente con matricola %s:\n", studente->matricola);
        if(studente->primoLibro != NULL){
           stampaListaLibri(studente->primoLibro);
        }else{
            printf("\nNessun libro\n");
        }


        switch(op){
            case 1:{

                //Richiedi libro
                printf("\nRichiedi libro, nome libro: \n");
                fgets(libroScelto, MAXSTRINGSIZE, stdin);

                //Controlla che la lunghezza della stringa inserita sia minore di MAXSTRINGSIZE
                while(libroScelto[strlen(libroScelto)-1] != '\n'){
                    fflush(stdin); //Libera stream input
                    system("cls");
                    stampaLibreria();

                    if(testaRichieste != NULL){
                    //Se ho delle richieste in sospeso
                    printf("\nLista richieste in sospeso:\n");
                    stampaListaRichieste(testaRichieste);
                    }
                    printf("\nLibri attualmente in possesso dello studente con matricola %s:\n", studente->matricola);
                    if(studente->primoLibro != NULL){
                       stampaListaLibri(studente->primoLibro);
                    }else{
                        printf("\nNessun libro\n");
                    }

                    printf("\n\aIl nome del libro inserito e' troppo lungo, riprova (Lunghezza max 50 caratteri\n");
                    printf("\nRichiedi libro, nome libro: \n");
                    fgets(libroScelto, MAXSTRINGSIZE, stdin);
                }

                //Controlla se almeno un carattere è stato inserito
                while(!strcmp(libroScelto, "\n")){
                    system("cls");
                    stampaLibreria();

                    if(testaRichieste != NULL){
                    //Se ho delle richieste in sospeso
                    printf("\nLista richieste in sospeso:\n");
                    stampaListaRichieste(testaRichieste);
                    }
                    printf("\nLibri attualmente in possesso dello studente con matricola %s:\n", studente->matricola);
                    if(studente->primoLibro != NULL){
                       stampaListaLibri(studente->primoLibro);
                    }else{
                        printf("\nNessun libro\n");
                    }

                    printf("\n\aInserire almeno un carattere per il nome del libro\n");
                    printf("\nRichiedi libro, nome libro: \n");
                    fgets(libroScelto, MAXSTRINGSIZE, stdin);
                }

                //Rimuovi \n dalla string
                strtok(libroScelto, "\n");

                //Controlla se la richiesta ha senso
                if(libroPresenteInLibreria(libroScelto)){
                    //Controlla se non ho già fatto la stessa richiesta
                    if(!richiestaPresente(testaRichieste, 0, libroScelto, studente->matricola)){
                        //Controlla se non ho già il libro
                        if(trovaLibro(studente->primoLibro, libroScelto, studente->matricola) == NULL){
                            //Controlla se la lista delle richieste è vuota o meno
                            if(testaRichieste == NULL){
                                testaRichieste = inserisciPrimaRichiesta(0, studente->matricola, libroScelto);
                            }else{
                                inserisciRichiesta(testaRichieste, 0, studente->matricola, libroScelto);
                            }
                            system("cls");
                            stampaLibreria();
                            if(testaRichieste != NULL){
                                //Se ho delle richieste in sospeso
                                printf("\nLista richieste in sospeso:\n");
                                stampaListaRichieste(testaRichieste);
                            }
                            printf("\nRichiesta accettata!\n");
                            printf("\nPremi invio per continuare\n");
                            getchar();
                        }else{
                            system("cls");
                            stampaLibreria();
                            if(testaRichieste != NULL){
                                //Se ho delle richieste in sospeso
                                printf("\nLista richieste in sospeso:\n");
                                stampaListaRichieste(testaRichieste);
                            }
                            printf("\n\aRichiesta non accettata, la matricola %s possiede gia' questo libro!", studente->matricola);
                            printf("\nPremi invio per continuare\n");
                            getchar();
                        }
                    }else{
                        system("cls");
                        stampaLibreria();
                        if(testaRichieste != NULL){
                            //Se ho delle richieste in sospeso
                            printf("\nLista richieste in sospeso:\n");
                            stampaListaRichieste(testaRichieste);
                        }
                        printf("\n\aRichiesta non accettata, la matricola %s ha gia' fatto questa richiesta!", studente->matricola);
                        printf("\nPremi invio per continuare\n");
                        getchar();
                    }
                }else{
                    system("cls");
                    stampaLibreria();
                    if(testaRichieste != NULL){
                        //Se ho delle richieste in sospeso
                        printf("\nLista richieste in sospeso:\n");
                        stampaListaRichieste(testaRichieste);
                    }
                    printf("\n\aRichiesta non accettata, il libro %s non e' presente nella libreria!\n", libroScelto);
                    printf("\nPremi invio per continuare\n");
                    getchar();
                }

            }break;
            case 2:{

                //Restituisci libro
                printf("\nRestituisci libro, nome libro: \n");
                fgets(libroScelto, MAXSTRINGSIZE, stdin);

                //Controlla che la lunghezza della stringa inserita sia minore di MAXSTRINGSIZE
                while(libroScelto[strlen(libroScelto)-1] != '\n'){
                    fflush(stdin); //Libera stream input
                    system("cls");
                    stampaLibreria();

                    if(testaRichieste != NULL){
                    //Se ho delle richieste in sospeso
                    printf("\nLista richieste in sospeso:\n");
                    stampaListaRichieste(testaRichieste);
                    }
                    printf("\nLibri attualmente in possesso dello studente con matricola %s:\n", studente->matricola);
                    if(studente->primoLibro != NULL){
                       stampaListaLibri(studente->primoLibro);
                    }else{
                        printf("\nNessun libro\n");
                    }

                    printf("\n\aIl nome del libro inserito e' troppo lungo, riprova (Lunghezza max 50 caratteri\n");
                    printf("\nRichiedi libro, nome libro: \n");
                    fgets(libroScelto, MAXSTRINGSIZE, stdin);
                }

                //Controlla se almeno un carattere è stato inserito
                while(!strcmp(libroScelto, "\n")){
                    system("cls");
                    stampaLibreria();

                    if(testaRichieste != NULL){
                    //Se ho delle richieste in sospeso
                    printf("\nLista richieste in sospeso:\n");
                    stampaListaRichieste(testaRichieste);
                    }
                    printf("\nLibri attualmente in possesso dello studente con matricola %s:\n", studente->matricola);
                    if(studente->primoLibro != NULL){
                       stampaListaLibri(studente->primoLibro);
                    }else{
                        printf("\nNessun libro\n");
                    }

                    printf("\n\aInserire almeno un carattere per il nome del libro\n");
                    printf("\nRichiedi libro, nome libro: \n");
                    fgets(libroScelto, MAXSTRINGSIZE, stdin);
                }

                //Rimuovi \n dalla string
                strtok(libroScelto, "\n");

                //Controlla se la richiesta ha senso
                if(libroPresente(studente->primoLibro, libroScelto)){
                    //Controlla se la lista delle richieste è vuota o meno
                    if(testaRichieste == NULL){
                        testaRichieste = inserisciPrimaRichiesta(1, studente->matricola, libroScelto);
                    }else{
                        inserisciRichiesta(testaRichieste, 1, studente->matricola, libroScelto);
                    }
                    system("cls");
                    stampaLibreria();
                    if(testaRichieste != NULL){
                        //Se ho delle richieste in sospeso
                        printf("\nLista richieste in sospeso:\n");
                        stampaListaRichieste(testaRichieste);
                    }
                    printf("\nRichiesta accettata!\n");
                    printf("\nPremi invio per continuare\n");
                    getchar();
                }else{
                    system("cls");
                    stampaLibreria();
                    if(testaRichieste != NULL){
                        //Se ho delle richieste in sospeso
                        printf("\nLista richieste in sospeso:\n");
                        stampaListaRichieste(testaRichieste);
                    }
                    printf("\n\aRichiesta non accettata, il libro %s non e' presente tra i libri dello studente!\n", libroScelto);
                    printf("\nPremi invio per continuare\n");
                    getchar();
                }

            }break;
            default:{
                printf("Terminazione\n");
            }break;
        }

        //Soddisfa le richieste che possono essere soddisfatte
        struct richiesta* tmp = testaRichieste;

        //Scorri lista richieste per provare a soddisfarme
        while(tmp != NULL){

            testaRichieste = soddisfaRichieste(testaRichieste, tmp);
            tmp = tmp->richiestaSuccessiva;

        }

        //Pulisci schermo
        system("cls");
        stampaLibreria();
        if(testaRichieste != NULL){
            //Se ho delle richieste in sospeso
            printf("\nLista richieste in sospeso:\n");
            stampaListaRichieste(testaRichieste);
        }

    }while(op);

    return 0;
}
