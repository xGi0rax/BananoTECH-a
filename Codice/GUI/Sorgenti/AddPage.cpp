#include "../Headers/AddPage.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSplitter>

AddPage::AddPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    showSelectionPage();
}

void AddPage::setupUI() {
    // Layout orizzontale principale
    QHBoxLayout *mainHLayout = new QHBoxLayout(this);
    mainHLayout->setContentsMargins(0, 0, 0, 0);
    mainHLayout->setSpacing(0);

    // Per dividere la pagine in barra laterale e area principale
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->setMinimumSize(300, 0);

    // Widget per la barra laterale
    QWidget *sidebarWidget = new QWidget();
    sidebarWidget->setObjectName("sidebarWidget");

    // Layout veticale per la barra laterale
    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebarWidget);
    sidebarLayout->setContentsMargins(10, 10, 10, 10);
    sidebarLayout->setSpacing(15);

    // 1. Pulsante indietro
    backButton = new QPushButton("Indietro");
    backButton->setMinimumSize(145, 30);
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
    connect(backButton, &QPushButton::clicked, this, &AddPage::onBackButtonClicked);
    sidebarLayout->addWidget(backButton, 0, Qt::AlignTop | Qt::AlignLeft);
      
    // 2. Sezione centrale per caricare l'immagine
    imagePreview = new QLabel("Seleziona un'immagine");
    imagePreview->setMinimumSize(220, 220);
    imagePreview->setMaximumSize(300, 300);
    imagePreview->setScaledContents(true);
    imagePreview->setAlignment(Qt::AlignCenter);
    imagePreview->setStyleSheet(
        "   border: 1px dashed #666666;"
        "   border-radius: 4px;"
    );

    uploadButton = new QPushButton("Carica");
    uploadButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(255, 208, 0);"
        "   color: black;"
        "   border: 2px solid rgb(119, 114, 114);"
        "   border-radius: 4px;"
        "   font-size: 15px;"
        "   padding: 8px 20px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(255, 170, 0);"
        "}"
    );
    connect(uploadButton, &QPushButton::clicked, this, &AddPage::onUploadButtonClicked);
    
    QVBoxLayout *imageLayout = new QVBoxLayout();
    imageLayout->setContentsMargins(20, 20, 20, 20);
    imageLayout->addWidget(imagePreview, 1);
    imageLayout->addWidget(uploadButton, 0, Qt::AlignCenter);

    sidebarLayout->addLayout(imageLayout, 1);

    // 3. Pulsante "salva media" in basso
    QPushButton *addButton = new QPushButton("SALVA MEDIA");
    addButton->setMinimumSize(200, 45);
    addButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 128, 0);"
        "   color: white;"
        "   border: 2px solid rgb(119, 114, 114);;"
        "   border-radius: 6px;"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(0, 100, 0);"
        "}"
    );
    connect(addButton, &QPushButton::clicked, this, &AddPage::onSaveMediaButtonClicked);
    sidebarLayout->addWidget(addButton, 0, Qt::AlignBottom | Qt::AlignCenter);

    // Aggiungo la barra laterale al divisore
    splitter->addWidget(sidebarWidget);

    // Widget per l'area principale
    mainContentStack = new QStackedWidget();    

    // Setup della pagina di selezione del media
    setupSelectionPage();
    mainContentStack->addWidget(selectionWidget);

    // Setup delle pagine di dettaglio dei media
    detailsStackedWidget = new QStackedWidget();
    setupDetailsPages();
    mainContentStack->addWidget(detailsStackedWidget);

    // Aggiungi l'area principale al divisore
    splitter->addWidget(mainContentStack);
    
    // Imposta la proporzione iniziale tra i due widget (1:2)
    splitter->setStretchFactor(0, 2);  // Sidebar (1/3)
    splitter->setStretchFactor(1, 3);  // Main area (2/3)
    
    // Aggiunge il divisore al layout principale
    mainHLayout->addWidget(splitter);
    
    setLayout(mainHLayout);
}

void AddPage::onUploadButtonClicked() {
    QString imagePath = QFileDialog::getOpenFileName(this, "Seleziona un'immagine", "", "Immagini (*.png *.jpg *.jpeg)");
    if (!imagePath.isEmpty()) {
        QPixmap pixmap(imagePath);
        if (!pixmap.isNull()) {
            imagePreview->setPixmap(pixmap);
            selectedImagePath = imagePath;
        } else {
            QMessageBox::warning(this, "Errore", "Impossibile caricare l'immagine selezionata.");
        }
    }
}

void AddPage::setupSelectionPage() {

    // Inizializzo il widget per la selezione del tipo di media
    selectionWidget = new QWidget(this);

    // Layout verticale per il contenuto del frame
    QVBoxLayout *selectionLayout = new QVBoxLayout(selectionWidget);
    selectionLayout->setContentsMargins(10, 10, 10, 10);
    selectionLayout->setSpacing(20);

    // Label con scritta
    QLabel *selectionLabel = new QLabel("Seleziona il tipo di media", selectionWidget);
    selectionLabel->setAlignment(Qt::AlignCenter);
    selectionLabel->setStyleSheet("background-color: #444444; font-size: 22px; font-weight: bold; color: white; margin-bottom: 10px; border: 2px solid black; border-radius: 8px; padding: 10px;");
    selectionLayout->addWidget(selectionLabel);

    // ButtonGroup di radio button per la selezione del tipo di media
    mediaTypeGroup = new QButtonGroup(selectionWidget);
    filmRadio = new QRadioButton("Film", selectionWidget);
    libroRadio = new QRadioButton("Libro", selectionWidget);
    vinileRadio = new QRadioButton("Vinile", selectionWidget);
    rivistaRadio = new QRadioButton("Rivista", selectionWidget);
    giocoRadio = new QRadioButton("Gioco da Tavolo", selectionWidget);

    // Stile per i radio button
    QString radioStyle = 
        "QRadioButton {"
        "   font-size: 18px;"
        "   color: white;"
        "   padding: 12px;"
        "   background-color: rgb(60, 85, 140);"
        "   border-radius: 8px;"
        "   margin: 3px 0px;"
        "}"
        "QRadioButton:hover {"
        "   background-color: rgb(80, 105, 160);"
        "}"
        "QRadioButton:checked {"
        "   background-color: rgb(255, 208, 0);"
        "   border: 2px solid rgb(119, 114, 114);"
        "   color: black;"
        "}"
        "QRadioButton::indicator {"
        "   width: 20px;"
        "   height: 20px;"
        "}";
    filmRadio->setStyleSheet(radioStyle);
    libroRadio->setStyleSheet(radioStyle);
    vinileRadio->setStyleSheet(radioStyle);
    rivistaRadio->setStyleSheet(radioStyle);
    giocoRadio->setStyleSheet(radioStyle);

    // Aggiungo i radio button al gruppo
    mediaTypeGroup->addButton(filmRadio, FILM);
    mediaTypeGroup->addButton(libroRadio, LIBRO);
    mediaTypeGroup->addButton(vinileRadio, VINILE);
    mediaTypeGroup->addButton(rivistaRadio, RIVISTA);
    mediaTypeGroup->addButton(giocoRadio, GIOCO_DA_TAVOLO);

    QVBoxLayout *radioLayout = new QVBoxLayout();
    radioLayout->addWidget(filmRadio);
    radioLayout->addWidget(libroRadio);
    radioLayout->addWidget(vinileRadio);
    radioLayout->addWidget(rivistaRadio);
    radioLayout->addWidget(giocoRadio);

    selectionLayout->addLayout(radioLayout);
    selectionLayout->addSpacing(15);

    // Pulsante Conferma
    confirmTypeButton = new QPushButton("Conferma", selectionWidget);
    confirmTypeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(255, 208, 0);"
        "   color: black;"
        "   border: 2px solid rgb(119, 114, 114);"
        "   border-radius: 6px;"
        "   font-size: 18px;"
        "   min-width: 150px;"
        "   min-height: 40px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(255, 170, 0);"
        "}"
    );
    connect(confirmTypeButton, &QPushButton::clicked, this, &AddPage::onConfirmTypeButtonClicked);

    selectionLayout->addWidget(confirmTypeButton, 0, Qt::AlignCenter);

    selectionLayout->addStretch(1);
    selectionLayout->insertStretch(0, 1);
}

void AddPage::setupDetailsPages() {
    // Crea widget per ogni tipo di media
    QWidget *filmWidget = new QWidget();
    QWidget *libroWidget = new QWidget();
    QWidget *vinileWidget = new QWidget();
    QWidget *rivistaWidget = new QWidget();
    QWidget *giocoWidget = new QWidget();
    
    // Setup delle pagine di dettaglio per ogni tipo di media
    setupFilmDetailsPage(filmWidget);
    setupLibroDetailsPage(libroWidget);
    setupVinileDetailsPage(vinileWidget);
    setupRivistaDetailsPage(rivistaWidget);
    setupGiocoDetailsPage(giocoWidget);
    
    // Aggiungi le pagine al widget stack
    detailsStackedWidget->addWidget(filmWidget);    // indice 0
    detailsStackedWidget->addWidget(libroWidget);   // indice 1
    detailsStackedWidget->addWidget(vinileWidget);  // indice 2
    detailsStackedWidget->addWidget(rivistaWidget); // indice 3
    detailsStackedWidget->addWidget(giocoWidget);   // indice 4
}

void AddPage::setupFilmDetailsPage(QWidget *container) {
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(20, 20, 20, 20);
    
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("background: transparent;");
    
    QWidget *scrollWidget = new QWidget();
    QFormLayout *formLayout = new QFormLayout(scrollWidget);
    formLayout->setSpacing(15);
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    formLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    
    QLabel *titleLabel = new QLabel("Dettagli Film", scrollWidget);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    formLayout->addRow(titleLabel);
    
    // Stile comune per le etichette
    QString labelStyle = "QLabel { font-size: 14px; }";
    
    // Stile comune per i campi di input
    QString inputStyle = "QLineEdit, QSpinBox, QComboBox { font-size: 14px; padding: 6px; min-height: 28px; }";

    // Campi comuni
    titleEdit = new QLineEdit(scrollWidget);
    titleEdit->setStyleSheet(inputStyle);
    titleEdit->setMinimumWidth(400);

    authorEdit = new QLineEdit(scrollWidget);
    authorEdit->setStyleSheet(inputStyle);

    genreComboBox = new QComboBox(scrollWidget);
    genreComboBox->addItems({"Animazione", "Azione", "Avventura", "Commedia", "Documentario", "Drammatico", "Fantasy", "Horror", "Romantico", "Sci-Fi", "Thriller", "Altro"});
    genreComboBox->setStyleSheet(inputStyle);

    yearEdit = new QSpinBox(scrollWidget);
    yearEdit->setRange(1880, 2100);
    yearEdit->setValue(2024);
    yearEdit->setStyleSheet(inputStyle);
    
    languageEdit = new QLineEdit(scrollWidget);
    languageEdit->setStyleSheet(inputStyle);
    
    ratingEdit = new QSpinBox(scrollWidget);
    ratingEdit->setRange(1.0, 5.0);
    ratingEdit->setStyleSheet(inputStyle);
    
    // Campi specifici per film
    durationFilmEdit = new QSpinBox(scrollWidget);
    durationFilmEdit->setRange(1, 999);
    durationFilmEdit->setSuffix(" min");
    durationFilmEdit->setStyleSheet(inputStyle);

    castEdit = new QLineEdit(scrollWidget);
    castEdit->setStyleSheet(inputStyle);
    castEdit->setPlaceholderText("(separati da virgola)");
    
    // Etichette con stile migliorato
    QLabel *titleLbl = new QLabel("Titolo:");
    titleLbl->setStyleSheet(labelStyle);
    QLabel *languageLbl = new QLabel("Lingua:");
    languageLbl->setStyleSheet(labelStyle);
    QLabel *authorLbl = new QLabel("Regista:");
    authorLbl->setStyleSheet(labelStyle);
    QLabel *yearLbl = new QLabel("Anno:");
    yearLbl->setStyleSheet(labelStyle);
    QLabel *durationLbl = new QLabel("Durata:");
    durationLbl->setStyleSheet(labelStyle);
    QLabel *genreLbl = new QLabel("Genere:");
    genreLbl->setStyleSheet(labelStyle);
    QLabel *castLbl = new QLabel("Attori:");
    castLbl->setStyleSheet(labelStyle);
    QLabel *ratingLbl = new QLabel("Valutazione:");
    ratingLbl->setStyleSheet(labelStyle);

    // Aggiungi i campi al form
    formLayout->addRow(titleLbl, titleEdit);
    formLayout->addRow(authorLbl, authorEdit);
    formLayout->addRow(genreLbl, genreComboBox);
    formLayout->addRow(yearLbl, yearEdit);
    formLayout->addRow(languageLbl, languageEdit);
    formLayout->addRow(durationLbl, durationFilmEdit);
    formLayout->addRow(castLbl, castEdit);
    formLayout->addRow(ratingLbl, ratingEdit);
    
    // Aggiungo spazio vuoto in fondo
    formLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    
    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea, 1);
    
    // Pulsante Annulla
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    cancelButton = new QPushButton("Annulla");
    cancelButton->setMinimumSize(150, 45);
        
    cancelButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(200, 0, 0);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "   padding: 8px 16px;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(150, 0, 0);"
        "}"
    );
    
    connect(cancelButton, &QPushButton::clicked, this, &AddPage::onCancelButtonClicked);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();
    
    QVBoxLayout *buttonContainerLayout = new QVBoxLayout();
    buttonContainerLayout->addLayout(buttonLayout);
    buttonContainerLayout->addSpacing(10);
    
    layout->addLayout(buttonContainerLayout); // Aggiungi il layout dei pulsanti in basso
}

void AddPage::setupLibroDetailsPage(QWidget *container) {
    QVBoxLayout *layout = new QVBoxLayout(container);layout->setContentsMargins(20, 20, 20, 20);
    
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("background: transparent;");
    
    QWidget *scrollWidget = new QWidget();
    QFormLayout *formLayout = new QFormLayout(scrollWidget);
    formLayout->setSpacing(15);
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    formLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    
    QLabel *titleLabel = new QLabel("Dettagli Libro", scrollWidget);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    formLayout->addRow(titleLabel);
    
    // Stile comune per le etichette
    QString labelStyle = "QLabel { font-size: 14px; }";
    
    // Stile comune per i campi di input
    QString inputStyle = "QLineEdit, QSpinBox, QComboBox { font-size: 14px; padding: 6px; min-height: 28px; }";

    // Campi comuni
    titleEdit = new QLineEdit(scrollWidget);
    titleEdit->setStyleSheet(inputStyle);
    titleEdit->setMinimumWidth(400);

    authorEdit = new QLineEdit(scrollWidget);
    authorEdit->setStyleSheet(inputStyle);

    genreComboBox = new QComboBox(scrollWidget);
    genreComboBox->addItems({"Avventura", "Biografia", "Fantasy" "Giallo", "Horror", "Romanzo", "Storico", "Saggio", "Thriller", "Altro"});
    genreComboBox->setStyleSheet(inputStyle);

    yearEdit = new QSpinBox(scrollWidget);
    yearEdit->setRange(1880, 2100);
    yearEdit->setValue(2024);
    yearEdit->setStyleSheet(inputStyle);
    
    languageEdit = new QLineEdit(scrollWidget);
    languageEdit->setStyleSheet(inputStyle);
    
    ratingEdit = new QSpinBox(scrollWidget);
    ratingEdit->setRange(1.0, 5.0);
    ratingEdit->setStyleSheet(inputStyle);
    
    // Campi specifici per libro
    isbnEdit = new QLineEdit(scrollWidget);
    isbnEdit->setStyleSheet(inputStyle);

    editorLibroEdit = new QLineEdit(scrollWidget);
    editorLibroEdit->setStyleSheet(inputStyle);

    pagesLibroEdit = new QSpinBox(scrollWidget);
    pagesLibroEdit->setRange(1, 9999);
    pagesLibroEdit->setStyleSheet(inputStyle);
    
    // Etichette con stile migliorato
    QLabel *titleLbl = new QLabel("Titolo:");
    titleLbl->setStyleSheet(labelStyle);
    QLabel *authorLbl = new QLabel("Autore:");
    authorLbl->setStyleSheet(labelStyle);
    QLabel *genreLbl = new QLabel("Genere:");
    genreLbl->setStyleSheet(labelStyle);
    QLabel *yearLbl = new QLabel("Anno:");
    yearLbl->setStyleSheet(labelStyle);
    QLabel *languageLbl = new QLabel("Lingua:");
    languageLbl->setStyleSheet(labelStyle);
    QLabel *isbnLbl = new QLabel("ISBN:");
    isbnLbl->setStyleSheet(labelStyle);
    QLabel *editorLbl = new QLabel("Editore:");
    editorLbl->setStyleSheet(labelStyle);
    QLabel *pagesLbl = new QLabel("Pagine:");
    pagesLbl->setStyleSheet(labelStyle);
    QLabel *ratingLbl = new QLabel("Valutazione:");
    ratingLbl->setStyleSheet(labelStyle);

    // Aggiungi i campi al form
    formLayout->addRow(titleLbl, titleEdit);
    formLayout->addRow(authorLbl, authorEdit);
    formLayout->addRow(genreLbl, genreComboBox);
    formLayout->addRow(yearLbl, yearEdit);
    formLayout->addRow(languageLbl, languageEdit);
    formLayout->addRow(isbnLbl, isbnEdit);
    formLayout->addRow(editorLbl, editorLibroEdit);
    formLayout->addRow(pagesLbl, pagesLibroEdit);
    formLayout->addRow(ratingLbl, ratingEdit);

    // Aggiungo spazio vuoto in fondo
    formLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    
    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea, 1);
    
    // Pulsante Annulla
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    cancelButton = new QPushButton("Annulla");
    cancelButton->setMinimumSize(150, 45);
    
    cancelButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(200, 0, 0);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "   padding: 8px 16px;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(150, 0, 0);"
        "}"
    );
    
    connect(cancelButton, &QPushButton::clicked, this, &AddPage::onCancelButtonClicked);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();
    
    QVBoxLayout *buttonContainerLayout = new QVBoxLayout();
    buttonContainerLayout->addLayout(buttonLayout);
    buttonContainerLayout->addSpacing(10);

    layout->addLayout(buttonContainerLayout);
}

void AddPage::setupVinileDetailsPage(QWidget *container) {
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(20, 20, 20, 30);
    
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("background: transparent;");
    
    QWidget *scrollWidget = new QWidget();
    QFormLayout *formLayout = new QFormLayout(scrollWidget);
    formLayout->setSpacing(15);
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    formLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    
    QLabel *titleLabel = new QLabel("Dettagli Vinile", scrollWidget);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    formLayout->addRow(titleLabel);
    
    // Stile comune per le etichette
    QString labelStyle = "QLabel { font-size: 14px; }";
    
    // Stile comune per i campi di input
    QString inputStyle = "QLineEdit, QSpinBox, QComboBox { font-size: 14px; padding: 6px; min-height: 28px; }";

    // Campi comuni
    titleEdit = new QLineEdit(scrollWidget);
    titleEdit->setStyleSheet(inputStyle);
    titleEdit->setMinimumWidth(400);

    authorEdit = new QLineEdit(scrollWidget);
    authorEdit->setStyleSheet(inputStyle);

    genreComboBox = new QComboBox(scrollWidget);
    genreComboBox->addItems({"Alternative", "Blues", "Classica","Country", "Elettronica", "Folk", "Hip Hop", "Jazz", "Metal", "Pop", "Rock", "Altro"});
    genreComboBox->setStyleSheet(inputStyle);

    yearEdit = new QSpinBox(scrollWidget);
    yearEdit->setRange(1880, 2100);
    yearEdit->setValue(2024);
    yearEdit->setStyleSheet(inputStyle);
    
    languageEdit = new QLineEdit(scrollWidget);
    languageEdit->setStyleSheet(inputStyle);
    
    ratingEdit = new QSpinBox(scrollWidget);
    ratingEdit->setRange(1.0, 5.0);
    ratingEdit->setStyleSheet(inputStyle);
    
    // Campi specifici per vinile
    trackCountEdit = new QSpinBox(scrollWidget);
    trackCountEdit->setRange(1, 99);
    trackCountEdit->setStyleSheet(inputStyle);

    durationVinileEdit = new QSpinBox(scrollWidget);
    durationVinileEdit->setRange(1, 999);
    durationVinileEdit->setSuffix(" min");
    durationVinileEdit->setStyleSheet(inputStyle);
    
    // Etichette con stile migliorato
    QLabel *titleLbl = new QLabel("Titolo album:");
    titleLbl->setStyleSheet(labelStyle);
    QLabel *authorLbl = new QLabel("Artista o gruppo:");
    authorLbl->setStyleSheet(labelStyle);
    QLabel *genreLbl = new QLabel("Genere:");
    genreLbl->setStyleSheet(labelStyle);
    QLabel *yearLbl = new QLabel("Anno:");
    yearLbl->setStyleSheet(labelStyle);
    QLabel *languageLbl = new QLabel("Lingua:");
    languageLbl->setStyleSheet(labelStyle);
    QLabel *trackCountLbl = new QLabel("Numero Tracce:");
    trackCountLbl->setStyleSheet(labelStyle);
    QLabel *durationLbl = new QLabel("Durata:");
    durationLbl->setStyleSheet(labelStyle);
    QLabel *ratingLbl = new QLabel("Valutazione:");
    ratingLbl->setStyleSheet(labelStyle);

    // Aggiungi i campi al form
    formLayout->addRow(titleLbl, titleEdit);
    formLayout->addRow(authorLbl, authorEdit);
    formLayout->addRow(genreLbl, genreComboBox);
    formLayout->addRow(yearLbl, yearEdit);
    formLayout->addRow(languageLbl, languageEdit);
    formLayout->addRow(trackCountLbl, trackCountEdit);
    formLayout->addRow(durationLbl, durationVinileEdit);
    formLayout->addRow(ratingLbl, ratingEdit);
    
    // Aggiungo spazio vuoto in fondo
    formLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea, 1);
    
    // Pulsante Annulla
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    cancelButton = new QPushButton("Annulla");
    cancelButton->setMinimumSize(150, 45);
    
    cancelButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(200, 0, 0);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "   padding: 8px 16px;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(150, 0, 0);"
        "}"
    );
    
    connect(cancelButton, &QPushButton::clicked, this, &AddPage::onCancelButtonClicked);

    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();
    
    QVBoxLayout *buttonContainerLayout = new QVBoxLayout();
    buttonContainerLayout->addLayout(buttonLayout);
    buttonContainerLayout->addSpacing(10);
    
    layout->addLayout(buttonContainerLayout);
}

void AddPage::setupRivistaDetailsPage(QWidget *container) {
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(20, 20, 20, 30);
    
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("background: transparent;");
    
    QWidget *scrollWidget = new QWidget();
    QFormLayout *formLayout = new QFormLayout(scrollWidget);
    formLayout->setSpacing(15);
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    formLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    
    QLabel *titleLabel = new QLabel("Dettagli Rivista", scrollWidget);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    formLayout->addRow(titleLabel);
    
    // Stile comune per le etichette
    QString labelStyle = "QLabel { font-size: 14px; }";
    
    // Stile comune per i campi di input
    QString inputStyle = "QLineEdit, QSpinBox, QComboBox { font-size: 14px; padding: 6px; min-height: 28px; }";

    // Campi comuni
    titleEdit = new QLineEdit(scrollWidget);
    titleEdit->setStyleSheet(inputStyle);
    titleEdit->setMinimumWidth(400);

    authorEdit = new QLineEdit(scrollWidget);
    authorEdit->setStyleSheet(inputStyle);

    genreComboBox = new QComboBox(scrollWidget);
    genreComboBox->addItems({"Attualità", "Arte", "Cucina", "Culturale","Economia", "Intrattenimento", "Moda", "Salute", "Scientifica", "Sport", "Tecnologia", "Viaggi", "Altro"});
    genreComboBox->setStyleSheet(inputStyle);

    yearEdit = new QSpinBox(scrollWidget);
    yearEdit->setRange(1880, 2100);
    yearEdit->setValue(2024);
    yearEdit->setStyleSheet(inputStyle);
    
    languageEdit = new QLineEdit(scrollWidget);
    languageEdit->setStyleSheet(inputStyle);
    
    ratingEdit = new QSpinBox(scrollWidget);
    ratingEdit->setRange(1.0, 5.0);
    ratingEdit->setStyleSheet(inputStyle);
    
    // Campi specifici per rivista
    editorRivistaEdit = new QLineEdit(scrollWidget);
    editorRivistaEdit->setStyleSheet(inputStyle);

    pagesRivistaEdit = new QSpinBox(scrollWidget);
    pagesRivistaEdit->setRange(1, 9999);
    pagesRivistaEdit->setStyleSheet(inputStyle);

    publicationDateEdit = new QDateEdit(scrollWidget);
    publicationDateEdit->setDisplayFormat("dd/MM/yyyy");
    publicationDateEdit->setStyleSheet(inputStyle);
    
    periodicityComboBox = new QComboBox(scrollWidget);
    periodicityComboBox->addItems({"Settimanale", "Mensile", "Trimestrale", "Semestrale", "Annuale"});
    periodicityComboBox->setStyleSheet(inputStyle);
    
    // Etichette con stile migliorato
    QLabel *titleLbl = new QLabel("Titolo:");
    titleLbl->setStyleSheet(labelStyle);
    QLabel *authorLbl = new QLabel("Autore:");
    authorLbl->setStyleSheet(labelStyle);
    QLabel *genreLbl = new QLabel("Genere:");
    genreLbl->setStyleSheet(labelStyle);
    QLabel *yearLbl = new QLabel("Anno:");
    yearLbl->setStyleSheet(labelStyle);
    QLabel *languageLbl = new QLabel("Lingua:");
    languageLbl->setStyleSheet(labelStyle);
    QLabel *editorLbl = new QLabel("Editore:");
    editorLbl->setStyleSheet(labelStyle);
    QLabel *pagesLbl = new QLabel("Pagine:");
    pagesLbl->setStyleSheet(labelStyle);
    QLabel *publicationDateLbl = new QLabel("Pubblicazione:");
    publicationDateLbl->setStyleSheet(labelStyle);
    QLabel *periodicityLbl = new QLabel("Periodicità:");
    periodicityLbl->setStyleSheet(labelStyle);
    QLabel *ratingLbl = new QLabel("Valutazione:");
    ratingLbl->setStyleSheet(labelStyle);

    // Aggiungi i campi al form
    formLayout->addRow(titleLbl, titleEdit);
    formLayout->addRow(authorLbl, authorEdit);
    formLayout->addRow(genreLbl, genreComboBox);
    formLayout->addRow(yearLbl, yearEdit);
    formLayout->addRow(languageLbl, languageEdit);
    formLayout->addRow(editorLbl, editorRivistaEdit);
    formLayout->addRow(pagesLbl, pagesRivistaEdit);
    formLayout->addRow(publicationDateLbl, publicationDateEdit);
    formLayout->addRow(periodicityLbl, periodicityComboBox);
    formLayout->addRow(ratingLbl, ratingEdit);  
    
    // Aggiungo spazio vuoto in fondo
    formLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea, 1);
    
    // Pulsante Annulla
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    cancelButton = new QPushButton("Annulla");
    cancelButton->setMinimumSize(150, 45);
    
    cancelButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(200, 0, 0);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "   padding: 8px 16px;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(150, 0, 0);"
        "}"
    );
    
    connect(cancelButton, &QPushButton::clicked, this, &AddPage::onCancelButtonClicked);

    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();
    
    QVBoxLayout *buttonContainerLayout = new QVBoxLayout();
    buttonContainerLayout->addLayout(buttonLayout);
    buttonContainerLayout->addSpacing(10);
    
    layout->addLayout(buttonContainerLayout);
}

void AddPage::setupGiocoDetailsPage(QWidget *container) {
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(20, 20, 20, 30);
    
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("background: transparent;");
    
    QWidget *scrollWidget = new QWidget();
    QFormLayout *formLayout = new QFormLayout(scrollWidget);
    formLayout->setSpacing(15);
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    formLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    
    QLabel *titleLabel = new QLabel("Dettagli Gioco da Tavolo", scrollWidget);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    formLayout->addRow(titleLabel);
    
    // Stile comune per le etichette
    QString labelStyle = "QLabel { font-size: 14px; }";
    
    // Stile comune per i campi di input
    QString inputStyle = "QLineEdit, QSpinBox, QComboBox { font-size: 14px; padding: 6px; min-height: 28px; }";

    // Campi comuni
    titleEdit = new QLineEdit(scrollWidget);
    titleEdit->setStyleSheet(inputStyle);
    titleEdit->setMinimumWidth(400);

    authorEdit = new QLineEdit(scrollWidget);
    authorEdit->setStyleSheet(inputStyle);

    genreComboBox = new QComboBox(scrollWidget);
    genreComboBox->addItems({"Avventura", "Carte", "Cooperativo", "Deduzione", "Economico", "Fantasy", "Guerra", "Party Game", "Strategia", "Altro"});
    genreComboBox->setStyleSheet(inputStyle);

    yearEdit = new QSpinBox(scrollWidget);
    yearEdit->setRange(1880, 2100);
    yearEdit->setValue(2024);
    yearEdit->setStyleSheet(inputStyle);
    
    languageEdit = new QLineEdit(scrollWidget);
    languageEdit->setStyleSheet(inputStyle);
    
    ratingEdit = new QSpinBox(scrollWidget);
    ratingEdit->setRange(1.0, 5.0);
    ratingEdit->setStyleSheet(inputStyle);
    
    
    // Campi specifici per gioco da tavolo
    maxPlayersEdit = new QSpinBox(scrollWidget);
    maxPlayersEdit->setRange(1, 99);
    maxPlayersEdit->setStyleSheet(inputStyle);

    playTimeEdit = new QSpinBox(scrollWidget);
    playTimeEdit->setRange(1, 999);
    playTimeEdit->setSuffix(" min");
    playTimeEdit->setStyleSheet(inputStyle);
    
    minAgeEdit = new QSpinBox(scrollWidget);
    minAgeEdit->setRange(1, 99);
    minAgeEdit->setSuffix(" anni");
    minAgeEdit->setStyleSheet(inputStyle);
    
    editorGiocoEdit = new QLineEdit(scrollWidget);
    editorGiocoEdit->setStyleSheet(inputStyle);
    
    // Etichette con stile migliorato
    QLabel *titleLbl = new QLabel("Titolo:");
    titleLbl->setStyleSheet(labelStyle);
    QLabel *authorLbl = new QLabel("Autore:");
    authorLbl->setStyleSheet(labelStyle);
    QLabel *genreLbl = new QLabel("Genere:");
    genreLbl->setStyleSheet(labelStyle);
    QLabel *yearLbl = new QLabel("Anno:");
    yearLbl->setStyleSheet(labelStyle);
    QLabel *languageLbl = new QLabel("Lingua:");
    languageLbl->setStyleSheet(labelStyle);
    QLabel *maxPlayersLbl = new QLabel("Numero Giocatori:");
    maxPlayersLbl->setStyleSheet(labelStyle);
    QLabel *durationLbl = new QLabel("Durata:");
    durationLbl->setStyleSheet(labelStyle);
    QLabel *minAgeLbl = new QLabel("Età Minima:");
    minAgeLbl->setStyleSheet(labelStyle);
    QLabel *editorLbl = new QLabel("Editore:");
    editorLbl->setStyleSheet(labelStyle); 
    QLabel *ratingLbl = new QLabel("Valutazione:");
    ratingLbl->setStyleSheet(labelStyle);

    // Aggiungi i campi al form
    formLayout->addRow(titleLbl, titleEdit);
    formLayout->addRow(authorLbl, authorEdit);
    formLayout->addRow(genreLbl, genreComboBox);
    formLayout->addRow(yearLbl, yearEdit);
    formLayout->addRow(languageLbl, languageEdit);
    formLayout->addRow(maxPlayersLbl, maxPlayersEdit);
    formLayout->addRow(durationLbl, playTimeEdit);
    formLayout->addRow(minAgeLbl, minAgeEdit);
    formLayout->addRow(editorLbl, editorGiocoEdit);
    formLayout->addRow(ratingLbl, ratingEdit);    
    
    // Aggiungo spazio vuoto in fondo
    formLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea, 1);
    
    // Pulsante Annulla
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    cancelButton = new QPushButton("Annulla");
    cancelButton->setMinimumSize(150, 45);
    
    cancelButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(200, 0, 0);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "   padding: 8px 16px;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(150, 0, 0);"
        "}"
    );
    
    connect(cancelButton, &QPushButton::clicked, this, &AddPage::onCancelButtonClicked);

    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();
    
    QVBoxLayout *buttonContainerLayout = new QVBoxLayout();
    buttonContainerLayout->addLayout(buttonLayout);
    buttonContainerLayout->addSpacing(10);
    
    layout->addLayout(buttonContainerLayout);
}

void AddPage::showSelectionPage() {
    mainContentStack->setCurrentWidget(selectionWidget);
}

void AddPage::showDetailsPage(MediaType type) {
    detailsStackedWidget->setCurrentIndex(static_cast<int>(type));
    mainContentStack->setCurrentWidget(detailsStackedWidget);
}

void AddPage::onBackButtonClicked() {
    emit goBackToMainPage();
}

void AddPage::onConfirmTypeButtonClicked() {
    // Controlla quale tipo di media è stato selezionato
    int selectedId = mediaTypeGroup->checkedId();
    showDetailsPage(static_cast<MediaType>(selectedId));
}

void AddPage::onSaveMediaButtonClicked() {
    // Controllo base che i campi principali non siano vuoti
    if (titleEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Campo obbligatorio", "Il titolo è obbligatorio");
        return;
    }
    
    // Qui potresti creare l'istanza specifica di media (Film, Libro, etc.)
    // e salvarla nel sistema
    
    QMessageBox::information(this, "Salvataggio", "Media salvato con successo!");
    
    // Dopo il salvataggio, torna alla pagina principale
    emit goBackToMainPage();
}

void AddPage::onCancelButtonClicked() {
    // Se siamo nella pagina di dettaglio, torna alla pagina di selezione
    if (detailsStackedWidget->isVisible()) {
        showSelectionPage();
    } else {
        // Altrimenti torna alla pagina principale
        emit goBackToMainPage();
    }
}

void AddPage::onMediaTypeChanged(int index) {
    Q_UNUSED(index);
    // Aggiorna i generi disponibili in base al tipo di media
    // (Questa funzione può essere utilizzata se decidi di cambiare 
    // dinamicamente il tipo di media in fase di editing)
}