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
    Rivista(string titolo, string genere, int anno, string immagine, bool disponibilita, int numero_copie, int in_prestito = 0, string collocazione = "", double rating = 0.0, string editore, int n_pagine, string data_pubb, string periodicita);
    ~Rivista();

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
};

#endif //RIVISTA_H