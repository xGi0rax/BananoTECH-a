#include "../../Headers/Widgets/GiocoModifyWidget.h"

GiocoModifyWidget::GiocoModifyWidget(QWidget* parent) : MediaModifyWidget(parent) {
    setupBaseUI("Modifica Gioco da Tavolo");
}

void GiocoModifyWidget::addSpecificFields() {
    // Imposta generi specifici per gioco da tavolo
    genreComboBox->addItems({"Avventura", "Carte", "Cooperativo", "Deduzione", "Economico", "Fantasy", "Guerra", "Party Game", "Strategia", "Altro"});
    
    // Se abbiamo già un media, impostiamo il genere
    if (currentMedia) {
        genreComboBox->setCurrentText(QString::fromStdString(currentMedia->getGenere()));
    }

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
    
    editorEdit = new QLineEdit(scrollWidget);
    editorEdit->setStyleSheet(getInputStyle());
    
    // Se abbiamo già un media, impostiamo i valori specifici
    GiocoDaTavolo* gioco = dynamic_cast<GiocoDaTavolo*>(currentMedia);
    if (gioco) {
        maxPlayersEdit->setValue(gioco->getNGiocatori());
        playTimeEdit->setValue(gioco->getDurata());
        minAgeEdit->setValue(gioco->getEtaMinima());
        editorEdit->setText(QString::fromStdString(gioco->getEditore()));
    }
    
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

bool GiocoModifyWidget::validateData() {
    return !titleEdit->text().isEmpty() && 
           !authorEdit->text().isEmpty() && 
           !genreComboBox->currentText().isEmpty() &&
           yearEdit->value() > 0 && 
           !languageEdit->text().isEmpty() && 
           maxPlayersEdit->value() > 0 && 
           playTimeEdit->value() > 0 && 
           minAgeEdit->value() > 0 && 
           !editorEdit->text().isEmpty();
}

bool GiocoModifyWidget::applyChanges() {
    if (!validateData() || !currentMedia)
        return false;

    // Cast per accedere ai metodi specifici di GiocoDaTavolo
    GiocoDaTavolo* gioco = dynamic_cast<GiocoDaTavolo*>(currentMedia);
    if (!gioco) return false;

    // Aggiorna tutti i campi comuni
    currentMedia->setTitolo(titleEdit->text().toStdString());
    currentMedia->setAutore(authorEdit->text().toStdString());
    currentMedia->setGenere(genreComboBox->currentText().toStdString());
    currentMedia->setAnno(yearEdit->value());
    currentMedia->setLingua(languageEdit->text().toStdString());
    currentMedia->setRating(ratingEdit->value());
    
    // Aggiorna i campi specifici del GiocoDaTavolo
    gioco->setNGiocatori(maxPlayersEdit->value());
    gioco->setDurata(playTimeEdit->value());
    gioco->setEtaMinima(minAgeEdit->value());
    gioco->setEditore(editorEdit->text().toStdString());
    
    return true;
}

void GiocoModifyWidget::setMedia(GiocoDaTavolo* gioco) {
    if (!gioco) return;
    
    // Salvo il riferimento al media
    currentMedia = gioco;
    
    // Popolamento campi base
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
    ratingEdit->setValue(gioco->getRating());
    
    // Campi specifici per gioco da tavolo
    maxPlayersEdit->setValue(gioco->getNGiocatori());
    playTimeEdit->setValue(gioco->getDurata());
    minAgeEdit->setValue(gioco->getEtaMinima());
    editorEdit->setText(QString::fromStdString(gioco->getEditore()));
}