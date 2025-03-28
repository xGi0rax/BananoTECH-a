#ifndef RIVISTA_H
#define RIVISTA_H
#include "Media.h"
using std::string;

class Rivista: public Media{
    private:
        string editore;
        int n_pagine;
        string mese_pubb;
    public:
        Rivista(int id, string titolo, string genere, int anno, string immagine, int disponibilita, int in_prestito = 0, string collocazione = "", double rating = 0.0, string editore, int n_pagine, string mese_pubb);
        ~Rivista();
};

#endif //RIVISTA_H