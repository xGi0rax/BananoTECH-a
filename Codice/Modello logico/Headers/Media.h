#ifndef MEDIA_H
#define MEDIA_H
#include <string>
using std::string;

class Media {
private:
    int id; // ID univoco del media
    string titolo; // Titolo del media
    string genere; // Genere del media (es. "Fantascienza", "Commedia", etc.)
    int anno; // Anno di pubblicazione
    string immagine;  // Percorso dell'immagine del media
    bool disponibilita; // Disponibilità del media (true se disponibile, false se tutte le copie in prestito)
    int numero_copie; // Numero totale di copie del media
    int in_prestito; // Numero di copie attualmente in prestito
    string collocazione; // Collocazione del media nella biblioteca (es. scaffale "A1", "B2", etc.)
    double rating; // Valutazione del media (da 1 a 5 stelle)
    
public:
    Media(int id, string titolo, string genere, int anno, string immagine, bool disponibilita, int numero_copie, int in_prestito = 0, string collocazione = "", double rating = 0.0);
    virtual ~Media() =default;

    // Metodi getter
    int getId() const;
    string getTitolo() const;
    string getGenere() const;
    int getAnno() const;
    string getImmagine() const;
    bool getDisponibilita() const;
    int getNumeroCopie() const;
    int getInPrestito() const;
    string getCollocazione() const;
    double getRating() const;

    // Metodi setter
    void setId(const int& id);
    void setTitolo(const string& titolo);
    void setGenere(const string& genere);
    void setAnno(const int& anno);
    void setImmagine(const string& imm);
    void setDisponibilita(bool dispon);
    void setNumeroCopie(const int& n_copie);
    void setInPrestito(const int& in_prestito);
    void setCollocazione(const string& coll);

    bool prendiInPrestito(); // Metoto per prendere in prestito un media
    bool restituisci(); // Metodo per restituire un media
};

#endif // MEDIA_H