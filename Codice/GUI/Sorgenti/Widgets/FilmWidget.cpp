#include "../../Headers/Widgets/FilmWidget.h"
#include "../../../Modello logico/Headers/Film.h"
#include <QLabel>
#include <vector>

using std::vector;
using std::string;

FilmWidget::FilmWidget(QWidget *parent) : MediaWidget(parent) {
    setupBaseUI("Scheda Film");
}

void FilmWidget::addSpecificFields() {
    // Imposta generi specifici per i film
    genreComboBox->addItems({"Animazione", "Azione", "Avventura", "Biografia", "Commedia", "Crime", "Documentario", "Drammatico", "Fantascienza", "Fantasy", "Horror", "Musical", "Mistero", "Romantico", "Thriller", "Western", "Altro"});

    // Campi specifici per film
    durationFilmEdit = new QSpinBox(scrollWidget);
    durationFilmEdit->setRange(1, 999);
    durationFilmEdit->setSuffix(" min");
    durationFilmEdit->setStyleSheet(getInputStyle());
    
    castEdit = new QLineEdit(scrollWidget);
    castEdit->setStyleSheet(getInputStyle());
    castEdit->setPlaceholderText("(separati da virgola)");
    
    // Etichette
    QLabel *durationLbl = new QLabel("Durata:");
    durationLbl->setStyleSheet(getLabelStyle());
    QLabel *castLbl = new QLabel("Attori:");
    castLbl->setStyleSheet(getLabelStyle());

    if (currentMedia){
        setCurrentValues();
    }

    // Aggiungi i campi al form
    formLayout->addRow(durationLbl, durationFilmEdit);
    formLayout->addRow(castLbl, castEdit);
}

void FilmWidget::setCurrentValues() {
    // Imposto i campi comuni a tutti i media
    MediaWidget::setCurrentValues();
    
    // Imposto i valori specifici per il film
    if (currentFilm) {
        durationFilmEdit->setValue(currentFilm->getDurata());
        
        // Converto il vettore del cast in una stringa per il campo
        QString castText;
        const std::vector<std::string>& cast = currentFilm->getCast();
        for (size_t i = 0; i < cast.size(); ++i) {
            castText += QString::fromStdString(cast[i]);
            if (i < cast.size() - 1) {
                castText += ", ";
            }
        }
        castEdit->setText(castText);
    }
}

bool FilmWidget::validateData() {
    return MediaWidget::validateData() && 
           durationFilmEdit->value() > 0 && 
           !castEdit->text().isEmpty();
}

bool FilmWidget::applyChanges() {
    // Controllo di validità
    if (!validateData()) return false;

    // Aggiorno i campi comuni
    MediaWidget::applyChanges();

    // Parsing del cast da stringa a vettore
    vector<string> castVector;
    QString castText = castEdit->text();
    QStringList castList = castText.split(",", Qt::SkipEmptyParts);
    for (const QString& actor : castList) {
        castVector.push_back(actor.trimmed().toStdString());
    }

    // Aggiorno i campi specifici del Film
    currentFilm->setDurata(durationFilmEdit->value());
    currentFilm->setCast(castVector);

    return true;
}

Media* FilmWidget::createMedia() {
    // Controllo validità
    if(!validateData()) return nullptr;

    // Estraggo il cast dalla stringa separata da virgole
    vector<string> cast;
    QString castString = castEdit->text();
    QStringList castList = castString.split(",", Qt::SkipEmptyParts);
    for (const QString &actor : castList) {
        cast.push_back(actor.trimmed().toStdString());
    }

    // Creo e restituisco un nuovo oggetto Film
    return new Film(
        titleEdit->text().toStdString(),
        authorEdit->text().toStdString(),
        genreComboBox->currentText().toStdString(),
        yearEdit->value(),
        languageEdit->text().toStdString(),
        "",  // immagine verrà impostata da AddPage
        true, // disponibilità predefinita
        1,    // copie predefinite
        durationFilmEdit->value(),
        cast,
        0,    // in prestito predefinito
        "",   // collocazione predefinita
        static_cast<float>(ratingEdit->value())
    );
}

void FilmWidget::setReadOnly(bool readOnly) {
    MediaWidget::setReadOnly(readOnly);
    durationFilmEdit->setReadOnly(readOnly);
    castEdit->setReadOnly(readOnly);
}