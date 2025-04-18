#include <QFile> 
#include "../Headers/MainPage.h"

MainPage::MainPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void MainPage::setupUI(){
    // Barra superiore
    backButton = new QPushButton("Indietro");
    addMediaButton = new QPushButton("Aggiungi Media");
    //editModeButton = new QPushButton("Modalità Modifica");
    backButton->setMinimumSize(100, 30);
    addMediaButton->setMinimumSize(100, 30);
    //editModeButton->setMinimumSize(100, 30);

    topBarLayout = new QHBoxLayout();
    topBarLayout->addWidget(backButton);
    topBarLayout->addWidget(addMediaButton);
    //topBarLayout->addWidget(editModeButton);

    // Menu filtri
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

    // Barra di ricerca e lista media
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

    QStringList mediaExamples = {
        "Libro: Il Nome della Rosa - Umberto Eco (1980) ★★★★☆",
        "Film: Inception - Christopher Nolan (2010) ★★★★★",
        "Vinile: Dark Side of the Moon - Pink Floyd (1973) ★★★★★",
        "Gioco da tavolo: Catan - Klaus Teuber (1995) ★★★★☆",
        "Libro: Il Codice Da Vinci - Dan Brown (2003) ★★★☆☆",
        "Libro: 1984 - George Orwell (1949) ★★★★★",
        "Libro: Orgoglio e Pregiudizio - Jane Austen (1813) ★★★★☆",
        "Libro: Il Piccolo Principe - Antoine de Saint-Exupéry (1943) ★★★★★",
        "Libro: Dracula - Bram Stoker (1897) ★★★☆☆",
        "Libro: Fahrenheit 451 - Ray Bradbury (1953) ★★★★☆",
        "Libro: Cime Tempestose - Emily Brontë (1847) ★★☆☆☆",
        "Film: The Shawshank Redemption - Frank Darabont (1994) ★★★★★",
        "Film: Pulp Fiction - Quentin Tarantino (1994) ★★★★☆",
        "Film: Inception - Christopher Nolan (2010) ★★★★★",
        "Film: La La Land - Damien Chazelle (2016) ★★★☆☆",
        "Film: Parasite - Bong Joon-ho (2019) ★★★★★",
        "Film: The Room - Tommy Wiseau (2003) ★☆☆☆☆",
        "Film: Interstellar - Christopher Nolan (2014) ★★★★☆",
        "Film: Forrest Gump - Robert Zemeckis (1994) ★★★★★",
        "Vinile: Thriller - Michael Jackson (1982) ★★★★★",
        "Vinile: The Dark Side of the Moon - Pink Floyd (1973) ★★★★★",
        "Vinile: Nevermind - Nirvana (1991) ★★★★☆",
        "Vinile: Back in Black - AC/DC (1980) ★★★☆☆",
        "Vinile: Rumours - Fleetwood Mac (1977) ★★★★★",
        "Gioco da tavolo: Catan - Klaus Teuber (1995) ★★★★☆",
        "Gioco da tavolo: Ticket to Ride - Alan R. Moon (2004) ★★★★☆",
        "Gioco da tavolo: Carcassonne - Klaus-Jürgen Wrede (2000) ★★★☆☆",
        "Gioco da tavolo: Pandemic - Matt Leacock (2008) ★★★★★",
        "Gioco da tavolo: Monopoly - Elizabeth Magie (1935) ★★☆☆☆",
        "Rivista: National Geographic - Vari Autori (1888) ★★★★★",
        "Rivista: Time - Vari Autori (1923) ★★★★☆",
        "Rivista: The Economist - Vari Autori (1843) ★★★★☆",
        "Rivista: Vogue - Vari Autori (1892) ★★★☆☆",
        "Rivista: Scientific American - Vari Autori (1845) ★★★★★"
    };

    foreach (const QString &media, mediaExamples) {
        QListWidgetItem *item = new QListWidgetItem(media, mediaList);
        // Puoi salvare dati aggiuntivi così:
        item->setData(Qt::UserRole, media.split(":").first()); // Salva il tipo
    }

    // Collega la selezione
    connect(mediaList, &QListWidget::itemClicked, this, &MainPage::onMediaSelected);

    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->addWidget(searchBar);
    centerLayout->addWidget(mediaList);

    // Sezione destra
    mediaImageLabel = new QLabel();
    mediaImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mediaImageLabel->setAlignment(Qt::AlignCenter);
    mediaImageLabel->setStyleSheet(
        "border: 1px solid black; background-color: white;"
        "QLabel:hover { border: 2px solid rgb(0, 104, 201); }"
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
        "   padding: 8px;"
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
    QString fullText = item->text();
    
    // Estrai le informazioni 
    QString type = fullText.split(":").first();
    QString title = fullText.split("-")[0].split(":").last().trimmed();
    QString author = fullText.split("-")[1].split("(").first().trimmed();
    QString year = fullText.split("(").last().split(")").first();
    QString rating = fullText.split(")").last().trimmed();

    // Aggiorna la sezione destra
    mediaTitleLabel->setText("Titolo: " + title);
    mediaAuthorLabel->setText("Autore: " + author);
    mediaYearLabel->setText("Anno: " + year);
    mediaRatingLabel->setText("Rating: " + rating);

    QPixmap pixmap;

    if (!pixmap.isNull()) {
        originalPixmapSize = pixmap.size();
        mediaImageLabel->setPixmap(pixmap);
    } else {
        mediaImageLabel->setText("Immagine non disponibile");
        mediaImageLabel->setStyleSheet(
            "border: 1px solid black;"
            "background-color: white;"
            "color: gray;"
            "font-style: italic;"
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