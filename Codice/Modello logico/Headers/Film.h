#ifndef FILM_H
#define FILM_H
#include "Media.h"
#include <vector>
using std::vector;

class Film: public Media{ 
private:
    string regista;
    int durata;
    vector<string> cast;

public:
    Film(int id, string titolo, string genere, int anno, string immagine, int disponibilita, int in_prestito = 0, string collocazione = "", double rating = 0.0, string regista, int durata, vector<string> cast);
    ~Film();
    void displayInfo() const override;
};
    
#endif //FILM_H