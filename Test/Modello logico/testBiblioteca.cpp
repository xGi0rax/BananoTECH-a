#include "../../Codice/Modello logico/Headers/Biblioteca.h"
#include "../../Codice/Modello logico/Headers/Libro.h"
#include "../../Codice/Modello logico/Headers/Vinile.h"
#include "../../Codice/Modello logico/Headers/GiocoDaTavolo.h"
#include "../../Codice/Modello logico/Headers/Rivista.h"
#include "../../Codice/Modello logico/Headers/Film.h"
#include "../../Codice/Modello logico/Headers/Media.h"
#include "../include/assert_utils.h"
#include <string>
#include <iostream>

using namespace std;


// Test di aggiungiMedia, getNumeroTotaleMedia ed esisteMedia
bool testAggiungiMedia(){
    string id = "AB";
    Biblioteca biblio(id);

    Media* libro = new Libro("Il Signore degli Anelli", "Fantasy", 1954, "Italiano", "lotr.jpg", true, 3, "978-0261102385", "J.R.R. Tolkien", "Allen & Unwin", 1216, 0, "Scaffale A1", 4.9);
    biblio.aggiungiMedia(libro);

    ASSERT(biblio.getNumeroTotaleMedia() == 1, "Il numero totale di media dovrebbe essere 1");
    ASSERT(biblio.esisteMedia("Il Signore degli Anelli", 1954, "Fantasy"), "Il libro 'Il Signore degli Anellis' non è stato trovato");

    return true;
}


// Test di rimuoviMedia e cercaMediaDaT_A_G
bool testRimuoviMedia(){
    string id = "CD";
    Biblioteca biblio(id);

    Media* libro = new Libro("Il Signore degli Automi", "Fantasy", 1954, "Italiano", "lotr.jpg", true, 3, "978-0261102385", "J.R.R. Tolkien", "Allen & Unwin", 1216, 0, "Scaffale A1", 4.9);

    biblio.aggiungiMedia(libro);

    string mediaId = biblio.cercaMediaDaT_A_G("Il Signore degli Automi", 1954, "Fantasy")->getId();

    bool rimosso = biblio.rimuoviMedia(mediaId);

    ASSERT(rimosso, "Il media non è stato rimosso");
    ASSERT(!biblio.esisteMedia("Il Signore degli Automi", 1954, "Fantasy"), "Il media rimosso è ancora presente");

    return true;
}


// Test di carcaMediaDaID, prendiInPrestito e restituisci
bool testPrestitoRestituzione() {
    string id = "XY";
    Biblioteca biblio(id);

    Media* libro = new Libro("Il Signore degli Automi", "Fantasy", 1954, "Italiano", "lotr.jpg", true, 3, "978-0261102385", "J.R.R. Tolkien", "Allen & Unwin", 1216, 0, "Scaffale A1", 4.9);
    libro->setNumeroCopie(2);
    libro->setDisponibilita(true);

    biblio.aggiungiMedia(libro);

    Media* trovato = biblio.cercaMediaDaID(libro->getId());
    ASSERT(trovato != nullptr, "Il libro non è stato trovato dopo l'aggiunta");

    ASSERT(biblio.prendiInPrestito(trovato), "Prestito fallito");
    ASSERT(trovato->getInPrestito() == 1, "Numero di copie in prestito errato dopo il prestito");
    ASSERT(biblio.restituisci(trovato), "Restituzione fallita");
    ASSERT(trovato->getInPrestito() == 0, "Numero di copie in prestito errato dopo la restituzione");

    return true;
}


// Test di filtra
bool testFiltra(){
    string id = "EF";
    Biblioteca biblio(id);

    Media* libro1 = new Libro("Libro1", "Fantasy", 1754, "Italiano", "lotr.jpg", true, 3, "978-0261102385", "J.R.R. Tolkien", "Allen & Unwin", 1210, 0, "Scaffale A1", 4.0);
    Media* libro2 = new Libro("Libro2", "Romanzo", 1954, "Italiano", "lotr.jpg", true, 3, "978-0261102385", "J.R.R. Tolkien", "Allen & Unwin", 116, 0, "Scaffale A1", 4.7);
    Media* libro3 = new Libro("Libro3", "Fantasy", 1954, "Italiano", "lotr.jpg", true, 3, "978-0261102385", "J.R.R. Tolkien", "Allen & Unwin", 219, 0, "Scaffale A1", 2.9);
    Media* vinile1 = new Vinile("Vinile1", "Rock", 1954, "Italiano", "lotr.jpg", true, 3, "Giacomo Nalotto", 12, 124, 0, "Scaffale A1", 3.7);
    Media* vinile2 = new Vinile("Vinile2", "Rock", 1954, "Italiano", "lotr.jpg", true, 3, "Giacomo Nalotto", 12, 124, 0, "Scaffale A1", 2.3);
    Media* film1 = new Film("Film1", "Azione", 1754, "Italiano", "lotr.jpg", true, 3, "Giacomo Giora", 121, {"Giacomo Giora", "Giacomo Nalotto"}, 0, "Scaffale A1", 4.9);

    biblio.aggiungiMedia(libro1);
    biblio.aggiungiMedia(libro2);
    biblio.aggiungiMedia(libro3);
    biblio.aggiungiMedia(vinile1);
    biblio.aggiungiMedia(vinile2);
    biblio.aggiungiMedia(film1);

    vector<Media*> risultati = biblio.filtra("", "", "", 1200, 1850, "", 0.0, 5.0);

    ASSERT(risultati.size() == 2, "Il numero di risultati filtrati non è corretto");

    cout << "\nRisultati del filtraggio:\n";
    for (Media* el : risultati){
        el->stampaInfo();
        cout << "---------\n";
    }

    return true;
}
