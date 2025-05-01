#ifndef FILMDETAILSWIDGET_H
#define FILMDETAILSWIDGET_H

#include "MediaDetailsWidget.h"
#include <QSpinBox>
#include <QLineEdit>

class FilmDetailsWidget : public MediaDetailsWidget {
    Q_OBJECT
    
public:
    explicit FilmDetailsWidget(QWidget *parent = nullptr);
    
    // Getters per i campi specifici
    int getDuration() const { return durationFilmEdit->value(); }
    QString getCast() const { return castEdit->text(); }
    
    // Implementazione dei metodi virtuali della classe base
    bool validateData() override;
    Media* createMedia() override;
    
protected:
    void addSpecificFields() override;
    
private:
    QSpinBox *durationFilmEdit;
    QLineEdit *castEdit;
};

#endif // FILMDETAILSWIDGET_H