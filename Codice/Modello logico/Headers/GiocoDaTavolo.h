#ifndef GIOCODATAVOLO_H
#define GIOCODATAVOLO_H
#include "Media.h"

class GiocoDaTavolo: public Media{
private: 
    int ngiocatori;
    int durata;
    int età;
    string editore;
public:
    GiocoDaTavolo(int id, string titolo, string genere, int anno, string immagine, int disponibilita, int in_prestito = 0, string collocazione = "", double rating = 0.0, int ngiocatori, int durata, int età, string editore);
    ~GiocoDaTavolo();
    void displayInfo() const override;
};
    
#endif //GIOCODATAVOLO_H