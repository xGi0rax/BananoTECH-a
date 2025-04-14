#ifndef GIOCODATAVOLO_H
#define GIOCODATAVOLO_H
#include "Media.h"
#include <string>
using std::string;

class GiocoDaTavolo: public Media{
private: 
    int ngiocatori; 
    int durata;  // Stima durata in minuti
    int etaMinima;
    string editore; 

public:
    GiocoDaTavolo(string titolo, string genere, int anno, string lingua, string immagine, bool disponibilita, int numero_copie, int ngiocatori, int durata, int etaMinima, string editore, int in_prestito = 0, string collocazione = "", double rating = 0.0);
    ~GiocoDaTavolo() = default;

    // Metodi getter
    int getNGiocatori() const;
    int getDurata() const;
    int getEtaMinima() const;
    string getEditore() const;

    // Metodi setter
    void setNGiocatori(const int& ngiocatori);
    void setDurata(const int& durata);
    void setEtaMinima(const int& etaMinima);
    void setEditore(const string& editore);

    void toJson(QJsonObject& jsonObj) const override;
    void toXml(QDomElement& elemento, QDomDocument& doc) const override;


    // Metodo di debug per stampare i dettagli del gioco da tavolo
    void stampaInfo() const override{
        Media::stampaInfo(); // Stampa le informazioni di base del media
        std::cout << "Numero di giocatori: " << ngiocatori << "\n"
                  << "Durata (min): " << durata << "\n"
                  << "Età minima: " << etaMinima << "\n"
                  << "Editore: " << editore << std::endl;
    }
};
    
#endif //GIOCODATAVOLO_H