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
#include "Headers/FileManager.h"

using namespace std;

int main() {
    // Creazione di una biblioteca con ID
    string idBiblioteca = "VC";
    Biblioteca biblioteca(idBiblioteca);

    // Creazione di diversi tipi di media
    // Film
    vector<string> castInception = {"Leonardo DiCaprio", "Joseph Gordon-Levitt", "Ellen Page"};
    Film* film1 = new Film(0, "Inception", "Fantascienza", 2010, 
                            "inception.jpg", true, 5, 2, "Scaffale A1", 4.8, 
                            "Christopher Nolan", 148, castInception);

    // Libro
    Libro* libro1 = new Libro(1, "1984", "Distopia", 1949, 
                             "1984.jpg", true, 3, 1, "Scaffale B2", 4.5, 
                             "George Orwell", "1234567890123", "Secker & Warburg", 328);

    // Rivista
    Rivista* rivista1 = new Rivista(2, "National Geographic", "Scienza", 2023, 
                                 "natgeo.jpg", true, 10, 0, "Scaffale C3", 4.2, 
                                 "National Geographic Society", 50, "Mensile", "01/2023");

    // Gioco da Tavolo
    GiocoDaTavolo* gioco1 = new GiocoDaTavolo(3, "Catan", "Strategia", 1995, 
                                             "catan.jpg", true, 4, 1, "Scaffale D4", 2.7, 
                                             4, 90, 10, "Kosmos");

    // Vinile
    Vinile* vinile1 = new Vinile(4, "Abbey Road", "Rock", 1969, 
                             "abbey_road.jpg", true, 2, 0, "Scaffale E5", 4.9, 
                             "The Beatles", 17, 47);

    // Aggiunta dei media alla biblioteca
    biblioteca.aggiungiMedia(film1);
    biblioteca.aggiungiMedia(libro1);
    biblioteca.aggiungiMedia(rivista1);
    biblioteca.aggiungiMedia(gioco1);
    biblioteca.aggiungiMedia(vinile1);

    // Stampa informazioni sulla biblioteca
    cout << "Biblioteca creata con ID: " << idBiblioteca << endl;
    cout << "Numero di media nella biblioteca: " << biblioteca.getNumeroTotaleMedia() << endl;

    // Creazione del FileManager e salvataggio su JSON
    FileManager fileManager;
    string filePath = "biblioteca_test.json";
    
    if (fileManager.salvaSuJson(biblioteca, filePath)) {
        cout << "\nSalvataggio su JSON riuscito! File creato: " << filePath << endl;
    } else {
        cerr << "Errore durante il salvataggio su JSON!" << endl;
        return 1;
    }

    // Nota: la biblioteca gestisce automaticamente la distruzione dei media nel suo distruttore
    return 0;
}