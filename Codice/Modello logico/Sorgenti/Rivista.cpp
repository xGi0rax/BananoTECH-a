#include "../Headers/Rivista.h"
#include <string>

Rivista::Rivista(int id, string titolo, string genere, int anno, string immagine, bool disponibilita, 
    int numero_copie, int in_prestito, string collocazione, double rating, string editore, int n_pagine, string mese_pubb) : 
    Media(id, titolo, genere, anno, immagine, disponibilita, numero_copie, in_prestito, collocazione, rating), editore(editore), n_pagine(n_pagine), mese_pubb(mese_pubb) {}

// Getter
string Rivista::getEditore() const {
    return editore;
}

int Rivista::getNPagine() const {
    return n_pagine;
}

string Rivista::getMesePubb() const {
    return mese_pubb;
}

// Setter
void Rivista::setEditore(const string& editore) {
    this->editore = editore;
}

void Rivista::setNPagine(const int& n_pagine) {
    this->n_pagine = n_pagine;
}

void Rivista::setMesePubb(const string& mese_pubb) {
    this->mese_pubb = mese_pubb;
}