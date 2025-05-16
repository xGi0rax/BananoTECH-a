#include "../../Headers/Widgets/FilmModifyWidget.h"
#include "../../../Modello logico/Headers/Film.h"

FilmModifyWidget::FilmModifyWidget(QWidget* parent) : MediaModifyWidget(parent) {
    setupBaseUI("Modifica Film");
}

void FilmModifyWidget::addSpecificFields() {
    // Imposta generi specifici per film
    genreComboBox->addItems({"Azione", "Avventura", "Animazione", "Biografia", "Commedia", 
                          "Crime", "Documentario", "Dramma", "Fantascienza", "Fantasy", 
                          "Horror", "Musical", "Mystery", "Romance", "Thriller", "Western"});
    
    // Se abbiamo già un media, impostiamo il genere
    if (currentMedia) {
        genreComboBox->setCurrentText(QString::fromStdString(currentMedia->getGenere()));
    }

    // Campi specifici per film
    durationEdit = new QSpinBox(scrollWidget);
    durationEdit->setRange(1, 999);
    durationEdit->setSuffix(" min");
    durationEdit->setStyleSheet(getInputStyle());
    
    castEdit = new QLineEdit(scrollWidget);
    castEdit->setStyleSheet(getInputStyle());
    castEdit->setPlaceholderText("Attori separati da virgola");
    
    // Se abbiamo già un media, impostiamo i valori specifici
    Film* film = dynamic_cast<Film*>(currentMedia);
    if (film) {
        durationEdit->setValue(film->getDurata());
        
        // Converti il vettore di cast in una stringa per il campo
        QString castText;
        const std::vector<std::string>& cast = film->getCast();
        for (size_t i = 0; i < cast.size(); ++i) {
            castText += QString::fromStdString(cast[i]);
            if (i < cast.size() - 1) {
                castText += ", ";
            }
        }
        castEdit->setText(castText);
    }
    
    // Etichette
    QLabel *durationLbl = new QLabel("Durata:");
    durationLbl->setStyleSheet(getLabelStyle());
    QLabel *castLbl = new QLabel("Cast:");
    castLbl->setStyleSheet(getLabelStyle());

    // Aggiungi i campi al form
    formLayout->addRow(durationLbl, durationEdit);
    formLayout->addRow(castLbl, castEdit);
}

bool FilmModifyWidget::validateData() {
    return !titleEdit->text().isEmpty() && 
           !authorEdit->text().isEmpty() && 
           !genreComboBox->currentText().isEmpty() &&
           yearEdit->value() > 0 && 
           !languageEdit->text().isEmpty() && 
           durationEdit->value() > 0;
}

bool FilmModifyWidget::applyChanges() {
    if (!validateData() || !currentMedia)
        return false;

    // Cast per accedere ai metodi specifici di Film
    Film* film = dynamic_cast<Film*>(currentMedia);
    if (!film) return false;

    // Aggiorna tutti i campi comuni
    currentMedia->setTitolo(titleEdit->text().toStdString());
    currentMedia->setAutore(authorEdit->text().toStdString());
    currentMedia->setGenere(genreComboBox->currentText().toStdString());
    currentMedia->setAnno(yearEdit->value());
    currentMedia->setLingua(languageEdit->text().toStdString());
    currentMedia->setRating(ratingEdit->value());
    
    // Parsing del cast da stringa a vettore
    std::vector<std::string> castVector;
    QString castText = castEdit->text();
    QStringList castList = castText.split(",", Qt::SkipEmptyParts);
    for (const QString& actor : castList) {
        castVector.push_back(actor.trimmed().toStdString());
    }
    
    // Aggiorna i campi specifici del Film
    film->setDurata(durationEdit->value());
    film->setCast(castVector);
    
    return true;
}

void FilmModifyWidget::setMedia(Film* film) {
    if (!film) return;
    
    // Salvo il riferimento al media
    currentMedia = film;
    
    // Popolamento campi base
    titleEdit->setText(QString::fromStdString(film->getTitolo()));
    authorEdit->setText(QString::fromStdString(film->getAutore()));
    
    // Trova e seleziona il genere corretto nella combobox
    QString genere = QString::fromStdString(film->getGenere());
    int genreIndex = genreComboBox->findText(genere);
    if (genreIndex >= 0) {
        genreComboBox->setCurrentIndex(genreIndex);
    } else {
        genreComboBox->setCurrentText(genere);
    }
    
    yearEdit->setValue(film->getAnno());
    languageEdit->setText(QString::fromStdString(film->getLingua()));
    ratingEdit->setValue(film->getRating());
    
    // Campi specifici per film
    durationEdit->setValue(film->getDurata());
    
    // Converti il vettore di cast in una stringa per il campo
    QString castText;
    const std::vector<std::string>& cast = film->getCast();
    for (size_t i = 0; i < cast.size(); ++i) {
        castText += QString::fromStdString(cast[i]);
        if (i < cast.size() - 1) {
            castText += ", ";
        }
    }
    castEdit->setText(castText);
}