#include "../../Headers/Widgets/GiocoDetailsWidget.h"
#include "../../../Modello logico/Headers/GiocoDaTavolo.h"
#include <QLabel>

GiocoDetailsWidget::GiocoDetailsWidget(QWidget *parent) : MediaDetailsWidget(parent) {
    setupBaseUI("Dettagli Gioco da Tavolo");
    
    // Imposta generi specifici per giochi
    genreComboBox->addItems({"Avventura", "Carte", "Cooperativo", "Deduzione", "Economico", "Fantasy", "Guerra", "Party Game", "Strategia", "Altro"});
}

void GiocoDetailsWidget::addSpecificFields() {
    // Campi specifici per gioco
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
    
    editorGiocoEdit = new QLineEdit(scrollWidget);
    editorGiocoEdit->setStyleSheet(getInputStyle());
    
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
    formLayout->addRow(editorLbl, editorGiocoEdit);
}

bool GiocoDetailsWidget::validateData() {
    return !titleEdit->text().isEmpty() && 
           !authorEdit->text().isEmpty() && 
           !genreComboBox->currentText().isEmpty() &&
           yearEdit->value() > 0 && 
           !languageEdit->text().isEmpty() && 
           maxPlayersEdit->value() > 0 && 
           playTimeEdit->value() > 0 && 
           minAgeEdit->value() > 0 && 
           !editorGiocoEdit->text().isEmpty();
}

Media* GiocoDetailsWidget::createMedia() {
    if (!validateData()) {
        return nullptr;
    }
    
    // Crea e restituisci un nuovo oggetto Gioco
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
        editorGiocoEdit->text().toStdString(),
        0,    // in prestito predefinito
        "",   // collocazione predefinita
        static_cast<float>(ratingEdit->value())
    );
}

void GiocoDetailsWidget::setMedia(GiocoDaTavolo* gioco) {
    if (!gioco) return;
    
    // Impostiamo i valori nei campi esistenti
    titleEdit->setText(QString::fromStdString(gioco->getTitolo()));
    authorEdit->setText(QString::fromStdString(gioco->getAutore()));
    
    // Trova e seleziona il genere corretto nella combobox
    QString genere = QString::fromStdString(gioco->getGenere());
    int genreIndex = genreComboBox->findText(genere);
    if (genreIndex >= 0) {
        genreComboBox->setCurrentIndex(genreIndex);
    } else {
        genreComboBox->setCurrentText(genere);
    }
    
    yearEdit->setValue(gioco->getAnno());
    languageEdit->setText(QString::fromStdString(gioco->getLingua()));
    maxPlayersEdit->setValue(gioco->getNGiocatori());
    minAgeEdit->setValue(gioco->getEtaMinima());
    editorGiocoEdit->setText(QString::fromStdString(gioco->getEditore()));
}

void GiocoDetailsWidget::setReadOnly(bool readOnly) {
    // Imposta tutti i campi in modalità sola lettura
    titleEdit->setReadOnly(readOnly);
    authorEdit->setReadOnly(readOnly);
    genreComboBox->setEnabled(!readOnly);
    yearEdit->setReadOnly(readOnly);
    languageEdit->setReadOnly(readOnly);
    maxPlayersEdit->setReadOnly(readOnly);
    playTimeEdit->setReadOnly(readOnly);
    minAgeEdit->setReadOnly(readOnly);
    editorGiocoEdit->setReadOnly(readOnly);
    
    // Nascondi pulsanti se in modalità lettura
    if (readOnly) {
        if (saveButton) saveButton->hide();
        if (cancelButton) cancelButton->hide();
    } else {
        if (saveButton) saveButton->show();
        if (cancelButton) cancelButton->show();
    }
}