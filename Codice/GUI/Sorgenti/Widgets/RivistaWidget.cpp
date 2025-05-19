#include "../../Headers/Widgets/RivistaWidget.h"
#include "../../../Modello logico/Headers/Rivista.h"
#include <QLabel>

using std::string;

RivistaWidget::RivistaWidget(QWidget *parent) : MediaWidget(parent), currentRivista(nullptr) {
    setupBaseUI("Scheda Rivista");
}

void RivistaWidget::setCurrentMedia(Media* media) {
    // Controllo di validità
    if (!media) {
        QMessageBox::warning(this, "Errore", "Media non valido");
        return;
    }

    // Salvo il riferimento al media corrente
    currentMedia = media;

    // Salvo il riferimento al film corrente
    currentRivista = dynamic_cast<Rivista*>(media);

    if (!currentRivista) {
        QMessageBox::warning(this, "Errore", "Media non è una rivista");
        currentMedia = nullptr;
        return;
    }

    // Imposto i valori nei campi
    setCurrentValues();
}

void RivistaWidget::addSpecificFields() {
    // Imposta generi specifici per i film
    genreComboBox->addItems({"Attualità", "Arte", "Cucina", "Cultura", "Economia", "Intrattenimento", "Informatica", "Moda", "Natura", "Salute", "Scienza", "Sport", "Tecnologia", "Viaggi", "Altro"});

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

void RivistaWidget::setCurrentValues() {
    // Imposto i campi comuni a tutti i media
    MediaWidget::setCurrentValues();
    
    // Imposto i valori specifici per il film
    if (currentRivista) {
        editorEdit->setText(QString::fromStdString(currentRivista->getEditore()));
        pagesEdit->setValue(currentRivista->getNPagine());
        publicationDateEdit->setDate(QDate::fromString(QString::fromStdString(currentRivista->getDataPubb()), "dd/MM/yyyy"));
        periodicityComboBox->setCurrentText(QString::fromStdString(currentRivista->getPeriodicita()));
    }
}

bool RivistaWidget::validateData() {
    return MediaWidget::validateData() && 
            !editorEdit->text().isEmpty() && 
            pagesEdit->value() > 0 && 
            !publicationDateEdit->text().isEmpty() && 
            !periodicityComboBox->currentText().isEmpty();
}

bool RivistaWidget::applyChanges() {
    // Controllo di validità
    if (!validateData()) return false;

    // Aggiorno i campi comuni
    MediaWidget::applyChanges();

    // Aggiorno i campi specifici della rivista
    currentRivista->setEditore(editorEdit->text().toStdString());
    currentRivista->setNPagine(pagesEdit->value());
    currentRivista->setDataPubb(publicationDateEdit->date().toString("dd/MM/yyyy").toStdString());
    currentRivista->setPeriodicita(periodicityComboBox->currentText().toStdString());

    return true;
}

Media* RivistaWidget::createMedia() {
    // Controllo validità
    if(!validateData()) return nullptr;

    // Converte QDate in std::string nel formato richiesto
    QString dateStr = publicationDateEdit->date().toString("dd/MM/yyyy");

    // Creo e restituisco un nuovo oggetto Libro
    return new Rivista(
        titleEdit->text().toStdString(),
        authorEdit->text().toStdString(),
        genreComboBox->currentText().toStdString(),
        yearEdit->value(),
        languageEdit->text().toStdString(),
        "",  // immagine verrà impostata da AddPage
        true, // disponibilità predefinita
        1,    // copie predefinite
        editorEdit->text().toStdString(),
        pagesEdit->value(),
        dateStr.toStdString(),
        periodicityComboBox->currentText().toStdString(),
        0,    // in prestito predefinito
        "",   // collocazione predefinita
        static_cast<float>(ratingEdit->value())
    );
}

void RivistaWidget::setReadOnly(bool readOnly) {
    MediaWidget::setReadOnly(readOnly);
    editorEdit->setReadOnly(readOnly);
    pagesEdit->setReadOnly(readOnly);
    publicationDateEdit->setReadOnly(readOnly);
    periodicityComboBox->setDisabled(readOnly);
}