#ifndef FILMMODIFYWIDGET_H
#define FILMMODIFYWIDGET_H

#include "MediaModifyWidget.h"
#include "../../../Modello logico/Headers/Film.h"
#include <QSpinBox>
#include <QLineEdit>

class FilmModifyWidget : public MediaModifyWidget {
    Q_OBJECT
    
public:
    explicit FilmModifyWidget(QWidget* parent = nullptr);
    
    void setMedia(Film* film);
    
    bool validateData() override;
    bool applyChanges() override;
    
protected:
    void addSpecificFields() override;
    
private:
    QSpinBox* durationEdit;
    QLineEdit* castEdit;
};

#endif // FILMMODIFYWIDGET_H