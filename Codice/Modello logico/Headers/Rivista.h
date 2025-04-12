#ifndef RIVISTA_H
#define RIVISTA_H
#include "Media.h"
#include <string>

class Rivista: public Media{
private:
    string editore; // Editore della rivista
    int n_pagine; // Numero di pagine
    string data_pubb; // Data di pubblicazione (formato: "YYYY-MM-DD")
    string periodicita; // Mensile, settimanale, annuale, ecc.

public:
    Rivista(string titolo, string genere, int anno, string lingua, string immagine, bool disponibilita, int numero_copie, string editore, int n_pagine, string data_pubb, string periodicita, int in_prestito = 0, string collocazione = "", double rating = 0.0);
    ~Rivista() = default;

    // Metodi getter
    string getEditore() const;
    int getNPagine() const;
    string getDataPubb() const;
    string getPeriodicita() const;

    // Metodi setter
    void setEditore(const string& editore);
    void setNPagine(const int& n_pagine);
    void setDataPubb(const string& mese_pubb);
    void setPeriodicita(const string& periodicita);

    void toJson(QJsonObject& jsonObj) const override;
    void toXml(QDomElement& elemento, QDomDocument& doc) const override;


    // Metodo di debug per stampare i dettagli della rivista
    void stampaInfo() const override{
        std::cout << "Editore: " << editore << "\n"
                  << "Numero di pagine: " << n_pagine << "\n"
                  << "Data di pubblicazione: " << data_pubb << "\n"
                  << "Periodicità: " << periodicita << std::endl;
    }
};

#endif //RIVISTA_H