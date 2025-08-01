#ifndef ICONVISITOR_H
#define ICONVISITOR_H

#include "../../Modello logico/Headers/MediaVisitor.h"
#include <QString>

class Libro;
class Film;
class Rivista;
class Vinile;
class GiocoDaTavolo;

class IconVisitor : public MediaVisitor {
private:
    QString iconPath;

public:
    void visit(const Libro&) override {
        iconPath = ":/Immagini/LogoLibro1.png";
    }
    
    void visit(const Film&) override {
        iconPath = ":/Immagini/LogoFilm1.png";
    }

    void visit(const Rivista&) override {
        iconPath = ":/Immagini/LogoRivista1.png";
    }
    
    void visit(const Vinile&) override {
        iconPath = ":/Immagini/LogoVinile1.png";
    }

    void visit(const GiocoDaTavolo&) override {
        iconPath = ":/Immagini/LogoGioco1.png";
    }
    
    QString getIconPath() const { return iconPath; }
};

#endif // ICONVISITOR_H