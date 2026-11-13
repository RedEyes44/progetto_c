/**
 * @file map.c
 * @brief Funzioni per la generazione procedurale e stampa della mappa.
 * @author Tonetto Riccardo
 */

#include "types.h"
#include "map.h"
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Cambia il terreno di una casella scelta casualmente in RELITTO, controllando che sia nella spiaggia
 * @param p Partita a cui fa riferimento la mappa
 * 
*/

void piazzaRelitto(Partita *p){


	int rigaRelitto, colonnaRelitto;

	do{

		rigaRelitto = rand()%DIM_MAPPA;
		colonnaRelitto = rand()%DIM_MAPPA;

	}while(p->mappa[rigaRelitto][colonnaRelitto].terreno!=SPIAGGIA);

	p->mappa[rigaRelitto][colonnaRelitto].terreno = RELITTO;


}


/**
 * @brief Cambia il terreno di una casella scelta casualmente in FARO, controllando che sia nella spiaggia
 * @param p Partita a cui fa riferimento la mappa
 * 
*/

void piazzaFaro(Partita *p){

	int rigaFaro, colonnaFaro;

	do{

		rigaFaro = rand()%DIM_MAPPA;
		colonnaFaro = rand()%DIM_MAPPA;

	}while(p->mappa[rigaFaro][colonnaFaro].terreno!=SPIAGGIA);

	p->mappa[rigaFaro][colonnaFaro].terreno = FARO;


}

/**
 * @brief Cambia il terreno di una casella scelta casualmente in GROTTA, controllando che non si trovi sulla spiaggia e che si trovi ad almeno 3 caselle di distanza dall'Accampamento
 * @param p Partita a cui fa riferimento la mappa
 * 
*/

void piazzaGrotta(Partita *p){

	int rigaGrotta, colonnaGrotta;

	do{

		rigaGrotta = rand()%7+1;
		colonnaGrotta = rand()%7+1;

	}while(abs(rigaGrotta-CENTRO_MAPPA) + abs(colonnaGrotta-CENTRO_MAPPA) < 3);

	p->mappa[rigaGrotta][colonnaGrotta].terreno = GROTTA;


}

/**
 * @brief Cambia il terreno di una casella in TANA, controllando che disti almeno 3 caselle dall'accampamento e che non ci sia già la grotta
 * @param p Partita a cui fa riferimento la mappa
 * 
*/

void piazzaTana(Partita *p){

	int rigaTana, colonnaTana;

	do{

		rigaTana = rand()%7+1;
		colonnaTana = rand()%7+1;

	}while(abs(rigaTana-CENTRO_MAPPA) + abs(colonnaTana-CENTRO_MAPPA)<3 || p->mappa[rigaTana][colonnaTana].terreno==GROTTA);

	p->mappa[rigaTana][colonnaTana].terreno = TANA;

}

/**
 * @brief Controlla se c'è almeno una sorgente in tutta la mappa
 * @param p Partita a cui fa riferimento la mappa
 * @return True appena trova una sorgente, False se non ne trova nessuna
*/

bool sorgente(Partita *p){

	

	for(int i=0;i<DIM_MAPPA;i++)
		for(int j=0;j<DIM_MAPPA;j++)
			if(p->mappa[i][j].terreno==SORGENTE)
					return true;


	return false;
}

/**
 * @brief Cambia il terreno di una casella in SORGENTE, controllando non ci sia la GROTTA, l'ACCAMPAMENTO e la TANA
 * @param p Partita a cui fa riferimento la mappa
 * 
*/

void piazzaSorgente(Partita *p){

	int rigaSorgente, colonnaSorgente;

	Terreno terreno;

	do{

		rigaSorgente = rand()%7+1;
		colonnaSorgente = rand()%7+1;

		terreno = p->mappa[rigaSorgente][colonnaSorgente].terreno;

	}while(terreno==GROTTA || terreno==ACCAMPAMENTO || terreno==TANA);

	p->mappa[rigaSorgente][colonnaSorgente].terreno=SORGENTE;

}




void inizializzaMappa(Partita *p){


	for(int r=0;r<DIM_MAPPA;r++) /* Tramite un for annidato, vengono fatte scorrere tutte le caselle della mappe*/
		for(int c=0;c<DIM_MAPPA;c++){
			p->mappa[r][c].evento_completato=false; /* All'inizio della partita, gli eventi sono ancora tutti da completare, oppure la casella ha un terreno "normale", perciò si setta subito l'evento a false*/
			if(r==CENTRO_MAPPA && c==CENTRO_MAPPA){ /* Se si arriva alla cella [4][4], si "piazza" l'accampamento*/
				p->mappa[r][c].stato = VISITATA;
				p->mappa[r][c].terreno = ACCAMPAMENTO;
			}else{                                   /* Altrimenti, si procederà con gli altri casi*/

				if(r==0 || c==0 || r==8 || c==8){    /* Se la cella si trova sul bordo, verrà settata come SPIAGGIA e, ovviamente, come NASCOSTA */
					p->mappa[r][c].stato = NASCOSTA;
					p->mappa[r][c].terreno = SPIAGGIA;
				}else{
					p->mappa[r][c].stato = NASCOSTA; /* Altrimenti, la cella verrà settata sempre come nascosta, ma gli verrà assegnato il tipo di TERRENO CASUALMENTE */

					int bioma = rand() % 6 + 1;

					if(bioma==1 || bioma==2)
						p->mappa[r][c].terreno = FORESTA;

					if(bioma==3)
						p->mappa[r][c].terreno = PALUDE;

					if(bioma==4)
						p->mappa[r][c].terreno = COLLINA;

					if(bioma==5)
						p->mappa[r][c].terreno = SORGENTE;

					if(bioma==6)
						p->mappa[r][c].terreno = SENTIERO;
				}
			}
		}

	piazzaRelitto(p); /* Attraverso le rispettive funzioni, si settano i luoghi speciali */
	piazzaFaro(p);
	piazzaGrotta(p);
	piazzaTana(p);

	if(!sorgente(p)){ /* Se non c'è nessuna sorgente, ne viene messa una casualmente */

		piazzaSorgente(p);

	}

}

/**
 * @brief Converte una casella nel rispettivo carattere, in base allo STATO e al TERRENO
 * @param c La casella da convertire 
 * @return Il carattere risultante
*/

char carattereCasella(Casella c){

	char carattere;

	if(c.stato==NASCOSTA)
		return '?';
	else{

		if(c.terreno==ACCAMPAMENTO)
			return 'C';

		if(c.terreno==SPIAGGIA)
			carattere = 'b';

		if(c.terreno==FORESTA)
			carattere = 'f';
		

		if(c.terreno==PALUDE)
			carattere = 'p';

		if(c.terreno==COLLINA)
			carattere = 'c';

		if(c.terreno==SORGENTE)
			carattere = 'o';

		if(c.terreno==SENTIERO)
			carattere = 's';

		if(c.terreno==RELITTO)
			carattere = 'r';

		if(c.terreno==GROTTA)
			carattere = 'g';

		if(c.terreno==TANA)
			carattere = 't';

		if(c.terreno==FARO)
			carattere = 'l';

		if(c.stato == VISITATA)
			carattere = carattere - 32;

	}

	return carattere;
}



void stampaMappa(Partita *p, Naufrago *explorer, int rigaExplorer, int colExplorer, int passiFatti){

	if(explorer!=NULL) /* Se c'è un esploratore in missione, si stampano anche passi fatti, numero e salute del naufrago*/
		printf("Mappa dell'isola, Giorno %d | %d passi | Naufrago %d (%d vita)\n", p->giorno_corrente, passiFatti, explorer->id, explorer->salute);
	else
		printf("Mappa dell'isola, Giorno %d\n", p->giorno_corrente);

	printf("  0 1 2 3 4 5 6 7 8\n");      /* Numerazione delle colonne*/

	for(int i=0;i<DIM_MAPPA;i++){
		printf("%d ", i);   /* Numerazione di ogni colonna */
		for(int j=0;j<DIM_MAPPA;j++){
			if(explorer!=NULL && rigaExplorer==i && colExplorer==j){	/* Se c'è l'esploratore in missione e viene trovato, si stampa il carattere relativo */
					printf("# ");
			}
			else{
				printf("%c ", carattereCasella(p->mappa[i][j])); /* altrimenti, stampa il carattere corrispondente*/
			}
		}

		printf("\n");

	}

	printf("Legenda: # naufrago C Accampamento b/B Spiaggia f/F Foresta p/P Palude c/C Collina o/O Sorgente s/S Sentiero\nr/R Relitto g/G Grotta t/T Tana l/L Faro ? nascosta\n");


}