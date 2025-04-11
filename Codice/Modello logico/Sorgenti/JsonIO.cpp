#include "../Headers/JsonIO.h"
#include "../Headers/Biblioteca.h"
#include "../Headers/Media.h"
#include "../Headers/Film.h"
#include "../Headers/Libro.h"
#include "../Headers/Vinile.h"
#include "../Headers/GiocoDaTavolo.h"
#include "../Headers/Rivista.h"
#include <QDomElement>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QString>
#include <QJsonObject>

#include <iostream>
using namespace std;

QJsonObject JsonIO::mediaToJson(const Media* media) const {
    QJsonObject jObj;
    media->toJson(jObj); // Chiamata polimorfica per convertire il media in JSON
    return jObj;
}

Media* JsonIO::jsonToMedia(const QJsonObject& json) const{
    // Attributi comuni a tutti i media
    string id = json["id"].toString().toStdString();
    string titolo = json["titolo"].toString().toStdString();
    string genere = json["genere"].toString().toStdString();
    int anno = json["anno"].toInt();
    string lingua = json["lingua"].toString().toStdString();
    string immagine = json["immagine"].toString().toStdString();
    bool disponibilita = json["disponibilita"].toBool();
    int numero_copie = json["numero_copie"].toInt();
    int in_prestito = json["in_prestito"].toInt();
    string collocazione = json["collocazione"].toString().toStdString();
    double rating = json["rating"].toDouble();

    // Creazione del media in base al tipo specificato nel JSON
    string tipo = json["tipo"].toString().toStdString();
    
    if (tipo == "film") {
        string regista = json["regista"].toString().toStdString();
        int durata = json["durata"].toInt();
        vector<string> cast;
        QJsonArray jCast = json["cast"].toArray();
        for (const QJsonValue& elemento : jCast) {
            cast.push_back(elemento.toString().toStdString());
        }
        return new Film(titolo, genere, anno, lingua, immagine, disponibilita, numero_copie, regista, durata, cast, in_prestito, collocazione, rating);

    } else if (tipo == "libro") {
        string isbn = json["isbn"].toString().toStdString();
        string autore = json["autore"].toString().toStdString();
        string editore = json["editore"].toString().toStdString();
        int numeroPagine = json["numero_pagine"].toInt();

        return new Libro(titolo, genere, anno, lingua, immagine, disponibilita, numero_copie, isbn, autore, editore, numeroPagine, in_prestito, collocazione, rating);

    } else if (tipo == "rivista") {
        string editore = json["editore"].toString().toStdString();
        int numeroPagine = json["numero_pagine"].toInt();
        string dataPubblicazione = json["data_pubblicazione"].toString().toStdString();
        string periodicita = json["periodicita"].toString().toStdString();

        return new Rivista(titolo, genere, anno, lingua, immagine, disponibilita, numero_copie, editore, numeroPagine, dataPubblicazione, periodicita, in_prestito, collocazione, rating);

    } else if (tipo == "gioco") {
        int numeroGiocatori = json["numero_giocatori"].toInt();
        int etaMinima = json["eta_minima"].toInt();
        int durata = json["durata"].toInt();
        string editore = json["editore"].toString().toStdString();

        return new GiocoDaTavolo(titolo, genere, anno, lingua, immagine, disponibilita, numero_copie, numeroGiocatori, etaMinima, durata, editore, in_prestito, collocazione, rating);

    } else if (tipo == "vinile") {
        string artista = json["artista"].toString().toStdString();
        int numeroTracce = json["numero_tracce"].toInt();
        int durata = json["durata"].toInt();

        return new Vinile(titolo, genere, anno, lingua, immagine, disponibilita, numero_copie, artista, numeroTracce, durata, in_prestito, collocazione, rating);
    }

    return nullptr;
}


bool JsonIO::salvaSuFile(const Biblioteca& biblio, const string& filePath) const {
    QFile file(QString::fromStdString(filePath));
    if (!file.open(QIODevice::WriteOnly)) {
        return false; // Errore nell'aprire il file
    }

    QJsonArray jArray;
    for (const Media* media : biblio.getListaMedia()) {
        jArray.append(mediaToJson(media)); // Converte ogni media in JSON e lo aggiunge all'array
    }

    QJsonDocument jDoc(jArray);
    file.write(jDoc.toJson());
    file.close();
    return true; // Salvataggio riuscito
}


bool JsonIO::caricaDaFile(Biblioteca& biblio, const string& filePath) {
    QFile file(QString::fromStdString(filePath));
    if (!file.open(QIODevice::ReadOnly)) {
        return false; // Errore nell'aprire il file
    }

    QByteArray dati = file.readAll();
    file.close();

    QJsonDocument jDoc(QJsonDocument::fromJson(dati));

    if (!jDoc.isArray()) {
        return false; // Il documento non continene un array JSON
    }
    QJsonArray jArray = jDoc.array();

    // aggiungere rimozione elementi da biblio

    for (const QJsonValue& elemento : jArray) {
        QJsonObject jObj = elemento.toObject();
        Media* media = jsonToMedia(jObj); // Crea un media da JSON polimorficamente
        if (media) {
            biblio.aggiungiMedia(media); // Aggiunge il media alla biblioteca
        }
    }

    return true; // Caricamento riuscito
}

