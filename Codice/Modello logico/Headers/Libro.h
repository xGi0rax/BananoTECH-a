#ifndef LIBRO_H
#define LIBRO_H
#include "Media.h"

class Libro : public Media{
private:
    string isbn;
    string autore;
    string editore;
    int npagine;

public:
    Libro(int id, string titolo, string genere, int anno, string immagine, int disponibilita, int numero_copie, int in_prestito = 0, string collocazione = "", double rating = 0.0, string isbn, string autore, string editore, int npagine);
    ~Libro();
    void displayInfo() const override;
};

#endif //LIBRO_H