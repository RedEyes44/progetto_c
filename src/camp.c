/**
 * @file camp.c
 * @brief Funzioni per la gestione dell'accampamento e della squadra
 * @author Gaffo Luca
*/

#include "types.h"
#include "camp.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void inizializzaLista(Partita *p){
	int i;
	
	p->count_id_naufraghi = 1;        //inizializzo ad 1 il contatore dei naufraghi
	
	for(i = 0; i < 4; i++){
		aggiungiNaufrago(p);          //ciclo per quattro volte per aggiungere i quattro naufraghi di partenza
	}
	
	return;
}

void aggiungiNaufrago(Partita *p){
	Naufrago *n = malloc(sizeof(Naufrago));
	
	if(n == NULL){
		exit(1);                     //errore nell'allocazione della memoria per il naufrago. Il programma si interrompe (intanto lo gestisco così)
	}
	
	n->id = p->count_id_naufraghi;   //assegno come identificatore del naufrago quello del naufrago corrente
	n->salute = MAX_SALUTE;          //assegno come salute iniziale del naufrago il valore MAX_SALUTE
	n->next = NULL;                  //imposto a NULL il puntatore al naufrago successivo
	p->count_id_naufraghi++;         //incremento il contatore per l'id del naufrago successivo
	
	if(p->squadra == NULL){
		p->squadra = n;
	}else{
		Naufrago *aus = p->squadra;   //salvo in un puntatore ausiliario la testa della lista squadra
		while(aus->next != NULL){
			aus = aus->next;          //scorro la lista ed esco quando il puntatore al successivo naufrago è uguale a NULL
		}
		aus->next = n;                //a quel punto sovrascrivo quel puntatore a NULL con un puntatore al nuovo ultimo naufrago
	}
	return;
}

void rimuoviNaufrago(Partita *p, int id){
	Naufrago *aus = p->squadra;      //puntatore ausiliario alla testa della lista
	Naufrago *prec = NULL;           //puntatore all'elemento precedente, mi serve per tener traccia di elementi da reincollare nella nuova lista
	while(aus != NULL && aus->id != id){  
	                                 //ciclo nella lista finchè non raggiungo la coda e l'id del mio naufrago non è uguale a quello da eliminare passato come parametro
		prec = aus;                  //visto che la condizione è vera aggiorno prec facendolo puntare all'elemento puntato da aus
		aus = aus->next;             //di conseguenza aus punta ora al successivo elemento della lista
	}
	
	if(aus == NULL){                 //ho ciclato fino in fondo alla lista ma non ho mai trovato l'elemento con id desiderato. Esco dalla funzione senza far nulla
		return;
	}
	
	
	if(prec == NULL){               //controllo il valore di prec per vedere se devo fare una estrazione dalla testa o meno
		p->squadra = aus->next;     //caso estrazione testa: assegno come nuova testa della lista il secondo elemento, ovvero quello puntato da aus->next
		free(aus);                  //libero la memoria dell'elemento da eliminare
	}else{
		prec->next = aus->next;     //caso estrazione non da testa: assegno come puntatore next all'elemento puntato da prec quello puntato da aus->next, che sarà NULL in caso di estrazione dalla coda o il puntatore successivo in caso di estrazione dal mezzo della lista
		free(aus);                  //libero la memoria dell'elemento da eliminare
	}
	
	return;
}

void menuPrincipale(Partita *p){
	char morse[] = {'.', '.', '.', '-', '-', '-', '.', '.', '.'};  //array che contiene la sequenza di ciò che va digitato per abilitare i trucchi
	int acc = 0;   //accumulatore per contare l'inserimento della sequenza di caratteri
	char opz, esci = '3'; 
	
	p->trucchi_attivi = false;   //ad inizio partita il flag dei trucchi deve essere settato a false
	
	do{
		
		//stampa a schermo gli elementi del menu
		printf("Menu principale del gioco\n");
		printf("1. Nuova partita\n");
		printf("2. Crediti");
		//se non sono ancora stati attivati mostra solo l'esci, altrimenti mostra anche l'accesso ai trucchi
		if(p->trucchi_attivi == false){
			printf("3. Esci\n");
		}else{
			printf("3. Trucchi\n");
			printf("4. Esci");
		}
		printf("Seleziona una delle opzioni del menu [1 - %c]: ", esci);
		scanf(" %c", &opz);  //prendo in input il carattere, che può essere il numero da 1 a 3/4 o il carattere della sequenza morse
		
		//verifico se il carattere inserito corrisponde all'attuale della sequenza morse o se già si è richiesto i trucchi. Se si incremento il contatore
		if(p->trucchi_attivi == false){
			if(opz == morse[acc]){
				acc++;
				if(acc == 9){
					//se il contatore raggiunge il valore 9 abilito la possibilità di usare i trucchi
					p->trucchi_attivi = true;
					esci = '4';
				}
			}else{
				//altrimenti lo riporto a 0 e bisogna ripartire con la sequenza
				acc = 0;
			}
		}
		
		if(opz == '2'){
			mostraCrediti();  //chiama la funzione che mostra i nomi di chi ha lavorato al programma
		}else{
			if(opz == '3' && opz != 'valido'){
				menuTrucchi(p);  //chiama la funzione che va ad attivare i trucchi (probabile necessità di modificare l'oggetto partita con altri parametri per i trucchi specifici)
			}
		}
		
	}while(opz != '1' && opz != esci);
	
	if(opz == '1'){
		//chiamare la funzione che permette di iniziare la partita, con inizializzazione della mappa e a quel punto inizio del gioco effettivo
	}else if(opz == esci){
		printf("Uscita dal gioco\n");
		return; //fine del programma, si è chiesto di uscire
	}else{
		exit(1); //qualche errore, esco dal programma
	}
	
}

void mostraCrediti(){
	//intanto la metto così, quello che va scritto lo determiniamo con calma in un secondo momento
	printf("CREDITI GIOCO: \n");
	return;
}

void menuTrucchi(Partita *p){
	int opz, value;
	
	do{
		printf("Menu trucchi: \n");
		printf("1. Imposta i PS iniziali dei naufraghi \n");
		printf("2. Imposta il numero iniziale dei naufraghi \n");
		printf("3. Imposta le quantità del magazzino \n");
		printf("4. Rivela le caselle della mappa di gioco \n");
		printf("5. Sblocca la missione finale \n");
		printf("6. Esci \n");
		printf("Seleziona una delle opzioni del menu [1 - 6]: ");
		
		value = scanf(" %d", &opz);
		
		//gestione dell'errore di input nel caso di tipo di dato errato
		if(value != 1){
			pulisciBuffer();
			opz = 0; //metto opz a 0 così da forzare la ripetizione del ciclo
		}
		
		if(opz == 1){
			impostaSalute(p);
		}else if(opz == 2){
			numeroNaufraghi(p);
		}else if(opz == 3){
			impostaMagazzino(p);
		}else if(opz == 4){
			rivelaCaselle(p);
		}else if(opz == 5){
			sbloccaMissioneFinale(p);
		}else if(opz == 6){
			printf("Uscita dal menu trucchi \n");
		}else{
			printf("Input inserito non valido \n");
		}
		
	}while(opz != 6);
	
	return;
}

void pulisciBuffer(){
	int aus = getchar();
	while(aus != '\n' && aus != EOF){
		aus = getchar();
	}
	return;	
}

void impostaSalute(Partita *p){
	int ps, value;
	do{
		printf("Inserisci il numero di ps (> 1) che i naufraghi devono avere di default ad inizio partita: ");
		value = scanf("%d", &ps);
		if(value != 1){
			pulisciBuffer();
			ps = -1;
		}
	}while(ps <= 1);
	//p->salute_trucco = ps; ulteriore parametro da aggiungere a portita per salvare il valore che l'utente desidera
	return;
}

void numeroNaufraghi(Partita *p){
	int num, value;
	do{
		printf("Inserisci il numero di naufraghi (>= 1) che desideri di avere di default ad inizio partita: ");
		value = scanf("%d", &num);
		if(value != 1){
			pulisciBuffer();
			num = -1;
		}
	}while(num < 1);
	//p->num_naufraghi = ps; ulteriore parametro da aggiungere a portita per salvare il valore che l'utente desidera
	return;
}

void impostaMagazzino(Partita *p){
	int cibo, acqua, legna, corda, rete, cisterna, value;
	bool flag = false;
	do{
		printf("Inserisci nell'ordine la quantità' di oggetti desiderati ad inizio partita: [cibo] [acqua] [legna] [corda] [rete - max 1] [cisterna - max 1]: ");
		value = scanf("%d %d %d %d %d %d", &cibo, &acqua, &legna, &corda, &rete, &cisterna);
		if(value == 6 && cibo >= 0 && acqua >= 0 && legna >= 0 && corda >= 0 && (rete == 0 || rete == 1) && (cisterna == 0 || cisterna == 1)){
			p->magazzino.acqua = acqua;
			p->magazzino.legna = legna;
			p->magazzino.corda = corda;
			p->magazzino.rete = rete;
			p->magazzino.cisterna = cisterna;
			p->magazzino.cibo = cibo;
			flag = true;
		}else{
			pulisciBuffer();
			printf("Errore nell'inserimento dei dati \n");
		}
	}while(flag == false);
	return;
}

void rivelaCaselle(Partita *p){
	int attivo, value;
	do{
		printf("Inserisci 1 per rivelare le caselle della mappa, 0 per mantenerle nascoste: ");
		value = scanf("%d", &attivo);
		if(value != 1){
			pulisciBuffer();
			attivo = -1;
		}
	}while(attivo != 0 && attivo != 1);
	//p->mostra_caselle = attivo; ulteriore flag per salvare la scelta dell'utente
	return;
}

void sbloccaMissioneFinale(Partita *p){
	int attivo, value;
	do{
		printf("Inserisci 1 per sbloccare la missione finale, 0 per lasciarla da sbloccare: ");
		value = scanf("%d", &attivo);
		if(value != 1){
			pulisciBuffer();
			attivo = -1;
		}
	}while(attivo != 0 && attivo != 1);
	
	if(attivo == 1){
		p->magazzino.lente = true;
		p->magazzino.olio = true;
		p->magazzino.chiave = true;
	}else{
		p->magazzino.lente = false;
		p->magazzino.olio = false;
		p->magazzino.chiave = false;
	}
	return;
}

