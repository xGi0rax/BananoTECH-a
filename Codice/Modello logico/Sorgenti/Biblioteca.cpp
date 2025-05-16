#include "../Headers/Biblioteca.h"
#include "../Headers/Media.h"
#include "../Headers/Film.h"
#include "../Headers/Libro.h"
#include "../Headers/Vinile.h"
#include "../Headers/GiocoDaTavolo.h"
#include "../Headers/Rivista.h"
#include <QDebug>


Biblioteca::Biblioteca(string& idBiblio) : idBiblioteca(idBiblio), nextIdmedia(1) {}

Biblioteca::~Biblioteca() {
    for (auto media : listaMedia) {
        delete media;
    }
}

void Biblioteca::aggiungiMedia(Media* media) {
    // Controllo se il media esiste già in biblioteca
    if (esisteMedia(media->getTitolo(), media->getAnno(), media->getGenere())) {
        // throw std::runtime_error("Il media esiste già in biblioteca.");
        
        //##############################
        // TO-DO: Chiedere all'utente tramite gui se si vuole incrementare il numero di copie del media esistente
        //##############################
        
        // Se l'utente accetta, recupero il media dalla listaMedia ed incremento il numero di copie
        Media* mediaEsistente = cercaMediaDaT_A_G(media->getTitolo(), media->getAnno(), media->getGenere());
        mediaEsistente->setNumeroCopie(mediaEsistente->getNumeroCopie() + 1);

    }else{ // altrimenti aggiungo il nuovo media alla lista
        media->setId(idBiblioteca + "-" + std::to_string(nextIdmedia++));
        listaMedia.push_back(media);
    }
}

bool Biblioteca::esisteMedia(const string& titolo, int anno, const string& genere) const {
    for (const Media* m : listaMedia) {
        if (m->getTitolo() == titolo && m->getAnno() == anno && m->getGenere() == genere) {
            return true;
        }
    }
    return false;
}

Media* Biblioteca::cercaMediaDaT_A_G(const string& titolo, int anno, const string& genere) const {
    for (Media* m : listaMedia) {
        if (m->getTitolo() == titolo && m->getAnno() == anno && m->getGenere() == genere) {
            return m;
        }
    }
    // throw std::runtime_error("Il media non esiste in biblioteca.");
    return nullptr; // Se non trovato, ritorna nullptr
}

bool Biblioteca::modificaMedia(const string& id, Media* media) {
    for (auto it = listaMedia.begin(); it != listaMedia.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it; // Elimina il vecchio media
            *it = media; // Sostituisci con il nuovo media
            return true;
        }
    }
    return false;
}

bool Biblioteca::rimuoviMedia(string& id){
    for (auto it = listaMedia.begin(); it != listaMedia.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            listaMedia.erase(it);
            return true;
        }
    }
    return false;
}

Media* Biblioteca::cercaMediaDaID(const string& id) const{
    for (Media* media : listaMedia) {
        if (media->getId() == id) {
            return media;
        }
    }
    return nullptr;
}

vector<Media*> Biblioteca::filtra(const string& titolo, const string& tipoMedia, const string& genere, double ratingMin, double ratingMax, bool disponibilita, const string& lingua, int annoMin, int annoMax) const {
    
    vector<Media*> risultati;

    for (auto media : listaMedia) {
        // Variabile per tenere traccia se il media corrente corrisponde ai filtri
        bool corrisponde = true; // Inizialmente assumiamo che corrisponda a tutti i filtri

        // Filtro per tipo
        if (!tipoMedia.empty()) {
            if (tipoMedia == "Libro" && dynamic_cast<Libro*>(media) == nullptr)
                corrisponde = false;  // Significa che sto cercando un tipoMedia Libro e l'oggetto attuale non è un Libro
            else if (tipoMedia == "Film" && dynamic_cast<Film*>(media) == nullptr)
                corrisponde = false;
            else if (tipoMedia == "Rivista" && dynamic_cast<Rivista*>(media) == nullptr)
                corrisponde = false;
            else if (tipoMedia == "Vinile" && dynamic_cast<Vinile*>(media) == nullptr)
                corrisponde = false;
            else if (tipoMedia == "Gioco da tavolo" && dynamic_cast<GiocoDaTavolo*>(media) == nullptr)
                corrisponde = false;
        }
        // Filtro per titolo
        if (corrisponde && !titolo.empty()) {
            if (media->getTitolo().find(titolo) == string::npos)
                corrisponde = false;
        }
        // Filtro per genere
        if (corrisponde && !genere.empty()) {
            if (media->getGenere().find(genere) == string::npos)
                corrisponde = false;
        }
        // Filtro per rating
        if (corrisponde) {
            if (media->getRating() < ratingMin || media->getRating() > ratingMax){
                corrisponde = false;
            }
        }
        // Filtro per disponibilità
        if (corrisponde) {
            if ((disponibilita && !media->getDisponibilita()) || (!disponibilita && media->getDisponibilita())) {
            corrisponde = false;
            }
        }
        // Filtro per lingua
        if (corrisponde && !lingua.empty()) {
            if (media->getLingua() != lingua){
                corrisponde = false;
            }
        }
        // Filtro per anno
        if (corrisponde) {
            if (media->getAnno() < annoMin || media->getAnno() > annoMax)
                corrisponde = false;
        }        
        
        // Aggiunta media ai risultati se corrisponde ai filtri
        if (corrisponde) {
            risultati.push_back(media);
        }
    }
    return risultati;
}

int Biblioteca::getNumeroTotaleMedia() const {
    return listaMedia.size();
}

bool Biblioteca::prendiInPrestito(const Media* media){
    Media* mediaInBiblioteca = cercaMediaDaID(media->getId());
    if(mediaInBiblioteca != nullptr && mediaInBiblioteca->getDisponibilita()){
        mediaInBiblioteca->setInPrestito(mediaInBiblioteca->getInPrestito() + 1);
        if(mediaInBiblioteca->getInPrestito() == mediaInBiblioteca->getNumeroCopie()){
            mediaInBiblioteca->setDisponibilita(false);
        }
        return true;        
    } else{
        //throw BibliotecaException("Media non trovato nella biblioteca (ID: " + media->getId() + ")");
    }
    return false;
}

bool Biblioteca::restituisci(const Media* media){
    Media* mediaInBiblioteca = cercaMediaDaID(media->getId()); // Cerca il media in biblioteca
    if(mediaInBiblioteca != nullptr){
        if(mediaInBiblioteca->getInPrestito() > 0){ // Controlla se ci sono copie in prestito 
            mediaInBiblioteca->setInPrestito(mediaInBiblioteca->getInPrestito() - 1);
            if(mediaInBiblioteca->getDisponibilita() == false){
                mediaInBiblioteca->setDisponibilita(true);
            }
            return true;
        } else {
            //throw BibliotecaException("Nessuna copia in prestito per questo media (ID: " + media->getId() + ")");
        }
    } 
    return false; // Se ritorno false, significa che non ci sono media nella biblioteca con l'id del media che vorrei restituire
}

vector<Media*> Biblioteca::getListaMedia() const{
    return listaMedia;
}


