#include "../Headers/GiocoDaTavolo.h"
#include "../Headers/Media.h"
#include <string>
#include <QJsonObject>
#include <QString>
#include <QDomElement>
#include <QDomDocument>

GiocoDaTavolo::GiocoDaTavolo(string titolo, string genere, int anno, string lingua, string immagine, bool disponibilita, 
    int numero_copie,  int ngiocatori, int durata, int età, string editore, int in_prestito, string collocazione, double rating) : Media(titolo, genere, anno, lingua, immagine, disponibilita, numero_copie, in_prestito, collocazione, rating), 
    ngiocatori(ngiocatori), durata(durata), età(età), editore(editore) {}

void GiocoDaTavolo::toJson(QJsonObject& jsonObj) const {
    Media::toJson(jsonObj);
    jsonObj["tipo"] = "gioco";
    jsonObj["numero_giocatori"] = ngiocatori;
    jsonObj["durata"] = durata;
    jsonObj["eta_minima"] = età;
    jsonObj["editore"] = QString::fromStdString(editore);
}

void GiocoDaTavolo::toXml(QDomElement& elemento, QDomDocument& doc) const {
    Q_UNUSED(doc); // Silenzia il warning per in non uso di doc
    Media::toXml(elemento, doc);
    elemento.setAttribute("tipo", "gioco");
    elemento.setAttribute("numero_giocatori", ngiocatori);
    elemento.setAttribute("durata", durata);
    elemento.setAttribute("eta_minima", età);
    elemento.setAttribute("editore", QString::fromStdString(editore));
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