#include "../../Headers/Widgets/RivistaDetailsWidget.h"
#include "../../../Modello logico/Headers/Rivista.h"
#include <QLabel>

RivistaDetailsWidget::RivistaDetailsWidget(QWidget *parent) : MediaDetailsWidget(parent) {
    setupBaseUI("Dettagli Rivista");
    
    // Imposta generi specifici per rivista
    genreComboBox->addItems({"Attualità", "Arte", "Cucina", "Culturale", "Economia", 
                          "Intrattenimento", "Moda", "Salute", "Scientifica", "Sport", "Tecnologia", "Viaggi", "Altro"});
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