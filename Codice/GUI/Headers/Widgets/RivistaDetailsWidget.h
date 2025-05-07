#ifndef RIVISTADETAILSWIDGET_H
#define RIVISTADETAILSWIDGET_H

#include "MediaDetailsWidget.h"
#include "../../../Modello logico/Headers/Rivista.h"
#include <QSpinBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>

class RivistaDetailsWidget : public MediaDetailsWidget {
    Q_OBJECT
    
public:
    explicit RivistaDetailsWidget(QWidget *parent = nullptr);
    
    // Getters specifici
    QString getEditore() const { return editorRivistaEdit->text(); }
    int getNumPagine() const { return pagesRivistaEdit->value(); }
    QDate getDataPubb() const { return publicationDateEdit->date(); }
    QString getPeriodicita() const { return periodicityComboBox->currentText(); }
    
    bool validateData() override;
    Media* createMedia() override;

    void setMedia(Rivista* rivista);
    void setReadOnly(bool readOnly);
    
protected:
    void addSpecificFields() override;
    
private:
    QLineEdit *editorRivistaEdit;
    QSpinBox *pagesRivistaEdit;
    QDateEdit *publicationDateEdit;
    QComboBox *periodicityComboBox;
};

#endif // RIVISTADETAILSWIDGET_H