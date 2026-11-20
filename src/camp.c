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

