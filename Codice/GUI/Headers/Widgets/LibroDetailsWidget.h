#ifndef LIBRODETAILSWIDGET_H
#define LIBRODETAILSWIDGET_H

#include "MediaDetailsWidget.h"
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
    
protected:
    void addSpecificFields() override;
    
private:
    QLineEdit *isbnEdit;
    QLineEdit *editorLibroEdit;
    QSpinBox *pagesLibroEdit;
};

#endif // LIBRODETAILSWIDGET_H