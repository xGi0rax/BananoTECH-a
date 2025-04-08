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
    string idBiblioteca; // ID della biblioteca (es. "AA")
    int nextIdmedia; // contatore per l'auto-incremento degli Id dei media

public:
    Biblioteca(string& idBiblio);
    ~Biblioteca();
        
    // Metodi per aggiunta e rimozione dei media
    void aggiungiMedia(Media* media); // Aggiunge un media (e assegna ID)
    bool esisteMedia(const string& titolo, int anno, const string& genere) const; // Metodo per controllare se un media esiste gia' prima di aggiungerlo
    bool rimuoviMedia(string& id); // Rimuove un media per ID
    Media* cercaMediaDaID(const string& id) const; // Cerca per ID
    
    // Metodo per filtrare i media in base a vari criteri
    vector<Media*> filtra(const string& titolo = "",
                            const string& tipoMedia = "",
                            const string& genere = "",
                            double ratingMin = 0.0,
                            double ratingMax = 5.0,
                            const string& lingua = "",
                            int annoMin = 1200,
                            int annoMax = 2050) const;
    
    int getNumeroTotaleMedia() const;

    // Metodi per gestione prestiti
    bool prendiInPrestito(const Media* media); // Metoto per prendere in prestito un media
    bool restituisci(const Media* media); // Metodo per restituire un media

    vector<Media*> getListaMedia() const; // Restituisce la lista dei media
};

#endif // BIBLIOTECA.H