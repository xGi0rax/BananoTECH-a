#include "Biblioteca.h"
#include "FileManager.h"
#include "Media.h"
#include "Film.h"
#include "Libro.h"
#include "Vinile.h"
#include "GiocoDaTavolo.h"
#include "Rivista.h"


Biblioteca::Biblioteca(string& idBiblio) : idBiblioteca(idBiblio), nextIdmedia(1) {}

Biblioteca::~Biblioteca() {
    for (auto media : listaMedia) {
        delete media;
    }
}

void Biblioteca::aggiungiMedia(Media* media) {
    media->setId(idBiblioteca + "-" + std::to_string(nextIdmedia++));
    listaMedia.push_back(media);
}

bool Biblioteca::esisteMedia(const string& titolo, int anno, const string& genere) const {
    for (const Media* m : listaMedia) {
        if (m->getTitolo() == titolo && m->getAnno() == anno && m->getGenere() == genere) {
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

vector<Media*> Biblioteca::filtra(const string& titolo = "", const string& tipoMedia = "", const string& genere = "", double ratingMin = 0.0, double ratingMax = 5.0, const string& lingua = "", int annoMin = 0, int annoMax = 9999 ) const {
    
    vector<Media*> risultati;

    for (auto media : listaMedia) {
        bool corrisponde = true;

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
            else if (tipoMedia == "Gioco" && dynamic_cast<GiocoDaTavolo*>(media) == nullptr)
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
            if (media->getRating() < ratingMin || media->getRating() > ratingMax)
                corrisponde = false;
        }
        // Filtro per lingua
        if (corrisponde && !lingua.empty()) {
            // if (media->getLingua() != lingua)
            //     corrisponde = false;
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

void Biblioteca::salvaSuFile(const QString& path) {
    FileManager fm;
    if (path.endsWith(".json")) {
        fm.salvaSuJson(*this, path.toStdString());
    } else if (path.endsWith(".xml")) {
        fm.salvaSuXml(*this, path.toStdString());
    }
}

void Biblioteca::caricaDaFile(const QString& path) {
    FileManager fm;
    if (path.endsWith(".json")) {
        fm.caricaDaJson(*this, path.toStdString());
    } else if (path.endsWith(".xml")) {
        fm.caricaDaXml(*this, path.toStdString());
    }
}

int Biblioteca::getNumeroTotaleMedia() const {
    return listaMedia.size();
}

bool Biblioteca::prendiInPrestito(const Media* media){
    Media* mediaInBiblioteca = cercaMediaDaID(media->getId());
    if(mediaInBiblioteca != nullptr){
        if(mediaInBiblioteca->getDisponibilita()){
            mediaInBiblioteca->setInPrestito(mediaInBiblioteca->getInPrestito() + 1);
            if(mediaInBiblioteca->getInPrestito() == mediaInBiblioteca->getNumeroCopie()){
                mediaInBiblioteca->setDisponibilita(false);
            }
            return true;
        }
    }
    return false;
}

bool Biblioteca::restituisci(const Media* media){
    Media* mediaInBiblioteca = cercaMediaDaID(media->getId()); // Cerca il media in biblioteca
    if(mediaInBiblioteca != nullptr){
        if(mediaInBiblioteca->getInPrestito() > 0){ // Controlla se ci sono copie in prestito (il caso in cui non ci siano copie in prestito è già gestito da cercaMediaDaID)
            mediaInBiblioteca->setInPrestito(mediaInBiblioteca->getInPrestito() - 1);
            if(mediaInBiblioteca->getDisponibilita() == false){
                mediaInBiblioteca->setDisponibilita(true);
            }
            return true;
        }
    }
    return false; // Se ritorno false, significa che non ci sono media nella biblioteca con l'id del media che vorrei restituire
}

vector<Media*> Biblioteca::getListaMedia() const{
    return listaMedia;
}
