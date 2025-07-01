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
#include "../../Modello logico/Headers/Biblioteca.h"

class ModifyPage : public QWidget {
    Q_OBJECT

public:
    explicit ModifyPage(QWidget* parent = nullptr);
    void setMedia(Media* media);
    void setBiblioteca(Biblioteca* biblio);

signals:
    void goBackToMainPage(); // Segnale per tornare alla pagina principale
    void mediaModified(); // Segnale per notificare che il media è stato modificato
    void mediaCopiesIncreased(); // Segnale per notificare che le copie del media sono state aumentate

private slots:
    void onBackButtonClicked(); // Slot per il pulsante indietro
    void onSaveButtonClicked(); // Slot per il salvataggio delle modifiche
    void onUploadButtonClicked(); // Slot per il caricamento dell'immagine
    
private:
    // Puntatore alla biblioteca
    Biblioteca* biblioteca;

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