#ifndef LIBROMODIFYWIDGET_H
#define LIBROMODIFYWIDGET_H

#include "MediaModifyWidget.h"
#include "../../../Modello logico/Headers/Libro.h"
#include <QSpinBox>
#include <QLineEdit>

class LibroModifyWidget : public MediaModifyWidget {
    Q_OBJECT
    
public:
    explicit LibroModifyWidget(QWidget* parent = nullptr);
    
    void setMedia(Libro* libro);
    
    bool validateData() override;
    bool applyChanges() override;
    
protected:
    void addSpecificFields() override;
    
private:
    QLineEdit* isbnEdit;
    QLineEdit* editorEdit;
    QSpinBox* pagesEdit;
};

#endif // LIBROMODIFYWIDGET_H