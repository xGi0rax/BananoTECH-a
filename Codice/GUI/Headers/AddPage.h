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

class AddPage : public QWidget {
    Q_OBJECT

public:
    explicit AddPage(QWidget *parent = nullptr);

signals:
    void goBackToMainPage(); // Segnale per tornare alla pagina principale

private slots:
    void onBackButtonClicked();
    void onConfirmTypeButtonClicked();
    void onSaveMediaButtonClicked();
    void onCancelButtonClicked();
    void onMediaTypeChanged(int index);
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
    
    // DA CONTROLLARE DA QUA IN GIU'

    // Campi comuni a tutti i media
    QLineEdit *titleEdit;
    QLineEdit *authorEdit;
    QSpinBox *yearEdit;
    QComboBox *genreComboBox;
    QLineEdit *descriptionEdit;
    QSpinBox *ratingEdit;
    
    // Campi specifici per i vari tipi di media
    // Per Film
    QLineEdit *directorEdit;
    QSpinBox *durationEdit;
    
    // Per Libro
    QLineEdit *publisherEdit;
    QSpinBox *pagesEdit;
    QLineEdit *isbnEdit;
    
    // Per Vinile
    QSpinBox *trackCountEdit;
    QComboBox *recordTypeComboBox; // 33, 45, 78 rpm
    
    // Per Rivista
    QLineEdit *publisherRivistaEdit;
    QSpinBox *issueNumberEdit;
    QComboBox *periodicityComboBox; // settimanale, mensile, ecc.
    
    // Per Gioco Da Tavolo
    QSpinBox *minPlayersEdit;
    QSpinBox *maxPlayersEdit;
    QSpinBox *minAgeEdit;
    QSpinBox *playTimeEdit;
    
    QPushButton *saveMediaButton;
    QPushButton *cancelButton;
    
    // Metodi privati di configurazione UI
    void setupUI();
    void setupSelectionPage();
    void setupDetailsPages();
    void setupFilmDetailsPage(QWidget *container);
    void setupLibroDetailsPage(QWidget *container);
    void setupVinileDetailsPage(QWidget *container);
    void setupRivistaDetailsPage(QWidget *container);
    void setupGiocoDetailsPage(QWidget *container);
    
    void showSelectionPage();
    void showDetailsPage(MediaType type);
};

#endif // ADDPAGE_H