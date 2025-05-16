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
#include <QGroupbox>
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
    void onMediaSelected(QListWidgetItem *item);

public slots:
    void onBackButtonClicked();  // Slot per il tasto indietro
    void onMediaTypeChanged(); // Slot per il cambio del tipo di media nei filtri
    void onApplyFiltersClicked(); // Slot per applicare i filtri
    void onClearFiltersClicked(); // Slot per cancellare i filtri
    void onAddMediaButtonClicked(); // Slot per aggiungere un nuovo media
    void onEditButtonClicked(); // Slot per il pulsante di modifica del media
    void onDeleteButtonClicked(); // Slot per il pulsante di rimozione del media dalla lista
    void onNewMediaCreated(Media* newMedia); // Slot per aggiungere un nuovo media alla lista
    void onExportLibraryButtonClicked(); // Nuovo slot per esportare la biblioteca
    void onMediaEdited(); // Slot per aggiornare un media esistente

signals:
    void goToLoginPage(); // Segnale per notificare il cambio alla LoginPage
    void goToAddPage(); // Segnale per notificare il cambio alla AddPage
    void goToModifyPage(Media* media); // Segnale per notificare il cambio alla ModifyPage
    void goToDetailsPage(Media* media); // Segnale per notificare il cambio alla DetailsPage

private:
    // Barra superiore
    QPushButton *backButton;
    QPushButton *addMediaButton;
    //QPushButton *editModeButton;

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

    // Sezione destra (Immagine di anteprima e dettagli principali media)
    QPixmap originalPixmap;
    QLabel *mediaImageLabel;
    QLabel *mediaInfoLabel;
    QPushButton *borrowButton;
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

    void setupUI(); // metodo per configurare l'interfaccia utente
    
    // void setupFilters(); // metodo per configurare i filtri
    void updateGenreComboBox(); // metodo per aggiornare la combobox dei generi in base al tipo di media selezionato
    void updateMediaList(vector<Media*> listaFiltrata); // metodo per aggiornare la lista dei media in base ai filtri selezionati
    void onDetailsButtonClicked();

protected:
    void resizeEvent(QResizeEvent* event) override;
    void updateImageSize();
};

#endif // MAINPAGE_H