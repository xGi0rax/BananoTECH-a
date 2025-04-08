#include "../Headers/Film.h"
#include "../Headers/Media.h"
#include <string>
#include <vector>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

Film::Film(string titolo, string genere, int anno, string immagine, bool disponibilita, int numero_copie,
    int in_prestito = 0, string collocazione = "", double rating = 0.0, string regista, int durata, vector<string> cast) : 
    Media(titolo, genere, anno, immagine, disponibilita, numero_copie, in_prestito, collocazione, rating), 
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