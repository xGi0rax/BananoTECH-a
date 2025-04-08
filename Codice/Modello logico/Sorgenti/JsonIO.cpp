#include "../Headers/JsonIO.h"
#include "../Headers/Biblioteca.h"
#include "../Headers/Media.h"
#include <QDomElement>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QString>
#include <QJsonObject>

QJsonObject JsonIO::mediaToJson(const Media* media) const {
    QJsonObject jObj;
    media->toJson(jObj); // Chiamata polimorfica per convertire il media in JSON
    return jObj;
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

/*
bool JsonIO::caricaDaFile(Biblioteca& biblio, const string& filePath) {
    
}
*/
