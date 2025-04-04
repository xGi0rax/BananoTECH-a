#include "../Headers/Libro.h"

Libro::Libro(int id, string titolo, string genere, int anno, string immagine, bool disponibilita, 
    int numero_copie, int in_prestito, string collocazione, double rating, string isbn, string autore, 
    string editore, int npagine) : Media(id, titolo, genere, anno, immagine, disponibilita, numero_copie, in_prestito, collocazione, rating), isbn(isbn), autore(autore), editore(editore), npagine(npagine) {}

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
