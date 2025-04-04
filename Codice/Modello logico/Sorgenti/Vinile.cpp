#include "../Headers/Vinile.h"
#include <string>

Vinile::Vinile(int id, string titolo, string genere, int anno, string immagine, bool disponibilita, int numero_copie, int in_prestito, string collocazione, double rating, string artista, int ntracce, int durata) : Media(id, titolo, genere, anno, immagine, disponibilita, numero_copie, in_prestito, collocazione, rating), artista(artista), ntracce(ntracce), durata(durata) {}

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