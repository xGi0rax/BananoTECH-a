#include <iostream>

// biblioteca
bool testAggiungiMedia();
bool testRimuoviMedia();
bool testPrestitoRestituzione();
bool testFiltra();

// xmlio
bool testSalvaSuFileX();
bool testCaricaDaFileX();

// jsonio
bool testSalvaSuFileJ();
bool testCaricaDaFileJ();

using namespace std;

int main(){

    // Test per la classe BIBLIOTECA
    int falliti = 0;

    cout << ">> Test: aggiunta media... ";
    if (testAggiungiMedia()) cout << "OK\n";
    else { cout << "Fallito\n"; falliti++; }

    cout << ">> Test: rimozione media... ";
    if (testRimuoviMedia()) cout << "OK\n";
    else { cout << "Fallito\n"; falliti++; }

    cout << ">> Test: prestito e restituzione... ";
    if (testPrestitoRestituzione()) cout << "OK\n";
    else { cout << "Fallito\n"; falliti++; }

    cout << ">> Test: filtraggio media... ";
    if (testFiltra()) cout << "OK\n";
    else { std::cout << "Fallito\n"; falliti++; }

    cout << "==========================\n";
    if (falliti == 0)
        cout << "Tutti i test per la classe BIBLIOTECA sono passati!\n";
    else
        cout << "Alcuni test sono falliti: " << falliti << "\n";

    cout << "==========================\n";


    // Test per la classe XMLIO
    falliti = 0;
    cout << "\n>> Test: salvataggio su file XML... ";
    if (testSalvaSuFileX()) cout << "OK\n";
    else { cout << "Fallito\n"; falliti++; }

    cout << ">> Test: caricamento da file XML... ";
    if (testCaricaDaFileX()) cout << "OK\n";
    else { cout << "Fallito\n"; falliti++; }

    cout << "==========================\n";
    if (falliti == 0)
        cout << "Tutti i test per la classe XMLIO sono passati!\n";
    else
        cout << "Alcuni test sono falliti: " << falliti << "\n";
    cout << "==========================\n";


    // Test per la classe JSONIO
    falliti = 0;
    cout << "\n>> Test: salvataggio su file JSON... ";
    if (testSalvaSuFileJ()) cout << "OK\n";
    else { cout << "Fallito\n"; falliti++; }

    cout << ">> Test: caricamento da file JSON... ";
    if (testCaricaDaFileJ()) cout << "OK\n";
    else { cout << "Fallito\n"; falliti++; }

    cout << "==========================\n";
    if (falliti == 0)
        cout << "Tutti i test per la classe JSONIO sono passati!\n";
    else
        cout << "Alcuni test sono falliti: " << falliti << "\n";
    cout << "==========================\n";

    return falliti;
}