#include <QFile> 
#include "../Headers/MainPage.h"
#include "../../Modello logico/Headers/Media.h"
#include "../../Modello logico/Headers/Libro.h"
#include "../../Modello logico/Headers/Film.h"
#include "../../Modello logico/Headers/Vinile.h"
#include "../../Modello logico/Headers/GiocoDaTavolo.h"
#include "../../Modello logico/Headers/Rivista.h"

MainPage::MainPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void MainPage::setupUI(){
    // ---------- Barra superiore ----------------------
    backButton = new QPushButton("Indietro");

    addMediaButton = new QPushButton("Aggiungi Media");
    //editModeButton = new QPushButton("Modalità Modifica");
    backButton->setMinimumSize(100, 30);
    addMediaButton->setMinimumSize(100, 30);
    //editModeButton->setMinimumSize(100, 30);

    backButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 104, 201);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "}"
        "QPushButton:hover {"
        "   background-color:rgb(11, 82, 189);"
        "}"
    );

    connect(backButton, &QPushButton::clicked, this, &MainPage::onBackButtonClicked);

    topBarLayout = new QHBoxLayout();
    topBarLayout->addWidget(backButton, 1);
    topBarLayout->addWidget(addMediaButton, 5);

    // --------------- Menu filtri -------------------
    // Selezione tipo media
    mediaTypeComboBox = new QComboBox();
    mediaTypeComboBox->addItem("Qualsiasi");
    mediaTypeComboBox->addItem("Libro");
    mediaTypeComboBox->addItem("Film");
    mediaTypeComboBox->addItem("Vinile");
    mediaTypeComboBox->addItem("Gioco da tavolo");
    mediaTypeComboBox->addItem("Rivista");

    // Collega il cambiamento del tipo media alla funzione di aggiornamento della combobox dei generi
    genreComboBox = new QComboBox();
    genreComboBox->addItem("Qualsiasi genere");
    updateGenreComboBox(); // Popola i generi in base al tipo selezionato

    connect(mediaTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainPage::onMediaTypeChanged);

    // Campi di input per rating
    ratingLineEdit = new QLineEdit();
    ratingLineEdit->setPlaceholderText("da 1 a 5");

    // Checkbox per disponibilità
    QCheckBox *availableCheckBox = new QCheckBox("Disponibile");
    availableCheckBox->setChecked(true); // Selezionato di default

    // Campi di input per lingua
    languageLineEdit = new QLineEdit();
    languageLineEdit->setPlaceholderText("lingua");

    // Campi di input per anno
    minYearLineEdit = new QLineEdit();
    minYearLineEdit->setPlaceholderText("anno min");
    maxYearLineEdit = new QLineEdit();
    maxYearLineEdit->setPlaceholderText("anno max");

    filtersLayout = new QVBoxLayout();
    filtersLayout->addWidget(new QLabel("Tipo media:"));
    filtersLayout->addWidget(mediaTypeComboBox);
    filtersLayout->addWidget(new QLabel("Genere:")); 
    filtersLayout->addWidget(genreComboBox);
    filtersLayout->addWidget(new QLabel("Rating"));
    filtersLayout->addWidget(ratingLineEdit);
    filtersLayout->addWidget(new QLabel("Disponibile:"));
    filtersLayout->addWidget(availableCheckBox);
    filtersLayout->addWidget(new QLabel("Lingua:"));
    filtersLayout->addWidget(languageLineEdit);
    filtersLayout->addWidget(new QLabel("Anno minimo:"));
    filtersLayout->addWidget(minYearLineEdit);
    filtersLayout->addWidget(new QLabel("Anno massimo:"));
    filtersLayout->addWidget(maxYearLineEdit);

    QGroupBox *filtersGroupBox = new QGroupBox("Filtri");
    filtersGroupBox->setLayout(filtersLayout);
    filtersGroupBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // ---------------- Barra di ricerca e lista media -----------------
    searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Cerca per titolo...");

    mediaList = new QListWidget();
    mediaList->setViewMode(QListView::ListMode); // Modalità lista (righe)
    mediaList->setResizeMode(QListView::Adjust); // Adatta le dimensioni
    mediaList->setMovement(QListView::Static); // Elementi non trascinabili
    mediaList->setSelectionMode(QAbstractItemView::SingleSelection); // Selezione singola
    mediaList->setStyleSheet(
        "QListWidget { background-color:rgb(33, 50, 74); border: 2px solid rgb(119, 114, 114); }"
        "QListWidget::item { border-bottom:3px solid #ddd; padding: 8px; color: white; }"
        "QListWidget::item:hover { background-color:rgb(101, 123, 152); color: white;}"
        "QListWidget::item:selected { background-color:rgb(255, 208, 0); color: black; }"
    );

    vector<Media*> listaMedia = {
        new Libro("Il Nome della Rosa", "Paperino", "Giallo", 1980, "Italiano", ":/Immagini/default_libro.png", true, 5, "123456789", "Bompiani", 500, 0, "Scaffale A1", 4.5),
        new Film("Inception", "Paperino", "Fantascienza", 2010, "Inglese", ":/Immagini/default_film.png", true, 3, 148, {"Leonardo DiCaprio", "Joseph Gordon-Levitt"}, 0, "Scaffale B2", 5.0),
        new Vinile("The Dark Side of the Moon", "Paperino", "Rock", 1973, "Inglese", ":/Immagini/default_vinile.png", true, 2,  10, 43, 0, "Scaffale C3", 5.0),
        new GiocoDaTavolo("Catan", "Paperino", "Strategia", 1995, "Italiano", ":/Immagini/default_gioco.png", true, 4, 4, 10, 60, "Klaus Teuber", 0, "Scaffale D4", 4.0),
        new Rivista("National Geographic", "Paperino", "Scientifica", 2023, "Italiano", ":/Immagini/default_rivista.png", true, 10, "National Geographic Society", 100, "2023-04-01", "Mensile", 0, "Scaffale E5", 4.8),
        new Rivista("Time", "Paperino", "Attualità", 2023, "Italiano", ":/Immagini/default_rivista.png", true, 10, "Time Inc.", 100, "2023-04-01", "Settimanale", 0, "Scaffale E5", 4.5),
        new Rivista("Vogue", "Paperino", "Moda", 2023, "Italiano", ":/Immagini/default_rivista.png", true, 10, "Condé Nast", 100, "2023-04-01", "Mensile", 0, "Scaffale E5", 4.2),
        new Libro("Il Codice Da Vinci", "Paperino", "Giallo", 2003, "Italiano", ":/Immagini/default_libro.png", true, 5, "123456789", "Mondadori", 500, 0, "Scaffale A1", 4.0),
        new Libro("1984", "Paperino", "Fantascienza", 1949, "Italiano", ":/Immagini/default_libro.png", true, 5, "123456789", "Mondadori", 500, 0, "Scaffale A1", 4.8),
        new Film("The Shawshank Redemption", "Paperino", "Drammatico", 1994, "Inglese", ":/Immagini/default_film.png", true, 3, 142, {"Tim Robbins", "Morgan Freeman"}, 0, "Scaffale B2", 5.0),
        new Film("Pulp Fiction", "Paperino", "Commedia", 1994, "Inglese", ":/Immagini/default_film.png", true, 3, 154, {"John Travolta", "Uma Thurman"}, 0, "Scaffale B2", 4.5),
        new GiocoDaTavolo("Ticket to Ride", "Paperino", "Strategia", 2004, "Italiano", ":/Immagini/default_gioco.png", true, 4, 2, 5, 120, "Alan R. Moon", 0, "Scaffale D4", 4.5),
        new GiocoDaTavolo("Carcassonne", "Paperino", "Strategia", 2000, "Italiano", ":/Immagini/default_gioco.png", true, 4, 2, 5, 35, "Klaus-Jürgen Wrede", 0, "Scaffale D4", 4.0)
    };

    for (Media* media : listaMedia) {
        QString mediaInfo = media->mediaInfo(); // Ottieni le informazioni del media

        QListWidgetItem *item = new QListWidgetItem(mediaInfo, mediaList);
        item->setData(Qt::UserRole, QVariant::fromValue(media)); // Save the media object
    }

    // Collega la selezione
    connect(mediaList, &QListWidget::itemClicked, this, &MainPage::onMediaSelected);

    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->addWidget(searchBar);
    centerLayout->addWidget(mediaList);

    // --------------------- Sezione destra -----------------------------
    mediaImageLabel = new QLabel();
    mediaImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mediaImageLabel->setAlignment(Qt::AlignCenter);
    mediaImageLabel->setStyleSheet(
        "border: 1px solid black; background-color: white;"
    );
    mediaImageLabel->setMinimumSize(200, 300);

    // Imposta la politica di dimensionamento
    mediaImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mediaImageLabel->setScaledContents(false); // Importante per mantenere le proporzioni

    mediaInfoLabel = new QLabel("Seleziona un media per vedere i dettagli");
    mediaTitleLabel = new QLabel("Titolo: ");
    mediaAuthorLabel = new QLabel("Autore: ");
    mediaYearLabel = new QLabel("Anno: ");
    mediaRatingLabel = new QLabel("Rating: ");

    QString labelStyle = "QLabel { font-size: 14px; margin: 5px; }";
    mediaTitleLabel->setStyleSheet(labelStyle + "font-weight: bold; font-size: 16px;");
    mediaAuthorLabel->setStyleSheet(labelStyle);
    mediaYearLabel->setStyleSheet(labelStyle);
    mediaRatingLabel->setStyleSheet(labelStyle);

    // Pulsanti per la sezione destra
    borrowButton = new QPushButton("Prendi in prestito");
    detailsButton = new QPushButton("Approfondisci");
    editMediaButton = new QPushButton("Modifica media");

    // Aggiungi nella funzione setupUI()
    borrowButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 104, 201);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "}"
        "QPushButton:hover {"
        "   background-color:rgb(11, 82, 189);"
        "}"
    );

    previewLayout = new QVBoxLayout();
    previewLayout->addWidget(mediaImageLabel);
    previewLayout->addWidget(mediaTitleLabel);
    previewLayout->addWidget(mediaAuthorLabel);
    previewLayout->addWidget(mediaYearLabel);
    previewLayout->addWidget(mediaRatingLabel);
    previewLayout->addSpacing(10);
    previewLayout->addWidget(borrowButton);
    previewLayout->addWidget(detailsButton);
    previewLayout->addWidget(editMediaButton);
    previewLayout->addStretch();

    QGroupBox *previewGroupBox = new QGroupBox("Anteprima");
    previewGroupBox->setLayout(previewLayout);
    previewGroupBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // Layout principale
    contentLayout = new QHBoxLayout();
    contentLayout->addWidget(filtersGroupBox, 1);
    contentLayout->addLayout(centerLayout, 3);
    contentLayout->addWidget(previewGroupBox, 2);

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topBarLayout);
    mainLayout->addLayout(contentLayout);

    setLayout(mainLayout);
}

void MainPage::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    updateImageSize();
}

void MainPage::updateImageSize() {
    if (!mediaImageLabel->pixmap().isNull()) {
        QPixmap original = mediaImageLabel->pixmap();
        // Calcola le dimensioni mantenendo le proporzioni originali
        QSize labelSize = mediaImageLabel->size();
        QPixmap scaled = original.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        
        mediaImageLabel->setPixmap(scaled);
    }
}

void MainPage::onMediaSelected(QListWidgetItem *item) {
    Media* selectedMedia = item->data(Qt::UserRole).value<Media*>();
    if (!selectedMedia) {
        return;
    }

    // Aggiorna la sezione destra con le informazioni del media selezionato
    mediaTitleLabel->setText("Titolo: " + QString::fromStdString(selectedMedia->getTitolo()));
    mediaAuthorLabel->setText("Autore: " + QString::fromStdString(selectedMedia->getAutore()));
    mediaYearLabel->setText("Anno: " + QString::number(selectedMedia->getAnno()));

    // Mostra il rating con le stelline
    double rating = selectedMedia->getRating();
    QString stars = QString("Rating: %1 %2").arg(QString("★").repeated(static_cast<int>(rating))).arg(QString::number(rating, 'f', 1));
    mediaRatingLabel->setText(stars);

    // Aggiorna l'immagine del media
    QPixmap pixmap(QString::fromStdString(selectedMedia->getImmagine()));
    if (!pixmap.isNull()) {
        originalPixmapSize = pixmap.size();
        mediaImageLabel->setPixmap(pixmap);
    } else {
        mediaImageLabel->setText("Immagine non disponibile");
        mediaImageLabel->setStyleSheet(
            "border: 1px solid black;"
            "background-color: white;"
            "color: gray;"
            "padding: 5px;"
        );
    }

    // Abilita i pulsanti
    borrowButton->setEnabled(true);
    detailsButton->setEnabled(true);
    editMediaButton->setEnabled(true);
}

void MainPage::updateGenreComboBox() {
    genreComboBox->clear();
    genreComboBox->addItem("Qualsiasi genere");
    
    int currentType = mediaTypeComboBox->currentIndex();
    
    switch(currentType) {
        case 1: // Libro
            genreComboBox->addItems({"Fantasy", "Fantascienza", "Horror", "Romanzo storico", 
                                    "Biografia", "Autobiografia", "Saggio", "Giallo", "Thriller"});
            break;
        case 2: // Film
            genreComboBox->addItems({"Azione", "Avventura", "Commedia", "Drammatico", 
                                    "Fantascienza", "Horror", "Thriller", "Documentario", "Animazione"});
            break;
        case 3: // Vinile
            genreComboBox->addItems({"Rock", "Pop", "Classica", "Jazz", "Blues", 
                                    "Metal", "Hip Hop", "Elettronica", "Folk"});
            break;
        case 4: // Gioco da tavolo
            genreComboBox->addItems({"Strategia", "Party game", "Cooperativo", "Giochi di carte", 
                                    "Giochi di miniature", "Giochi di ruolo", "Astratto"});
            break;
        case 5: // Rivista
            genreComboBox->addItems({"Scientifica", "Culturale", "Attualità", "Moda", 
                                    "Tecnologia", "Sport", "Fumetti"});
            break;
        default: // Qualsiasi o non specificato
            break;
    }
}

void MainPage::onMediaTypeChanged(int index) {
    Q_UNUSED(index);
    updateGenreComboBox();
}

void MainPage::onBackButtonClicked() {
    // Cambia pagina alla LoginPage
    emit goToLoginPage(); // Emetti un segnale per notificare il cambio di pagina
}