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
    Vinile(string titolo, string genere, int anno, string lingua, string immagine, bool disponibilita, int numero_copie, string artista, int ntracce, int durata, int in_prestito = 0, string collocazione = "", double rating = 0.0);
    ~Vinile() = default;

    // Metodi getter
    string getArtista() const;
    int getNTracce() const;
    int getDurata() const;

    // Metodi setter
    void setArtista(const string& artista);
    void setNTracce(const int& ntracce);
    void setDurata(const int& durata);

    void toJson(QJsonObject& jsonObj) const override;
    void toXml(QDomElement& elemento, QDomDocument& doc) const override;


    // Metodo di debug per stampare i dettagli del vinile
    void stampaInfo() const override{
        Media::stampaInfo(); // Stampa le informazioni di base del media
        std::cout << "Artista: " << artista << "\n"
                  << "Numero di tracce: " << ntracce << "\n"
                  << "Durata (min): " << durata << std::endl;
    }
};

#endif //VINILE_H