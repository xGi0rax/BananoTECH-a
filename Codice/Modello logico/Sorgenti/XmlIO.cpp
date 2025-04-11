#include "../Headers/XmlIO.h"
#include "../Headers/Media.h"
#include "../Headers/Film.h"
#include "../Headers/Libro.h"
#include "../Headers/Vinile.h"
#include "../Headers/GiocoDaTavolo.h"
#include "../Headers/Rivista.h"
#include "../Headers/Biblioteca.h"
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QTextStream>

QDomElement XmlIO::mediaToXml(const Media* media, QDomDocument& doc) const {
    QDomElement elemento = doc.createElement("media");
    media->toXml(elemento, doc); // Chiamata polimorfica per convertire il media in XML
    return elemento;
}

Media* XmlIO::xmlToMedia(const QDomElement& element) const{
    
}


bool XmlIO::salvaSuFile(const Biblioteca& biblio, const string& filePath) const {
    QDomDocument doc;
    QDomElement root = doc.createElement("biblioteca");
    doc.appendChild(root);

    for (const Media* media : biblio.getListaMedia()) {
        QDomElement elemento = mediaToXml(media, doc);
        root.appendChild(elemento); // Aggiunge l'elemento alla radice del documento
    }

    QFile file(QString::fromStdString(filePath));
    if (!file.open(QIODevice::WriteOnly)) {
        return false; // Errore nell'aprire il file
    }

    QTextStream stream(&file);
    stream << doc.toString(); // Scrive il documento XML nel file
    file.close();
    return true; // Salvataggio riuscito
}

bool XmlIO::caricaDaFile(Biblioteca& biblio, const string& filePath) {
    return true;
}