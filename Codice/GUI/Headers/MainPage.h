#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QListWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QPixmap>
#include <QSizePolicy>
#include <QCheckBox>
#include <QListWidgetItem>
#include <QPixmap>
#include <QPainter>
#include "AddPage.h"
#include "../../Modello logico/Headers/Media.h"
#include "../../Modello logico/Headers/Biblioteca.h"

class MainPage : public QWidget {
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr, Biblioteca* biblioteca = nullptr);
    void onMediaSelected(QListWidgetItem *item); // Metodo per gestire la selezione di un media dalla lista
    void setCurrentFile(const QString& filePath); 
    void setLibraryInfo(bool isNew, bool hasChanges);  
    void resetUnsavedChanges();
    void setHasUnsavedChanges(bool hasChanges);
    void updateTextTruncation();

public slots:
    void onBackButtonClicked();  // Slot per pulsante indietro
    void onMediaTypeChanged(); // Slot per il cambio del tipo di media nei filtri
    void onApplyFiltersClicked(); // Slot per applicare i filtri
    void onClearFiltersClicked(); // Slot per cancellare i filtri
    void onAddMediaButtonClicked(); // Slot per il pulsante di aggiunta di un nuovo media
    void onBorrowButtonClicked(); // Slot per il pulsante di prestito del media
    void onReturnButtonClicked(); // Slot per il pulsante di restituzione del media
    void onDetailsButtonClicked(); // Slot per il pulsante di visualizzazione dei dettagli del media
    void onEditButtonClicked(); // Slot per il pulsante di modifica del media
    void onDeleteButtonClicked(); // Slot per il pulsante di rimozione del media dalla lista
    void onNewMediaCreated(Media* newMedia); // Slot per aggiungere un nuovo media alla lista
    void onMediaEdited(); // Slot per aggiornare un media esistente
    void onSearchTextChanged(const QString& searchText); // Slot per gestire il cambiamento del testo nella barra di ricerca
    void onScrollChanged(); 
    
    void onSaveButtonClicked(); // Slot per pulsante "Salva"
    void onSaveAsButtonClicked(); // Slot per pulsante "Salva come"

signals:
    void goToChoicePage(); // Segnale per notificare il cambio alla ChoicePage
    void goToLoginPage(); // Segnale per notificare il cambio alla LoginPage
    void goToAddPage(); // Segnale per notificare il cambio alla AddPage
    void goToModifyPage(Media* media); // Segnale per notificare il cambio alla ModifyPage
    void goToDetailsPage(Media* media); // Segnale per notificare il cambio alla DetailsPage
    void borrowMedia(Media* media); // Segnale per prendere in prestito un media
    void returnMedia(Media* media); // Segnale per restituire un media
    void libraryModified(); // Segnale per notificare modifiche ------------------------- QUESTO SEGNALE NON VIENE USATO
    void unsavedChangesUpdated(bool hasChanges); // Segnale per aggiornare lo stato delle modifiche non salvate

private:
    // Barra superiore
    QPushButton *backButton;
    QPushButton *addMediaButton;
    QPushButton *saveButton;
    QPushButton *saveAsButton;

    // Sezione sinistra (Filtri)
    QComboBox *mediaTypeComboBox;
    QComboBox *genreComboBox;
    QLineEdit *minYearLineEdit;
    QLineEdit *maxYearLineEdit;
    QLineEdit *ratingMinLineEdit;
    QLineEdit *ratingMaxLineEdit;
    QLineEdit *languageLineEdit;
    QPushButton *applyFiltersButton;
    QPushButton *clearFiltersButton;
    QCheckBox *availableCheckBox;

    // Sezione centrale (Barra di ricerca e lista media)
    QLineEdit *searchBar;
    QListWidget *mediaList;
    int currentSelectedRow = -1; // Indice della riga attualmente selezionata nella lista

    // Sezione destra (Immagine di anteprima e dettagli principali media)
    QPixmap originalPixmap;
    QLabel *mediaImageLabel;
    QLabel *mediaInfoLabel;
    QPushButton *borrowButton;
    QPushButton *returnButton;
    QPushButton *detailsButton;
    QLabel *mediaTitleLabel;
    QLabel *mediaAuthorLabel;
    QLabel *mediaYearLabel;
    QLabel *mediaRatingLabel;
    QPushButton *editMediaButton; 

    // Widget per i pulsanti nella lista
    QPushButton* listEditButton;
    QPushButton* listDeleteButton;
    QWidget* buttonsContainer;

    // Metodi per la gestione dei pulsanti nella lista
    void showActionButtons(int row);
    void hideActionButtons();
    void updateButtonsPosition(); // Metodo per aggiornare la posizione dei pulsanti in base alla riga selezionata

    // Layout
    QVBoxLayout *mainLayout;
    QHBoxLayout *topBarLayout;
    QVBoxLayout *filtersLayout;
    QVBoxLayout *centerLayout;
    QVBoxLayout *previewLayout;
    QHBoxLayout *contentLayout;

    QGroupBox *filtersGroupBox;
    QGroupBox *previewGroupBox;

    Biblioteca *biblioteca; // Oggetto Biblioteca per gestire i media
    QString currentFilePath; // Percorso del file attualmente in uso
    bool hasCurrentFile; // Flag per sapere se c'è un file corrente
    bool isNewLibrary; // Flag per sapere se è una biblioteca nuova
    bool hasUnsavedChanges; // Flag per tracciare modifiche

    void setupUI(); // metodo per configurare l'interfaccia utente
    
    // void setupFilters(); // metodo per configurare i filtri
    void updateGenreComboBox(); // metodo per aggiornare la combobox dei generi in base al tipo di media selezionato
    void updateMediaList(vector<Media*> listaFiltrata); // metodo per aggiornare la lista dei media in base ai filtri selezionati
    void saveToFile(const QString& filePath); 
    void updateSaveButtonsState(); // Metodo per aggiornare stato pulsanti

protected:
    void resizeEvent(QResizeEvent* event) override;
    void updateImageSize();
};

#endif // MAINPAGE_H