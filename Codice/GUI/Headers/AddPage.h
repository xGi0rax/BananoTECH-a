#ifndef ADDPAGE_H
#define ADDPAGE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QStackedWidget>
#include <QFormLayout>
#include <QSpinBox>
#include <QDateEdit>
#include <QScrollArea>
#include "Widgets/MediaWidget.h"
#include "Widgets/FilmWidget.h"
#include "Widgets/LibroWidget.h"
#include "Widgets/VinileWidget.h"
#include "Widgets/RivistaWidget.h"
#include "Widgets/GiocoWidget.h"


class AddPage : public QWidget {
    Q_OBJECT

public:
    explicit AddPage(QWidget *parent = nullptr);

signals:
    void goBackToMainPage(); // Segnale per tornare alla pagina principale
    void mediaCreated(Media *media); // Segnale per notificare la creazione del nuovo media

private slots:
    void onBackButtonClicked();  // Slot per il pulsante indietro
    void onConfirmTypeButtonClicked(); // Slot per il pulsante di conferma del tipo di media
    void onAddButtonClicked(); // Slot per il pulsante di salvataggio del media
    void onUploadButtonClicked(); // Slot per il caricamento dell'immagine

private:
    // Enum per identificare il tipo di media
    enum MediaType {
        FILM = 0,
        LIBRO,
        VINILE,
        RIVISTA,
        GIOCO_DA_TAVOLO
    };

    // StackedWidget principale per la pagina
    QStackedWidget *mainContentStack;

    // Barra laterale contente pulsante indietro, immagine e pulsante carica immagine
    QPushButton *backButton;
    QLabel *imagePreview;
    QPushButton *uploadButton;
    QString selectedImagePath;
    
    // Widget per la selezione del tipo di media
    QWidget *selectionWidget;
    QButtonGroup *mediaTypeGroup;
    QRadioButton *filmRadio;
    QRadioButton *libroRadio;
    QRadioButton *vinileRadio;
    QRadioButton *rivistaRadio;
    QRadioButton *giocoRadio;
    QPushButton *confirmTypeButton;

    // Widget per l'inserimento dei campi del nuovo media
    QStackedWidget *detailsStackedWidget;
    MediaWidget *currentWidget;
    
    // Bottone per tornare alla pagina di selezione
    QPushButton *backToSelectionButton;
    
    // Metodi di configurazione UI
    void setupUI();
    void setupSelectionPage();
    void showSelectionPage();
};

#endif // ADDPAGE_H