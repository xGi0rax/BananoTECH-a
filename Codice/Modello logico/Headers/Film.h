#ifndef FILM_H
#define FILM_H
#include "Media.h"
using std::string;

class Film: public Media{ 
    private:
        string regista;
        int durata;
        vector<string> cast;
    public:
        Film(int id, string titolo, string genere, int anno, string immagine, int disponibilita, int in_prestito = 0, string collocazione = "", double rating = 0.0, string regista, int durata, vector cast);
        ~Film();
        void displayInfo() const override;
};
    
#endif //FILM_H