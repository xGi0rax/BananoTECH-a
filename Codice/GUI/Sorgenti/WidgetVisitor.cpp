#include "../Headers/WidgetVisitor.h"
#include "../Headers/Widgets/FilmWidget.h"
#include "../Headers/Widgets/LibroWidget.h"
#include "../Headers/Widgets/VinileWidget.h"
#include "../Headers/Widgets/RivistaWidget.h"
#include "../Headers/Widgets/GiocoWidget.h"

void WidgetVisitor::visit(const Libro& libro) {
    LibroWidget* widget = new LibroWidget();
    if (isModifyMode) {
        widget->setCurrentMedia(const_cast<Libro*>(&libro));
    }
    if (isReadOnly) {
        widget->setReadOnly(true);
    }
    createdWidget = widget;
}

void WidgetVisitor::visit(const Film& film) {
    FilmWidget* widget = new FilmWidget();
    if (isModifyMode) {
        widget->setCurrentMedia(const_cast<Film*>(&film));
    }
    if (isReadOnly) {
        widget->setReadOnly(true);
    }
    createdWidget = widget;
}

void WidgetVisitor::visit(const Rivista& rivista) {
    RivistaWidget* widget = new RivistaWidget();
    if (isModifyMode) {
        widget->setCurrentMedia(const_cast<Rivista*>(&rivista));
    }
    if (isReadOnly) {
        widget->setReadOnly(true);
    }
    createdWidget = widget;
}

void WidgetVisitor::visit(const Vinile& vinile) {
    VinileWidget* widget = new VinileWidget();
    if (isModifyMode) {
        widget->setCurrentMedia(const_cast<Vinile*>(&vinile));
    }
    if (isReadOnly) {
        widget->setReadOnly(true);
    }
    createdWidget = widget;
}

void WidgetVisitor::visit(const GiocoDaTavolo& gioco) {
    GiocoWidget* widget = new GiocoWidget();
    if (isModifyMode) {
        widget->setCurrentMedia(const_cast<GiocoDaTavolo*>(&gioco));
    }
    if (isReadOnly) {
        widget->setReadOnly(true);
    }
    createdWidget = widget;
}