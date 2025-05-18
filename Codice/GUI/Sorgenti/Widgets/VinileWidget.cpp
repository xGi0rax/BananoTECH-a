#include "../../Headers/Widgets/VinileWidget.h"
#include "../../../Modello logico/Headers/Vinile.h"
#include <QLabel>

using std::string;

VinileWidget::VinileWidget(QWidget *parent) : MediaWidget(parent){
    setupBaseUI("Scheda Libro");
}

void VinileWidget::addSpecificFields() {
    // Imposta generi specifici per i film
    genreComboBox->addItems({"Alternative", "Blues", "Classica", "Country", "Disco", "Elettronica", "Folk", "Funk", "Hip Hop", "Jazz", "Metal", "Pop", "Punk", "Reggae", "Rock", "Soul", "Altro"});

    // Campi specifici per vinile
    trackCountEdit = new QSpinBox(scrollWidget);
    trackCountEdit->setRange(1, 99);
    trackCountEdit->setStyleSheet(getInputStyle());
    
    durationEdit = new QSpinBox(scrollWidget);
    durationEdit->setRange(1, 999);
    durationEdit->setSuffix(" min");
    durationEdit->setStyleSheet(getInputStyle());

    // Etichette
    QLabel *trackCountLbl = new QLabel("Numero tracce:");
    trackCountLbl->setStyleSheet(getLabelStyle());
    QLabel *durationLbl = new QLabel("Durata totale:");
    durationLbl->setStyleSheet(getLabelStyle());

    if (currentMedia){
        setCurrentValues();
    }

    // Aggiungi i campi al form
    formLayout->addRow(trackCountLbl, trackCountEdit);
    formLayout->addRow(durationLbl, durationEdit);
}

void VinileWidget::setCurrentValues() {
    // Imposto i campi comuni a tutti i media
    MediaWidget::setCurrentValues();
    
    // Imposto i valori specifici per il film
    if (currentVinile) {
        trackCountEdit->setValue(currentVinile->getNTracce());
        durationEdit->setValue(currentVinile->getDurata());
    }
}

bool VinileWidget::validateData() {
    return MediaWidget::validateData() && 
            trackCountEdit->value() > 0 && 
            durationEdit->value() > 0;
}

bool VinileWidget::applyChanges() {
    // Controllo di validità
    if (!validateData()) return false;

    // Aggiorno i campi comuni
    MediaWidget::applyChanges();

    // Aggiorna i campi specifici del Vinile
    currentVinile->setNTracce(trackCountEdit->value());
    currentVinile->setDurata(durationEdit->value());

    return true;
}

Media* VinileWidget::createMedia() {
    // Controllo validità
    if(!validateData()) return nullptr;

    // Creo e restituisco un nuovo oggetto Libro
    return new Vinile(
        titleEdit->text().toStdString(),
        authorEdit->text().toStdString(),
        genreComboBox->currentText().toStdString(),
        yearEdit->value(),
        languageEdit->text().toStdString(),
        "",  // immagine verrà impostata da AddPage
        true, // disponibilità predefinita
        1,    // copie predefinite
        trackCountEdit->value(),
        durationEdit->value(),
        0,    // in prestito predefinito
        "",   // collocazione predefinita
        static_cast<float>(ratingEdit->value())
    );
}

void VinileWidget::setReadOnly(bool readOnly) {
    MediaWidget::setReadOnly(readOnly);
    trackCountEdit->setReadOnly(readOnly);
    durationEdit->setReadOnly(readOnly);
}