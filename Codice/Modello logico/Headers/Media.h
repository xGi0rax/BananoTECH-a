#ifndef MEDIA_H
#define MEDIA_H
#include <string>
using std::string;

class Media {
    private:
        int id;
        string titolo;
        string genere;
        int anno;
        string immagine;
        bool disponibilita;
        int numero_copie;
        int in_prestito;
        string collocazione;
        double rating;
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