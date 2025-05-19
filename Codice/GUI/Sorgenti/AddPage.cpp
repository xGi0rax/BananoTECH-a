#include "../Headers/AddPage.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSplitter>

AddPage::AddPage(QWidget *parent) : QWidget(parent), currentWidget(nullptr) {
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
    addButton->setMinimumSize(190, 40);
    addButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 128, 0);"
        "   color: white;"
        "   border: 2px solid rgb(119, 114, 114);"
        "   border-radius: 6px;"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(0, 100, 0);"
        "}"
    );
    connect(addButton, &QPushButton::clicked, this, &AddPage::onAddButtonClicked);
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
    selectionLayout->setContentsMargins(40, 40, 40, 40);
    selectionLayout->setSpacing(20);

    // Label con scritta
    QLabel *selectionLabel = new QLabel("Seleziona il tipo di media", selectionWidget);
    selectionLabel->setAlignment(Qt::AlignCenter);
    selectionLabel->setStyleSheet("background-color: #444444; font-size: 22px; font-weight: bold; color: white; margin-bottom: 10px; border: 2px solid black; border-radius: 8px; padding: 10px;");
    selectionLayout->addWidget(selectionLabel);

    // ButtonGroup di radio button per la selezione del tipo di media
    mediaTypeGroup = new QButtonGroup(this);
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

void AddPage::showSelectionPage() {
    // Reset della selezione
    if (mediaTypeGroup->checkedButton()) {
        mediaTypeGroup->setExclusive(false);
        mediaTypeGroup->checkedButton()->setChecked(false);
        mediaTypeGroup->setExclusive(true);
    }
    
    // Mostro la pagina di selezione
    mainContentStack->setCurrentWidget(selectionWidget);
}

void AddPage::onBackButtonClicked() {
    // Se l'utente è nella pagina di selezione, torna alla pagina principale
    // Se l'utente è in una pagina di dettaglio, torna alla pagina di selezione
    if (mainContentStack->currentWidget() == selectionWidget) {
        emit goBackToMainPage();
        return;
    } else if (mainContentStack->currentWidget() == detailsStackedWidget) {
        showSelectionPage();
        return;
    }
}

void AddPage::onConfirmTypeButtonClicked() {
    // Verifico che sia selezionato un tipo di media
    if (!mediaTypeGroup->checkedButton()) {
        QMessageBox::warning(this, "Errore", "Seleziona un tipo di media!");
        return;
    }

    int selectedId = mediaTypeGroup->checkedId();

    if (selectedId < 0) {
        QMessageBox::warning(this, "Errore", "ID non valido");
        return;
    }

    // Rimuovi il widget corrente se esiste
    if (currentWidget) {
        detailsStackedWidget->removeWidget(currentWidget);
        delete currentWidget;
        currentWidget = nullptr;
    }
    
    // Crea un nuovo widget in base al tipo selezionato
    MediaType mediaType = static_cast<MediaType>(selectedId);
    
    switch (mediaType) {
        case FILM:
            currentWidget = new FilmWidget();
            break;
        case LIBRO:
            currentWidget = new LibroWidget();
            break;
        case VINILE:
            currentWidget = new VinileWidget();
            break;
        case RIVISTA:
            currentWidget = new RivistaWidget();
            break;
        case GIOCO_DA_TAVOLO:
            currentWidget = new GiocoWidget();
            break;
        default:
            QMessageBox::warning(this, "Errore", "Tipo di media non valido!");
            return;
    }
    
    // Aggiungi il widget al layout e mostralo
    detailsStackedWidget->addWidget(currentWidget);
    detailsStackedWidget->setCurrentWidget(currentWidget);
    mainContentStack->setCurrentWidget(detailsStackedWidget);
}

void AddPage::onAddButtonClicked() {
    if (!currentWidget) {
        QMessageBox::warning(this, "Errore", "Nessun widget attivo trovato!");
        return;
    }

    // Controllo se tutti i campi sono stati inseriti
    if (!currentWidget->validateData()) {
        QMessageBox::warning(this, "Errore", "Tutti i campi sono obbligatori!");
        return;
    }
    
    // Crea l'oggetto media usando il widget attualmente visualizzato
    Media* newMedia = currentWidget->createMedia();

    if (newMedia) {
        // Imposta l'immagine del media se è stata selezionata
        if (!selectedImagePath.isEmpty()) {
            newMedia->setImmagine(selectedImagePath.toStdString());
        }
        
        // Emetti un segnale con il nuovo media creato
        emit mediaCreated(newMedia);
        
        QMessageBox::information(this, "Salvataggio", "Media salvato con successo!");
        
        // Resetto la selezione e mostro la pagina di selezione
        if (mediaTypeGroup->checkedButton()) {
            mediaTypeGroup->setExclusive(false);
            mediaTypeGroup->checkedButton()->setChecked(false);
            mediaTypeGroup->setExclusive(true);
        }
        // Mostro la pagina di selezione
        mainContentStack->setCurrentWidget(selectionWidget);

        // Torna alla pagina principale
        emit goBackToMainPage();
    } else {
        QMessageBox::warning(this, "Errore", "Errore nella creazione del media!");
    }
}