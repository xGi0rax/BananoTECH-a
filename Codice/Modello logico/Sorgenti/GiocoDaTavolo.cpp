#include "../Headers/GiocoDaTavolo.h"
#include "../Headers/Media.h"
#include <string>
#include <QJsonObject>
#include <QString>

GiocoDaTavolo::GiocoDaTavolo(int id, string titolo, string genere, int anno, string immagine, bool disponibilita, 
    int numero_copie, int in_prestito, string collocazione, double rating, int ngiocatori, int durata, 
    int età, string editore) : Media(id, titolo, genere, anno, immagine, disponibilita, numero_copie, in_prestito, collocazione, rating), 
    ngiocatori(ngiocatori), durata(durata), età(età), editore(editore) {}

void GiocoDaTavolo::toJson(QJsonObject& jsonObj) const {
    Media::toJson(jsonObj);
    jsonObj["tipo"] = "gioco";
    jsonObj["numero_giocatori"] = ngiocatori;
    jsonObj["durata"] = durata;
    jsonObj["eta_minima"] = età;
    jsonObj["editore"] = QString::fromStdString(editore);
}

// Getter
int GiocoDaTavolo::getNGiocatori() const {
    return ngiocatori;
}

int GiocoDaTavolo::getDurata() const {
    return durata;
}

int GiocoDaTavolo::getEtà() const {
    return età;
}

string GiocoDaTavolo::getEditore() const {
    return editore;
}

// Setter
void GiocoDaTavolo::setNGiocatori(const int& ngiocatori) {
    this->ngiocatori = ngiocatori;
}

void GiocoDaTavolo::setDurata(const int& durata) {
    this->durata = durata;
}

void GiocoDaTavolo::setEtà(const int& età) {
    this->età = età;
}

void GiocoDaTavolo::setEditore(const string& editore) {
    this->editore = editore;
}