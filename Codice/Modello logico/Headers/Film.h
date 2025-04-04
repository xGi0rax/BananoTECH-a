#ifndef FILM_H
#define FILM_H
#include "Media.h"
#include <vector>
#include <string>
using std::vector;

class Film: public Media{ 
private:
    string regista;
    int durata;
    vector<string> cast;

public:
    Film(int id, string titolo, string genere, int anno, string immagine, bool disponibilita, int numero_copie, 
        int in_prestito = 0, string collocazione = "", double rating = 0.0, string regista, int durata, vector<string> cast);
    ~Film() =default; 

    // Metodi getter
    string getRegista() const;
    int getDurata() const;
    vector<string> getCast() const;

    //Metodi setter
    void setRegista(const string& regista);
    void setDurata(const int& durata);
    void setCast(const vector<string>& cast);
};
    
#endif //FILM_H