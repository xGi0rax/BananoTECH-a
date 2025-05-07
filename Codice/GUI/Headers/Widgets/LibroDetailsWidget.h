#ifndef LIBRODETAILSWIDGET_H
#define LIBRODETAILSWIDGET_H

#include "MediaDetailsWidget.h"
#include "../../../Modello logico/Headers/Libro.h"
#include <QSpinBox>
#include <QLineEdit>

class LibroDetailsWidget : public MediaDetailsWidget {
    Q_OBJECT
    
public:
    explicit LibroDetailsWidget(QWidget *parent = nullptr);
    
    // Getters specifici
    QString getISBN() const { return isbnEdit->text(); }
    QString getEditore() const { return editorLibroEdit->text(); }
    int getNumPagine() const { return pagesLibroEdit->value(); }
    
    bool validateData() override;
    Media* createMedia() override;

    void setMedia(Libro* libro);
    void setReadOnly(bool readOnly);
    
protected:
    void addSpecificFields() override;
    
private:
    QLineEdit *isbnEdit;
    QLineEdit *editorLibroEdit;
    QSpinBox *pagesLibroEdit;
};

#endif // LIBRODETAILSWIDGET_H