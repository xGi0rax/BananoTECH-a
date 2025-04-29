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
#include "../../Modello logico/Headers/Biblioteca.h"

class MainPage : public QWidget {
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    void onMediaSelected(QListWidgetItem *item);

private slots:
    void onBackButtonClicked();  // Slot per il tasto indietro
    void onMediaTypeChanged(); // Slot per il cambio del tipo di media nei filtri
    void onApplyFiltersClicked(); // Slot per applicare i filtri
    void onClearFiltersClicked(); // Slot per cancellare i filtri
    void onAddMediaButtonClicked(); // Slot per aggiungere un nuovo media
    void onEditButtonClicked(); // Slot per il pulsante di modifica del media
    void onDeleteButtonClicked(); // Slot per il pulsante di rimozione del media dalla lista

signals:
    void goToLoginPage(); // Segnale per notificare il cambio alla LoginPage
    void goToAddPage(); // Segnale per notificare il cambio alla AddPage

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
    QLineEdit *ratingLineEdit;
    QLineEdit *languageLineEdit;
    QPushButton *applyFiltersButton;
    QPushButton *clearFiltersButton;

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

    void setupBiblioteca(); // metodo per inizializzare la biblioteca
    void setupUI(); // metodo per configurare l'interfaccia utente
    // void setupFilters(); // metodo per configurare i filtri
    void updateGenreComboBox(); // metodo per aggiornare la combobox dei generi in base al tipo di media selezionato
    // void updateMediaList(); // metodo per aggiornare la lista dei media in base ai filtri selezionati

protected:
    void resizeEvent(QResizeEvent* event) override;
    void updateImageSize();
};

#endif // MAINPAGE_H