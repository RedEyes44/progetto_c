/**
 * @file events.c
 * @brief Funzioni per la gestione degli eventi di esplorazione del gioco
 * @author Zia Cristiano
 */

#include "events.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Evento della casella SPIAGGIA:
 * Lancia un dado a 6 facce: con risultato >= 3 aggiunge legna al magazzino,
 * altrimenti riduce la salute dell'esploratore.
 */
void eventoSpiaggia(Partita *p, Naufrago *explorer, Casella *c) {
    /* Evita warning del compilatore su parametro non usato in questo evento */
    (void)c;

    /* Tiro casuale tra 1 e 6 (ricordarsi di fare srand() all'avvio del programma) */
    int tiro = (rand() % 6) + 1;
    printf("[Spiaggia] %s esplora la battigia (dado: %d).\n", explorer->nome, tiro);

    if (tiro >= 3) {
        p->magazzino.legna += 1;
        printf("Hai recuperato +1 legna!\n");
    } else {
        explorer->salute -= 10;
        printf("Il sole e la fatica ti provano: -10 salute.\n");
    }
}

/*
 * Evento della casella FORESTA:
 * Puo' far trovare legna e cibo oppure infliggere danni piu' o meno gravi.
 */
void eventoForesta(Partita *p, Naufrago *explorer, Casella *c) {
    (void)c;

    int tiro = (rand() % 6) + 1;
    printf("[Foresta] %s si addentra tra gli alberi (dado: %d).\n", explorer->nome, tiro);

    if (tiro >= 4) {
        /* Esito positivo: raccolta doppia (legna + cibo) */
        p->magazzino.legna += 2;
        p->magazzino.cibo += 1;
        printf("Trovi risorse utili: +2 legna, +1 cibo.\n");
    } else if (tiro == 1) {
        /* Esito peggiore: danno maggiore */
        explorer->salute -= 20;
        printf("Rami e rovi ti feriscono: -20 salute.\n");
    } else {
        /* Esito intermedio negativo (tiro 2 o 3) */
        explorer->salute -= 10;
        printf("Cammino insidioso nella foresta: -10 salute.\n");
    }
}

/*
 * Evento della casella PALUDE:
 * Ambiente difficile: solo un tiro alto (5 o 6) frutta cibo, altrimenti costa salute.
 */
void eventoPalude(Partita *p, Naufrago *explorer, Casella *c) {
    (void)c;

    int tiro = (rand() % 6) + 1;
    printf("[Palude] %s affonda nel fango (dado: %d).\n", explorer->nome, tiro);

    if (tiro >= 5) {
        p->magazzino.cibo += 1;
        printf("Nonostante il fango, scovi +1 cibo.\n");
    } else {
        explorer->salute -= 20;
        printf("L'aria malsana e il fango ti indeboliscono: -20 salute.\n");
    }
}

/*
 * Evento del luogo speciale RELITTO:
 * Se non e' ancora stato completato, permette di ottenere risorse e segnare
 * c->evento_completato = true; in caso di fallimento infligge danni.
 */
void eventoRelitto(Partita *p, Naufrago *explorer, Casella *c) {
    /* Se il relitto e' gia' stato superato in precedenza, non assegna piu' il premio */
    if (c->evento_completato) {
        printf("[Relitto] Hai gia' completato l'esplorazione di questo relitto.\n");
        return;
    }

    int tiro = (rand() % 6) + 1;
    printf("[Relitto] %s ispeziona il relitto (dado: %d).\n", explorer->nome, tiro);

    if (tiro >= 3) {
        p->magazzino.legna += 3;
        p->magazzino.cibo += 2;
        /* Segna il luogo speciale come completato */
        c->evento_completato = true;
        printf("Relitto messo in sicurezza! +3 legna, +2 cibo.\n");
    } else {
        explorer->salute -= 25;
        printf("Una paratia cede all'improvviso: -25 salute.\n");
    }
}

/*
 * Evento del luogo speciale GROTTA:
 * Prova/sfida della grotta; al superamento assegna cibo e imposta evento_completato.
 * (Punto ideale dove inserire in futuro eventuale logica dedicata come Tribonacci).
 */
void eventoGrotta(Partita *p, Naufrago *explorer, Casella *c) {
    if (c->evento_completato) {
        printf("[Grotta] Questa grotta e' gia' stata esplorata.\n");
        return;
    }

    printf("[Grotta] %s entra nella grotta buia.\n", explorer->nome);
    int tiro = (rand() % 6) + 1;

    if (tiro >= 3) {
        p->magazzino.cibo += 3;
        c->evento_completato = true;
        printf("Hai superato la prova della grotta! +3 cibo.\n");
    } else {
        explorer->salute -= 25;
        printf("Trappola nella grotta: -25 salute.\n");
    }
}

/*
 * Evento del luogo speciale TANA:
 * Incontro pericoloso con soglia piu' alta (tiro >= 4); se superato da' cibo
 * e marca la tana come completata.
 */
void eventoTana(Partita *p, Naufrago *explorer, Casella *c) {
    if (c->evento_completato) {
        printf("[Tana] La tana e' gia' stata bonificata.\n");
        return;
    }

    printf("[Tana] %s affronta la minaccia nella tana!\n", explorer->nome);
    int tiro = (rand() % 6) + 1;

    if (tiro >= 4) {
        p->magazzino.cibo += 4;
        c->evento_completato = true;
        printf("Minaccia sconfitta! +4 cibo.\n");
    } else {
        explorer->salute -= 30;
        printf("Contrattacco feroce nella tana: -30 salute.\n");
    }
}

/*
 * Evento del luogo speciale FARO:
 * Chiede il codice di attivazione. Se corretto, imposta c->evento_completato = true
 * e restituisce true per segnalare a map.c la vittoria della partita.
 */
bool eventoFaro(Partita *p, Naufrago *explorer, Casella *c) {
    (void)p;

    /* Se il Faro era gia' stato attivato, la vittoria e' gia' stata raggiunta */
    if (c->evento_completato) {
        printf("[Faro] Il Faro e' gia' stato attivato!\n");
        return true;
    }

    printf("[Faro] %s raggiunge il Faro! Inserisci il codice di attivazione: ",
           explorer->nome);

    int codice = 0;
    /* Verifica che l'utente inserisca un intero valido */
    if (scanf("%d", &codice) != 1) {
        int ch;
        /* Svuota il buffer fino a fine riga per non lasciare caratteri sporchi */
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        printf("Input non valido.\n");
        return false;
    }

    if (codice == 42) {
        c->evento_completato = true;
        printf("Codice corretto! Il Faro si accende: avete vinto la partita!\n");
        return true;
    }

    /* Codice errato: penalita' sulla salute, la partita continua */
    explorer->salute -= 25;
    printf("Codice errato! Il sistema di difesa del Faro ti colpisce: -25 salute.\n");
    return false;
}

/*
 * Smista l'evento in base al tipo di terreno della casella `c`.
 * Restituisce true solo in caso di vittoria (Faro attivato).
 */
bool gestisciEvento(Partita *p, Naufrago *explorer, Casella *c) {
    /* Controllo difensivo sui puntatori per evitare dereferenziazioni nulle */
    if (!p || !explorer || !c) {
        return false;
    }

    bool vittoria = false;

    switch (c->terreno) {
        case SPIAGGIA:
            eventoSpiaggia(p, explorer, c);
            break;
        case FORESTA:
            eventoForesta(p, explorer, c);
            break;
        case PALUDE:
            eventoPalude(p, explorer, c);
            break;
        case RELITTO:
            eventoRelitto(p, explorer, c);
            break;
        case GROTTA:
            eventoGrotta(p, explorer, c);
            break;
        case TANA:
            eventoTana(p, explorer, c);
            break;
        case FARO:
            vittoria = eventoFaro(p, explorer, c);
            break;
        default:
            /* Accampamento, Collina, Sorgente, Sentiero non passano da qui */
            break;
    }

    /* Evita valori negativi di salute (il controllo <= 0 lo fa map.c per la rimozione) */
    if (explorer->salute < 0) {
        explorer->salute = 0;
    }

    return vittoria;
}