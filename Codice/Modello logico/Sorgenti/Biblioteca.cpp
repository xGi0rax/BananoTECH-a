#include "../Headers/Biblioteca.h"
#include "../Headers/Media.h"
#include "../Headers/Film.h"
#include "../Headers/Libro.h"
#include "../Headers/Vinile.h"
#include "../Headers/GiocoDaTavolo.h"
#include "../Headers/Rivista.h"

Biblioteca::Biblioteca() : nextIdmedia(1) {}

Biblioteca::~Biblioteca() {
    for (auto media : listaMedia) {
        delete media;
    }
}

void Biblioteca::aggiungiMedia(Media* media) {
    media->setId(std::to_string(nextIdmedia++));
    listaMedia.push_back(media);
}

bool Biblioteca::esisteMedia(const string& titolo, const string& autore, int anno) const {
    string titoloLower = titolo;
    string autoreLower = autore;
    
    // Converte a lowercase
    std::transform(titoloLower.begin(), titoloLower.end(), titoloLower.begin(), ::tolower);
    std::transform(autoreLower.begin(), autoreLower.end(), autoreLower.begin(), ::tolower);
    
    for (const Media* m : listaMedia) {
        string mediaTitoloLower = m->getTitolo();
        string mediaAutoreLower = m->getAutore();
        
        // Converte a lowercase
        std::transform(mediaTitoloLower.begin(), mediaTitoloLower.end(), mediaTitoloLower.begin(), ::tolower);
        std::transform(mediaAutoreLower.begin(), mediaAutoreLower.end(), mediaAutoreLower.begin(), ::tolower);
        
        if (mediaTitoloLower == titoloLower && mediaAutoreLower == autoreLower && m->getAnno() == anno) {
            return true;
        }
    }
    return false;
}

Media* Biblioteca::cercaMediaDaT_A_A(const string& titolo, const string& autore, int anno) const {
    string titoloLower = titolo;
    string autoreLower = autore;
    
    // Converte a lowercase
    std::transform(titoloLower.begin(), titoloLower.end(), titoloLower.begin(), ::tolower);
    std::transform(autoreLower.begin(), autoreLower.end(), autoreLower.begin(), ::tolower);

    for (Media* m : listaMedia) {
        string mediaTitoloLower = m->getTitolo();
        string mediaAutoreLower = m->getAutore();
        
        // Converte a lowercase
        std::transform(mediaTitoloLower.begin(), mediaTitoloLower.end(), mediaTitoloLower.begin(), ::tolower);
        std::transform(mediaAutoreLower.begin(), mediaAutoreLower.end(), mediaAutoreLower.begin(), ::tolower);

        if (mediaTitoloLower == titoloLower && mediaAutoreLower == autoreLower && m->getAnno() == anno) {
            return m;
        }
    }
    return nullptr; // Se non trovato, ritorna nullptr
}

bool Biblioteca::modificaMedia(const string& id, Media* newMedia) {
    for (auto it = listaMedia.begin(); it != listaMedia.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it; // Elimina il vecchio media
            *it = newMedia; // Sostituisci con il nuovo media
            return true;
        }
    }
    return false;
}

bool Biblioteca::rimuoviMedia(Media* media) {
    if (!media) return false;
    
    auto it = std::find(listaMedia.begin(), listaMedia.end(), media);
    if (it != listaMedia.end()) {
        listaMedia.erase(it);
        delete media;
        return true;
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
                corrisponde = false;
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
            if (media->getTitolo().find(titolo) == string::npos) corrisponde = false;
        }
        // Filtro per genere
        if (corrisponde && !genere.empty()) {
            if (media->getGenere().find(genere) == string::npos) corrisponde = false;
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

bool Biblioteca::prendiInPrestito(const Media* media){
    Media* mediaInBiblioteca = cercaMediaDaID(media->getId()); // Cerca il media in biblioteca
    if(mediaInBiblioteca != nullptr){
        if(mediaInBiblioteca->getDisponibilita()){ // Controlla se ci sono copie disponibili
            mediaInBiblioteca->setInPrestito(mediaInBiblioteca->getInPrestito() + 1); // Incrementa il numero di copie in prestito
            if(mediaInBiblioteca->getInPrestito() == mediaInBiblioteca->getNumeroCopie()){
                mediaInBiblioteca->setDisponibilita(false); // Se tutte le copie sono in prestito, imposta disponibilità a false
            }
            return true;
        }
    }
    return false;
}

bool Biblioteca::restituisci(const Media* media){
    Media* mediaInBiblioteca = cercaMediaDaID(media->getId()); // Cerca il media in biblioteca
    if(mediaInBiblioteca != nullptr){
        if(mediaInBiblioteca->getInPrestito() > 0){ // Controlla se ci sono copie in prestito 
            mediaInBiblioteca->setInPrestito(mediaInBiblioteca->getInPrestito() - 1); // // Controlla se ci sono copie in prestito 
            if(mediaInBiblioteca->getDisponibilita() == false){ 
                mediaInBiblioteca->setDisponibilita(true); // Se prima non c'erano copie disponibili, imposta disponibilità a true
            }
            return true;
        }
    } 
    return false;
}

vector<Media*> Biblioteca::getListaMedia() const{
    return listaMedia;
}


