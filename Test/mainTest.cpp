#include <iostream>

bool testAggiungiMedia();
bool testRimuoviMedia();
bool testPrestitoRestituzione();

int main(){
    int falliti = 0;

    std::cout << ">> Test: aggiunta media... ";
    if (testAggiungiMedia()) std::cout << "OK\n";
    else { std::cout << "Fallito\n"; falliti++; }

    std::cout << ">> Test: rimozione media... ";
    if (testRimuoviMedia()) std::cout << "OK\n";
    else { std::cout << "Fallito\n"; falliti++; }

    std::cout << ">> Test: prestito e restituzione... ";
    if (testPrestitoRestituzione()) std::cout << "OK\n";
    else { std::cout << "Fallito\n"; falliti++; }

    std::cout << "\n==========================\n";
    if (falliti == 0)
        std::cout << "Tutti i test sono passati!\n";
    else
        std::cout << "Alcuni test sono falliti: " << falliti << "\n";

    return falliti;
}