#ifndef VINILEMODIFYWIDGET_H
#define VINILEMODIFYWIDGET_H

#include "MediaModifyWidget.h"
#include "../../../Modello logico/Headers/Vinile.h"
#include <QSpinBox>

class VinileModifyWidget : public MediaModifyWidget {
    Q_OBJECT
    
public:
    explicit VinileModifyWidget(QWidget* parent = nullptr);
    
    void setMedia(Vinile* vinile);
    
    bool validateData() override;
    bool applyChanges() override;
    
protected:
    void addSpecificFields() override;
    
private:
    QSpinBox* trackCountEdit;
    QSpinBox* durationEdit;
};

#endif // VINILEMODIFYWIDGET_H