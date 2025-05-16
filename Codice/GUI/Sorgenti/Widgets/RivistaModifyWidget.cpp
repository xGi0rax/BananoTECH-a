#include "../../Headers/Widgets/RivistaModifyWidget.h"
#include "../../../Modello logico/Headers/Rivista.h"
#include <QDate>

RivistaModifyWidget::RivistaModifyWidget(QWidget* parent) : MediaModifyWidget(parent) {
    setupBaseUI("Modifica Rivista");
}

void RivistaModifyWidget::addSpecificFields() {
    // Imposta generi specifici per rivista
    genreComboBox->addItems({"Attualità", "Arte", "Cucina", "Cultura", "Economia", "Informatica", "Moda", "Natura", "Scienza", "Sport", "Tecnologia", "Viaggi"});
    
    // Se abbiamo già un media, impostiamo il genere
    if (currentMedia) {
        genreComboBox->setCurrentText(QString::fromStdString(currentMedia->getGenere()));
    }

    // Campi specifici per rivista
    editorEdit = new QLineEdit(scrollWidget);
    editorEdit->setStyleSheet(getInputStyle());

    pagesEdit = new QSpinBox(scrollWidget);
    pagesEdit->setRange(1, 999);
    pagesEdit->setStyleSheet(getInputStyle());
    
    publicationDateEdit = new QDateEdit(scrollWidget);
    publicationDateEdit->setDisplayFormat("dd/MM/yyyy");
    publicationDateEdit->setCalendarPopup(true);
    publicationDateEdit->setStyleSheet(getInputStyle());
    
    periodicityComboBox = new QComboBox(scrollWidget);
    periodicityComboBox->addItems({"Settimanale", "Bisettimanale", "Mensile", "Bimestrale", "Trimestrale", "Semestrale", "Annuale"});
    periodicityComboBox->setStyleSheet(getInputStyle());
    
    // Se abbiamo già un media, impostiamo i valori specifici
    Rivista* rivista = dynamic_cast<Rivista*>(currentMedia);
    if (rivista) {
        editorEdit->setText(QString::fromStdString(rivista->getEditore()));
        pagesEdit->setValue(rivista->getNPagine());
        
        // Gestione della data di pubblicazione
        QString dateStr = QString::fromStdString(rivista->getDataPubb());
        QDate date = QDate::fromString(dateStr, "dd/MM/yyyy");
        if (date.isValid()) {
            publicationDateEdit->setDate(date);
        } else {
            publicationDateEdit->setDate(QDate::currentDate());
        }
        
        // Imposta periodicità
        QString periodicita = QString::fromStdString(rivista->getPeriodicita());
        int periodicityIndex = periodicityComboBox->findText(periodicita);
        if (periodicityIndex >= 0) {
            periodicityComboBox->setCurrentIndex(periodicityIndex);
        } else {
            periodicityComboBox->setCurrentText(periodicita);
        }
    } else {
        publicationDateEdit->setDate(QDate::currentDate());
    }
    
    // Etichette
    QLabel *editorLbl = new QLabel("Editore:");
    editorLbl->setStyleSheet(getLabelStyle());
    QLabel *pagesLbl = new QLabel("Pagine:");
    pagesLbl->setStyleSheet(getLabelStyle());
    QLabel *dateLbl = new QLabel("Data pubblicazione:");
    dateLbl->setStyleSheet(getLabelStyle());
    QLabel *periodicityLbl = new QLabel("Periodicità:");
    periodicityLbl->setStyleSheet(getLabelStyle());

    // Aggiungi i campi al form
    formLayout->addRow(editorLbl, editorEdit);
    formLayout->addRow(pagesLbl, pagesEdit);
    formLayout->addRow(dateLbl, publicationDateEdit);
    formLayout->addRow(periodicityLbl, periodicityComboBox);
}

bool RivistaModifyWidget::validateData() {
    return !titleEdit->text().isEmpty() && 
           !authorEdit->text().isEmpty() && 
           !genreComboBox->currentText().isEmpty() &&
           yearEdit->value() > 0 && 
           !languageEdit->text().isEmpty() && 
           !editorEdit->text().isEmpty() && 
           pagesEdit->value() > 0;
}

bool RivistaModifyWidget::applyChanges() {
    if (!validateData() || !currentMedia)
        return false;

    // Cast per accedere ai metodi specifici di Rivista
    Rivista* rivista = dynamic_cast<Rivista*>(currentMedia);
    if (!rivista) return false;

    // Aggiorna tutti i campi comuni
    currentMedia->setTitolo(titleEdit->text().toStdString());
    currentMedia->setAutore(authorEdit->text().toStdString());
    currentMedia->setGenere(genreComboBox->currentText().toStdString());
    currentMedia->setAnno(yearEdit->value());
    currentMedia->setLingua(languageEdit->text().toStdString());
    currentMedia->setRating(ratingEdit->value());
    
    // Aggiorna i campi specifici della Rivista
    rivista->setEditore(editorEdit->text().toStdString());
    rivista->setNPagine(pagesEdit->value());
    rivista->setDataPubb(publicationDateEdit->date().toString("dd/MM/yyyy").toStdString());
    rivista->setPeriodicita(periodicityComboBox->currentText().toStdString());
    
    return true;
}

void RivistaModifyWidget::setMedia(Rivista* rivista) {
    if (!rivista) return;
    
    // Salvo il riferimento al media
    currentMedia = rivista;
    
    // Popolamento campi base
    titleEdit->setText(QString::fromStdString(rivista->getTitolo()));
    authorEdit->setText(QString::fromStdString(rivista->getAutore()));
    
    // Trova e seleziona il genere corretto nella combobox
    QString genere = QString::fromStdString(rivista->getGenere());
    int genreIndex = genreComboBox->findText(genere);
    if (genreIndex >= 0) {
        genreComboBox->setCurrentIndex(genreIndex);
    } else {
        genreComboBox->setCurrentText(genere);
    }
    
    yearEdit->setValue(rivista->getAnno());
    languageEdit->setText(QString::fromStdString(rivista->getLingua()));
    ratingEdit->setValue(rivista->getRating());
    
    // Campi specifici per rivista
    editorEdit->setText(QString::fromStdString(rivista->getEditore()));
    pagesEdit->setValue(rivista->getNPagine());
    
    // Gestione della data di pubblicazione
    QString dateStr = QString::fromStdString(rivista->getDataPubb());
    QDate date = QDate::fromString(dateStr, "dd/MM/yyyy");
    if (date.isValid()) {
        publicationDateEdit->setDate(date);
    }
    
    // Imposta periodicità
    QString periodicita = QString::fromStdString(rivista->getPeriodicita());
    int periodicityIndex = periodicityComboBox->findText(periodicita);
    if (periodicityIndex >= 0) {
        periodicityComboBox->setCurrentIndex(periodicityIndex);
    } else {
        periodicityComboBox->setCurrentText(periodicita);
    }
}