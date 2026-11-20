/**
 * @file camp.h
 * @brief Funzioni per la gestione dell'accampamento e della squadra
 * @author Gaffo Luca
 */

#ifndef CAMP_H
#define CAMP_H

/**
 * @brief Crea la lista concatenata che contiene i naufraghi appartenenti alla squadra
 * @param p Partita che contiene al suo interno la lista dei naufraghi
 * 
*/
void inizializzaLista(Partita *p);

/**
 * @brief Aggiunge all'interno della lista un nuovo naufrago
 * @param p Partita che contiene al suo interno la lista dei naufraghi
 * 
*/
void aggiungiNaufrago(Partita *p);

/**
 * @brief Rimuove un naufrago all'interno della lista quando questo termina i PS e sistema i collegamenti tra gli elementi della lista
 * @param p Partita che contiene al suo interno la lista dei naufraghi
 * @param id L'identificatore del naufrago da rimuovere
 * 
*/
void rimuoviNaufrago(Partita *p, int id);

#endif
