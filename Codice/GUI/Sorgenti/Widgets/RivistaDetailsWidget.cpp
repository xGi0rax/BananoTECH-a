#include "../../Headers/Widgets/RivistaDetailsWidget.h"
#include "../../../Modello logico/Headers/Rivista.h"
#include <QLabel>

RivistaDetailsWidget::RivistaDetailsWidget(QWidget *parent) : MediaDetailsWidget(parent) {
    setupBaseUI("Dettagli Rivista");
    
    // Imposta generi specifici per rivista
    genreComboBox->addItems({"Attualità", "Arte", "Cucina", "Culturale", "Economia", "Intrattenimento", "Moda", "Salute", "Scientifica", "Sport", "Tecnologia", "Viaggi", "Altro"});
}

void RivistaDetailsWidget::addSpecificFields() {
    // Campi specifici per rivista
    editorRivistaEdit = new QLineEdit(scrollWidget);
    editorRivistaEdit->setStyleSheet(getInputStyle());

    pagesRivistaEdit = new QSpinBox(scrollWidget);
    pagesRivistaEdit->setRange(1, 9999);
    pagesRivistaEdit->setStyleSheet(getInputStyle());

    publicationDateEdit = new QDateEdit(scrollWidget);
    publicationDateEdit->setDisplayFormat("dd/MM/yyyy");
    publicationDateEdit->setStyleSheet(getInputStyle());
    publicationDateEdit->setDate(QDate::currentDate());
    
    periodicityComboBox = new QComboBox(scrollWidget);
    periodicityComboBox->addItems({"Settimanale", "Mensile", "Trimestrale", "Semestrale", "Annuale"});
    periodicityComboBox->setStyleSheet(getInputStyle());
    
    // Etichette
    QLabel *editorLbl = new QLabel("Editore:");
    editorLbl->setStyleSheet(getLabelStyle());
    QLabel *pagesLbl = new QLabel("Pagine:");
    pagesLbl->setStyleSheet(getLabelStyle());
    QLabel *publicationDateLbl = new QLabel("Pubblicazione:");
    publicationDateLbl->setStyleSheet(getLabelStyle());
    QLabel *periodicityLbl = new QLabel("Periodicità:");
    periodicityLbl->setStyleSheet(getLabelStyle());

    // Aggiungi i campi al form
    formLayout->addRow(editorLbl, editorRivistaEdit);
    formLayout->addRow(pagesLbl, pagesRivistaEdit);
    formLayout->addRow(publicationDateLbl, publicationDateEdit);
    formLayout->addRow(periodicityLbl, periodicityComboBox);
}

bool RivistaDetailsWidget::validateData() {
    return !titleEdit->text().isEmpty() && 
           !authorEdit->text().isEmpty() && 
           !genreComboBox->currentText().isEmpty() &&
           yearEdit->value() > 0 && 
           !languageEdit->text().isEmpty() && 
           !editorRivistaEdit->text().isEmpty() && 
           pagesRivistaEdit->value() > 0;
}

Media* RivistaDetailsWidget::createMedia() {
    if (!validateData()) {
        return nullptr;
    }
    
    // Converte QDate in std::string nel formato richiesto
    QString dateStr = publicationDateEdit->date().toString("dd/MM/yyyy");
    
    // Crea e restituisci un nuovo oggetto Rivista
    return new Rivista(
        titleEdit->text().toStdString(),
        authorEdit->text().toStdString(),
        genreComboBox->currentText().toStdString(),
        yearEdit->value(),
        languageEdit->text().toStdString(),
        "",  // immagine verrà impostata da AddPage
        true, // disponibilità predefinita
        1,    // copie predefinite
        editorRivistaEdit->text().toStdString(),
        pagesRivistaEdit->value(),
        dateStr.toStdString(),
        periodicityComboBox->currentText().toStdString(),
        0,    // in prestito predefinito
        "",   // collocazione predefinita
        static_cast<float>(ratingEdit->value())
    );
}

void RivistaDetailsWidget::setMedia(Rivista* rivista) {
    if (!rivista) return;
    
    // Impostiamo i valori nei campi esistenti
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
    editorRivistaEdit->setText(QString::fromStdString(rivista->getEditore()));
    pagesRivistaEdit->setValue(rivista->getNPagine());
    
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

void RivistaDetailsWidget::setReadOnly(bool readOnly) {
    // Imposta tutti i campi in modalità sola lettura
    titleEdit->setReadOnly(readOnly);
    authorEdit->setReadOnly(readOnly);
    genreComboBox->setEnabled(!readOnly);
    yearEdit->setReadOnly(readOnly);
    languageEdit->setReadOnly(readOnly);
    editorRivistaEdit->setReadOnly(readOnly);
    pagesRivistaEdit->setReadOnly(readOnly);
    publicationDateEdit->setReadOnly(readOnly);
    periodicityComboBox->setEnabled(!readOnly);
    
    // Nascondi pulsanti se in modalità lettura
    if (readOnly) {
        if (saveButton) saveButton->hide();
        if (cancelButton) cancelButton->hide();
    } else {
        if (saveButton) saveButton->show();
        if (cancelButton) cancelButton->show();
    }
}