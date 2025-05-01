#include <QFile> 
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
#include <QDebug>

MainPage::MainPage(QWidget *parent) : QWidget(parent) {
    setupBiblioteca(); // Inizializza la biblioteca
    setupUI(); // Configura l'interfaccia utente

    // Inizializza i pulsanti per la lista ma li nasconde inizialmente
    buttonsContainer = new QWidget(mediaList);
    buttonsContainer->hide();
    
    QHBoxLayout* buttonsLayout = new QHBoxLayout(buttonsContainer);
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->setSpacing(6);
    
    // Crea i pulsanti
    listEditButton = new QPushButton();
    listEditButton->setToolTip("Modifica");
    listEditButton->setFixedSize(30, 30); // Dimensione circolare
    listEditButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(131, 187, 222);"
        "   color: black;"
        "   border: 2px solid rgb(92, 92, 93);"
        "   border-radius: 15px;" // Metà della larghezza per renderlo circolare
        "   font-size: 12px;"
        "   font-weight: bold;"
        "   text-align: center;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(87, 163, 210);"
        "}"
    );
    listEditButton->setIcon(QIcon(":/Immagini/matita.png"));
    
    listDeleteButton = new QPushButton();
    listDeleteButton->setToolTip("Rimuovi");
    listDeleteButton->setFixedSize(30, 30); // Dimensione circolare
    listDeleteButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(240, 107, 70);"
        "   color: black;"
        "   border: 2px solid rgb(92, 92, 93);"
        "   border-radius: 15px;" // Metà della larghezza per renderlo circolare
        "   font-size: 12px;"
        "   font-weight: bold;"
        "   text-align: center;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(250, 81, 34);"
        "}"
    );
    listDeleteButton->setIcon(QIcon(":/Immagini/cestino.png"));
    
    // Aggiungi i pulsanti al layout
    buttonsLayout->addWidget(listEditButton);
    buttonsLayout->addWidget(listDeleteButton);
    
    // Collega i segnali
    connect(listEditButton, &QPushButton::clicked, this, &MainPage::onEditButtonClicked);
    connect(listDeleteButton, &QPushButton::clicked, this, &MainPage::onDeleteButtonClicked);
    
    // Collega il cambio di selezione per nascondere i pulsanti
    connect(mediaList, &QListWidget::currentRowChanged, this, [this](int) { 
        hideActionButtons(); 
    });
}

void MainPage::setupBiblioteca() {
    string id = "VC";
    biblioteca = new Biblioteca(id); // Inizializza la biblioteca

    // Apri una finestra di dialogo per selezionare un file JSON o XML
    QFileDialog fileDialog(this);
    fileDialog.setWindowTitle("Seleziona un file Json o Xml per importare i dati");
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter("File supportati (*.json *.xml)");
    fileDialog.setViewMode(QFileDialog::Detail);
    
    QString filePath;
    bool success = false;

    // Se l'utente ha selezionato un file
    if (fileDialog.exec()) {
        QStringList selectedFiles = fileDialog.selectedFiles();
        if (!selectedFiles.isEmpty()) {
            filePath = selectedFiles.first();
            
            if (filePath.endsWith(".json", Qt::CaseInsensitive)) {
                JsonIO jsonLoader;
                success = jsonLoader.caricaDaFile(*biblioteca, filePath.toStdString());
            } else if (filePath.endsWith(".xml", Qt::CaseInsensitive)) {
                XmlIO xmlLoader;
                success = xmlLoader.caricaDaFile(*biblioteca, filePath.toStdString());
            } else {
                QMessageBox::warning(this, "Errore di caricamento", 
                                    "Formato file non supportato. Utilizzare un file .json o .xml.");
            }
        }
    } else {
        // L'utente ha annullato la selezione
        QMessageBox::information(this, "Informazione", 
                              "Nessun file selezionato. Verrà utilizzata una biblioteca vuota.");
    }

    if (!success && !filePath.isEmpty()) {
        QMessageBox::warning(this, "Errore di caricamento", 
                            "Impossibile caricare i dati dal file specificato.\n"
                            "Verrà utilizzata una biblioteca vuota.");
    } else if (success) {
        QMessageBox::information(this, "Caricamento completato", 
                                "I dati della biblioteca sono stati caricati con successo.");
    }
}

void MainPage::setupUI(){
    // ------------------------- Barra superiore ----------------------------
    backButton = new QPushButton("Indietro");
    addMediaButton = new QPushButton("Aggiungi Media");
    backButton->setMinimumSize(100, 30);
    addMediaButton->setMinimumSize(100, 30);

    // Tasto indietro
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
    connect(backButton, &QPushButton::clicked, this, &MainPage::onBackButtonClicked);
    connect(addMediaButton, &QPushButton::clicked, this, &MainPage::onAddMediaButtonClicked);

    topBarLayout = new QHBoxLayout();
    topBarLayout->addWidget(backButton, 1);
    topBarLayout->addWidget(addMediaButton, 5);


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
    clearFiltersButton = new QPushButton("Elimina filtri");

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

    // Separatore orizzontale
    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);

    filtersLayout = new QVBoxLayout();
    filtersLayout->addWidget(new QLabel("Tipo media:"));
    filtersLayout->addWidget(mediaTypeComboBox);

    // Separatore sottile dopo il filtro tipo media
    QFrame *separator1 = new QFrame();
    separator1->setFrameShape(QFrame::HLine);
    separator1->setFrameShadow(QFrame::Sunken);
    separator1->setMaximumHeight(1);
    filtersLayout->addWidget(separator1);

    filtersLayout->addWidget(new QLabel("Genere:")); 
    filtersLayout->addWidget(genreComboBox);

    // Separatore sottile dopo il filtro genere
    QFrame *separator2 = new QFrame();
    separator2->setFrameShape(QFrame::HLine);
    separator2->setFrameShadow(QFrame::Sunken);
    separator2->setMaximumHeight(1);
    filtersLayout->addWidget(separator2);

    filtersLayout->addWidget(new QLabel("Rating"));
    filtersLayout->addWidget(ratingMinLineEdit);
    filtersLayout->addWidget(ratingMaxLineEdit);

    // Separatore sottile dopo il filtro rating
    QFrame *separator3 = new QFrame();
    separator3->setFrameShape(QFrame::HLine);
    separator3->setFrameShadow(QFrame::Sunken);
    separator3->setMaximumHeight(1);
    filtersLayout->addWidget(separator3);

    filtersLayout->addWidget(new QLabel("Disponibilità:"));
    filtersLayout->addWidget(availableCheckBox);

    // Separatore sottile dopo il filtro disponibilità
    QFrame *separator4 = new QFrame();
    separator4->setFrameShape(QFrame::HLine);
    separator4->setFrameShadow(QFrame::Sunken);
    separator4->setMaximumHeight(1);
    filtersLayout->addWidget(separator4);

    filtersLayout->addWidget(new QLabel("Lingua:"));
    filtersLayout->addWidget(languageLineEdit);

    // Separatore sottile dopo il filtro lingua
    QFrame *separator5 = new QFrame();
    separator5->setFrameShape(QFrame::HLine);
    separator5->setFrameShadow(QFrame::Sunken);
    separator5->setMaximumHeight(1);
    filtersLayout->addWidget(separator5);

    filtersLayout->addWidget(new QLabel("Anno minimo:"));
    filtersLayout->addWidget(minYearLineEdit);

    // Separatore sottile dopo il filtro anno minimo
    QFrame *separator6 = new QFrame();
    separator6->setFrameShape(QFrame::HLine);
    separator6->setFrameShadow(QFrame::Sunken);
    separator6->setMaximumHeight(1);
    filtersLayout->addWidget(separator6);

    filtersLayout->addWidget(new QLabel("Anno massimo:"));
    filtersLayout->addWidget(maxYearLineEdit);

    QFrame *separator7 = new QFrame();
    separator7->setFrameShape(QFrame::HLine);
    separator7->setFrameShadow(QFrame::Sunken);
    separator7->setMaximumHeight(2);
    filtersLayout->addWidget(separator7);

    // Aggiunta dei pulsanti al layout contenitore
    filtersLayout->addWidget(applyFiltersButton);
    filtersLayout->addWidget(clearFiltersButton);

    filtersGroupBox = new QGroupBox("Filtri");
    filtersGroupBox->setLayout(filtersLayout);
    filtersGroupBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);


    // ------------------------- Barra di ricerca e lista media ------------------------
    searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Cerca per titolo...");
    searchBar->setStyleSheet("QLineEdit { background-color: rgb(255, 208, 0); color: black; border: 2px solid rgb(119, 114, 114); padding: 5px; border-radius: 4px; font-size: 12px; }");

    mediaList = new QListWidget();
    mediaList->setViewMode(QListView::ListMode); // Modalità lista (righe)
    mediaList->setResizeMode(QListView::Adjust); // Adatta le dimensioni
    mediaList->setMovement(QListView::Static); // Elementi non trascinabili
    mediaList->setSelectionMode(QAbstractItemView::SingleSelection); // Selezione singola
    mediaList->setMinimumWidth(300); // Imposta un'altezza minima per la lista

    vector<Media*> listaMedia = biblioteca->getListaMedia(); // Ottieni la lista dei media dalla biblioteca

    updateMediaList(listaMedia); // Popola la lista con i media

    mediaList->setFocusPolicy(Qt::NoFocus); // Disabilita il focus per la lista

    mediaList->setIconSize(QSize(27, 27)); // Imposta la dimensione dell'icona
    mediaList->setStyleSheet(
    "QListWidget { background-color:rgb(81, 125, 187); border: 2px solid rgb(119, 114, 114); border-radius: 4px; font-size: 14px; }"
    "QListWidget::item { border-bottom:3px solid #ddd; padding: 8px; padding-left: 4px; color: white; }"
    "QListWidget::item:hover { background-color:rgb(101, 123, 152); color: white;}"
    "QListWidget::item:selected { background-color:rgb(255, 208, 0); color: black; }"
    "QListWidget::item:focus { outline: none; }"
);

    // Collega la selezione
    connect(mediaList, &QListWidget::itemClicked, this, &MainPage::onMediaSelected);
    connect(applyFiltersButton, &QPushButton::clicked, this, &MainPage::onApplyFiltersClicked);
    connect(clearFiltersButton, &QPushButton::clicked, this, &MainPage::onClearFiltersClicked);

    centerLayout = new QVBoxLayout();
    centerLayout->addWidget(searchBar);
    centerLayout->addWidget(mediaList);


    // ------------------------------ Sezione destra ----------------------------------
    previewGroupBox = new QGroupBox("Anteprima");
    
    // Label per l'immagine del media
    mediaImageLabel = new QLabel();
    mediaImageLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    mediaImageLabel->setAlignment(Qt::AlignCenter);
    mediaImageLabel->setMinimumSize(100, 100);
    mediaImageLabel->setStyleSheet("border: 1px solid black; background-color: white; color: gray; font-size: 14px;");
    mediaImageLabel->setText("Nessuna immagine");

    // Label per le informazioni del media
    mediaTitleLabel = new QLabel();
    mediaAuthorLabel = new QLabel("Seleziona un media per vedere i dettagli");
    mediaYearLabel = new QLabel();
    mediaRatingLabel = new QLabel();

    // Pulsanti
    borrowButton = new QPushButton("Prendi in prestito");
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

    // Layout verticale per la sezione destra
    previewLayout = new QVBoxLayout();
    previewLayout->addWidget(mediaImageLabel);
    previewLayout->addWidget(mediaTitleLabel);
    previewLayout->addWidget(mediaAuthorLabel);
    previewLayout->addWidget(mediaYearLabel);
    previewLayout->addWidget(mediaRatingLabel);
    previewLayout->addStretch();
    previewLayout->addWidget(borrowButton);
    previewLayout->addWidget(detailsButton);
    previewLayout->addWidget(editMediaButton);

    previewGroupBox->setLayout(previewLayout);

    // Layout principale
    contentLayout = new QHBoxLayout();
    contentLayout->addWidget(filtersGroupBox, 2);
    contentLayout->addLayout(centerLayout, 4);
    contentLayout->addWidget(previewGroupBox, 3);

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topBarLayout);
    mainLayout->addLayout(contentLayout);

    setLayout(mainLayout);

    connect(detailsButton, &QPushButton::clicked, this, [this]() {
        QListWidgetItem* currentItem = mediaList->currentItem();
        if (!currentItem) return;
        
        Media* selectedMedia = currentItem->data(Qt::UserRole).value<Media*>();
        if (!selectedMedia) return;
        
        emit goToDetailsPage(selectedMedia);
    });
}

void MainPage::updateImageSize(){
    if (!originalPixmap.isNull()) {
        // Calcola la dimensione massima disponibile per l'immagine
        int maxImageWidth = this->width() / 3;
        int availableWidth = qMin(previewGroupBox->width(), maxImageWidth); 
        int availableHeight = previewGroupBox->height() / 2; // Metà altezza per l'immagine
        
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
    int imageWidth = qMin(previewGroupBox->width(), maxImageWidth);
    int imageHeight = previewGroupBox->height() / 2;
    
    mediaImageLabel->setFixedSize(imageWidth, imageHeight); 

    updateImageSize();
}

void MainPage::onMediaSelected(QListWidgetItem *item) {
    Media* selectedMedia = item->data(Qt::UserRole).value<Media*>();
    if (!selectedMedia) return;
    
    // Aggiorno l'anteprima con le informazioni del media selezionato
    mediaTitleLabel->setText(QString::fromStdString(selectedMedia->getTitolo()));
    mediaTitleLabel->setStyleSheet("font-weight: bold; font-size: 20px;");
    mediaAuthorLabel->setText(QString::fromStdString(selectedMedia->getAutore()));
    mediaAuthorLabel->setStyleSheet("font-size: 16px;");
    mediaYearLabel->setText(QString::number(selectedMedia->getAnno()));
    mediaYearLabel->setStyleSheet("font-size: 14px;");

    // Aggiorno il rating con le stelline
    double rating = selectedMedia->getRating();
    QString stars = QString("Rating: %1 %2").arg(QString("★").repeated(static_cast<int>(rating))).arg(QString::number(rating, 'f', 1));
    mediaRatingLabel->setText(stars);
    mediaRatingLabel->setStyleSheet("font-size: 14px;");

    // Aggiorno l'immagine
    QPixmap pixmap(QString::fromStdString(selectedMedia->getImmagine()));
    if (!pixmap.isNull()) {
        originalPixmap = pixmap;
        // Rimuovi il fixed size e usa minimum/maximum size invece
        mediaImageLabel->setMinimumSize(150, 150); // Dimensione minima
        mediaImageLabel->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX); // Dimensione massima illimitata
        updateImageSize(); // Aggiorna la dimensione dell'immagine
    } else {
        mediaImageLabel->setText("Immagine non disponibile");
        mediaImageLabel->setStyleSheet(
            "border: 1px solid black;"
            "background-color: white;"
            "color: gray;"
            "padding: 5px;"
        );
    }

    // Abilito i pulsanti
    borrowButton->setEnabled(true);
    detailsButton->setEnabled(true);
    editMediaButton->setEnabled(true);

    // Mostra i pulsanti di azione per la riga selezionata
    int row = mediaList->row(item);
    showActionButtons(row);
}

void MainPage::showActionButtons(int row) {
    // Nascondi eventuali pulsanti precedentemente mostrati
    hideActionButtons();
    
    if (row < 0 || row >= mediaList->count()) return;
    
    // Ottieni l'item e il suo rect
    QListWidgetItem* item = mediaList->item(row);
    QRect rect = mediaList->visualItemRect(item);
    
    // Calcola la larghezza dei pulsanti
    int buttonWidth = buttonsContainer->sizeHint().width();
    int buttonHeight = buttonsContainer->sizeHint().height();
    
    // Ottieni il testo dell'elemento e calcola approssimativamente la larghezza del testo
    QString itemText = item->text();
    QFontMetrics fontMetrics(mediaList->font());
    int textWidth = fontMetrics.horizontalAdvance(itemText) + 40; // Aggiungi margine per l'icona e spazio extra
    
    // Assicurati che la larghezza del testo non superi il 70% della larghezza dell'elemento
    int maxTextWidth = rect.width() * 0.7;
    if (textWidth > maxTextWidth) {
        textWidth = maxTextWidth;
    }
    
    // Posiziona i pulsanti a destra del testo, con un margine di sicurezza
    int xPosition = rect.left() + textWidth + 15; // 15px di margine dopo il testo
    
    // Se i pulsanti finissero fuori dal campo visibile, riposizionali
    if (xPosition + buttonWidth > rect.right()) {
        xPosition = rect.right() - buttonWidth - 5; // 5px di margine dal bordo destro
    }
    
    // Centramento verticale
    int yPosition = rect.top() + (rect.height() - buttonHeight) / 2;
    
    buttonsContainer->setGeometry(xPosition, yPosition, buttonWidth, buttonHeight);
    buttonsContainer->show();
    
    // Memorizza l'item corrente per riferimento futuro
    mediaList->setCurrentRow(row);
}

void MainPage::hideActionButtons() {
    buttonsContainer->hide();
}

void MainPage::onEditButtonClicked() {
    // Ottieni l'elemento correntemente selezionato
    QListWidgetItem* currentItem = mediaList->currentItem();
    if (!currentItem) return;
    
    Media* selectedMedia = currentItem->data(Qt::UserRole).value<Media*>();
    if (!selectedMedia) return;
    
    // Qui puoi implementare la logica per aprire la finestra di modifica
    QMessageBox::information(this, "Modifica Media", 
                            QString("Modifica di '%1' in fase di implementazione").arg(
                              QString::fromStdString(selectedMedia->getTitolo())));
}

void MainPage::onDeleteButtonClicked() {
    // Ottieni l'elemento correntemente selezionato
    QListWidgetItem* currentItem = mediaList->currentItem();
    if (!currentItem) return;
    
    Media* selectedMedia = currentItem->data(Qt::UserRole).value<Media*>();
    if (!selectedMedia) return;
    
    // Chiedi conferma prima di eliminare
    QString message = QString("Sei sicuro di voler rimuovere '%1' dalla biblioteca?").arg(QString::fromStdString(selectedMedia->getTitolo()));
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Conferma eliminazione", message, QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Rimuovi l'elemento dalla lista e elimina l'oggetto
        delete mediaList->takeItem(mediaList->row(currentItem));
        delete selectedMedia;
        
        // Nascondi i pulsanti di azione
        hideActionButtons();
        
        // Resetta l'anteprima
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
        
        // Disabilita i pulsanti dell'anteprima
        borrowButton->setEnabled(false);
        detailsButton->setEnabled(false);
        editMediaButton->setEnabled(false);
    }
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
}

void MainPage::onBackButtonClicked() {
    // Torna alla pagina LoginPage
    emit goToLoginPage(); // Emetto un segnale per notificare il cambio di pagina
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
    ratingMinLineEdit->clear();
    ratingMaxLineEdit->clear();
    languageLineEdit->clear();
    minYearLineEdit->clear();
    maxYearLineEdit->clear();
    qDebug() << "Filtri eliminati!";
}

void MainPage::onAddMediaButtonClicked() {
    emit goToAddPage(); // Emetto un segnale per passare alla pagina di aggiunta media
}

void MainPage::updateMediaList(vector<Media*> listaFiltrata){
    mediaList->clear(); // Pulisci la lista esistente

    for (Media* media : listaFiltrata) {
        QString mediaInfo = media->mediaInfo(); // Ottieni le informazioni del media

        // Crea l'elemento della lista
        QListWidgetItem *item = new QListWidgetItem(mediaInfo, mediaList);
        
        // Carica l'immagine del media
        QPixmap pixmap(QString::fromStdString(media->getImmagine()));
        if (!pixmap.isNull()) {
            // Ridimensiona l'immagine a una dimensione appropriata per un'icona (es: 32x32 pixel)
            QPixmap scaledPixmap = pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            
            // Imposta l'immagine ridimensionata come icona dell'elemento
            item->setIcon(QIcon(scaledPixmap));
            
            // Imposta la dimensione del testo in modo che ci sia spazio per l'icona
            item->setSizeHint(QSize(mediaList->width(), 40)); // Altezza un po' maggiore per accogliere l'icona
        }
        
        // Salva l'oggetto media nei dati dell'elemento
        item->setData(Qt::UserRole, QVariant::fromValue(media));
    }
}
