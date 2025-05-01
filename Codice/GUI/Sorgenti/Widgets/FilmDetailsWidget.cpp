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