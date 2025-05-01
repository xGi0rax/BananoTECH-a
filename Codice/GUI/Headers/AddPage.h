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
#include "Widgets/MediaDetailsWidget.h"
#include "Widgets/FilmDetailsWidget.h"
#include "Widgets/LibroDetailsWidget.h"
#include "Widgets/VinileDetailsWidget.h"
#include "Widgets/RivistaDetailsWidget.h"
#include "Widgets/GiocoDetailsWidget.h"


class AddPage : public QWidget {
    Q_OBJECT

public:
    explicit AddPage(QWidget *parent = nullptr);

signals:
    void goBackToMainPage(); // Segnale per tornare alla pagina principale
    void mediaCreated(Media *media); // Segnale per passare il nuovo media creato

private slots:
    void onBackButtonClicked();
    void onConfirmTypeButtonClicked();
    void onSaveMediaButtonClicked();
    void onUploadButtonClicked();

private:
    // Enum per identificare il tipo di media
    enum MediaType {
        FILM = 0,
        LIBRO,
        VINILE,
        RIVISTA,
        GIOCO_DA_TAVOLO
    };

    QStackedWidget *mainContentStack;

    // Barra laterale contente pulsante indietro, immagine e pulsante aggiungi
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

    MediaDetailsWidget *currentDetailsWidget;
    
    QPushButton *cancelButton;
    
    // Metodi privati di configurazione UI
    void setupUI();
    void setupSelectionPage();
    void setupDetailsPages();
    void showSelectionPage();
};

#endif // ADDPAGE_H