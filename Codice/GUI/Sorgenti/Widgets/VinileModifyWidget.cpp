#include "../../Headers/Widgets/VinileModifyWidget.h"
#include "../../../Modello logico/Headers/Vinile.h"

VinileModifyWidget::VinileModifyWidget(QWidget* parent) : MediaModifyWidget(parent) {
    setupBaseUI("Modifica Vinile");
}

void VinileModifyWidget::addSpecificFields() {
    // Imposta generi specifici per vinile
    genreComboBox->addItems({"Blues", "Classical", "Country", "Disco", "Electronic", "Folk", "Funk", "Hip Hop", "Jazz", "Metal", "Pop", "Punk", "Reggae", "Rock", "Soul"});
    
    // Se abbiamo già un media, impostiamo il genere
    if (currentMedia) {
        genreComboBox->setCurrentText(QString::fromStdString(currentMedia->getGenere()));
    }

    // Campi specifici per vinile
    trackCountEdit = new QSpinBox(scrollWidget);
    trackCountEdit->setRange(1, 99);
    trackCountEdit->setStyleSheet(getInputStyle());
    
    durationEdit = new QSpinBox(scrollWidget);
    durationEdit->setRange(1, 999);
    durationEdit->setSuffix(" min");
    durationEdit->setStyleSheet(getInputStyle());
    
    // Se abbiamo già un media, impostiamo i valori specifici
    Vinile* vinile = dynamic_cast<Vinile*>(currentMedia);
    if (vinile) {
        trackCountEdit->setValue(vinile->getNTracce());
        durationEdit->setValue(vinile->getDurata());
    }
    
    // Etichette
    QLabel *trackCountLbl = new QLabel("Numero tracce:");
    trackCountLbl->setStyleSheet(getLabelStyle());
    QLabel *durationLbl = new QLabel("Durata totale:");
    durationLbl->setStyleSheet(getLabelStyle());

    // Aggiungi i campi al form
    formLayout->addRow(trackCountLbl, trackCountEdit);
    formLayout->addRow(durationLbl, durationEdit);
}

bool VinileModifyWidget::validateData() {
    return !titleEdit->text().isEmpty() && 
           !authorEdit->text().isEmpty() && 
           !genreComboBox->currentText().isEmpty() &&
           yearEdit->value() > 0 && 
           !languageEdit->text().isEmpty() && 
           trackCountEdit->value() > 0 && 
           durationEdit->value() > 0;
}

bool VinileModifyWidget::applyChanges() {
    if (!validateData() || !currentMedia)
        return false;

    // Cast per accedere ai metodi specifici di Vinile
    Vinile* vinile = dynamic_cast<Vinile*>(currentMedia);
    if (!vinile) return false;

    // Aggiorna tutti i campi comuni
    currentMedia->setTitolo(titleEdit->text().toStdString());
    currentMedia->setAutore(authorEdit->text().toStdString());
    currentMedia->setGenere(genreComboBox->currentText().toStdString());
    currentMedia->setAnno(yearEdit->value());
    currentMedia->setLingua(languageEdit->text().toStdString());
    currentMedia->setRating(ratingEdit->value());
    
    // Aggiorna i campi specifici del Vinile
    vinile->setNTracce(trackCountEdit->value());
    vinile->setDurata(durationEdit->value());
    
    return true;
}

void VinileModifyWidget::setMedia(Vinile* vinile) {
    if (!vinile) return;
    
    // Salvo il riferimento al media
    currentMedia = vinile;
    
    // Popolamento campi base
    titleEdit->setText(QString::fromStdString(vinile->getTitolo()));
    authorEdit->setText(QString::fromStdString(vinile->getAutore()));
    
    // Trova e seleziona il genere corretto nella combobox
    QString genere = QString::fromStdString(vinile->getGenere());
    int genreIndex = genreComboBox->findText(genere);
    if (genreIndex >= 0) {
        genreComboBox->setCurrentIndex(genreIndex);
    } else {
        genreComboBox->setCurrentText(genere);
    }
    
    yearEdit->setValue(vinile->getAnno());
    languageEdit->setText(QString::fromStdString(vinile->getLingua()));
    ratingEdit->setValue(vinile->getRating());
    
    // Campi specifici per vinile
    trackCountEdit->setValue(vinile->getNTracce());
    durationEdit->setValue(vinile->getDurata());
}