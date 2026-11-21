#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "types.h"
#include "map.h"

int main() {

    Partita p;

    srand(time(NULL));
    
    //menuPrincipale(p);

    Naufrago test = {1, 10, NULL};

    p.giorno_corrente = 1;

    inizializzaMappa(&p);

    gestisciSpedizione(&p, &test);

    //rivelaFaro(&p);
    //rivelaMappa(&p);

    //stampaMappa(&p, NULL, 0, 0, 0);
    return 0;
    
}
