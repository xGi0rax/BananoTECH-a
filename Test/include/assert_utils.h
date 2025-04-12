#ifndef ASSERT_UTILS_H
#define ASSERT_UTILS_H

#include <iostream>

#define ASSERT(condizione, messaggio) \
    if(!(condizione)){ \
        return false; \
    }

#endif // ASSERT_UTILS_H

// File di utilità che contiene una macro per le asserzioni (test di unità)
// La macro ASSERT verifica una condizione e stampa un messaggio di errore se la condizione è falsa