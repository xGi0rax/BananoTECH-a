#ifndef VINILE_H
#define VINILE_H
#include "Media.h"
#include <string>

class Vinile: public Media{ 
    private:
        string artista;
        int ntracce;
        int durata;
    public:
        Vinile(int id, string titolo, string genere, int anno, string immagine, bool disponibilita, int numero_copie, int in_prestito = 0, string collocazione = "", double rating = 0.0, string artista, int ntracce, int durata);
        ~Vinile();

        // Metodi getter
        string getArtista() const;
        int getNTracce() const;
        int getDurata() const;

        // Metodi setter
        void setArtista(const string& artista);
        void setNTracce(const int& ntracce);
        void setDurata(const int& durata);
};

#endif //VINILE_H