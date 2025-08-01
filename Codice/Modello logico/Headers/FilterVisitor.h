#ifndef FILTERVISITOR_H
#define FILTERVISITOR_H

#include "MediaVisitor.h"
#include <string>

class Libro;
class Film;
class Rivista;
class Vinile;
class GiocoDaTavolo;

class FilterVisitor : public MediaVisitor {
private:
    std::string targetType;
    bool matches;

public:
    FilterVisitor(const std::string& type) : targetType(type), matches(false) {}
    
    void visit(const Libro&) override {
        matches = (targetType == "Libro");
    }
    
    void visit(const Film&) override {
        matches = (targetType == "Film");
    }

    void visit(const Rivista&) override {
        matches = (targetType == "Rivista");
    }
    
    void visit(const Vinile&) override {
        matches = (targetType == "Vinile");
    }

    void visit(const GiocoDaTavolo&) override {
        matches = (targetType == "Gioco da tavolo");
    }
    
    bool getResult() const { return matches; }
    void reset() { matches = false; }
};

#endif