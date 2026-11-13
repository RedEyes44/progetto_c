/**
 * @file map.h
 * @brief Funzioni per la generazione procedurale e stampa della mappa.
 * @author Tonetto Riccardo
 */


#ifndef MAP_H
#define MAP_H

#include "types.h"

/**
 * @brief Genera la mappa di gioco proceduralmente: il bordo esterno come la spiaggia, il centro come l'accampamento, i tipi di terreno, le sorgenti e i luoghi speciali
 * @param p Partita a cui fa riferimento la mappa
 * 
*/

void inizializzaMappa(Partita *p);

/**
 * @brief Mostra a schermo lo stato attuale della mappa
 * @param p Partita a cui fa riferimento la mappa
 * @param explorer Puntatore all'eventuale naufrago in esplorazione
 * @param rigaExplorer Riga della matrice su cui si trova attualmente l'eventuale Explorer
 * @param colExplorer Colonna della matrice su cui si trova attualmente l'eventuale Explorer
 * @param passiFatti Numero di passi fatta dall'eventuale Explorer
 * 
*/

void stampaMappa(Partita *p, Naufrago *explorer, int rigaExplorer, int colExplorer, int passiFatti);




#endif