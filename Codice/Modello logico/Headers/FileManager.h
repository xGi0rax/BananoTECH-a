#ifndef FILEMANAGER.H
#define FILEMANAGER.H

#include "Biblioteca.h"
#include "Media.h"
#include <QJsonObject>
#include <QDomElement>

class FileManager{
public:
    // Serializzazione (salvataggio)
    bool salvaSuJson(const Biblioteca& biblio, const string& filePath) const;
    bool salvaSuXml(const Biblioteca& biblio, const string& filePath) const;
    
    // Deserializzazione (caricamento)
    bool caricaDaJson(Biblioteca& biblio, const string& filePath);
    bool caricaDaXml(Biblioteca& biblio, const string& filePath);

private:
    // metodi per convertire un media da file e viceversa
    // Per JSON 
    QJsonObject mediaToJson(const Media* media) const;  // Converte un Media in QJsonObject 
    Media* jsonToMedia(const QJsonObject& json) const;  // Crea un Media da QJsonObject (usa factory)
    
    // Versioni analoghe per XML
    QDomElement mediaToXml(const Media* media, QDomDocument& doc) const;
    Media* xmlToMedia(const QDomElement& element) const;
};
    
#endif #FILEMANAGER.H