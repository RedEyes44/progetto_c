/**
 * @file events.h
 * @brief Dichiarazioni delle funzioni di gestione degli eventi di esplorazione.
 * @author Zia Cristiano
 */

#ifndef EVENTS_H
#define EVENTS_H

#include <stdbool.h>
#include "types.h"

/**
 * @brief Smista e risolve l'evento associato alla casella raggiunta dal naufrago.
 * @param p Puntatore alla struttura della partita in corso.
 * @param explorer Puntatore al naufrago attualmente in spedizione.
 * @param c Puntatore alla casella su cui si trova il naufrago.
 * @return true se l'evento comporta la vittoria della partita (Faro attivato), false altrimenti.
 */
bool gestisciEvento(Partita *p, Naufrago *explorer, Casella *c);

/**
 * @brief Gestisce l'evento casuale su una casella di tipo SPIAGGIA.
 * @param p Puntatore alla struttura della partita in corso.
 * @param explorer Puntatore al naufrago attualmente in spedizione.
 * @param c Puntatore alla casella di spiaggia.
 */
void eventoSpiaggia(Partita *p, Naufrago *explorer, Casella *c);

/**
 * @brief Gestisce l'evento casuale su una casella di tipo FORESTA.
 * @param p Puntatore alla struttura della partita in corso.
 * @param explorer Puntatore al naufrago attualmente in spedizione.
 * @param c Puntatore alla casella di foresta.
 */
void eventoForesta(Partita *p, Naufrago *explorer, Casella *c);

/**
 * @brief Gestisce l'evento casuale su una casella di tipo PALUDE.
 * @param p Puntatore alla struttura della partita in corso.
 * @param explorer Puntatore al naufrago attualmente in spedizione.
 * @param c Puntatore alla casella di palude.
 */
void eventoPalude(Partita *p, Naufrago *explorer, Casella *c);

/**
 * @brief Gestisce l'evento del luogo speciale RELITTO.
 * @param p Puntatore alla struttura della partita in corso.
 * @param explorer Puntatore al naufrago attualmente in spedizione.
 * @param c Puntatore alla casella del relitto.
 */
void eventoRelitto(Partita *p, Naufrago *explorer, Casella *c);

/**
 * @brief Gestisce l'evento del luogo speciale GROTTA.
 * @param p Puntatore alla struttura della partita in corso.
 * @param explorer Puntatore al naufrago attualmente in spedizione.
 * @param c Puntatore alla casella della grotta.
 */
void eventoGrotta(Partita *p, Naufrago *explorer, Casella *c);

/**
 * @brief Gestisce l'evento del luogo speciale TANA.
 * @param p Puntatore alla struttura della partita in corso.
 * @param explorer Puntatore al naufrago attualmente in spedizione.
 * @param c Puntatore alla casella della tana.
 */
void eventoTana(Partita *p, Naufrago *explorer, Casella *c);

/**
 * @brief Gestisce l'evento del luogo speciale FARO e il tentativo di attivazione.
 * @param p Puntatore alla struttura della partita in corso.
 * @param explorer Puntatore al naufrago attualmente in spedizione.
 * @param c Puntatore alla casella del faro.
 * @return true se il Faro viene attivato con successo, false altrimenti.
 */
bool eventoFaro(Partita *p, Naufrago *explorer, Casella *c);

#endif /* EVENTS_H */