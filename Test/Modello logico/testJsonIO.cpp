#include "../../Codice/Modello logico/Headers/Biblioteca.h"
#include "../../Codice/Modello logico/Headers/Libro.h"
#include "../../Codice/Modello logico/Headers/Vinile.h"
#include "../../Codice/Modello logico/Headers/GiocoDaTavolo.h"
#include "../../Codice/Modello logico/Headers/Rivista.h"
#include "../../Codice/Modello logico/Headers/Film.h"
#include "../../Codice/Modello logico/Headers/Media.h"
#include "../../Codice/Modello logico/Headers/JsonIO.h"
#include "../../Codice/Modello logico/Headers/IOStrategy.h"
#include "../include/assert_utils.h"
#include <string>
#include <iostream>

using namespace std;


bool testSalvaSuFileJ(){
    string id = "VC";
    Biblioteca biblioteca(id);

    Media* libro1 = new Libro("Libro1", "Fantasy", 1754, "Italiano", "lotr.jpg", true, 3, "978-0261102385", "J.R.R. Tolkien", "Allen & Unwin", 1210, 0, "Scaffale A1", 4.0);
    Media* libro2 = new Libro("Libro2", "Romanzo", 1954, "Italiano", "lotr.jpg", true, 3, "978-0261102385", "J.R.R. Tolkien", "Allen & Unwin", 116, 0, "Scaffale A1", 4.7);
    Media* libro3 = new Libro("Libro3", "Fantasy", 1954, "Italiano", "lotr.jpg", true, 3, "978-0261102385", "J.R.R. Tolkien", "Allen & Unwin", 219, 0, "Scaffale A1", 2.9);
    Media* vinile1 = new Vinile("Vinile1", "Rock", 1954, "Italiano", "lotr.jpg", true, 3, "Giacomo Nalotto", 12, 124, 0, "Scaffale A1", 3.7);
    Media* vinile2 = new Vinile("Vinile2", "Rock", 1954, "Italiano", "lotr.jpg", true, 3, "Giacomo Nalotto", 12, 124, 0, "Scaffale A1", 2.3);
    Media* film1 = new Film("Film1", "Azione", 1754, "Italiano", "lotr.jpg", true, 3, "Giacomo Giora", 121, {"Giacomo Giora", "Giacomo Nalotto"}, 0, "Scaffale A1", 4.9);

    biblioteca.aggiungiMedia(libro1);
    biblioteca.aggiungiMedia(libro2);
    biblioteca.aggiungiMedia(libro3);
    biblioteca.aggiungiMedia(vinile1);
    biblioteca.aggiungiMedia(vinile2);
    biblioteca.aggiungiMedia(film1);

    JsonIO jsonIO;
    string jsonFilePath = "biblioteca_testSalva.json";
    bool salvato = jsonIO.salvaSuFile(biblioteca, jsonFilePath);

    ASSERT(salvato, "Errore nel salvataggio del file JSON");

    return true;
}

bool testCaricaDaFileJ(){
    string id = "VC";
    Biblioteca biblioteca(id);

    JsonIO jsonIO;
    string jsonFilePath = "biblioteca_testCarica.json";
    bool caricato = jsonIO.caricaDaFile(biblioteca, jsonFilePath);
    
    ASSERT(caricato, "Errore nel caricamento del file XML");
    ASSERT(biblioteca.getNumeroTotaleMedia() == 5, "Il numero totale di media non corrisponde a quello atteso dopo il caricamento");

    return true;
}