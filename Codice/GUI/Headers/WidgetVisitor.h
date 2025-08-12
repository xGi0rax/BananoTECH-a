#ifndef WIDGETVISITOR_H
#define WIDGETVISITOR_H

#include "../../Modello logico/Headers/MediaVisitor.h"
#include "../Headers/Widgets/MediaWidget.h"

class Libro;
class Film;
class Rivista;
class Vinile;
class GiocoDaTavolo;

class WidgetVisitor : public MediaVisitor {
private:
    MediaWidget* createdWidget;
    bool isReadOnly;
    bool isModifyMode;

public:
    WidgetVisitor(bool readOnly = false, bool modifyMode = false) 
        : createdWidget(nullptr), isReadOnly(readOnly), isModifyMode(modifyMode) {}
    
    void visit(const Libro& libro) override;
    void visit(const Film& film) override;
    void visit(const Rivista& rivista) override;
    void visit(const Vinile& vinile) override;
    void visit(const GiocoDaTavolo& gioco) override;
    
    MediaWidget* getCreatedWidget() const { return createdWidget; }
    void reset() { createdWidget = nullptr; }
};

#endif