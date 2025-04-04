#include "../Headers/Film.h"
#include "../Headers/Media.h"
#include <string>
#include <vector>

Film::Film(int id, string titolo, string genere, int anno, string immagine, bool disponibilita, int numero_copie,
    int in_prestito = 0, string collocazione = "", double rating = 0.0, string regista, int durata, vector<string> cast) : 
    Media(id, titolo, genere, anno, immagine, disponibilita, numero_copie, in_prestito, collocazione, rating), 
    regista(regista), durata(durata), cast(cast) {}

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