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


/**
 * @brief Funzione che mostra il menu principale di avvio del gioco, gestendo l'inserimento del morse sos per i trucchi (intanto la metto qua)
 * @param p Partita, che contiene i dati del gioco da avviare
 *
*/
void menuPrincipale(Partita *p);

/**
 * @brief Funzione che mostra i nomi di chi ha lavorato al progetto del gioco
 *
*/
void mostraCrediti();

/**
 * @brief Funzione che dal menu principale permette di mostrare il menu dei trucchi
 * @param p Partita, che contiene i dati del gioco da avviare
 *
*/
void menuTrucchi(Partita *p);

/**
 * @brief Funzione che permette di pulire il buffer dai caratteri in eccesso
 *
*/
void pulisciBuffer();

/**
 * @brief Funzione che permette di impostare un valore personalizzato dei ps che i naufraghi hanno ad inizio partita
 * @param p Partita, che contiene i dati del gioco da avviare
 *
*/
void impostaSalute(Partita *p);

/**
 * @brief Funzione che permette di impostare un numero personalizzato di naufraghi disponibili ad inizio partita
 * @param p Partita, che contiene i dati del gioco da avviare
 *
*/
void numeroNaufraghi(Partita *p);

/**
 * @brief Funzione che permette di impostare un numero personalizzato di collezionabili presenti in magazzino ad inizio partita e di avere già le strutture avanzate
 * @param p Partita, che contiene i dati del gioco da avviare
 *
*/
void impostaMagazzino(Partita *p);

/**
 * @brief Funzione che permette di rivelare o meno le caselle della mappa gia all'inizio della partita
 * @param p Partita, che contiene i dati del gioco da avviare
 *
*/
void rivelaCaselle(Partita *p);

/**
 * @brief Funzione che permette di rendere disponibile sin dal primo turno la missione finale da superare per vincere il gioco
 * @param p Partita, che contiene i dati del gioco da avviare
 *
*/
void sbloccaMissioneFinale(Partita *p)

#endif
