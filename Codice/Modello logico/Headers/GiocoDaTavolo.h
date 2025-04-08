#ifndef GIOCODATAVOLO_H
#define GIOCODATAVOLO_H
#include "Media.h"
#include <string>
using std::string;

class GiocoDaTavolo: public Media{
private: 
    int ngiocatori; 
    int durata;  // Stima durata in minuti
    int età;
    string editore; 

public:
    GiocoDaTavolo(int id, string titolo, string genere, int anno, string immagine, bool disponibilita, int numero_copie, int in_prestito = 0, string collocazione = "", double rating = 0.0, int ngiocatori, int durata, int età, string editore);
    ~GiocoDaTavolo();

    // Metodi getter
    int getNGiocatori() const;
    int getDurata() const;
    int getEtà() const;
    string getEditore() const;

    // Metodi setter
    void setNGiocatori(const int& ngiocatori);
    void setDurata(const int& durata);
    void setEtà(const int& età);
    void setEditore(const string& editore);

    void toJson(QJsonObject& jsonObj) const override;
};
    
#endif //GIOCODATAVOLO_H