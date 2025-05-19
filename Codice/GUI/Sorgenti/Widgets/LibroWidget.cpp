#include "../../Headers/Widgets/LibroWidget.h"
#include "../../../Modello logico/Headers/Libro.h"
#include <QLabel>

using std::string;

LibroWidget::LibroWidget(QWidget *parent) : MediaWidget(parent), currentLibro(nullptr) {
    setupBaseUI("Scheda Libro");
}

void LibroWidget::setCurrentMedia(Media* media) {
    // Controllo di validità
    if (!media) {
        QMessageBox::warning(this, "Errore", "Media non valido");
        return;
    }

    // Salvo il riferimento al media corrente
    currentMedia = media;

    // Salvo il riferimento al film corrente
    currentLibro = dynamic_cast<Libro*>(media);

    if (!currentLibro) {
        QMessageBox::warning(this, "Errore", "Media non è un libro");
        currentMedia = nullptr;
        return;
    }

    // Imposto i valori nei campi
    setCurrentValues();
}

void LibroWidget::addSpecificFields() {
    // Imposta generi specifici per i film
    genreComboBox->addItems({"Avventura", "Biografia", "Fantasy", "Fantascienza", "Giallo", "Horror", "Narrativa", "Poesia", "Romanzo", "Saggistica", "Storico", "Thriller", "Altro"});

    // Campi specifici per libro
    isbnEdit = new QLineEdit(scrollWidget);
    isbnEdit->setStyleSheet(getInputStyle());

    editorEdit = new QLineEdit(scrollWidget);
    editorEdit->setStyleSheet(getInputStyle());

    pagesEdit = new QSpinBox(scrollWidget);
    pagesEdit->setRange(1, 9999);
    pagesEdit->setStyleSheet(getInputStyle());

    // Etichette
    QLabel *isbnLbl = new QLabel("ISBN:");
    isbnLbl->setStyleSheet(getLabelStyle());
    QLabel *editorLbl = new QLabel("Editore:");
    editorLbl->setStyleSheet(getLabelStyle());
    QLabel *pagesLbl = new QLabel("Pagine:");
    pagesLbl->setStyleSheet(getLabelStyle());

    // Aggiungi i campi al form
    formLayout->addRow(isbnLbl, isbnEdit);
    formLayout->addRow(editorLbl, editorEdit);
    formLayout->addRow(pagesLbl, pagesEdit);
}

void LibroWidget::setCurrentValues() {
    // Imposto i campi comuni a tutti i media
    MediaWidget::setCurrentValues();
    
    // Imposto i valori specifici per il film
    if (currentLibro) {
        isbnEdit->setText(QString::fromStdString(currentLibro->getIsbn()));
        editorEdit->setText(QString::fromStdString(currentLibro->getEditore()));
        pagesEdit->setValue(currentLibro->getNPagine());
    }
}

bool LibroWidget::validateData() {
    return MediaWidget::validateData() && 
            !isbnEdit->text().isEmpty() && 
            !editorEdit->text().isEmpty() && 
            pagesEdit->value() > 0;
}

bool LibroWidget::applyChanges() {
    // Controllo di validità
    if (!validateData()) return false;

    // Aggiorno i campi comuni
    MediaWidget::applyChanges();

    // Aggiorno i campi specifici del libro
    currentLibro->setIsbn(isbnEdit->text().toStdString());
    currentLibro->setEditore(editorEdit->text().toStdString());
    currentLibro->setNPagine(pagesEdit->value());

    return true;
}

Media* LibroWidget::createMedia() {
    // Controllo validità
    if(!validateData()) return nullptr;

    // Creo e restituisco un nuovo oggetto Libro
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
        editorEdit->text().toStdString(),
        pagesEdit->value(),
        0,    // in prestito predefinito
        "",   // collocazione predefinita
        static_cast<float>(ratingEdit->value())
    );
}

void LibroWidget::setReadOnly(bool readOnly) {
    MediaWidget::setReadOnly(readOnly);
    isbnEdit->setReadOnly(readOnly);
    editorEdit->setReadOnly(readOnly);
    pagesEdit->setReadOnly(readOnly);
}