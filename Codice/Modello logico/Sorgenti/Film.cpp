#include "../Headers/Film.h"
#include "../Headers/Media.h"
#include <string>
#include <vector>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QDomElement>
#include <QDomDocument>

Film::Film(string titolo, string genere, int anno, string lingua, string immagine, bool disponibilita, int numero_copie, string regista, 
    int durata, vector<string> cast, int in_prestito, string collocazione, double rating) : 
    Media(titolo, genere, anno, lingua, immagine, disponibilita, numero_copie, in_prestito, collocazione, rating), 
    regista(regista), durata(durata), cast(cast) {}

void Film::toJson(QJsonObject& jsonObj) const {
    Media::toJson(jsonObj);
    jsonObj["tipo"] = "film";
    jsonObj["regista"] = QString::fromStdString(regista);
    jsonObj["durata"] = durata;
    
    QJsonArray castArray;
    for (const string& attore : cast) {  // 'cast' è il membro della classe, 'attore' è la variabile locale
        castArray.append(QString::fromStdString(attore));
    }
    jsonObj["cast"] = castArray;
}

void Film::toXml(QDomElement& elemento, QDomDocument& doc) const {
    Media::toXml(elemento, doc);
    elemento.setAttribute("tipo", "film");
    elemento.setAttribute("regista", QString::fromStdString(regista));
    elemento.setAttribute("durata", durata);
    
    QDomElement castElement = doc.createElement("cast");
    for (const string& attore : cast) {
        QDomElement attoreElement = doc.createElement("attore");
        attoreElement.appendChild(doc.createTextNode(QString::fromStdString(attore)));
        castElement.appendChild(attoreElement);
    }
    elemento.appendChild(castElement);
}


// Getter
string Film::getRegista() const{
    return regista;
}

int Film::getDurata() const{
    return durata;
}

vector<string> Film::getCast() const{
    return cast;
}

// Setter
void Film::setRegista(const string& regista){
    this->regista = regista;
}

void Film::setDurata(const int& durata){
    this->durata = durata;
}

void Film::setCast(const vector<string>& cast){
    this->cast = cast;
}