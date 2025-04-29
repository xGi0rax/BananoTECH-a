#ifndef DETAILSPAGE_H
#define DETAILSPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPixmap>
#include <QScrollArea>
#include <QSplitter>
#include <QMessageBox>
#include "../../Modello logico/Headers/Media.h"
#include "../../Modello logico/Headers/Libro.h"
#include "../../Modello logico/Headers/Film.h"
#include "../../Modello logico/Headers/Vinile.h"
#include "../../Modello logico/Headers/GiocoDaTavolo.h"
#include "../../Modello logico/Headers/Rivista.h"

class DetailsPage : public QWidget {
    Q_OBJECT

public:
    explicit DetailsPage(QWidget *parent = nullptr);
    void setMedia(Media* media); // Imposta il media da visualizzare

signals:
    void goBackToMainPage(); // Segnale per tornare alla pagina principale
    void mediaBorrowed(Media* media); // Segnale per notificare che un media è stato dato in prestito
    void mediaReturned(Media* media); // Segnale per notificare che un media è stato restituito

private slots:
    void onBackButtonClicked(); // Slot per il pulsante indietro
    void onBorrowButtonClicked(); // Slot per il pulsante di prestito
    void onReturnButtonClicked(); // Slot per il pulsante di restituzione
    void onRequestButtonClicked(); // Slot per il pulsante di richiesta a biblioteca affiliata

private:
    // UI Elements
    QPushButton* backButton;
    QLabel* imageLabel;
    QLabel* mediaTitleLabel;
    QLabel* mediaTypeLabel;
    QPixmap originalPixmap;
    
    // Pulsanti per le azioni
    QPushButton* borrowButton;
    QPushButton* returnButton;
    QPushButton* requestButton;
    
    // Label per informazioni disponibilità
    QLabel* availableCopiesLabel;
    
    // Campi di dettaglio comuni
    QLabel* authorLabel;
    QLabel* genreLabel;
    QLabel* yearLabel;
    QLabel* languageLabel;
    QLabel* ratingLabel;
    
    // Campi specifici per i diversi tipi di media
    QWidget* specificDetailsContainer;
    QVBoxLayout* specificDetailsLayout;
    
    // Riferimento al media corrente
    Media* currentMedia;
    
    void setupUI(); // Configura l'interfaccia utente
    void updateUI(); // Aggiorna l'interfaccia con i dati del media corrente
    void updateAvailability(); // Aggiorna l'indicatore di disponibilità
    void displaySpecificDetails(); // Mostra i dettagli specifici in base al tipo di media
    void updateImageSize(); // Aggiorna la dimensione dell'immagine

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // DETAILSPAGE_H