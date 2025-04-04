#include "../Headers/FileManager.h"
#include "../Headers/Media.h"
#include "../Headers/Film.h"
#include "../Headers/Libro.h"
#include "../Headers/Vinile.h"
#include "../Headers/GiocoDaTavolo.h"
#include "../Headers/Rivista.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDomDocument>
#include <QTextStream>
#include <QJsonObject>
#include <QDomElement>
#include <QString>
#include <string>


// Salvataggio su file
bool FileManager::salvaSuJson(const Biblioteca& biblio, const string& filePath) const{
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

bool FileManager::salvaSuXml(const Biblioteca& biblio, const string& filePath) const{

}

// Caricamento da file
bool FileManager::caricaDaJson(Biblioteca& biblio, const string& filePath){

}

bool FileManager::caricaDaXml(Biblioteca& biblio, const string& filePath){

}


// Metodi privati per convertire un media in JSON e viceversa
QJsonObject FileManager::mediaToJson(const Media* media) const{
    QJsonObject jObj;
    jObj["id"] = media->getId(); 
    jObj["titolo"] = QString::fromStdString(media->getTitolo()); 
    jObj["genere"] = QString::fromStdString(media->getGenere()); 
    jObj["anno"] = media->getAnno(); 
    jObj["immagine"] = QString::fromStdString(media->getImmagine()); 
    jObj["disponibilita"] = media->getDisponibilita(); 
    jObj["numero_copie"] = media->getNumeroCopie(); 
    jObj["in_prestito"] = media->getInPrestito(); 
    jObj["collocazione"] = QString::fromStdString(media->getCollocazione()); 
    jObj["rating"] = media->getRating(); 
    
    // Aggiunta eventuali campi specifici per sottoclassi di Media
    if (dynamic_cast<const Film*>(media)) {
        const Film* film = static_cast<const Film*>(media);
        jObj["regista"] = QString::fromStdString(film->getRegista());
        jObj["durata"] = film->getDurata();
        string cast;
        for (const auto& attore : film->getCast()) {
            if (!cast.empty()) {
                cast += ", ";
            }
            cast += attore;
        }
        jObj["cast"] = QString::fromStdString(cast);

    } else if (dynamic_cast<const Libro*>(media)) {
        const Libro* libro = static_cast<const Libro*>(media);
        jObj["isbn"] = QString::fromStdString(libro->getIsbn());
        jObj["autore"] = QString::fromStdString(libro->getAutore());
        jObj["editore"] = QString::fromStdString(libro->getEditore());
        jObj["numero_pagine"] = libro->getNPagine();

    } else if (dynamic_cast<const Vinile*>(media)) {
        const Vinile* vinile = static_cast<const Vinile*>(media);
        jObj["artista"] = QString::fromStdString(vinile->getArtista());
        jObj["numero_tracce"] = vinile->getNTracce();
        jObj["durata"] = vinile->getDurata();

    } else if (dynamic_cast<const GiocoDaTavolo*>(media)) {
        const GiocoDaTavolo* gioco = static_cast<const GiocoDaTavolo*>(media);
        jObj["numero_giocatori"] = gioco->getNGiocatori();
        jObj["durata"] = gioco->getDurata();
        jObj["eta"] = gioco->getEtà();
        jObj["editore"] = QString::fromStdString(gioco->getEditore());

    } else if (dynamic_cast<const Rivista*>(media)) {
        const Rivista* rivista = static_cast<const Rivista*>(media);
        jObj["editore"] = QString::fromStdString(rivista->getEditore());
        jObj["numero_pagine"] = rivista->getNPagine();
        jObj["data_pubb"] = QString::fromStdString(rivista->getDataPubb());
        //jObj["periodicita"] = QString::fromStdString(rivista->getPeriodicita());

    } 

} 

Media* FileManager::jsonToMedia(const QJsonObject& json) const{

}   

QDomElement FileManager::mediaToXml(const Media* media, QDomDocument& doc) const{

}

Media* FileManager::xmlToMedia(const QDomElement& element) const{

}
