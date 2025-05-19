#include "../../Headers/Widgets/GiocoWidget.h"
#include "../../../Modello logico/Headers/GiocoDaTavolo.h"
#include <QLabel>

using std::string;

GiocoWidget::GiocoWidget(QWidget *parent) : MediaWidget(parent), currentGioco(nullptr) {
    setupBaseUI("Scheda Gioco da Tavolo");
}

void GiocoWidget::setCurrentMedia(Media* media) {
    // Controllo di validità
    if (!media) {
        QMessageBox::warning(this, "Errore", "Media non valido");
        return;
    }

    // Salvo il riferimento al media corrente
    currentMedia = media;

    // Salvo il riferimento al film corrente
    currentGioco = dynamic_cast<GiocoDaTavolo*>(media);

    if (!currentGioco) {
        QMessageBox::warning(this, "Errore", "Media non è un gioco da tavolo");
        currentMedia = nullptr;
        return;
    }

    // Imposto i valori nei campi
    setCurrentValues();
}

void GiocoWidget::addSpecificFields() {
    // Imposta generi specifici per i film
    genreComboBox->addItems({"Avventura", "Carte", "Cooperativo", "Deduzione", "Economico", "Fantasy", "Guerra", "Party Game", "Strategia", "Altro"});

    // Campi specifici per film
    maxPlayersEdit = new QSpinBox(scrollWidget);
    maxPlayersEdit->setRange(1, 99);
    maxPlayersEdit->setStyleSheet(getInputStyle());
    
    playTimeEdit = new QSpinBox(scrollWidget);
    playTimeEdit->setRange(1, 999);
    playTimeEdit->setSuffix(" min");
    playTimeEdit->setStyleSheet(getInputStyle());
    
    minAgeEdit = new QSpinBox(scrollWidget);
    minAgeEdit->setRange(1, 99);
    minAgeEdit->setSuffix(" anni");
    minAgeEdit->setStyleSheet(getInputStyle());
    
    editorEdit = new QLineEdit(scrollWidget);
    editorEdit->setStyleSheet(getInputStyle());
    
    // Etichette
    QLabel *maxPlayersLbl = new QLabel("Giocatori max:");
    maxPlayersLbl->setStyleSheet(getLabelStyle());
    QLabel *playTimeLbl = new QLabel("Durata gioco:");
    playTimeLbl->setStyleSheet(getLabelStyle());
    QLabel *minAgeLbl = new QLabel("Età minima:");
    minAgeLbl->setStyleSheet(getLabelStyle());
    QLabel *editorLbl = new QLabel("Editore:");
    editorLbl->setStyleSheet(getLabelStyle());

    // Aggiungi i campi al form
    formLayout->addRow(maxPlayersLbl, maxPlayersEdit);
    formLayout->addRow(playTimeLbl, playTimeEdit);
    formLayout->addRow(minAgeLbl, minAgeEdit);
    formLayout->addRow(editorLbl, editorEdit);
}

void GiocoWidget::setCurrentValues() {
    // Imposto i campi comuni a tutti i media
    MediaWidget::setCurrentValues();
    
    // Imposto i valori specifici per il film
    if (currentGioco) {
        maxPlayersEdit->setValue(currentGioco->getNGiocatori());
        playTimeEdit->setValue(currentGioco->getDurata());
        minAgeEdit->setValue(currentGioco->getEtaMinima());
        editorEdit->setText(QString::fromStdString(currentGioco->getEditore()));
    }
}

bool GiocoWidget::validateData() {
    return MediaWidget::validateData() && 
           maxPlayersEdit->value() > 0 && 
           playTimeEdit->value() > 0 && 
           minAgeEdit->value() > 0 && 
           !editorEdit->text().isEmpty();
}

bool GiocoWidget::applyChanges() {
    // Controllo di validità
    if (!validateData()) return false;

    // Aggiorno i campi comuni
    MediaWidget::applyChanges();

    // Aggiorno i campi specifici del gioco
    currentGioco->setNGiocatori(maxPlayersEdit->value());
    currentGioco->setDurata(playTimeEdit->value());
    currentGioco->setEtaMinima(minAgeEdit->value());
    currentGioco->setEditore(editorEdit->text().toStdString());

    return true;
}

Media* GiocoWidget::createMedia() {
    // Controllo di validità
    if(!validateData()) return nullptr;

    // Creo e restituisco un nuovo oggetto GiocoDaTavolo
    return new GiocoDaTavolo(
        titleEdit->text().toStdString(),
        authorEdit->text().toStdString(),
        genreComboBox->currentText().toStdString(),
        yearEdit->value(),
        languageEdit->text().toStdString(),
        "",  // immagine verrà impostata da AddPage
        true, // disponibilità predefinita
        1,    // copie predefinite
        maxPlayersEdit->value(),
        playTimeEdit->value(),
        minAgeEdit->value(),
        editorEdit->text().toStdString(),
        0,    // in prestito predefinito
        "",   // collocazione predefinita
        static_cast<float>(ratingEdit->value())
    );
}

void GiocoWidget::setReadOnly(bool readOnly) {
    MediaWidget::setReadOnly(readOnly);
    maxPlayersEdit->setReadOnly(readOnly);
    playTimeEdit->setReadOnly(readOnly);
    minAgeEdit->setReadOnly(readOnly);
    editorEdit->setReadOnly(readOnly);
}