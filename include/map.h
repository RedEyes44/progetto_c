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

/**
 * 
 * @brief Imposta lo stato tutte le caselle della mappa a RIVELATA, eccetto quelle già scoperte. Da usare per il menu' trucchi.
 * @param p Partita a cui fa riferimento la mappa
 */

void rivelaMappa(Partita *p);

/**
 * 
 * @brief Rende visibile la casella del faro. Da usare per il menu' trucchi.
 * @param p Partita a cui fa riferimento la mappa
 * 
 */
void rivelaFaro(Partita *p);

/**
 * 
 * @brief Fa muovere il simbolo del naufrago in spedizione (#) dopo aver letto il comando da tastiera (w,a,s,d o r).
 * @bref Inoltre, aggiorna i passi fatti e cambia lo stato delle caselle calpestate in VISITATA, e gestisce direttamente COLLINA, SENTIERO E SORGENTE
 * @param p Partita a cui fa riferimento la 
 * @param explorer Puntatore al naufrago in spedizione
 * @return true olo se il giocatore vince al faro, false in tutti gli altri casi
 * 
 */


bool gestisciSpedizione(Partita *p, Naufrago *explorer);

#endif