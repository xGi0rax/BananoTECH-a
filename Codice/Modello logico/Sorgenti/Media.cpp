#include "../Headers/Media.h"
#include <string>
#include <QJsonObject>
#include <QString>

Media::Media(int id, string titolo, string genere, int anno, string immagine, bool disponibilita, 
            int numero_copie, int in_prestito = 0, string collocazione = "", double rating = 0.0) : 
            id(id), titolo(titolo), genere(genere), anno(anno), immagine(immagine), disponibilita(disponibilita), 
            numero_copie(numero_copie), in_prestito(in_prestito), collocazione(collocazione), rating(rating) {}

virtual void toJson(QJsonObject& jsonObj) const {
        jsonObj["id"] = id;
        jsonObj["titolo"] = QString::fromStdString(titolo);
        jsonObj["genere"] = QString::fromStdString(genere);
        jsonObj["anno"] = anno;
        jsonObj["immagine"] = QString::fromStdString(immagine);
        jsonObj["disponibilita"] = disponibilita;
        jsonObj["numero_copie"] = numero_copie;
        jsonObj["in_prestito"] = in_prestito;
        jsonObj["collocazione"] = QString::fromStdString(collocazione);
        jsonObj["rating"] = rating;
    }

// Metodi getter
int Media::getId() const{
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
void Media::setId(const int& id){
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

