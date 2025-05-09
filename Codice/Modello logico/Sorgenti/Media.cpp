#include "../Headers/Media.h"
#include <string>
#include <QJsonObject>
#include <QDomElement>
#include <QDomDocument>
#include <QString>

Media::Media(string titolo, string genere, int anno, string lingua, string immagine, bool disponibilita, 
            int numero_copie, int in_prestito, string collocazione, double rating) : 
            titolo(titolo), genere(genere), anno(anno), lingua(lingua), immagine(immagine), disponibilita(disponibilita), 
            numero_copie(numero_copie), in_prestito(in_prestito), collocazione(collocazione), rating(rating) {}

void Media::toJson(QJsonObject& jsonObj) const {
    jsonObj["id"] = QString::fromStdString(id);
    jsonObj["titolo"] = QString::fromStdString(titolo);
    jsonObj["genere"] = QString::fromStdString(genere);
    jsonObj["anno"] = anno;
    jsonObj["lingua"] = QString::fromStdString(lingua);
    jsonObj["immagine"] = QString::fromStdString(immagine);
    jsonObj["disponibilita"] = disponibilita;
    jsonObj["numero_copie"] = numero_copie;
    jsonObj["in_prestito"] = in_prestito;
    jsonObj["collocazione"] = QString::fromStdString(collocazione);
    jsonObj["rating"] = rating;
}


void Media::toXml(QDomElement& elemento, QDomDocument& doc) const {
    Q_UNUSED(doc); // Silenzia il warning per in non uso di doc
    elemento.setAttribute("id", QString::fromStdString(id));
    elemento.setAttribute("titolo", QString::fromStdString(titolo));
    elemento.setAttribute("genere", QString::fromStdString(genere));
    elemento.setAttribute("anno", anno);
    elemento.setAttribute("lingua", QString::fromStdString(lingua));
    elemento.setAttribute("immagine", QString::fromStdString(immagine));
    elemento.setAttribute("disponibilita", disponibilita);
    elemento.setAttribute("numero_copie", numero_copie);
    elemento.setAttribute("in_prestito", in_prestito);
    elemento.setAttribute("collocazione", QString::fromStdString(collocazione));
    elemento.setAttribute("rating", rating);
}


// Metodi getter
string Media::getId() const{
    return id;
}

string Media::getTitolo() const{
    return titolo;
}

string Media::getGenere() const{
    return genere;
}

int Media::getAnno() const{
    return anno;
}

string Media::getLingua() const{
    return lingua;
}

string Media::getImmagine() const{
    return immagine;
}

bool Media::getDisponibilita() const{
    return disponibilita;
}

int Media::getNumeroCopie() const{
    return numero_copie;
}

int Media::getInPrestito() const{
    return in_prestito;
}

string Media::getCollocazione() const{
    return collocazione;
}

double Media::getRating() const{
    return rating;
}

// Metodi setter
void Media::setId(const string& id){
    this->id = id;
}

void Media::setTitolo(const string& titolo){
    this->titolo = titolo;
}

void Media::setGenere(const string& genere){
    this->genere = genere;
}

void Media::setAnno(const int& anno){
    this->anno = anno;
}

void Media::setLingua(const string &lingua){
    this->lingua = lingua;
}

void Media::setImmagine(const string& imm){
    this->immagine = imm;
}

void Media::setDisponibilita(bool dispon){
    this->disponibilita = dispon;
}

void Media::setNumeroCopie(const int& n_copie){
    this->numero_copie = n_copie;
}

void Media::setInPrestito(const int& in_prestito){
    this->in_prestito = in_prestito;
}

void Media::setCollocazione(const string& coll){
    this->collocazione = coll;
}

