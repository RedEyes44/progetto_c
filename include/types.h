/** @file types.h @brief ... */

#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>


#define DIM_MAPPA 9 /**< Dimensione della mappa (9X9) */
#define CENTRO_MAPPA 4 /**< Posizione dell'accampamento (4X4) */
#define MAX_SALUTE 10 /**< Salute massima del naufrago */
#define SALUTE_MIN_AZIONE 3 /**< Salute minima per iniziare una spedizione o raccogliere risorse */
#define MAX_PASSI 8 /**< Numeri di passi massimi in una spedizione */
#define MAX_GIORNI 30 /**< Massimo di giorni per finire il gioco */
#define DIM_CODICE_FARO 4 /**< Cifre del codice del faro */
#define MAX_TENTATIVI_FARO 8 /**< Numero massimo di tentativi */

/**
 * @brief Tipi di terreno possibili per la singola casella della mappa.
 */

typedef enum Terreno{

	ACCAMPAMENTO,
	SPIAGGIA,
	FORESTA,
	PALUDE,
	COLLINA,
	SORGENTE,
	SENTIERO,
	FARO,
	RELITTO,
	GROTTA,
	TANA

}Terreno;

/**
 * @brief Stato per la singola casella.
 */

typedef enum Stato_Casella{

	NASCOSTA, /**< Caselle con ?*/
	RIVELATA, /**< Lettera minuscola, vista da una collina o tramite un sentiero*/
	VISITATA  /**< Lettera maiuscola, un naufrago ci è "passato sopra"*/


}Stato_Casella;


/**
 * @brief Struttura del singolo naufrago, servirà per la squadra dei naufraghi.
 */
typedef struct Naufrago{

	int id;               /**< Identificatore unico del naufrago */
	int salute;           /**<  Punti salute del naufrago*/
	struct Naufrago *next;/**<  Puntantore al naufrago successivo nella squadra*/

}Naufrago;

/**
 * @brief Struttura per la singola casella della mappa.
 */

typedef struct Casella{

	Terreno terreno;   /**< Tipo di terreno della casella*/
	Stato_Casella stato; /**< Stato di visibilità della casella*/  
	bool evento_completato;  /**< Se si tratta di un luogo speciale, passerà a true quando l'evento verrà completato*/


}Casella;

/**
 * @brief Struttura del magazzino, con tutti i consumabili, i materiali e gli oggetti speciali
 * 
 */


typedef struct Magazzino{

	int cibo, acqua, legna, corda;  /**<  Contatori dei consumabili e dei materiali base */
	bool olio, lente, chiave; /**<  Elementi chiave del faro*/
	bool rete, cisterna;  /**< Oggetti "raccoglitori" */

}Magazzino;

/**
 * @brief Struttura della partita. Contiene tutte le variabili che mutano nel tempo.
 * 
 *  */



typedef struct Partita{

	int giorno_corrente; /**< Giorno corrente, se arriva a 30, la partita è persa */

	Naufrago *squadra;  /**< L'array dinamico della squadra */

	int count_id_naufraghi;  /**<  Tiene traccia dell'id dell'ultimo naufrago arrivato. 
	Ogni volta che si aggiunge un naufrago viene incrementato (così facendo, se ad esempio il naufrago 4 muore, il nuovo naufrago non avrà come numero il 4 ma il 5)  */

	Casella mappa[DIM_MAPPA][DIM_MAPPA];  /**< La matrice della mappa, di dimensione 9X9 */

	Magazzino magazzino;  /**< Magazzino delle risorse */

	bool sorgente;  /**< Se è true, la raccolta all'accampamento fornisce +2 acqua a tutti i naufraghi */

	int codice_faro[DIM_CODICE_FARO];  /**< Array con le 4 cifre del codice del faro */

	bool trucchi_attivi;  /**< Flag per i trucchi */


}Partita;


 
#endif