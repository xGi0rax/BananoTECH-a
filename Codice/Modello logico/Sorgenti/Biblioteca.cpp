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

// ===============================
// GESTIONE MEDIA
// ===============================

void Biblioteca::aggiungiMedia(Media* media) {
    media->setId(std::to_string(nextIdmedia++));
    listaMedia.push_back(media);
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

bool Biblioteca::modificaMedia(const string& id, Media* newMedia) {
    for (auto it = listaMedia.begin(); it != listaMedia.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            *it = newMedia;
            return true;
        }
    }
    return false;
}

// ============================
// RICERCA MEDIA
// ============================

Media* Biblioteca::cercaMediaDaID(const string& id) const {
    for (Media* media : listaMedia) {
        if (media->getId() == id) {
            return media;
        }
    }
    return nullptr;
}

Media* Biblioteca::cercaMediaDaT_A_A(const string& titolo, const string& autore, int anno) const {
    string titoloLower = QString::fromStdString(titolo).toLower().toStdString();
    string autoreLower = QString::fromStdString(autore).toLower().toStdString();
    
    for (Media* m : listaMedia) {
        string mediaTitoloLower = QString::fromStdString(m->getTitolo()).toLower().toStdString();
        string mediaAutoreLower = QString::fromStdString(m->getAutore()).toLower().toStdString();
        
        if (mediaTitoloLower == titoloLower && 
            mediaAutoreLower == autoreLower && 
            m->getAnno() == anno) {
            return m;
        }
    }
    return nullptr;
}

bool Biblioteca::esisteMedia(const string& titolo, const string& autore, int anno) const {
    string titoloLower = QString::fromStdString(titolo).toLower().toStdString();
    string autoreLower = QString::fromStdString(autore).toLower().toStdString();

    for (const Media* m : listaMedia) {
        string mediaTitoloLower = QString::fromStdString(m->getTitolo()).toLower().toStdString();
        string mediaAutoreLower = QString::fromStdString(m->getAutore()).toLower().toStdString();
        
        if (mediaTitoloLower == titoloLower && 
            mediaAutoreLower == autoreLower && 
            m->getAnno() == anno) {
            return true;
        }
    }
    return false;
}

// =======================
// FILTRI
// =======================

vector<Media*> Biblioteca::filtra(const string& titolo, 
                                 const string& tipoMedia, 
                                 const string& genere, 
                                 double ratingMin, 
                                 double ratingMax, 
                                 bool disponibilita, 
                                 const string& lingua, 
                                 int annoMin, 
                                 int annoMax) const {
    vector<Media*> risultati;

    for (auto media : listaMedia) {
        bool corrisponde = true;

        // Filtro per tipo di media
        if (!tipoMedia.empty()) {
            if (tipoMedia == "Libro" && dynamic_cast<Libro*>(media) == nullptr) {
                corrisponde = false;
            } else if (tipoMedia == "Film" && dynamic_cast<Film*>(media) == nullptr) {
                corrisponde = false;
            } else if (tipoMedia == "Rivista" && dynamic_cast<Rivista*>(media) == nullptr) {
                corrisponde = false;
            } else if (tipoMedia == "Vinile" && dynamic_cast<Vinile*>(media) == nullptr) {
                corrisponde = false;
            } else if (tipoMedia == "Gioco da tavolo" && dynamic_cast<GiocoDaTavolo*>(media) == nullptr) {
                corrisponde = false;
            }
        }

        // Filtro per titolo
        if (corrisponde && !titolo.empty()) {
            if (media->getTitolo().find(titolo) == string::npos) {
                corrisponde = false;
            }
        }

        // Filtro per genere
        if (corrisponde && !genere.empty()) {
            if (media->getGenere().find(genere) == string::npos) {
                corrisponde = false;
            }
        }

        // Filtro per rating
        if (corrisponde) {
            if (media->getRating() < ratingMin || media->getRating() > ratingMax) {
                corrisponde = false;
            }
        }

        // Filtro per disponibilità
        if (corrisponde) {
            if ((disponibilita && !media->getDisponibilita()) || 
                (!disponibilita && media->getDisponibilita())) {
                corrisponde = false;
            }
        }

        // Filtro per lingua
        if (corrisponde && !lingua.empty()) {
            string mediaLanguageLower = QString::fromStdString(media->getLingua()).toLower().toStdString();
            if (mediaLanguageLower != lingua) {
                corrisponde = false;
            }
        }

        // Filtro per anno
        if (corrisponde) {
            if (media->getAnno() < annoMin || media->getAnno() > annoMax) {
                corrisponde = false;
            }
        }

        // Aggiunta media ai risultati se corrisponde ai filtri
        if (corrisponde) {
            risultati.push_back(media);
        }
    }
    
    return risultati;
}

// ===========================
// GESTIONE PRESTITI
// ===========================

bool Biblioteca::prendiInPrestito(const Media* media) {
    Media* mediaInBiblioteca = cercaMediaDaID(media->getId());
    
    if (mediaInBiblioteca != nullptr) {
        if (mediaInBiblioteca->getDisponibilita()) {
            mediaInBiblioteca->setInPrestito(mediaInBiblioteca->getInPrestito() + 1);
            
            if (mediaInBiblioteca->getInPrestito() == mediaInBiblioteca->getNumeroCopie()) {
                mediaInBiblioteca->setDisponibilita(false);
            }
            return true;
        }
    }
    return false;
}

bool Biblioteca::restituisci(const Media* media) {
    Media* mediaInBiblioteca = cercaMediaDaID(media->getId());
    
    if (mediaInBiblioteca != nullptr) {
        if (mediaInBiblioteca->getInPrestito() > 0) {
            mediaInBiblioteca->setInPrestito(mediaInBiblioteca->getInPrestito() - 1);
            
            if (mediaInBiblioteca->getDisponibilita() == false) {
                mediaInBiblioteca->setDisponibilita(true);
            }
            return true;
        }
    }
    return false;
}

// ========================
// GETTER
// ========================

vector<Media*> Biblioteca::getListaMedia() const {
    return listaMedia;
}


