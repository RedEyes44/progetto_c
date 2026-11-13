#include "types.h"
#include "map.h"
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

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





