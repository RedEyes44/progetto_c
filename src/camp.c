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

void inizializzaPartita(Partita *p){
	p->giorno_corrente = 1;                       //imposto a 1 il giorno corrente
	p->count_id_naufraghi = 1;                    //imposto a 1 il contatore dei naufraghi, mi serve per dopo
	p->squadra = NULL;                            //imposto a NULL il puntatore della lista
	p->missione_finale = false;                   //imposto a false il flag per la missione finale
	p->num_naufraghi_iniziale = 4;                //imposto al default 4 il numero di naufraghi iniziale
	p->salute_naufraghi_iniziale = MAX_SALUTE;    //imposto al default MAX_SAlUTE la salute iniziale dei naufraghi
	p->sorgente = false;                          //imposto a false il flag della scoperta della sorgente
	p->magazzino->cisterna = false;               //imposto a false il flag della costruzione della cisterna
	p->trucchi_attivi = false;                    //imposto a false il flag dei trucchi attivi
	p->trucco_mostra_caselle = false;             //imposto a false il flag del trucco mostra caselle
	p->magazzino->chiave = false;                 //imposto a false i flag dell'acquisizione dei materiali della missione finale, ovvero chiave, lente e olio
	p->magazzino->lente = false;
	p->magazzino->olio = false;
	p->magazzino->rete = false;                  //imposto a false il flag della costruzione della rete
	p->magazzino->acqua = 8;                     //imposto al valore di default l'equipaggiamento del magazzino,, ovvero 8 unità di acqua e cibo e 0 unità di corda e legna
	p->magazzino->cibo = 8;
	p->magazzino->corda = 0;
	p->magazzino->legna = 0;
}

void inizializzaLista(Partita *p){
	int i;
	
	for(i = 0; i < p->num_naufraghi_iniziale; i++){
		aggiungiNaufrago(p);          //ciclo per  per aggiungere i naufraghi di partenza
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

void liberaLista(Partita *p){
    Naufrago *aus;
    while(p->squadra != NULL){
        aus = p->squadra;          //mantengo il nodo della lista attuale
        p->squadra = aus->next;    //vado a impostare come nuova testa della lista il successivo elemento. Se il vecchio primo era l'ultimo, ora la testa punta a NULL
        free(aus);                 //libero la memoria dell'elemento da eliminare
    }
}

bool menuPrincipale(Partita *p){
	char morse[] = {'.', '.', '.', '-', '-', '-', '.', '.', '.'};  //array che contiene la sequenza di ciò che va digitato per abilitare i trucchi
	int acc = 0;   //accumulatore per contare l'inserimento della sequenza di caratteri
	char opz, esci = '3'; 
	
	p->trucchi_attivi = false;   //ad inizio partita il flag dei trucchi deve essere settato a false
	
	do{
		
		//stampa a schermo gli elementi del menu
		printf("Menu principale del gioco\n");
		printf("1. Nuova partita\n");
		printf("2. Crediti\n");
		//se non sono ancora stati attivati mostra solo l'esci, altrimenti mostra anche l'accesso ai trucchi
		if(p->trucchi_attivi == false){
			printf("3. Esci\n");
		}else{
			printf("3. Trucchi\n");
			printf("4. Esci\n");
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
			if(opz == '3' && opz != esci){
				menuTrucchi(p);  //chiama la funzione che va ad attivare i trucchi (probabile necessità di modificare l'oggetto partita con altri parametri per i trucchi specifici)
			}
		}
		
	}while(opz != '1' && opz != esci);
	
	if(opz == '1'){
		return true;
	}else if(opz == esci){
		printf("Uscita dal gioco\n");
		return false;    //fine del programma, si è chiesto di uscire
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
			//chiamo la funzione che permette di impostare i ps iniziali dei naufraghi
			impostaSalute(p);
		}else if(opz == 2){
			//chiamo la funzione che permette di impostare il numero iniziale di naufraghi
			numeroNaufraghi(p);
		}else if(opz == 3){
			//chiamo la funzione che permette di impostare la quantità iniziale dell'equipaggiamento
			impostaMagazzino(p);
		}else if(opz == 4){
			//chiamo la funzione che permette di impostare la rivelazione o meno delle caselle della mappa ad inizio partita
			rivelaCaselle(p);
		}else if(opz == 5){
			//chiamo la funzione che permette di impostare come disponibile da subito o meno la missione finale
			sbloccaMissioneFinale(p);
		}else if(opz == 6){
			//esco dal menu trucchi
			printf("Uscita dal menu trucchi \n");
		}else{
			//input inserito non valido: avviso l'utente con un messaggio
			printf("Input inserito non valido \n");
		}
		
	}while(opz != 6);
	//se opz = 6 vuol dire che l'utente desidera uscire dal menu trucchi, quindi termina l'esecuzione della funzione	
	return;
}

void pulisciBuffer(){
	int aus = getchar();
	while(aus != '\n' && aus != EOF){
		aus = getchar();  //ciclo man mano i caratteri salvati nel buffer, così da eliminare quello che non interessa e che può risultare dannoso per l'esecuzione del programma
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
	//assegno come valore iniziale dei ps dei miei naufraghi quello scelto dall'utente
	p->salute_naufraghi_iniziale = ps;
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
	//assegno come valore iniziale del numero dei miei naufraghi quello scelto dall'utente
	p->num_naufraghi_iniziale = num;
	return;
}

void impostaMagazzino(Partita *p){
	int cibo, acqua, legna, corda, rete, cisterna, value;
	bool flag = false;
	do{
		printf("Inserisci nell'ordine la quantità' di oggetti desiderati ad inizio partita: [cibo] [acqua] [legna] [corda] [rete - max 1] [cisterna - max 1]: ");
		value = scanf("%d %d %d %d %d %d", &cibo, &acqua, &legna, &corda, &rete, &cisterna);
		if(value == 6 && cibo >= 0 && acqua >= 0 && legna >= 0 && corda >= 0 && (rete == 0 || rete == 1) && (cisterna == 0 || cisterna == 1)){
			//se l'utente ha inserito come richiesto i valori per i materiali dell'inventario, li si imposta 
			p->magazzino.acqua = acqua;
			p->magazzino.legna = legna;
			p->magazzino.corda = corda;
			p->magazzino.rete = rete;
			p->magazzino.cisterna = cisterna;
			p->magazzino.cibo = cibo;
			printf("Impostazione dei valori avvenuta con successo. Si ritorna al menu dei trucchi \n");
			flag = true;
		}else{
			//altrimenti pulisco il buffer e si fa riprovare l'utente
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
	//salvo la scelta dell'utente riguardo alla volontò di rivelare o meno all'inizio della partita le caselle della mappa
	p->trucco_mostra_caselle = attivo; 
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
		//se l'utente ha scelto di rendere disponibile sin da subito la missione finale rendo disponibile i materiali necessari nell'inventario e attivo il flag dedicato
		p->magazzino.lente = true;
		p->magazzino.olio = true;
		p->magazzino.chiave = true;
		p->missione_finale = true;
	}else{
		//altrimenti si riporta alla situazione normale, ovvero che la missione va sbloccata giocando col passare dei turni
		p->magazzino.lente = false;
		p->magazzino.olio = false;
		p->magazzino.chiave = false;
		p->missione_finale = false;
	}
	return;
}

