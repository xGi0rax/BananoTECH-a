#ifndef VINILEDETAILSWIDGET_H
#define VINILEDETAILSWIDGET_H

#include "MediaDetailsWidget.h"
#include <QSpinBox>

class VinileDetailsWidget : public MediaDetailsWidget {
    Q_OBJECT
    
public:
    explicit VinileDetailsWidget(QWidget *parent = nullptr);
    
    // Getters specifici
    int getNumTracce() const { return trackCountEdit->value(); }
    int getDurata() const { return durationVinileEdit->value(); }
    
    bool validateData() override;
    Media* createMedia() override;
    
protected:
    void addSpecificFields() override;
    
private:
    QSpinBox *trackCountEdit;
    QSpinBox *durationVinileEdit;
};

#endif // VINILEDETAILSWIDGET_H