#include "../Headers/Vinile.h"
#include "../Headers/Media.h"
#include <string>
#include <QJsonObject>
#include <QString>
#include <QDomElement>
#include <QDomDocument>

Vinile::Vinile(string titolo, string genere, int anno, string lingua, string immagine, bool disponibilita, int numero_copie, string artista, int ntracce, int durata, int in_prestito, string collocazione, double rating) : Media(titolo, genere, anno, lingua, immagine, disponibilita, numero_copie, in_prestito, collocazione, rating), artista(artista), ntracce(ntracce), durata(durata) {}

void Vinile::toJson(QJsonObject& jsonObj) const {
    Media::toJson(jsonObj);
    jsonObj["tipo"] = "vinile";
    jsonObj["artista"] = QString::fromStdString(artista);
    jsonObj["numero_tracce"] = ntracce;
    jsonObj["durata"] = durata;
}

void Vinile::toXml(QDomElement& elemento, QDomDocument& doc) const {
    Q_UNUSED(doc); // Silenzia il warning per in non uso di doc
    Media::toXml(elemento, doc);
    elemento.setAttribute("tipo", "vinile");
    elemento.setAttribute("artista", QString::fromStdString(artista));
    elemento.setAttribute("numero_tracce", ntracce);
    elemento.setAttribute("durata", durata);
}

// Getter
string Vinile::getArtista() const {
    return artista;
}

int Vinile::getNTracce() const {
    return ntracce;
}

int Vinile::getDurata() const {
    return durata;
}

// Setter
void Vinile::setArtista(const string& artista) {
    this->artista = artista;
}

void Vinile::setNTracce(const int& ntracce) {
    this->ntracce = ntracce;
}

void Vinile::setDurata(const int& durata) {
    this->durata = durata;
}