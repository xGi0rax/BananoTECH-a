#ifndef GIOCODETAILSWIDGET_H
#define GIOCODETAILSWIDGET_H

#include "MediaDetailsWidget.h"
#include "../../../Modello logico/Headers/GiocoDaTavolo.h"
#include <QSpinBox>
#include <QLineEdit>

class GiocoDetailsWidget : public MediaDetailsWidget {
    Q_OBJECT
    
public:
    explicit GiocoDetailsWidget(QWidget *parent = nullptr);
    
    // Getters specifici
    int getMaxGiocatori() const { return maxPlayersEdit->value(); }
    int getDurataGioco() const { return playTimeEdit->value(); }
    int getEtaMinima() const { return minAgeEdit->value(); }
    QString getEditore() const { return editorGiocoEdit->text(); }
    
    bool validateData() override;
    Media* createMedia() override;

    void setMedia(GiocoDaTavolo* gioco);
    void setReadOnly(bool readOnly);
    
protected:
    void addSpecificFields() override;
    
private:
    QSpinBox *maxPlayersEdit;
    QSpinBox *playTimeEdit;
    QSpinBox *minAgeEdit;
    QLineEdit *editorGiocoEdit;
};

#endif // GIOCODETAILSWIDGET_H