#include "../../Codice/Modello logico/Headers/Biblioteca.h"
#include "../../Codice/Modello logico/Headers/Libro.h"
#include "../../Codice/Modello logico/Headers/Media.h"
#include "../include/assert_utils.h"
#include <string>


// Metodo per testare l'aggiunta di un media alla biblioteca
bool testAggiungiMedia(){
    std::string id = "AB";
    Biblioteca biblio(id);

    Media* libro = new Libro("Il Signore degli Anelli", "Fantasy", 1954, "Italiano", "lotr.jpg", true, 3, "978-0261102385", "J.R.R. Tolkien", "Allen & Unwin", 1216, 0, "Scaffale A1", 4.9);
    biblio.aggiungiMedia(libro);

    ASSERT(biblio.getNumeroTotaleMedia() == 1, "Il numero totale di media dovrebbe essere 1");
    ASSERT(biblio.esisteMedia("Il Signore degli Anelli", 1954, "Fantasy"), "Il libro 'Il Signore degli Anellis' non è stato trovato");

    return true;
}


// Metodo per testare la rimozione di un media dalla biblioteca
bool testRimuoviMedia(){
    std::string id = "CD";
    Biblioteca biblio(id);

    Media* libro = new Libro("Il Signore degli Automi", "Fantasy", 1954, "Italiano", "lotr.jpg", true, 3, "978-0261102385", "J.R.R. Tolkien", "Allen & Unwin", 1216, 0, "Scaffale A1", 4.9);

    biblio.aggiungiMedia(libro);

    std::string mediaId = biblio.cercaMediaDaT_A_G("Il Signore degli Automi", 1954, "Fantasy")->getId();

    bool rimosso = biblio.rimuoviMedia(mediaId);

    ASSERT(rimosso, "Il media non è stato rimosso");
    ASSERT(!biblio.esisteMedia("Il Signore degli Automi", 1954, "Fantasy"), "Il media rimosso è ancora presente");

    return true;
}


// Metodo per testare prestito e restituzione di un media
bool testPrestitoRestituzione() {
    std::string id = "XY";
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
