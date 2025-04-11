#include "../Headers/Libro.h"
#include "../Headers/Media.h"
#include <string>
#include <QJsonObject>
#include <QString>
#include <QDomElement>
#include <QDomDocument>

Libro::Libro(string titolo, string genere, int anno, string lingua, string immagine, bool disponibilita, 
    int numero_copie, string isbn, string autore, string editore, int npagine,int in_prestito, string collocazione, double rating) : Media(titolo, genere, anno, lingua, immagine, disponibilita, numero_copie, in_prestito, collocazione, rating), 
    isbn(isbn), autore(autore), editore(editore), npagine(npagine) {}

void Libro::toJson(QJsonObject& jsonObj) const {
    Media::toJson(jsonObj);
    jsonObj["tipo"] = "libro";
    jsonObj["isbn"] = QString::fromStdString(isbn);
    jsonObj["autore"] = QString::fromStdString(autore);
    jsonObj["editore"] = QString::fromStdString(editore);
    jsonObj["numero_pagine"] = npagine;
}

void Libro::toXml(QDomElement& elemento, QDomDocument& doc) const {
    Q_UNUSED(doc); // Silenzia il warning per in non uso di doc
    Media::toXml(elemento, doc);
    elemento.setAttribute("tipo", "libro");
    elemento.setAttribute("isbn", QString::fromStdString(isbn));
    elemento.setAttribute("autore", QString::fromStdString(autore));
    elemento.setAttribute("editore", QString::fromStdString(editore));
    elemento.setAttribute("numero_pagine", npagine);
}

// Getter
string Libro::getIsbn() const {
    return isbn;
}

string Libro::getAutore() const {
    return autore;
}

string Libro::getEditore() const {
    return editore;
}

int Libro::getNPagine() const {
    return npagine;
}

// Setter

void Libro::setIsbn(const string& isbn) {
    this->isbn = isbn;
}

void Libro::setAutore(const string& autore) {
    this->autore = autore;
}

void Libro::setEditore(const string& editore) {
    this->editore = editore;
}

void Libro::setNPagine(const int& npagine) {
    this->npagine = npagine;
}
