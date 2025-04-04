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
    Libro(int id, string titolo, string genere, int anno, string immagine, bool disponibilita, int numero_copie, int in_prestito = 0, string collocazione = "", double rating = 0.0, string isbn, string autore, string editore, int npagine);
    ~Libro();

    // Metodi getter
    string getIsbn() const;
    string getAutore() const;
    string getEditore() const;
    int getNPagine() const;

    // Metodi setter
    void setIsbn(const string& isbn);
    void setAutore(const string& autore);
    void setEditore(const string& editore);
    void setNPagine(const int& npagine);
};

#endif //LIBRO_H