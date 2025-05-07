#include "../../Headers/Widgets/FilmDetailsWidget.h"
#include "../../../Modello logico/Headers/Film.h"
#include <QLabel>
#include <vector>

using std::vector;
using std::string;

FilmDetailsWidget::FilmDetailsWidget(QWidget *parent) : MediaDetailsWidget(parent) {
    setupBaseUI("Dettagli Film");
    
    // Imposta generi specifici per film
    genreComboBox->addItems({"Animazione", "Azione", "Avventura", "Commedia", "Documentario", "Drammatico", "Fantasy", "Horror", "Romantico", "Sci-Fi", "Thriller", "Altro"});
}

void FilmDetailsWidget::addSpecificFields() {
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

    // Aggiungi i campi al form
    formLayout->addRow(durationLbl, durationFilmEdit);
    formLayout->addRow(castLbl, castEdit);
}

bool FilmDetailsWidget::validateData() {
    return !titleEdit->text().isEmpty() && 
           !authorEdit->text().isEmpty() && 
           !genreComboBox->currentText().isEmpty() &&
           yearEdit->value() > 0 && 
           !languageEdit->text().isEmpty() && 
           durationFilmEdit->value() > 0;
}

Media* FilmDetailsWidget::createMedia() {
    // Il controllo di valità è già stato fatto da validateData() in AddPage una volta premuto il pulsante "Salva Media" (metodo onSaveMediaButtonClicked())

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

void FilmDetailsWidget::setMedia(Film* film) {
    if (!film) return;
    
    // Impostiamo i valori nei campi esistenti
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
    durationFilmEdit->setValue(film->getDurata());
    
    // Gestisci il cast
    QString castText;
    const vector<string>& cast = film->getCast();
    for (size_t i = 0; i < cast.size(); ++i) {
        castText += QString::fromStdString(cast[i]);
        if (i < cast.size() - 1) {
            castText += ", ";
        }
    }
    castEdit->setText(castText);
}

void FilmDetailsWidget::setReadOnly(bool readOnly) {
    // Imposta tutti i campi in modalità sola lettura
    titleEdit->setReadOnly(readOnly);
    authorEdit->setReadOnly(readOnly);
    genreComboBox->setEnabled(!readOnly);
    yearEdit->setReadOnly(readOnly);
    languageEdit->setReadOnly(readOnly);
    durationFilmEdit->setReadOnly(readOnly);
    castEdit->setReadOnly(readOnly);
    
    // Nascondi pulsanti se in modalità lettura
    if (readOnly) {
        if (saveButton) saveButton->hide();
        if (cancelButton) cancelButton->hide();
    } else {
        if (saveButton) saveButton->show();
        if (cancelButton) cancelButton->show();
    }
}