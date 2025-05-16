#ifndef RIVISTAMODIFYWIDGET_H
#define RIVISTAMODIFYWIDGET_H

#include "MediaModifyWidget.h"
#include "../../../Modello logico/Headers/Rivista.h"
#include <QSpinBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>

class RivistaModifyWidget : public MediaModifyWidget {
    Q_OBJECT
    
public:
    explicit RivistaModifyWidget(QWidget* parent = nullptr);
    
    void setMedia(Rivista* rivista);
    
    bool validateData() override;
    bool applyChanges() override;
    
protected:
    void addSpecificFields() override;
    
private:
    QLineEdit* editorEdit;
    QSpinBox* pagesEdit;
    QDateEdit* publicationDateEdit;
    QComboBox* periodicityComboBox;
};

#endif // RIVISTAMODIFYWIDGET_H