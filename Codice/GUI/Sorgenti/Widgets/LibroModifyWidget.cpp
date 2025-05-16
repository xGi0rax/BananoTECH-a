#include "../../Headers/Widgets/LibroModifyWidget.h"
#include "../../../Modello logico/Headers/Libro.h"

LibroModifyWidget::LibroModifyWidget(QWidget* parent) : MediaModifyWidget(parent) {
    setupBaseUI("Modifica Libro");
}

void LibroModifyWidget::addSpecificFields() {
    // Imposta generi specifici per libro
    genreComboBox->addItems({"Biografia", "Fantasy", "Fantascienza", "Giallo", "Horror", "Narrativa", "Poesia", "Romanzo", "Saggistica", "Storico", "Thriller"});
    
    // Se abbiamo già un media, impostiamo il genere
    if (currentMedia) {
        genreComboBox->setCurrentText(QString::fromStdString(currentMedia->getGenere()));
    }

    // Campi specifici per libro
    isbnEdit = new QLineEdit(scrollWidget);
    isbnEdit->setStyleSheet(getInputStyle());

    editorEdit = new QLineEdit(scrollWidget);
    editorEdit->setStyleSheet(getInputStyle());

    pagesEdit = new QSpinBox(scrollWidget);
    pagesEdit->setRange(1, 9999);
    pagesEdit->setStyleSheet(getInputStyle());
    
    // Se abbiamo già un media, impostiamo i valori specifici
    Libro* libro = dynamic_cast<Libro*>(currentMedia);
    if (libro) {
        isbnEdit->setText(QString::fromStdString(libro->getIsbn()));
        editorEdit->setText(QString::fromStdString(libro->getEditore()));
        pagesEdit->setValue(libro->getNPagine());
    }
    
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

bool LibroModifyWidget::validateData() {
    return !titleEdit->text().isEmpty() && 
           !authorEdit->text().isEmpty() && 
           !genreComboBox->currentText().isEmpty() &&
           yearEdit->value() > 0 && 
           !languageEdit->text().isEmpty() && 
           !isbnEdit->text().isEmpty() && 
           !editorEdit->text().isEmpty() && 
           pagesEdit->value() > 0;
}

bool LibroModifyWidget::applyChanges() {
    if (!validateData() || !currentMedia)
        return false;

    // Cast per accedere ai metodi specifici di Libro
    Libro* libro = dynamic_cast<Libro*>(currentMedia);
    if (!libro) return false;

    // Aggiorna tutti i campi comuni
    currentMedia->setTitolo(titleEdit->text().toStdString());
    currentMedia->setAutore(authorEdit->text().toStdString());
    currentMedia->setGenere(genreComboBox->currentText().toStdString());
    currentMedia->setAnno(yearEdit->value());
    currentMedia->setLingua(languageEdit->text().toStdString());
    currentMedia->setRating(ratingEdit->value());
    
    // Aggiorna i campi specifici del Libro
    libro->setIsbn(isbnEdit->text().toStdString());
    libro->setEditore(editorEdit->text().toStdString());
    libro->setNPagine(pagesEdit->value());
    
    return true;
}

void LibroModifyWidget::setMedia(Libro* libro) {
    if (!libro) return;
    
    // Salvo il riferimento al media
    currentMedia = libro;
    
    // Popolamento campi base
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
    ratingEdit->setValue(libro->getRating());
    
    // Campi specifici per libro
    isbnEdit->setText(QString::fromStdString(libro->getIsbn()));
    editorEdit->setText(QString::fromStdString(libro->getEditore()));
    pagesEdit->setValue(libro->getNPagine());
}