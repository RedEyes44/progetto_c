#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "types.h"
#include "map.h"
#include "camp.h"

int main() {

    Partita p;

    srand(time(NULL));
    

    Naufrago test = {1, 10, NULL};
    inizializzaPartita(p);
    //p.giorno_corrente = 1;

    inizializzaMappa(&p);
    
    //start = menuPrincipale(p);

    gestisciSpedizione(&p, &test);

    //rivelaFaro(&p);
    //rivelaMappa(&p);

    //stampaMappa(&p, NULL, 0, 0, 0);
    return 0;
    
}
