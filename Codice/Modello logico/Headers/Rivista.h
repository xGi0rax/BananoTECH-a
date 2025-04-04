#ifndef RIVISTA_H
#define RIVISTA_H
#include "Media.h"
#include <string>

class Rivista: public Media{
private:
    string editore;
    int n_pagine;
    string mese_pubb;
public:
    Rivista(int id, string titolo, string genere, int anno, string immagine, bool disponibilita, int numero_copie, int in_prestito = 0, string collocazione = "", double rating = 0.0, string editore, int n_pagine, string mese_pubb);
    ~Rivista();

    // Metodi getter
    string getEditore() const;
    int getNPagine() const;
    string getMesePubb() const;

    // Metodi setter
    void setEditore(const string& editore);
    void setNPagine(const int& n_pagine);
    void setMesePubb(const string& mese_pubb);
};

#endif //RIVISTA_H