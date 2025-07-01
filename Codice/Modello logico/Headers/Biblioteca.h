#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include "Media.h"
#include <string>
#include <vector>
#include <QString>

using std::vector;

class Biblioteca{
private:
    vector<Media*> listaMedia; // vettore di puntatori a Media
    int nextIdmedia; // contatore per l'auto-incremento degli Id dei media

public:
    Biblioteca();
    ~Biblioteca();
        
    void aggiungiMedia(Media* media); // Aggiunge un media (e assegna ID)
    bool esisteMedia(const string& titolo, const string& autore, int anno) const; // Metodo per controllare se un media esiste gia' prima di aggiungerlo
    bool rimuoviMedia(Media* media); // Rimuove un media dalla biblioteca
    Media* cercaMediaDaID(const string& id) const; // Restituisce un media dall'ID
    Media* cercaMediaDaT_A_A(const string& titolo, const string& autore, int anno) const; // Restituisce un media in base a titolo, autore e anno
    bool modificaMedia(const string& id, Media* newMedia); // Modifica un media esistente in base all'ID

    // Metodo che ritorna una lista filtrata dei media in base a vari criteri
    vector<Media*> filtra(const string& titolo = "",
                            const string& tipoMedia = "",
                            const string& genere = "",
                            double ratingMin = 0.0,
                            double ratingMax = 5.0,
                            bool disponibilita = true,
                            const string& lingua = "",
                            int annoMin = 1200,
                            int annoMax = 2050
    ) const;
    

    // Metodi per gestione prestiti
    bool prendiInPrestito(const Media* media); // Metoto per prendere in prestito un media
    bool restituisci(const Media* media); // Metodo per restituire un media

    vector<Media*> getListaMedia() const; // Restituisce la lista dei media
};

#endif // BIBLIOTECA.H