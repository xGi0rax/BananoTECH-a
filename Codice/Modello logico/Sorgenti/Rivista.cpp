#include "../Headers/Rivista.h"
#include "../Headers/Media.h"
#include <string>
#include <QJsonObject>
#include <QString>

Rivista::Rivista(string titolo, string genere, int anno, string immagine, bool disponibilita, 
    int numero_copie, string editore, int n_pagine, string data_pubb, string periodicita, int in_prestito, string collocazione, double rating) : Media(titolo, genere, anno, immagine, disponibilita, numero_copie, in_prestito, collocazione, rating), 
    editore(editore), n_pagine(n_pagine), data_pubb(data_pubb), periodicita(periodicita) {}

void Rivista::toJson(QJsonObject& jsonObj) const {
    Media::toJson(jsonObj);
    jsonObj["tipo"] = "rivista";
    jsonObj["editore"] = QString::fromStdString(editore);
    jsonObj["numero_pagine"] = n_pagine;
    jsonObj["mese_pubblicazione"] = QString::fromStdString(data_pubb);
    jsonObj["periodicita"] = QString::fromStdString(periodicita);
}

// Getter
string Rivista::getEditore() const {
    return editore;
}

int Rivista::getNPagine() const {
    return n_pagine;
}

string Rivista::getDataPubb() const {
    return data_pubb;
}

string Rivista::getPeriodicita() const {
    return periodicita;
}

// Setter
void Rivista::setEditore(const string& editore) {
    this->editore = editore;
}

void Rivista::setNPagine(const int& n_pagine) {
    this->n_pagine = n_pagine;
}

void Rivista::setDataPubb(const string& data_pubb) {
    this->data_pubb = data_pubb;
}

void Rivista::setPeriodicita(const string& periodicita) {
    this->periodicita = periodicita;
}