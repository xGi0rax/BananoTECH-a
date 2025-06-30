#include <QFile> 
#include <QScrollBar>
#include <QModelIndex>
#include "../Headers/MainPage.h"
#include "../../Modello logico/Headers/Media.h"
#include "../../Modello logico/Headers/Libro.h"
#include "../../Modello logico/Headers/Film.h"
#include "../../Modello logico/Headers/Vinile.h"
#include "../../Modello logico/Headers/GiocoDaTavolo.h"
#include "../../Modello logico/Headers/Rivista.h"
#include "../../Modello logico/Headers/Biblioteca.h"
#include "../../Modello logico/Headers/IOStrategy.h"
#include "../../Modello logico/Headers/JsonIO.h"
#include "../../Modello logico/Headers/XmlIO.h"
#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QStringConverter>
#include <QDebug>

MainPage::MainPage(QWidget *parent, Biblioteca* biblio) : QWidget(parent) {
    biblioteca = biblio;

    // Inizializzazione del tracciamento del file utilizzato per caricare la biblioteca
    hasCurrentFile = false;
    currentFilePath = "";
    isNewLibrary = true;
    hasUnsavedChanges = false;

    setupUI();
}

void MainPage::setupUI(){
    // ------------------------- Barra superiore ----------------------------
    backButton = new QPushButton("Indietro");
    addMediaButton = new QPushButton("Aggiungi Media");
    saveButton = new QPushButton("Salva");
    saveAsButton = new QPushButton("Salva come");

    backButton->setMinimumSize(100, 30);
    addMediaButton->setMinimumSize(100, 30);
    saveButton->setMinimumSize(100, 30);
    saveAsButton->setMinimumSize(120, 30);

    saveButton->setObjectName("saveButton");
    saveAsButton->setObjectName("saveAsButton");

    // Pulsante indietro
    backButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 104, 201);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "   background-color:rgb(11, 82, 189);"
        "}"
    );

    // Pulsante Salva
    saveButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 153, 51);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(0, 128, 43);"
        "}"
    );

    // Pulsante Salva come
    saveAsButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 102, 153);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(0, 85, 128);"
        "}"
    );

    connect(backButton, &QPushButton::clicked, this, &MainPage::onBackButtonClicked);
    connect(addMediaButton, &QPushButton::clicked, this, &MainPage::onAddMediaButtonClicked);
    connect(saveButton, &QPushButton::clicked, this, &MainPage::onSaveButtonClicked);
    connect(saveAsButton, &QPushButton::clicked, this, &MainPage::onSaveAsButtonClicked);

    topBarLayout = new QHBoxLayout();
    topBarLayout->addWidget(backButton, 1);
    topBarLayout->addWidget(addMediaButton, 5);
    topBarLayout->addWidget(saveButton, 1);
    topBarLayout->addWidget(saveAsButton, 1);


    // ------------------------------- Menu filtri --------------------------------
    // Selezione tipo media
    mediaTypeComboBox = new QComboBox();
    mediaTypeComboBox->addItem("Qualsiasi");
    mediaTypeComboBox->addItem("Libro");
    mediaTypeComboBox->addItem("Film");
    mediaTypeComboBox->addItem("Vinile");
    mediaTypeComboBox->addItem("Rivista");
    mediaTypeComboBox->addItem("Gioco da tavolo");
    
    // Collego il cambiamento del tipo media alla funzione di aggiornamento della combobox dei generi
    genreComboBox = new QComboBox();
    genreComboBox->addItem("Qualsiasi genere");
    genreComboBox->setEnabled(false); // Inizialmente disabilitato
    genreComboBox->setToolTip("Seleziona prima un tipo di media specifico");
    updateGenreComboBox(); // Popola i generi in base al tipo selezionato

    connect(mediaTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainPage::onMediaTypeChanged);

    // Campi di input per rating
    ratingMinLineEdit = new QLineEdit();
    ratingMinLineEdit->setPlaceholderText("0.0");
    ratingMaxLineEdit = new QLineEdit();
    ratingMaxLineEdit->setPlaceholderText("5.0");

    // Checkbox per disponibilità
    availableCheckBox = new QCheckBox("Disponibile");
    availableCheckBox->setChecked(true); // Selezionato di default

    // Campi di input per lingua
    languageLineEdit = new QLineEdit();
    languageLineEdit->setPlaceholderText("lingua");

    // Campi di input per anno
    minYearLineEdit = new QLineEdit();
    minYearLineEdit->setPlaceholderText("anno min");
    maxYearLineEdit = new QLineEdit();
    maxYearLineEdit->setPlaceholderText("anno max");

    // Pulsanti per applicare ed eliminare i filtri
    applyFiltersButton = new QPushButton("Applica filtri");
    clearFiltersButton = new QPushButton("Cancella filtri");

    applyFiltersButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(255, 208, 0);"
        "   color: black;"
        "   border: 2px solid rgb(119, 114, 114);"
        "   border-radius: 4px;"
        "   font-size: 12px;"
        "   padding: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(255, 170, 0);"
        "}"
    );

    clearFiltersButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(255, 69, 0);"
        "   color: white;"
        "   border: 2px solid rgb(119, 114, 114);"
        "   border-radius: 4px;"
        "   font-size: 12px;"
        "   padding: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(200, 50, 0);"
        "}"
    );

    filtersLayout = new QVBoxLayout();
    filtersLayout->addWidget(new QLabel("Tipo media:"));
    filtersLayout->addWidget(mediaTypeComboBox);

    filtersLayout->addWidget(new QLabel("Genere:")); 
    filtersLayout->addWidget(genreComboBox);

    filtersLayout->addWidget(new QLabel("Rating:"));
    filtersLayout->addWidget(ratingMinLineEdit);
    filtersLayout->addWidget(ratingMaxLineEdit);

    filtersLayout->addWidget(new QLabel("Disponibilità:"));
    filtersLayout->addWidget(availableCheckBox);

    filtersLayout->addWidget(new QLabel("Lingua:"));
    filtersLayout->addWidget(languageLineEdit);

    filtersLayout->addWidget(new QLabel("Anno minimo:"));
    filtersLayout->addWidget(minYearLineEdit);

    filtersLayout->addWidget(new QLabel("Anno massimo:"));
    filtersLayout->addWidget(maxYearLineEdit);

    // Aggiunta dei pulsanti al layout contenitore
    filtersLayout->addWidget(applyFiltersButton);
    filtersLayout->addWidget(clearFiltersButton);

    filtersGroupBox = new QGroupBox("Filtri");
    filtersGroupBox->setLayout(filtersLayout);
    filtersGroupBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    connect(applyFiltersButton, &QPushButton::clicked, this, &MainPage::onApplyFiltersClicked);
    connect(clearFiltersButton, &QPushButton::clicked, this, &MainPage::onClearFiltersClicked);


    // ------------------------- Barra di ricerca e lista media ------------------------
    searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Cerca per titolo o autore...");
    searchBar->setStyleSheet("QLineEdit { background-color: rgb(255, 208, 0); color: black; border: 2px solid rgb(119, 114, 114); padding: 5px; border-radius: 4px; font-size: 12px; }");

    connect(searchBar, &QLineEdit::textChanged, this, &MainPage::onSearchTextChanged);

    mediaList = new QListWidget();
    mediaList->setViewMode(QListView::ListMode);
    mediaList->setResizeMode(QListView::Adjust);
    mediaList->setMovement(QListView::Static);
    mediaList->setSelectionMode(QAbstractItemView::SingleSelection);

    // listaMedia è un parametro locale a questo metodo, che sia da metterlo come membro della classe?
    vector<Media*> listaMedia = biblioteca->getListaMedia();
    updateMediaList(listaMedia);

    mediaList->setFocusPolicy(Qt::NoFocus);
    mediaList->setIconSize(QSize(27, 27));
    mediaList->setStyleSheet(
        "QListWidget { background-color: rgb(243, 238, 238); border: 2px solid rgb(119, 114, 114); border-radius: 4px; font-size: 14px; }"
        "QListWidget::item { border-bottom:3px solid #ddd; padding: 8px; padding-left: 4px; color: black; }"
        "QListWidget::item:hover { background-color:rgb(151, 168, 190); color: white;}"
        "QListWidget::item:selected { background-color:rgb(255, 208, 0); color: black; }"
        "QListWidget::item:focus { outline: none; }"
    );

    // Collega la selezione e lo scroll
    connect(mediaList, &QListWidget::itemClicked, this, &MainPage::onMediaSelected);
    connect(mediaList->verticalScrollBar(), &QScrollBar::valueChanged, this, &MainPage::onScrollChanged);
    
    centerLayout = new QVBoxLayout();
    centerLayout->addWidget(searchBar);
    centerLayout->addWidget(mediaList);

    // Inizializzazione widget dei pulsanti da visualizzare quando un elemento è selezionato
    buttonsContainer = new QWidget(mediaList);
    buttonsContainer->hide(); // inizialmente nascosto
    
    QHBoxLayout* buttonsLayout = new QHBoxLayout(buttonsContainer);
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->setSpacing(6);
    
    // Creazione pulsanti
    listEditButton = new QPushButton();
    listEditButton->setToolTip("Modifica");
    listEditButton->setFixedSize(26, 26);
    QPixmap editIcon(":/Immagini/BottoneMatita.png");
    listEditButton->setIcon(QIcon(editIcon));
    listEditButton->setIconSize(QSize(16, 16));
    listEditButton->setStyleSheet(
        "QPushButton {"
    "   background-color: rgb(131, 187, 222);"
    "   color: black;"
    "   border: 2px solid rgb(92, 92, 93);"
    "   border-radius: 13px;"
    "   font-size: 12px;"
    "   font-weight: bold;"
    "   text-align: center;"
    "   padding: 2px;"
    "}"
        "QPushButton:hover {"
        "   background-color: rgb(87, 163, 210);"
        "}"
    );
    
    listDeleteButton = new QPushButton();
    listDeleteButton->setToolTip("Rimuovi");
    listDeleteButton->setFixedSize(26, 26);
    QPixmap deleteIcon(":/Immagini/BottoneCestino.png");
    listDeleteButton->setIcon(QIcon(deleteIcon));
    listDeleteButton->setIconSize(QSize(20, 20));
    listDeleteButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(240, 107, 70);"
        "   color: black;"
        "   border: 2px solid rgb(92, 92, 93);"
        "   border-radius: 13px;"
        "   font-size: 12px;"
        "   font-weight: bold;"
        "   text-align: center;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(250, 81, 34);"
        "}"
    );
    
    // Aggiunta pulsanti al layout
    buttonsLayout->addWidget(listEditButton);
    buttonsLayout->addWidget(listDeleteButton);
    
    // Collegamento segnali
    connect(listEditButton, &QPushButton::clicked, this, &MainPage::onEditButtonClicked);
    connect(listDeleteButton, &QPushButton::clicked, this, &MainPage::onDeleteButtonClicked);
    
    // Collegamento al cambio di selezione per nascondere i pulsanti
    connect(mediaList, &QListWidget::currentRowChanged, this, &MainPage::hideActionButtons);


    // ------------------------------------- Sezione destra ----------------------------------------
    previewGroupBox = new QGroupBox("Anteprima");
    
    // Label per l'immagine del media
    mediaImageLabel = new QLabel();
    mediaImageLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    mediaImageLabel->setAlignment(Qt::AlignCenter);
    mediaImageLabel->setMinimumSize(150, 150);
    mediaImageLabel->setStyleSheet("border: 1px solid black; background-color: white; color: gray; font-size: 14px;");
    mediaImageLabel->setText("Nessuna immagine");

    // Label per le informazioni del media
    mediaTitleLabel = new QLabel();
    mediaTitleLabel->setMinimumWidth(150);
    mediaTitleLabel->setWordWrap(true); // Abilita il wrapping del testo
    mediaTitleLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft); // Allinea in alto a sinistra
    
    mediaAuthorLabel = new QLabel("Seleziona un media per vedere i dettagli");
    mediaAuthorLabel->setWordWrap(true); // Abilita il wrapping anche per l'autore
    
    mediaYearLabel = new QLabel();
    mediaRatingLabel = new QLabel();

    // Pulsanti
    borrowButton = new QPushButton("Prendi in prestito");
    returnButton = new QPushButton("Restituisci");
    detailsButton = new QPushButton("Approfondisci");
    editMediaButton = new QPushButton("Modifica media");

    borrowButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 104, 201);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "   padding: 3px;"
        "}"
        "QPushButton:hover {"
        "   background-color:rgb(11, 82, 189);"
        "}"
    );

    returnButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 104, 201);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "   padding: 3px;"
        "}"
        "QPushButton:hover {"
        "   background-color:rgb(11, 82, 189);"
        "}"
    );

    detailsButton->setStyleSheet(
        "QPushButton {"
        "   font-size: 14px;"
        "   padding: 2px;"
        "}"
    );

    editMediaButton->setStyleSheet(
        "QPushButton {"
        "   font-size: 14px;"
        "   padding: 2px;"
        "}"
    );

    connect(borrowButton, &QPushButton::clicked, this, &MainPage::onBorrowButtonClicked);
    connect(returnButton, &QPushButton::clicked, this, &MainPage::onReturnButtonClicked);
    connect(detailsButton, &QPushButton::clicked, this, &MainPage::onDetailsButtonClicked);
    connect(editMediaButton, &QPushButton::clicked, this, &MainPage::onEditButtonClicked);

    // Layout verticale per la sezione destra
    previewLayout = new QVBoxLayout();
    previewLayout->addWidget(mediaImageLabel);
    previewLayout->addWidget(mediaTitleLabel);
    previewLayout->addWidget(mediaAuthorLabel);
    previewLayout->addWidget(mediaYearLabel);
    previewLayout->addWidget(mediaRatingLabel);
    previewLayout->addStretch();
    previewLayout->addWidget(borrowButton);
    previewLayout->addWidget(returnButton);
    previewLayout->addWidget(detailsButton);
    previewLayout->addWidget(editMediaButton);

    previewGroupBox->setLayout(previewLayout);
    
    // Imposta le policy di dimensionamento per mantenere le proporzioni
    previewGroupBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    
    // Imposta dimensioni minime e massime per evitare espansioni indesiderate
    previewGroupBox->setMinimumWidth(200);
    previewGroupBox->setMaximumWidth(400);
    filtersGroupBox->setMinimumWidth(200);
    filtersGroupBox->setMaximumWidth(400);

    // Layout principale
    contentLayout = new QHBoxLayout();
    contentLayout->addWidget(filtersGroupBox, 1);
    contentLayout->addLayout(centerLayout, 2);
    contentLayout->addWidget(previewGroupBox, 1);

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topBarLayout);
    mainLayout->addLayout(contentLayout);

    setLayout(mainLayout);
}

void MainPage::updateImageSize(){
    if (!originalPixmap.isNull()) {
        // Calcola la dimensione massima disponibile per l'immagine
        int maxImageWidth = this->width() / 3;
        
        // Sottrai i margini del layout e del GroupBox per evitare overflow
        int groupBoxMargins =  5; // Ridotto da 20 a 5 per margine meno largo
        int layoutMargins = previewLayout->contentsMargins().left() + previewLayout->contentsMargins().right();
        int totalMargins = groupBoxMargins + layoutMargins - 3;
        
        int availableWidth = qMin(previewGroupBox->width() - totalMargins, maxImageWidth - totalMargins); 
        int availableHeight = previewGroupBox->height() / 3; // Cambiato da /2 a /3 per fare spazio ai bottoni
        
        // Assicurati che le dimensioni siano positive
        availableWidth = qMax(150, availableWidth); // Dimensione minima
        availableHeight = qMax(150, availableHeight);
        
        // Calcola la dimensione mantenendo le proporzioni
        QSize newSize = originalPixmap.size();
        newSize.scale(availableWidth, availableHeight, Qt::KeepAspectRatio);

        QPixmap background(availableWidth, availableHeight);
        background.fill(Qt::white);
        
        QPainter painter(&background);
        int x = (availableWidth - newSize.width()) / 2;
        int y = (availableHeight - newSize.height()) / 2;
        painter.drawPixmap(x, y, originalPixmap.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        // Imposta la dimensione calcolata
        mediaImageLabel->setPixmap(background);
        mediaImageLabel->setFixedSize(availableWidth, availableHeight);

        mediaImageLabel->setPixmap(background);
    } 
}

void MainPage::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);

    int maxImageWidth = this->width() / 3;
    
    // Sottrai i margini per evitare overflow
    int groupBoxMargins = 5;
    int layoutMargins = previewLayout->contentsMargins().left() + previewLayout->contentsMargins().right();
    int totalMargins = groupBoxMargins + layoutMargins - 3; 
    
    int imageWidth = qMin(previewGroupBox->width() - totalMargins, maxImageWidth - totalMargins);
    int imageHeight = previewGroupBox->height() / 3; // Cambiato da /2 a /3
    
    // Assicurati che le dimensioni siano positive
    imageWidth = qMax(150, imageWidth);
    imageHeight = qMax(150, imageHeight);
    
    mediaImageLabel->setFixedSize(imageWidth, imageHeight); 

    updateImageSize();
    
    // AGGIUNGI QUESTA RIGA per aggiornare il troncamento quando la finestra viene ridimensionata
    updateTextTruncation();
}

void MainPage::onMediaSelected(QListWidgetItem *item) {
    if (!item) return;
    
    int row = mediaList->row(item);
    
    // Altrimenti mostra i pulsanti per la nuova riga
    showActionButtons(row);
    
    // CORREZIONE: Usa l'oggetto Media salvato nell'item invece dell'indice
    Media* media = item->data(Qt::UserRole).value<Media*>();
    
    // Aggiorna il pannello di anteprima
    if (media) {
        // Aggiorno l'anteprima con le informazioni del media selezionato
        mediaTitleLabel->setText(QString::fromStdString(media->getTitolo()));
        mediaTitleLabel->setStyleSheet("font-weight: bold; font-size: 20px;");
        mediaAuthorLabel->setText(QString::fromStdString(media->getAutore()));
        mediaAuthorLabel->setStyleSheet("font-size: 16px;");
        mediaYearLabel->setText(QString::number(media->getAnno()));
        mediaYearLabel->setStyleSheet("font-size: 14px;");

        // Aggiorno il rating con le stelline
        double rating = media->getRating();
        QString stars = QString("Rating: %1 %2").arg(QString("★").repeated(static_cast<int>(rating))).arg(QString::number(rating, 'f', 1));
        mediaRatingLabel->setText(stars);
        mediaRatingLabel->setStyleSheet("font-size: 14px;");

        // Aggiorno l'immagine - GESTIONE CROSS-PLATFORM
        QString imagePath = QString::fromStdString(media->getImmagine());
        
        QPixmap pixmap;
        
        // Usa QDir per gestire i percorsi in modo cross-platform
        QDir currentDir = QDir::current();
        
        // Prova diverse possibili ubicazioni
        QStringList possiblePaths = {
            currentDir.absoluteFilePath("Immagini/" + imagePath),           // ./Immagini/
            currentDir.absoluteFilePath("../Immagini/" + imagePath),        // ../Immagini/
            currentDir.absoluteFilePath("../../Immagini/" + imagePath),     // ../../Immagini/
            currentDir.absoluteFilePath("GUI/Immagini/" + imagePath),       // ./GUI/Immagini/
            currentDir.absoluteFilePath("../GUI/Immagini/" + imagePath)     // ../GUI/Immagini/
        };
        
        // Prova ogni percorso finché non ne trova uno che funziona
        for (const QString& path : possiblePaths) {
            if (QFile::exists(path)) {
                pixmap.load(path);
                if (!pixmap.isNull()) {
                    qDebug() << "Immagine caricata da:" << path;
                    break;
                }
            }
        }

        if (!pixmap.isNull()) {
            originalPixmap = pixmap;
            // Rimuovi il fixed size e usa minimum/maximum size invece
            mediaImageLabel->setMinimumSize(150, 150); // Dimensione minima
            mediaImageLabel->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX); // Dimensione massima illimitata
            updateImageSize(); // Aggiorna la dimensione dell'immagine
        } else {
            qDebug() << "Immagine non trovata:" << imagePath;
            mediaImageLabel->setText("Immagine non disponibile");
            mediaImageLabel->setStyleSheet(
                "border: 1px solid black;"
                "background-color: white;"
                "color: gray;"
                "padding: 5px;"
            );
        }

        // Abilisco i pulsanti
        borrowButton->setEnabled(true);
        returnButton->setEnabled(true);
        detailsButton->setEnabled(true);
        editMediaButton->setEnabled(true);
    }
}

void MainPage::showActionButtons(int row) {
    // Nascondi eventuali pulsanti precedentemente mostrati
    hideActionButtons();
    
    if (row < 0 || row >= mediaList->count()) return;
    
    // Memorizza la riga corrente per riferimenti futuri
    currentSelectedRow = row;
    
    // Calcola e imposta la posizione dei pulsanti
    updateButtonsPosition();
    
    buttonsContainer->show();
}

void MainPage::hideActionButtons() {
    buttonsContainer->hide();
    currentSelectedRow = -1; // Reset della riga selezionata
}

void MainPage::updateGenreComboBox() {
    genreComboBox->clear();
    genreComboBox->addItem("Qualsiasi genere");
    
    int currentType = mediaTypeComboBox->currentIndex();
    
    switch(currentType) {
        case 1: // Libro
            genreComboBox->addItems({"Avventura", "Biografia", "Biografia", "Fantasy", "Giallo", "Horror", "Romanzo", "Storico", "Saggio", "Thriller"});
            break;
        case 2: // Film
            genreComboBox->addItems({"Animazione", "Azione", "Avventura", "Commedia", 
                                    "Documentario", "Drammatico", "Fantasy", "Horror", "Romantico", "Sci-Fi", "Thriller"});
            break;
        case 3: // Vinile
            genreComboBox->addItems({"Alternative", "Blues", "Classica", "Country", "Elettronica", "Folk", "Hip Hop", 
                                    "Jazz", "Metal", "Pop", "Rock"});
            break;
        case 4: // Rivista
            genreComboBox->addItems({"Attualità", "Arte", "Cucina","Culturale", "Economia", "Intrattenimento", "Moda",  "Salute",
                                    "Scientifica", "Sport", "Tecnologia", "Viaggi"});
            break;
        case 5: // Gioco da tavolo
            genreComboBox->addItems({"Astratto", "Cooperativo", "Giochi di carte", "Giochi di miniature", 
                                    "Giochi di ruolo", "Party game", "Strategia"});
            break;
        default: // Qualsiasi o non specificato
            break;
    }
}

// -----------------------------
// --------------SLOTS----------
// -----------------------------
void MainPage::onMediaTypeChanged() {
    updateGenreComboBox();
    
    // Abilita la combobox dei generi solo se è stato selezionato un tipo di media specifico
    int selectedIndex = mediaTypeComboBox->currentIndex();
    
    if (selectedIndex == 0) { // "Qualsiasi" è selezionato
        genreComboBox->setEnabled(false);
        genreComboBox->setToolTip("Seleziona prima un tipo di media specifico");
    } else {
        genreComboBox->setEnabled(true);
        genreComboBox->setToolTip(""); // Rimuove il tooltip
    }
}

void MainPage::onBackButtonClicked() {
    // Torna alla pagina ChoicePage
    emit goToChoicePage(); // Emetto un segnale per notificare il cambio di pagina
}

void MainPage::onApplyFiltersClicked() {
    // Logica per applicare i filtri impostati
    string mediaType = mediaTypeComboBox->currentText().toStdString();
    if (mediaType == "Qualsiasi") {
        mediaType = ""; // Se l'utente ha selezionato "Qualsiasi", non applicare il filtro
    }

    string genre = genreComboBox->currentText().toStdString();
    if (genre == "Qualsiasi genere") {
        genre = ""; // Se l'utente ha selezionato "Qualsiasi genere", non applicare il filtro
    }

    double ratingMin = ratingMinLineEdit->text().toDouble();
    double ratingMax = ratingMaxLineEdit->text().toDouble();
    if (ratingMax == 0) {
        ratingMax = 5.0; // Se l'utente non ha inserito un valore, impostalo a 5.0
    }

    string language = languageLineEdit->text().toStdString();

    int minYear = minYearLineEdit->text().toInt();
    int maxYear = maxYearLineEdit->text().toInt();
    if (maxYear == 0) {
        maxYear = 3000; // Se l'utente non ha inserito un valore, impostalo a 3000
    }
    bool available = availableCheckBox->isChecked();

    vector<Media*> listaFiltrata = biblioteca->filtra("", mediaType, genre, ratingMin, ratingMax, available, language, minYear, maxYear);

    if (listaFiltrata.empty()) {
        QMessageBox::information(this, "Nessun risultato", "Nessun media trovato con i filtri selezionati.");
    } else{
        updateMediaList(listaFiltrata);
    }    
}

void MainPage::onClearFiltersClicked() {
    // Logica per eliminare i filtri impostati
    mediaTypeComboBox->setCurrentIndex(0);
    genreComboBox->setCurrentIndex(0);
    genreComboBox->setEnabled(false); // Disabilita nuovamente quando i filtri sono cancellati
    genreComboBox->setToolTip("Seleziona prima un tipo di media specifico");
    ratingMinLineEdit->clear();
    ratingMaxLineEdit->clear();
    languageLineEdit->clear();
    minYearLineEdit->clear();
    maxYearLineEdit->clear();
    availableCheckBox->setChecked(true); // Reset checkbox disponibilità a stato predefinito
    
    searchBar->clear(); //viene cancellato anche il contenuto della barra di ricerca

    // Ripristina la lista con tutti i media disponibili in biblioteca
    vector<Media*> listaCompleta = biblioteca->getListaMedia();
    updateMediaList(listaCompleta);
}

void MainPage::onAddMediaButtonClicked() {
    emit goToAddPage(); // Emetto un segnale per passare alla pagina di aggiunta media
}

void MainPage::onEditButtonClicked() {
    // Ottieni l'elemento correntemente selezionato
    QListWidgetItem* currentItem = mediaList->currentItem();
    if (!currentItem) return;
    
    Media* selectedMedia = currentItem->data(Qt::UserRole).value<Media*>();
    if (!selectedMedia){ 
        QMessageBox::warning(this, "Errore", "Media selezionato non valido.");
        return;
    }

    // Passa l'oggetto media alla pagina di modifica
    emit goToModifyPage(selectedMedia);
}

void MainPage::onDeleteButtonClicked() {
    QListWidgetItem* currentItem = mediaList->currentItem();
    if (!currentItem) {
        qDebug() << "Nessun elemento selezionato per la rimozione";
        return;
    }
    
    Media* selectedMedia = currentItem->data(Qt::UserRole).value<Media*>();
    if (!selectedMedia) {
        qDebug() << "Media non valido nell'elemento selezionato";
        return;
    }
    
    QString message = QString("Sei sicuro di voler rimuovere '%1' dalla biblioteca?")
                      .arg(QString::fromStdString(selectedMedia->getTitolo()));
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, 
        "Conferma eliminazione", 
        message, 
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        qDebug() << "=== INIZIO eliminazione media ===";
        qDebug() << "Eliminando:" << QString::fromStdString(selectedMedia->getTitolo());
        
        // STEP 1: Rimuovi dalla biblioteca (verifica che il metodo esista)
        if (biblioteca && biblioteca->rimuoviMedia(selectedMedia)) {
            qDebug() << "Media rimosso dalla biblioteca con successo";
            
            // STEP 2: Nascondi immediatamente i pulsanti per evitare azioni su un elemento inesistente
            hideActionButtons();
            
            // STEP 3: Reset dell'anteprima PRIMA di rimuovere dalla UI
            mediaTitleLabel->setText("");
            mediaAuthorLabel->setText("Seleziona un media per vedere i dettagli");
            mediaYearLabel->setText("");
            mediaRatingLabel->setText("");
            mediaImageLabel->setText("Nessuna immagine");
            mediaImageLabel->setStyleSheet(
                "border: 1px solid black;"
                "background-color: white;"
                "color: gray;"
                "padding: 5px;"
            );
            
            borrowButton->setEnabled(false);
            detailsButton->setEnabled(false);
            editMediaButton->setEnabled(false);
            
            // STEP 4: Reset della selezione corrente
            currentSelectedRow = -1;
            
            // STEP 5: Rimuovi dalla UI (l'elemento dalla lista)
            int row = mediaList->row(currentItem);
            QListWidgetItem* removedItem = mediaList->takeItem(row);
            if (removedItem) {
                delete removedItem; // Pulisci solo l'item UI, non il Media*
                qDebug() << "Elemento UI rimosso dalla lista";
            }
            
            // STEP 6: Aggiorna lo stato delle modifiche
            hasUnsavedChanges = true;
            emit unsavedChangesUpdated(true);
            updateSaveButtonsState();
            
            // STEP 7: Se la lista è vuota, assicurati che tutto sia pulito
            if (mediaList->count() == 0) {
                qDebug() << "Lista media ora vuota - reset completo UI";
                mediaList->clearSelection();
            }
            
            qDebug() << "=== FINE eliminazione media (successo) ===";
            
        } else {
            // ERRORE: La rimozione dalla biblioteca è fallita
            QMessageBox::warning(this, "Errore", 
                "Impossibile rimuovere il media dalla biblioteca. Riprova.");
            qDebug() << "ERRORE: Rimozione dalla biblioteca fallita";
        }
    } else {
        qDebug() << "Eliminazione annullata dall'utente";
    }
}

void MainPage::onBorrowButtonClicked() {
    // Ottieni l'elemento correntemente selezionato
    QListWidgetItem* currentItem = mediaList->currentItem();
    if (!currentItem) {
        return;
    }
    
    QVariant mediaData = currentItem->data(Qt::UserRole);
    if (!mediaData.isValid()) {
        return;
    }
    
    Media* selectedMedia = mediaData.value<Media*>();
    if (!selectedMedia) {
        return;
    }
    
    // Emetti il segnale per prendere in prestito il media
    emit borrowMedia(selectedMedia);
}

void MainPage::onReturnButtonClicked() {
    // Ottieni l'elemento correntemente selezionato
    QListWidgetItem* currentItem = mediaList->currentItem();
    if (!currentItem) {
        return;
    }
    
    QVariant mediaData = currentItem->data(Qt::UserRole);
    if (!mediaData.isValid()) {
        return;
    }
    
    Media* selectedMedia = mediaData.value<Media*>();
    if (!selectedMedia) {
        return;
    }
    
    // Emetti il segnale per restituire il media
    emit returnMedia(selectedMedia);
}

void MainPage::updateMediaList(vector<Media*> listaFiltrata) {
    mediaList->clear(); // Pulisci la lista esistente

    for (Media* media : listaFiltrata) {
        QString mediaInfo = media->mediaInfo(); // Ottieni le informazioni del media

        // Calcola la larghezza disponibile per il testo
        int listWidth = mediaList->width();
        int buttonSpace = 70; // Spazio riservato per i pulsanti (modifica + elimina)
        int iconSpace = 35; // Spazio per l'icona + margini
        int scrollBarSpace = 20; // Spazio per la scrollbar
        int availableWidth = listWidth - buttonSpace - iconSpace - scrollBarSpace;

        // Calcola la larghezza del testo con il font corrente
        QFontMetrics fontMetrics(mediaList->font());
        QString truncatedText = mediaInfo;
        
        // Se il testo è troppo lungo, troncalo con ellipsis
        if (fontMetrics.horizontalAdvance(mediaInfo) > availableWidth) {
            truncatedText = fontMetrics.elidedText(mediaInfo, Qt::ElideRight, availableWidth);
        }

        // Crea l'elemento della lista
        QListWidgetItem *item = new QListWidgetItem(mediaList);
        
        // Imposta il testo dell'elemento
        item->setText(truncatedText);
        
        item->setToolTip(mediaInfo);

        // Determina l'icona in base al tipo di media
        QString iconPath;
        
        if (dynamic_cast<Libro*>(media)) {
            iconPath = ":/Immagini/LogoLibro1.png";
        } 
        else if (dynamic_cast<Film*>(media)) {
            iconPath = ":/Immagini/LogoFilm1.png";
        } 
        else if (dynamic_cast<Vinile*>(media)) {
            iconPath = ":/Immagini/LogoVinile1.png";
        } 
        else if (dynamic_cast<Rivista*>(media)) {
            iconPath = ":/Immagini/LogoRivista1.png";
        } 
        else if (dynamic_cast<GiocoDaTavolo*>(media)) {
            iconPath = ":/Immagini/LogoGioco1.png";
        }
        
        // Imposta l'icona specifica per il tipo di media
        if (!iconPath.isEmpty()) {
            QIcon icon(iconPath);
            item->setIcon(icon);
        }
        
        // Imposta la dimensione dell'elemento per avere spazio sufficiente
        item->setSizeHint(QSize(mediaList->width(), 48));
        
        // IMPORTANTE: Salva l'oggetto media nei dati dell'elemento
        item->setData(Qt::UserRole, QVariant::fromValue(media));
    }
}

void MainPage::onNewMediaCreated(Media* newMedia) {
    if(biblioteca->esisteMedia(newMedia->getTitolo(), newMedia->getAnno(), newMedia->getGenere())){
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Media già esistente", 
            "Un media con lo stesso titolo, anno e genere esiste già nella biblioteca. Vuoi aumentare il numero di copie di questo media presenti in biblioteca?", 
            QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            Media* mediaEsistente = biblioteca->cercaMediaDaT_A_G(newMedia->getTitolo(), newMedia->getAnno(), newMedia->getGenere());
            mediaEsistente->setNumeroCopie(mediaEsistente->getNumeroCopie() + 1);
            delete newMedia;
            QMessageBox::information(this, "Salvataggio", "Numero copie del media aumentate con successo!");
        }
    } else {
        biblioteca->aggiungiMedia(newMedia);
        QMessageBox::information(this, "Salvataggio", "Media aggiunto con successo!");
        updateMediaList(biblioteca->getListaMedia());
        
        // Reset dell'anteprima
        mediaTitleLabel->setText("");
        mediaAuthorLabel->setText("Seleziona un media per vedere i dettagli");
        mediaYearLabel->setText("");
        mediaRatingLabel->setText("");
        mediaImageLabel->setText("Nessuna immagine");
        mediaImageLabel->setStyleSheet(
            "border: 1px solid black;"
            "background-color: white;"
            "color: gray;"
            "padding: 5px;"
        );
        
        borrowButton->setEnabled(false);
        detailsButton->setEnabled(false);
        editMediaButton->setEnabled(false);
    }

    hasUnsavedChanges = true;
    emit unsavedChangesUpdated(true);
    updateSaveButtonsState();
}

void MainPage::onMediaEdited() {
    updateMediaList(biblioteca->getListaMedia());
    
    // Reset anteprima
    mediaTitleLabel->setText("");
    mediaAuthorLabel->setText("Seleziona un media per vedere i dettagli");
    mediaYearLabel->setText("");
    mediaRatingLabel->setText("");
    mediaImageLabel->setText("Nessuna immagine");
    mediaImageLabel->setStyleSheet(
        "border: 1px solid black;"
        "background-color: white;"
        "color: gray;"
        "padding: 5px;"
    );
    
    borrowButton->setEnabled(false);
    detailsButton->setEnabled(false);
    editMediaButton->setEnabled(false);

    // AGGIUNGI QUESTE RIGHE CRUCIALI:
    hasUnsavedChanges = true;
    emit unsavedChangesUpdated(true);
    updateSaveButtonsState();
}

void MainPage::onDetailsButtonClicked() {
    QListWidgetItem* currentItem = mediaList->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "Errore", "Nessun elemento selezionato.");
        return;
    }
    
    QVariant mediaData = currentItem->data(Qt::UserRole);
    if (!mediaData.isValid()) {
        QMessageBox::warning(this, "Errore", "Il media selezionato non è valido.");
        return;
    }
    
    Media* selectedMedia = mediaData.value<Media*>();
    if (!selectedMedia) {
        QMessageBox::warning(this, "Errore", "Elemento selezionato non valido.");
        return;
    }
    
    emit goToDetailsPage(selectedMedia);
}

void MainPage::setCurrentFile(const QString& filePath) {
    currentFilePath = filePath;
    hasCurrentFile = !filePath.isEmpty();
}

void MainPage::updateSaveButtonsState() {
    // Trovo i pulsanti nella UI
    QPushButton* saveButton = findChild<QPushButton*>("saveButton");
    QPushButton* saveAsButton = findChild<QPushButton*>("saveAsButton");
    
    if (saveButton && saveAsButton) {
        if (isNewLibrary) {
            // Per nuove biblioteche: "Salva" disibalitato, "Salva come" abilitato
            saveButton->setEnabled(false);
            saveButton->setToolTip("Usa 'Salva come' per creare un nuovo file");
            saveAsButton->setEnabled(true);
        } else {
            saveButton->setEnabled(true);

            if (!hasCurrentFile) {
                saveButton->setToolTip("Nessun file corrente");
            } else if (!hasUnsavedChanges) {
                saveButton->setToolTip("Nessuna modifica da salvare");
            } else {
                saveButton->setToolTip("Salva nel file corrente");
            }
            
            saveAsButton->setEnabled(true);
        }
    }
}

void MainPage::onSaveButtonClicked() {
    if (isNewLibrary) {
        QMessageBox::information(this, "Nuova biblioteca", 
            "Per una nuova biblioteca, usa 'Salva come' per creare il file.");
        return;
    }

    if (!hasUnsavedChanges) {
        QMessageBox::information(this, "Nessuna modifica", "Non ci sono modifiche da salvare, la biblioteca è già aggiornata.");
        return;
    }
    
    if (hasCurrentFile && !currentFilePath.isEmpty()) {
        // Salva direttamente nel file corrente
        saveToFile(currentFilePath);
        
        // IMPORTANTE: Reset del flag modifiche dopo salvataggio riuscito
        hasUnsavedChanges = false;
        updateSaveButtonsState();
        
        // Notifica il MainWindow che non ci sono più modifiche non salvate
        emit unsavedChangesUpdated(false); 
    } else {
        // Se non c'è un file corrente, chiama "Salva come"
        onSaveAsButtonClicked();
    }
}

void MainPage::onSaveAsButtonClicked() {
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setWindowTitle("Salva biblioteca come");
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setNameFilter("File JSON (*.json);;File XML (*.xml)");
    fileDialog.setDefaultSuffix("json");
    
    // Se c'è un file corrente, impostalo come directory di partenza
    if (hasCurrentFile && !currentFilePath.isEmpty()) {
        QFileInfo fileInfo(currentFilePath);
        fileDialog.setDirectory(fileInfo.absolutePath());
        fileDialog.selectFile(fileInfo.fileName());
    } else {
        fileDialog.setDirectory(QDir::currentPath());
    }
    
    if (fileDialog.exec()) {
        QStringList selectedFiles = fileDialog.selectedFiles();
        if (!selectedFiles.isEmpty()) {
            QString filePath = selectedFiles.first();
            
            // Assicurati che il file abbia l'estensione corretta
            QString selectedFilter = fileDialog.selectedNameFilter();
            if (selectedFilter.contains("*.json") && !filePath.endsWith(".json", Qt::CaseInsensitive)) {
                filePath += ".json";
            } else if (selectedFilter.contains("*.xml") && !filePath.endsWith(".xml", Qt::CaseInsensitive)) {
                filePath += ".xml";
            }
            
            // Salva nel file selezionato
            saveToFile(filePath);
            
            // Aggiorna lo stato DOPO salvataggio riuscito
            setCurrentFile(filePath);
            isNewLibrary = false; // Non è più una nuova biblioteca
            hasUnsavedChanges = false; // RESET del flag modifiche
            updateSaveButtonsState();
            
            // Notifica il MainWindow che non ci sono più modifiche non salvate
            emit unsavedChangesUpdated(false);
        }
    }
}

void MainPage::onSearchTextChanged(const QString& searchText) {
    vector<Media*> listaCompleta = biblioteca->getListaMedia();
    
    if (searchText.isEmpty()) {
        updateMediaList(listaCompleta);
        return;
    }
    
    // Filtra i media in base al testo di ricerca
    vector<Media*> listaFiltrata;
    QString searchLower = searchText.toLower();
    
    for (Media* media : listaCompleta) {
        QString titolo = QString::fromStdString(media->getTitolo()).toLower();
        QString autore = QString::fromStdString(media->getAutore()).toLower();
        
        if (titolo.contains(searchLower) || autore.contains(searchLower)) {
            listaFiltrata.push_back(media);
        }
    }
    
    updateMediaList(listaFiltrata);
    
    mediaList->clearSelection();
    mediaTitleLabel->setText("");
    mediaAuthorLabel->setText("Seleziona un media per vedere i dettagli");
    mediaYearLabel->setText("");
    mediaRatingLabel->setText("");
    mediaImageLabel->setText("Nessuna immagine");
    mediaImageLabel->setStyleSheet(
        "border: 1px solid black;"
        "background-color: white;"
        "color: gray;"
        "padding: 5px;"
    );
    
    // Disabilito i pulsanti dell'anteprima
    borrowButton->setEnabled(false);
    detailsButton->setEnabled(false);
    editMediaButton->setEnabled(false);
    hideActionButtons();
}

void MainPage::onScrollChanged() {
    // Se ci sono pulsanti visibili e una riga selezionata, aggiorna la loro posizione
    if (buttonsContainer->isVisible() && currentSelectedRow >= 0) {
        updateButtonsPosition();
    }
}

void MainPage::updateButtonsPosition() {
    if (currentSelectedRow < 0 || currentSelectedRow >= mediaList->count()) {
        hideActionButtons();
        return;
    }
    
    // Ottieni l'item e il suo rect
    QListWidgetItem* item = mediaList->item(currentSelectedRow);
    if (!item) {
        hideActionButtons();
        return;
    }
    
    QRect rect = mediaList->visualItemRect(item);

    
    // Calcola la larghezza dei pulsanti
    int buttonWidth = buttonsContainer->sizeHint().width();
    int buttonHeight = buttonsContainer->sizeHint().height();
    
    // Ottieni il testo dell'elemento e calcola approssimativamente la larghezza del testo
    QString itemText = item->text();
    QFontMetrics fontMetrics(mediaList->font());
    int iconWidth = 27;
    int iconMargin = 8;
    int textWidth = fontMetrics.horizontalAdvance(itemText);
    int totalContentWidth = iconWidth + iconMargin + textWidth;

    // Posizione X: sempre dopo il contenuto + margine di sicurezza
    int marginAfterText = 15; // Margine fisso dopo il testo
    int xPosition = rect.left() + totalContentWidth + marginAfterText;
    
    // IMPORTANTE: Assicurati che i pulsanti non escano dal bordo destro
    int rightMargin = 10; // Margine dal bordo destro
    int maxXPosition = rect.right() - buttonWidth - rightMargin;
    
    // Se la posizione calcolata è troppo a destra, limita alla posizione massima
    if (xPosition > maxXPosition) {
        xPosition = maxXPosition;
    }
    
    // CORREZIONE: Se anche la posizione massima non è sufficiente, 
    // significa che il testo è troppo lungo per l'elemento
    if (xPosition < rect.left() + totalContentWidth + 5) {
        // In questo caso, posiziona i pulsanti al 75% della larghezza dell'elemento
        xPosition = rect.left() + (rect.width() * 0.75);
        
        // Verifica ancora che non escano dal bordo
        if (xPosition + buttonWidth > rect.right() - rightMargin) {
            xPosition = rect.right() - buttonWidth - rightMargin;
        }
    }
    
    // Centramento verticale
    int yPosition = rect.top() + (rect.height() - buttonHeight) / 2;
    
    buttonsContainer->setGeometry(xPosition, yPosition, buttonWidth, buttonHeight);
    buttonsContainer->show();
}

void MainPage::saveToFile(const QString& filePath) {
    bool success = false;
    QString errorMessage = "";
    
    try {
        if (filePath.endsWith(".json", Qt::CaseInsensitive)) {
            JsonIO jsonSaver;
            success = jsonSaver.salvaSuFile(*biblioteca, filePath.toStdString());
            if (!success) {
                errorMessage = "Errore durante il salvataggio del file JSON.";
            }
        } else if (filePath.endsWith(".xml", Qt::CaseInsensitive)) {
            XmlIO xmlSaver;
            success = xmlSaver.salvaSuFile(*biblioteca, filePath.toStdString());
            if (!success) {
                errorMessage = "Errore durante il salvataggio del file XML.";
            }
        } else {
            errorMessage = "Formato file non supportato. Utilizzare .json o .xml";
        }
    } catch (const std::exception& e) {
        errorMessage = QString("Errore durante il salvataggio: %1").arg(e.what());
        success = false;
    }
    
    if (success) {
        // Verifica che il file sia stato effettivamente salvato
        QFile file(filePath);
        if (file.exists() && file.size() > 0) {
            QMessageBox::information(this, "Salvataggio completato", 
                QString("La biblioteca è stata salvata con successo in:\n%1").arg(filePath));
            
            // IMPORTANTE: Reset delle modifiche non salvate SOLO se il salvataggio è riuscito
            hasUnsavedChanges = false;
            updateSaveButtonsState();
            
            emit unsavedChangesUpdated(false);
        } else {
            QMessageBox::warning(this, "Errore di salvataggio", 
                "Il file è stato creato ma potrebbe essere vuoto o corrotto.");
        }
    } else {
        QMessageBox::warning(this, "Errore di salvataggio", 
            errorMessage.isEmpty() ? 
            "Impossibile salvare la biblioteca nel file specificato." : 
            errorMessage);
    }
}

void MainPage::setLibraryInfo(bool isNew, bool hasChanges) {
    isNewLibrary = isNew;
    hasUnsavedChanges = hasChanges;
    updateSaveButtonsState();
}

// Aggiungi questo metodo per resettare le modifiche dopo il salvataggio
void MainPage::resetUnsavedChanges() {
    hasUnsavedChanges = false;
    emit unsavedChangesUpdated(false);
}

void MainPage::setHasUnsavedChanges(bool hasChanges) {
    hasUnsavedChanges = hasChanges;
    emit unsavedChangesUpdated(hasChanges);
    updateSaveButtonsState();
}

void MainPage::updateTextTruncation() {
    // Aggiorna il troncamento del testo per tutti gli elementi visibili
    for (int i = 0; i < mediaList->count(); ++i) {
        QListWidgetItem* item = mediaList->item(i);
        if (!item) continue;
        
        // Recupera il media associato
        Media* media = item->data(Qt::UserRole).value<Media*>();
        if (!media) continue;
        
        // Ricalcola il testo troncato
        QString fullText = media->mediaInfo();
        
        int listWidth = mediaList->width();
        int buttonSpace = 70;
        int iconSpace = 35;
        int scrollBarSpace = 20;
        int availableWidth = listWidth - buttonSpace - iconSpace - scrollBarSpace;
        
        QFontMetrics fontMetrics(mediaList->font());
        QString truncatedText = fullText;
        
        if (fontMetrics.horizontalAdvance(fullText) > availableWidth) {
            truncatedText = fontMetrics.elidedText(fullText, Qt::ElideRight, availableWidth);
        }
        
        // Aggiorna il testo dell'elemento
        item->setText(truncatedText);
    }
    
    // AGGIUNTA: Aggiorna la posizione dei pulsanti se c'è un elemento selezionato
    if (buttonsContainer->isVisible() && currentSelectedRow >= 0) {
        updateButtonsPosition();
    }
}