#ifndef MODIFYPAGE_H
#define MODIFYPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QStackedWidget>
#include "../../Modello logico/Headers/Media.h"
#include "../../Modello logico/Headers/Film.h"
#include "../../Modello logico/Headers/Libro.h"
#include "../../Modello logico/Headers/Vinile.h"
#include "../../Modello logico/Headers/Rivista.h"
#include "../../Modello logico/Headers/GiocoDaTavolo.h"
#include "Widgets/MediaModifyWidget.h"

class ModifyPage : public QWidget {
    Q_OBJECT

public:
    explicit ModifyPage(QWidget* parent = nullptr);
    void setMedia(Media* media);

signals:
    void goBackToMainPage();

private slots:
    void onBackButtonClicked();
    void onSaveButtonClicked();
    void onUploadButtonClicked();
    
private:
    // Pannello immagine
    QLabel* imagePreview;
    QPushButton* uploadButton;
    QString currentImagePath;
    
    // Widget per i dettagli specifici del media
    QStackedWidget* detailsStackedWidget;
    MediaModifyWidget* currentDetailsWidget;
    
    // Pulsanti
    QPushButton* saveButton;
    QPushButton* cancelButton;
    
    // Puntatore al media corrente
    Media* currentMedia;
};

#endif // MODIFYPAGE_H