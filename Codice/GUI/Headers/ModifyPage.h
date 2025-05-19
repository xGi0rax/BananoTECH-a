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
#include "Widgets/MediaWidget.h"
#include "Widgets/FilmWidget.h"
#include "Widgets/LibroWidget.h"
#include "Widgets/VinileWidget.h"
#include "Widgets/RivistaWidget.h"
#include "Widgets/GiocoWidget.h"

class ModifyPage : public QWidget {
    Q_OBJECT

public:
    explicit ModifyPage(QWidget* parent = nullptr);
    void setMedia(Media* media);

signals:
    void goBackToMainPage(); // Segnale per tornare alla pagina principale
    void mediaEdited(); // Segnale per notificare la modifica del media

private slots:
    void onBackButtonClicked(); // Slot per il pulsante indietro
    void onSaveButtonClicked(); // Slot per il salvataggio delle modifiche
    void onUploadButtonClicked(); // Slot per il caricamento dell'immagine
    
private:
    // Puntatore al media corrente
    Media* currentMedia;

    // Pannello immagine
    QLabel* imagePreview;
    QPushButton* uploadButton;
    QString currentImagePath;
    
    // Widget per i dettagli specifici del media
    QStackedWidget* detailsStackedWidget;
    MediaWidget* currentWidget;
    
    // Pulsanti indietro e salva modifiche
    QPushButton* backButton;
    QPushButton* saveButton;

    // Metodi di configurazione UI
    void setupUI();
};

#endif // MODIFYPAGE_H