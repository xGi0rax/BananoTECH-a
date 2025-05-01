#include "../../Headers/Widgets/VinileDetailsWidget.h"
#include "../../../Modello logico/Headers/Vinile.h"
#include <QLabel>

VinileDetailsWidget::VinileDetailsWidget(QWidget *parent) : MediaDetailsWidget(parent) {
    setupBaseUI("Dettagli Vinile");
    
    // Imposta generi specifici per vinile
    genreComboBox->addItems({"Alternative", "Blues", "Classica", "Country", "Elettronica", 
                          "Folk", "Hip Hop", "Jazz", "Metal", "Pop", "Rock", "Altro"});
}

void VinileDetailsWidget::addSpecificFields() {
    // Campi specifici per vinile
    trackCountEdit = new QSpinBox(scrollWidget);
    trackCountEdit->setRange(1, 99);
    trackCountEdit->setStyleSheet(getInputStyle());

    durationVinileEdit = new QSpinBox(scrollWidget);
    durationVinileEdit->setRange(1, 999);
    durationVinileEdit->setSuffix(" min");
    durationVinileEdit->setStyleSheet(getInputStyle());
    
    // Etichette
    QLabel *trackCountLbl = new QLabel("Numero Tracce:");
    trackCountLbl->setStyleSheet(getLabelStyle());
    QLabel *durationLbl = new QLabel("Durata:");
    durationLbl->setStyleSheet(getLabelStyle());

    // Aggiungi i campi al form
    formLayout->addRow(trackCountLbl, trackCountEdit);
    formLayout->addRow(durationLbl, durationVinileEdit);
}

bool VinileDetailsWidget::validateData() {
    return !titleEdit->text().isEmpty() && 
           !authorEdit->text().isEmpty() && 
           !genreComboBox->currentText().isEmpty() &&
           yearEdit->value() > 0 && 
           !languageEdit->text().isEmpty() && 
           trackCountEdit->value() > 0 && 
           durationVinileEdit->value() > 0;
}

Media* VinileDetailsWidget::createMedia() {
    if (!validateData()) {
        return nullptr;
    }
    
    // Crea e restituisci un nuovo oggetto Vinile
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
        durationVinileEdit->value(),
        0,    // in prestito predefinito
        "",   // collocazione predefinita
        static_cast<float>(ratingEdit->value())
    );
}