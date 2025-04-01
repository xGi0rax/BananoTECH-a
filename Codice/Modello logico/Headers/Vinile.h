#ifndef VINILE_H
#define VINILE_H
#include "Media.h"

class Vinile: public Media{ 
    private:
        string artista;
        int ntracce;
        int durata;
    public:
        Vinile(int id, string titolo, string genere, int anno, string immagine, int disponibilita, int numero_copie, int in_prestito = 0, string collocazione = "", double rating = 0.0, string artista, int ntracce, int durata);
        ~Vinile();
        void displayInfo() const override;
};

#endif //VINILE_H