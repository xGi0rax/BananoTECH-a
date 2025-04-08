#include <iostream>
#include <vector>
#include <string>
#include "Headers/Biblioteca.h"
#include "Headers/Media.h"
#include "Headers/Film.h"
#include "Headers/Libro.h"
#include "Headers/Vinile.h"
#include "Headers/GiocoDaTavolo.h"
#include "Headers/Rivista.h"
#include "Headers/JSonIO.h"
#include "Headers/XmlIO.h"

using namespace std;

int main() {
    // Creazione di una biblioteca con ID
    string idBiblioteca = "VC";
    Biblioteca biblioteca(idBiblioteca);

    // Creazione di diversi tipi di media
    // Film
    vector<string> castInception = {"Leonardo DiCaprio", "Joseph Gordon-Levitt", "Ellen Page"};
    Film* film1 = new Film("Inception", "Fantascienza", 2010, 
                            "inception.jpg", true, 5, "Christopher Nolan", 148, castInception, 0, "PG-13", 4.8);

    // Libro
    Libro* libro1 = new Libro("Il Signore degli Anelli", "Fantasy", 1954, 
                            "lotr.jpg", true, 3, "978-0261102385", 
                            "J.R.R. Tolkien", "Allen & Unwin", 1216, 0, 
                            "Scaffale A1", 4.9);

    // Rivista
    Rivista* rivista1 = new Rivista("National Geographic", "Natura", 2023, 
                            "natgeo.jpg", true, 10, "National Geographic Society", 
                            100, "2023-01-01", "Mensile", 0, 
                            "Scaffale B2", 4.5);
        
    // Gioco da Tavolo
    GiocoDaTavolo* gioco1 = new GiocoDaTavolo("Catan", "Strategia", 1995, 
                            "catan.jpg", true, 4, 3, 90, 10, 
                            "Kosmos", 0, "Scaffale C3", 4.7);

    // Vinile
    Vinile* vinile1 = new Vinile("Abbey Road", "Rock", 1969, 
                            "abbey_road.jpg", true, 2, "The Beatles", 4, 20,
                            0, "Scaffale D4", 4.8);

    // Aggiunta dei media alla biblioteca
    biblioteca.aggiungiMedia(film1);
    biblioteca.aggiungiMedia(libro1);
    biblioteca.aggiungiMedia(rivista1);
    biblioteca.aggiungiMedia(gioco1);
    biblioteca.aggiungiMedia(vinile1);

    // Stampa informazioni sulla biblioteca
    cout << "Biblioteca creata con ID: " << idBiblioteca << endl;
    cout << "Numero di media nella biblioteca: " << biblioteca.getNumeroTotaleMedia() << endl;

    
    JsonIO jsonIO;
    string filePath = "biblioteca_test.json";
    
    // Salvataggio della biblioteca su file JSON
    if (jsonIO.salvaSuFile(biblioteca, filePath)) {
        cout << "Biblioteca salvata su file JSON: " << filePath << endl;
    } else {
        cout << "Errore durante il salvataggio della biblioteca su file JSON." << endl;
    }
    

    
    return 0;
}