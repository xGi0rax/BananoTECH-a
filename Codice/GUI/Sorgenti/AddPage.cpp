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
    mainContentStack->setObjectName("mainContentStack");
    mainContentStack->setStyleSheet("QStackedWidget#mainContentStack { background-color: rgb(240, 240, 245); }");
    

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
    
    // NON aggiungere detailsStackedWidget a mainLayout qui
    // Sarà aggiunto dinamicamente in showDetailsPage()
}

void AddPage::setupFilmDetailsPage(QWidget *container) {
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
    
    QLabel *titleLabel = new QLabel("Dettagli Film", scrollWidget);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    formLayout->addRow(titleLabel);
    
     // Stile comune per le etichette
     QString labelStyle = "QLabel { font-size: 16px; }"; // Testo più grande
    
     // Stile comune per i campi di input
     QString inputStyle = "QLineEdit, QSpinBox, QComboBox { font-size: 16px; padding: 8px; min-height: 30px; }"; // Input più grandi 

    // Campi comuni
    titleEdit = new QLineEdit(scrollWidget);
    titleEdit->setStyleSheet(inputStyle);
    titleEdit->setMinimumWidth(400);

    authorEdit = new QLineEdit(scrollWidget);
    authorEdit->setStyleSheet(inputStyle);

    yearEdit = new QSpinBox(scrollWidget);
    yearEdit->setRange(1880, 2100);
    yearEdit->setValue(2024);
    yearEdit->setStyleSheet(inputStyle);
    
    genreComboBox = new QComboBox(scrollWidget);
    genreComboBox->addItems({"Azione", "Commedia", "Drammatico", "Fantasy", "Horror", "Romantico", "Sci-Fi", "Thriller", "Documentario", "Animazione"});
    genreComboBox->setStyleSheet(inputStyle);
    
    descriptionEdit = new QLineEdit(scrollWidget);
    descriptionEdit->setStyleSheet(inputStyle);
    
    ratingEdit = new QSpinBox(scrollWidget);
    ratingEdit->setRange(1.0, 5.0);
    ratingEdit->setStyleSheet(inputStyle);
    
    // Campi specifici per film
    directorEdit = new QLineEdit(scrollWidget);
    directorEdit->setStyleSheet(inputStyle);

    durationEdit = new QSpinBox(scrollWidget);
    durationEdit->setRange(1, 999);
    durationEdit->setSuffix(" min");
    durationEdit->setStyleSheet(inputStyle);
    
    // Etichette con stile migliorato
    QLabel *titleLbl = new QLabel("Titolo:");
    titleLbl->setStyleSheet(labelStyle);
    QLabel *directorLbl = new QLabel("Regista:");
    directorLbl->setStyleSheet(labelStyle);
    QLabel *authorLbl = new QLabel("Attori:");
    authorLbl->setStyleSheet(labelStyle);
    QLabel *yearLbl = new QLabel("Anno:");
    yearLbl->setStyleSheet(labelStyle);
    QLabel *durationLbl = new QLabel("Durata:");
    durationLbl->setStyleSheet(labelStyle);
    QLabel *genreLbl = new QLabel("Genere:");
    genreLbl->setStyleSheet(labelStyle);
    QLabel *descLbl = new QLabel("Descrizione:");
    descLbl->setStyleSheet(labelStyle);
    QLabel *imgLbl = new QLabel("Immagine:");
    imgLbl->setStyleSheet(labelStyle);
    QLabel *ratingLbl = new QLabel("Valutazione:");
    ratingLbl->setStyleSheet(labelStyle);

    // Aggiungi i campi al form
    formLayout->addRow(titleLbl, titleEdit);
    formLayout->addRow(directorLbl, directorEdit);
    formLayout->addRow(authorLbl, authorEdit);
    formLayout->addRow(yearLbl, yearEdit);
    formLayout->addRow(durationLbl, durationEdit);
    formLayout->addRow(genreLbl, genreComboBox);
    formLayout->addRow(descLbl, descriptionEdit);
    formLayout->addRow(ratingLbl, ratingEdit);

    // Aggiungo spazio vuoto in fondo
    formLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    
    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea, 1);
    
    // Pulsanti Salva e Annulla
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    saveMediaButton = new QPushButton("Salva");
    cancelButton = new QPushButton("Annulla");

    saveMediaButton->setMinimumSize(150, 45); // Pulsanti più grandi
    cancelButton->setMinimumSize(150, 45);
    
    saveMediaButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 128, 0);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 16px;"
        "   padding: 8px 16px;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(0, 100, 0);"
        "}"
    );
    
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
    
    connect(saveMediaButton, &QPushButton::clicked, this, &AddPage::onSaveMediaButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AddPage::onCancelButtonClicked);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveMediaButton);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();
    
    QVBoxLayout *buttonContainerLayout = new QVBoxLayout();
    buttonContainerLayout->addLayout(buttonLayout);
    buttonContainerLayout->addSpacing(10);
    
    layout->addLayout(buttonContainerLayout); // Aggiungi il layout dei pulsanti in basso
}

void AddPage::setupLibroDetailsPage(QWidget *container) {
    QVBoxLayout *layout = new QVBoxLayout(container);
    
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    
    QWidget *scrollWidget = new QWidget();
    QFormLayout *formLayout = new QFormLayout(scrollWidget);
    
    QLabel *titleLabel = new QLabel("Dettagli Libro", scrollWidget);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");
    formLayout->addRow(titleLabel);
    
    // Campi comuni
    titleEdit = new QLineEdit(scrollWidget);
    authorEdit = new QLineEdit(scrollWidget);
    yearEdit = new QSpinBox(scrollWidget);
    yearEdit->setRange(1000, 2100);
    yearEdit->setValue(2024);
    
    genreComboBox = new QComboBox(scrollWidget);
    genreComboBox->addItems({"Romanzo", "Saggio", "Biografia", "Fantasy", "Sci-Fi", "Thriller", "Horror", "Poesia", "Storia", "Scienza"});
    
    descriptionEdit = new QLineEdit(scrollWidget);
    
    ratingEdit = new QSpinBox(scrollWidget);
    ratingEdit->setRange(1, 5);
    
    // Campi specifici per libro
    publisherEdit = new QLineEdit(scrollWidget);
    pagesEdit = new QSpinBox(scrollWidget);
    pagesEdit->setRange(1, 9999);
    isbnEdit = new QLineEdit(scrollWidget);
    
    // Aggiungi i campi al form
    formLayout->addRow("Titolo:", titleEdit);
    formLayout->addRow("Autore:", authorEdit);
    formLayout->addRow("Anno:", yearEdit);
    formLayout->addRow("Editore:", publisherEdit);
    formLayout->addRow("Pagine:", pagesEdit);
    formLayout->addRow("ISBN:", isbnEdit);
    formLayout->addRow("Genere:", genreComboBox);
    formLayout->addRow("Descrizione:", descriptionEdit);
    formLayout->addRow("Valutazione:", ratingEdit);
    
    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea);
    
    // Pulsanti Salva e Annulla
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    saveMediaButton = new QPushButton("Salva");
    cancelButton = new QPushButton("Annulla");
    
    saveMediaButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 128, 0);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "   padding: 8px 16px;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(0, 100, 0);"
        "}"
    );
    
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
    
    connect(saveMediaButton, &QPushButton::clicked, this, &AddPage::onSaveMediaButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AddPage::onCancelButtonClicked);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveMediaButton);
    buttonLayout->addWidget(cancelButton);
    
    layout->addLayout(buttonLayout);
}

void AddPage::setupVinileDetailsPage(QWidget *container) {
    QVBoxLayout *layout = new QVBoxLayout(container);
    
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    
    QWidget *scrollWidget = new QWidget();
    QFormLayout *formLayout = new QFormLayout(scrollWidget);
    
    QLabel *titleLabel = new QLabel("Dettagli Vinile", scrollWidget);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");
    formLayout->addRow(titleLabel);
    
    // Campi comuni
    titleEdit = new QLineEdit(scrollWidget);
    authorEdit = new QLineEdit(scrollWidget);
    yearEdit = new QSpinBox(scrollWidget);
    yearEdit->setRange(1900, 2100);
    yearEdit->setValue(2024);
    
    genreComboBox = new QComboBox(scrollWidget);
    genreComboBox->addItems({"Rock", "Pop", "Jazz", "Blues", "Soul", "Rap", "Hip-Hop", "Classica", "Elettronica", "Folk"});
    
    descriptionEdit = new QLineEdit(scrollWidget);
    
    ratingEdit = new QSpinBox(scrollWidget);
    ratingEdit->setRange(1, 5);
    
    // Campi specifici per vinile
    trackCountEdit = new QSpinBox(scrollWidget);
    trackCountEdit->setRange(1, 99);
    recordTypeComboBox = new QComboBox(scrollWidget);
    recordTypeComboBox->addItems({"33 RPM", "45 RPM", "78 RPM"});
    
    // Aggiungi i campi al form
    formLayout->addRow("Titolo Album:", titleEdit);
    formLayout->addRow("Artista:", authorEdit);
    formLayout->addRow("Anno:", yearEdit);
    formLayout->addRow("Numero Tracce:", trackCountEdit);
    formLayout->addRow("Tipo Vinile:", recordTypeComboBox);
    formLayout->addRow("Genere:", genreComboBox);
    formLayout->addRow("Descrizione:", descriptionEdit);
    formLayout->addRow("Valutazione:", ratingEdit);
    
    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea);
    
    // Pulsanti Salva e Annulla
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    saveMediaButton = new QPushButton("Salva");
    cancelButton = new QPushButton("Annulla");
    
    saveMediaButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 128, 0);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "   padding: 8px 16px;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(0, 100, 0);"
        "}"
    );
    
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
    
    connect(saveMediaButton, &QPushButton::clicked, this, &AddPage::onSaveMediaButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AddPage::onCancelButtonClicked);
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveMediaButton);
    buttonLayout->addWidget(cancelButton);
    
    layout->addLayout(buttonLayout);
}

void AddPage::setupRivistaDetailsPage(QWidget *container) {
    QVBoxLayout *layout = new QVBoxLayout(container);
    
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    
    QWidget *scrollWidget = new QWidget();
    QFormLayout *formLayout = new QFormLayout(scrollWidget);
    
    QLabel *titleLabel = new QLabel("Dettagli Rivista", scrollWidget);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");
    formLayout->addRow(titleLabel);
    
    // Campi comuni
    titleEdit = new QLineEdit(scrollWidget);
    authorEdit = new QLineEdit(scrollWidget);
    yearEdit = new QSpinBox(scrollWidget);
    yearEdit->setRange(1900, 2100);
    yearEdit->setValue(2024);
    
    genreComboBox = new QComboBox(scrollWidget);
    genreComboBox->addItems({"Attualità", "Sport", "Tecnologia", "Moda", "Cucina", "Scienza", "Auto", "Casa", "Salute", "Economia"});
    
    descriptionEdit = new QLineEdit(scrollWidget);
    
    ratingEdit = new QSpinBox(scrollWidget);
    ratingEdit->setRange(1, 5);
    
    // Campi specifici per rivista
    publisherRivistaEdit = new QLineEdit(scrollWidget);
    issueNumberEdit = new QSpinBox(scrollWidget);
    periodicityComboBox = new QComboBox(scrollWidget);
    periodicityComboBox->addItems({"Settimanale", "Bisettimanale", "Mensile", "Bimestrale", "Trimestrale", "Semestrale", "Annuale"});
    
    // Aggiungi i campi al form
    formLayout->addRow("Titolo:", titleEdit);
    formLayout->addRow("Editore:", publisherRivistaEdit);
    formLayout->addRow("Numero:", issueNumberEdit);
    formLayout->addRow("Anno:", yearEdit);
    formLayout->addRow("Periodicità:", periodicityComboBox);
    formLayout->addRow("Autori:", authorEdit);
    formLayout->addRow("Genere:", genreComboBox);
    formLayout->addRow("Descrizione:", descriptionEdit);
    formLayout->addRow("Valutazione:", ratingEdit);
    
    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea);
    
    // Pulsanti Salva e Annulla
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    saveMediaButton = new QPushButton("Salva");
    cancelButton = new QPushButton("Annulla");
    
    saveMediaButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 128, 0);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "   padding: 8px 16px;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(0, 100, 0);"
        "}"
    );
    
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
    
    connect(saveMediaButton, &QPushButton::clicked, this, &AddPage::onSaveMediaButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AddPage::onCancelButtonClicked);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveMediaButton);
    buttonLayout->addWidget(cancelButton);
    
    layout->addLayout(buttonLayout);
}

void AddPage::setupGiocoDetailsPage(QWidget *container) {
    QVBoxLayout *layout = new QVBoxLayout(container);
    
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    
    QWidget *scrollWidget = new QWidget();
    QFormLayout *formLayout = new QFormLayout(scrollWidget);
    
    QLabel *titleLabel = new QLabel("Dettagli Gioco da Tavolo", scrollWidget);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");
    formLayout->addRow(titleLabel);
    
    // Campi comuni
    titleEdit = new QLineEdit(scrollWidget);
    authorEdit = new QLineEdit(scrollWidget);
    yearEdit = new QSpinBox(scrollWidget);
    yearEdit->setRange(1900, 2100);
    yearEdit->setValue(2024);
    
    genreComboBox = new QComboBox(scrollWidget);
    genreComboBox->addItems({"Strategia", "Party Game", "Carte", "Cooperativo", "Famiglia", "Astratto", "Wargame", "Fantasy", "Ruolo", "Educativo"});
    
    descriptionEdit = new QLineEdit(scrollWidget);
    
    ratingEdit = new QSpinBox(scrollWidget);
    ratingEdit->setRange(1, 5);
    
    // Campi specifici per gioco da tavolo
    minPlayersEdit = new QSpinBox(scrollWidget);
    minPlayersEdit->setRange(1, 20);
    maxPlayersEdit = new QSpinBox(scrollWidget);
    maxPlayersEdit->setRange(1, 99);
    minAgeEdit = new QSpinBox(scrollWidget);
    minAgeEdit->setRange(1, 99);
    minAgeEdit->setSuffix(" anni");
    playTimeEdit = new QSpinBox(scrollWidget);
    playTimeEdit->setRange(1, 999);
    playTimeEdit->setSuffix(" min");
    
    // Aggiungi i campi al form
    formLayout->addRow("Titolo:", titleEdit);
    formLayout->addRow("Autore/Designer:", authorEdit);
    formLayout->addRow("Anno:", yearEdit);
    formLayout->addRow("Min Giocatori:", minPlayersEdit);
    formLayout->addRow("Max Giocatori:", maxPlayersEdit);
    formLayout->addRow("Età Minima:", minAgeEdit);
    formLayout->addRow("Durata:", playTimeEdit);
    formLayout->addRow("Genere:", genreComboBox);
    formLayout->addRow("Descrizione:", descriptionEdit);
    formLayout->addRow("Valutazione:", ratingEdit);
    
    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea);
    
    // Pulsanti Salva e Annulla
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    saveMediaButton = new QPushButton("Salva");
    cancelButton = new QPushButton("Annulla");
    
    saveMediaButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 128, 0);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "   padding: 8px 16px;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(0, 100, 0);"
        "}"
    );
    
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
    
    connect(saveMediaButton, &QPushButton::clicked, this, &AddPage::onSaveMediaButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AddPage::onCancelButtonClicked);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveMediaButton);
    buttonLayout->addWidget(cancelButton);
    
    layout->addLayout(buttonLayout);
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