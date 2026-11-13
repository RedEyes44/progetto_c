#include "types.h"
#include "map.h"
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void piazzaRelitto(Partita *p){


	int rigaRelitto, colonnaRelitto;

	do{

		rigaRelitto = rand()%DIM_MAPPA;
		colonnaRelitto = rand()%DIM_MAPPA;

	}while(p->mappa[rigaRelitto][colonnaRelitto].terreno!=SPIAGGIA);

	p->mappa[rigaRelitto][colonnaRelitto].terreno = RELITTO;


}




void piazzaFaro(Partita *p){

	int rigaFaro, colonnaFaro;

	do{

		rigaFaro = rand()%DIM_MAPPA;
		colonnaFaro = rand()%DIM_MAPPA;

	}while(p->mappa[rigaFaro][colonnaFaro].terreno!=SPIAGGIA);

	p->mappa[rigaFaro][colonnaFaro].terreno = FARO;


}

void piazzaGrotta(Partita *p){

	int rigaGrotta, colonnaGrotta;

	do{

		rigaGrotta = rand()%7+1;
		colonnaGrotta = rand()%7+1;

	}while(abs(rigaGrotta-CENTRO_MAPPA) + abs(colonnaGrotta-CENTRO_MAPPA) < 3);

	p->mappa[rigaGrotta][colonnaGrotta].terreno = GROTTA;


}

void piazzaTana(Partita *p){

	int rigaTana, colonnaTana;

	do{

		rigaTana = rand()%7+1;
		colonnaTana = rand()%7+1;

	}while(abs(rigaTana-CENTRO_MAPPA) + abs(colonnaTana-CENTRO_MAPPA)<3 || p->mappa[rigaTana][colonnaTana].terreno==GROTTA);

	p->mappa[rigaTana][colonnaTana].terreno = TANA;

}

bool sorgente(Partita *p){

	

	for(int i=0;i<DIM_MAPPA;i++)
		for(int j=0;j<DIM_MAPPA;j++)
			if(p->mappa[i][j].terreno==SORGENTE)
					return true;


	return false;
}

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


	for(int r=0;r<DIM_MAPPA;r++)
		for(int c=0;c<DIM_MAPPA;c++){
			p->mappa[r][c].evento_completato=false;
			if(r==CENTRO_MAPPA && c==CENTRO_MAPPA){
				p->mappa[r][c].stato = VISITATA;
				p->mappa[r][c].terreno = ACCAMPAMENTO;
			}else{

				if(r==0 || c==0 || r==8 || c==8){
					p->mappa[r][c].stato = NASCOSTA;
					p->mappa[r][c].terreno = SPIAGGIA;
				}else{
					p->mappa[r][c].stato = NASCOSTA;

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

	piazzaRelitto(p);
	piazzaFaro(p);
	piazzaGrotta(p);
	piazzaTana(p);

	if(!sorgente(p)){

		piazzaSorgente(p);

	}

}

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

	if(explorer!=NULL)
		printf("Mappa dell'isola, Giorno %d | %d passi | Naufrago %d (%d vita)\n", p->giorno_corrente, passiFatti, explorer->id, explorer->salute);
	else
		printf("Mappa dell'isola, Giorno %d\n", p->giorno_corrente);

	printf("  0 1 2 3 4 5 6 7 8\n");

	for(int i=0;i<DIM_MAPPA;i++){
		printf("%d ", i);
		for(int j=0;j<DIM_MAPPA;j++){
			if(explorer!=NULL && rigaExplorer==i && colExplorer==j){	
					printf("# ");
			}
			else{
				printf("%c ", carattereCasella(p->mappa[i][j]));
			}
		}

		printf("\n");

	}

	printf("Legenda: # naufrago C Accampamento b/B Spiaggia f/F Foresta p/P Palude c/C Collina o/O Sorgente s/S Sentiero\nr/R Relitto g/G Grotta t/T Tana l/L Faro ? nascosta\n");


}






