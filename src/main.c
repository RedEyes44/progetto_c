#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "types.h"
#include "map.h"

int main() {

    Partita p;

    srand(time(NULL));

    inizializzaMappa(&p);

    stampaMappa(&p, NULL, 0, 0, 0);
    return 0;
    
}