#ifndef MEDIAVISITOR_H
#define MEDIAVISITOR_H

class Libro;
class Film;
class Rivista;
class Vinile;
class GiocoDaTavolo;

class MediaVisitor {
public:
    virtual ~MediaVisitor() = default;
    virtual void visit(const Libro& libro) = 0;
    virtual void visit(const Film& film) = 0;
    virtual void visit(const Rivista& rivista) = 0;
    virtual void visit(const Vinile& vinile) = 0;
    virtual void visit(const GiocoDaTavolo& gioco) = 0;
};

#endif // MEDIAVISITOR_H