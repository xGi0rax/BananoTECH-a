#include "../../Headers/Widgets/LibroDetailsWidget.h"
#include "../../../Modello logico/Headers/Libro.h"
#include <QLabel>

LibroDetailsWidget::LibroDetailsWidget(QWidget *parent) : MediaDetailsWidget(parent) {
    setupBaseUI("Dettagli Libro");
    
    // Imposta generi specifici per libro
    genreComboBox->addItems({"Avventura", "Biografia", "Fantasy", "Giallo", "Horror", 
                          "Romanzo", "Storico", "Saggio", "Thriller", "Altro"});
}

void LibroDetailsWidget::addSpecificFields() {
    // Campi specifici per libro
    isbnEdit = new QLineEdit(scrollWidget);
    isbnEdit->setStyleSheet(getInputStyle());

    editorLibroEdit = new QLineEdit(scrollWidget);
    editorLibroEdit->setStyleSheet(getInputStyle());

    pagesLibroEdit = new QSpinBox(scrollWidget);
    pagesLibroEdit->setRange(1, 9999);
    pagesLibroEdit->setStyleSheet(getInputStyle());
    
    // Etichette
    QLabel *isbnLbl = new QLabel("ISBN:");
    isbnLbl->setStyleSheet(getLabelStyle());
    QLabel *editorLbl = new QLabel("Editore:");
    editorLbl->setStyleSheet(getLabelStyle());
    QLabel *pagesLbl = new QLabel("Pagine:");
    pagesLbl->setStyleSheet(getLabelStyle());

    // Aggiungi i campi al form
    formLayout->addRow(isbnLbl, isbnEdit);
    formLayout->addRow(editorLbl, editorLibroEdit);
    formLayout->addRow(pagesLbl, pagesLibroEdit);
}

bool LibroDetailsWidget::validateData() {
    return !titleEdit->text().isEmpty() && 
           !authorEdit->text().isEmpty() && 
           !genreComboBox->currentText().isEmpty() &&
           yearEdit->value() > 0 && 
           !languageEdit->text().isEmpty() && 
           !isbnEdit->text().isEmpty() && 
           !editorLibroEdit->text().isEmpty() && 
           pagesLibroEdit->value() > 0;
}

Media* LibroDetailsWidget::createMedia() {
    if (!validateData()) {
        return nullptr;
    }
    
    // Crea e restituisci un nuovo oggetto Libro
    return new Libro(
        titleEdit->text().toStdString(),
        authorEdit->text().toStdString(),
        genreComboBox->currentText().toStdString(),
        yearEdit->value(),
        languageEdit->text().toStdString(),
        "",  // immagine verrà impostata da AddPage
        true, // disponibilità predefinita
        1,    // copie predefinite
        isbnEdit->text().toStdString(),
        editorLibroEdit->text().toStdString(),
        pagesLibroEdit->value(),
        0,    // in prestito predefinito
        "",   // collocazione predefinita
        static_cast<float>(ratingEdit->value())
    );
}

void LibroDetailsWidget::setMedia(Libro* libro) {
    if (!libro) return;
    
    // Impostiamo i valori nei campi esistenti
    titleEdit->setText(QString::fromStdString(libro->getTitolo()));
    authorEdit->setText(QString::fromStdString(libro->getAutore()));
    
    // Trova e seleziona il genere corretto nella combobox
    QString genere = QString::fromStdString(libro->getGenere());
    int genreIndex = genreComboBox->findText(genere);
    if (genreIndex >= 0) {
        genreComboBox->setCurrentIndex(genreIndex);
    } else {
        genreComboBox->setCurrentText(genere);
    }
    
    yearEdit->setValue(libro->getAnno());
    languageEdit->setText(QString::fromStdString(libro->getLingua()));
    isbnEdit->setText(QString::fromStdString(libro->getIsbn()));
    editorLibroEdit->setText(QString::fromStdString(libro->getEditore()));
    pagesLibroEdit->setValue(libro->getNPagine());
}

void LibroDetailsWidget::setReadOnly(bool readOnly) {
    // Imposta tutti i campi in modalità sola lettura
    titleEdit->setReadOnly(readOnly);
    authorEdit->setReadOnly(readOnly);
    genreComboBox->setEnabled(!readOnly);
    yearEdit->setReadOnly(readOnly);
    languageEdit->setReadOnly(readOnly);
    isbnEdit->setReadOnly(readOnly);
    editorLibroEdit->setReadOnly(readOnly);
    pagesLibroEdit->setReadOnly(readOnly);
    
    // Nascondi pulsanti se in modalità lettura
    if (readOnly) {
        if (saveButton) saveButton->hide();
        if (cancelButton) cancelButton->hide();
    } else {
        if (saveButton) saveButton->show();
        if (cancelButton) cancelButton->show();
    }
}