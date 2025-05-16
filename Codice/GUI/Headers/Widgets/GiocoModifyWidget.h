#ifndef GIOCOMODIFYWIDGET_H
#define GIOCOMODIFYWIDGET_H

#include "MediaModifyWidget.h"
#include "../../../Modello logico/Headers/GiocoDaTavolo.h"
#include <QSpinBox>
#include <QLineEdit>

class GiocoModifyWidget : public MediaModifyWidget {
    Q_OBJECT
    
public:
    explicit GiocoModifyWidget(QWidget* parent = nullptr);
    
    void setMedia(GiocoDaTavolo* gioco);
    
    bool validateData() override;
    bool applyChanges() override;
    
protected:
    void addSpecificFields() override;
    
private:
    QSpinBox* maxPlayersEdit;
    QSpinBox* playTimeEdit;
    QSpinBox* minAgeEdit;
    QLineEdit* editorEdit;
};

#endif // GIOCOMODIFYWIDGET_H