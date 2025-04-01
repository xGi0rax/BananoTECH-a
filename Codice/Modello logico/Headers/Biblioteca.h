#ifndef BIBLIOTECA.H
#define BIBLIOTECA.H
#include "Media.h"
#include "FileManager.h"
#include <vector>
#include <QString>

using std::vector;

class Biblioteca{
private:
    vector<Media*> listaMedia; // vettore di puntatori a Media
    int nextId; //contatore per l'auto-incremento degli Id

public:
    Biblioteca();
    ~Biblioteca();
        
    void aggiungiMedia(Media* media);    // Aggiunge un media (assegna ID)
    bool esisteMedia(const string& titolo, int anno) const;  // Metodo per controllare se un media esiste gia' prima di aggiungerlo
    bool rimuoviMedia(int id);       // Rimuove un media per ID
    Media* cercaMediaDaID(int id);       // Cerca per ID
    vector<Media*> cerca(const string& query) const; // Cerca per titolo/autore/etc.
    
    void salvaSuFile(const QString& path); // Salva in JSON/XML
    void caricaDaFile(const QString& path); // Carica da file
    
    int getNumeroTotaleMedia() const;
};

#endif // BIBLIOTECA.H