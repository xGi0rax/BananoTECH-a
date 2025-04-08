#ifndef FILEMANAGER.H
#define FILEMANAGER.H

#include "Biblioteca.h"
#include "Media.h"
#include <QJsonObject>

class FileManager{
public:
    // Salvataggio su file
    bool salvaSuJson(const Biblioteca& biblio, const string& filePath) const;
    bool salvaSuXml(const Biblioteca& biblio, const string& filePath) const;
    
    // Caricamento su file
    bool caricaDaJson(Biblioteca& biblio, const string& filePath);
    bool caricaDaXml(Biblioteca& biblio, const string& filePath);

private:
    // Metodi per convertire un media da file e viceversa
    // Per JSON 
    QJsonObject mediaToJson(const Media* media) const;  // Converte un Media in QJsonObject 
    Media* jsonToMedia(const QJsonObject& json) const;  // Crea un Media da QJsonObject (usa factory)
    
    // Versioni analoghe per XML
    /*QDomElement mediaToXml(const Media* media, QDomDocument& doc) const;
    Media* xmlToMedia(const QDomElement& element) const;*/
};
    
#endif //FILEMANAGER.H