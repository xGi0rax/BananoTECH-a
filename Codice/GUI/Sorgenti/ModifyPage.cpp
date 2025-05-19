#include "../Headers/ModifyPage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QFileDialog>
#include <QMessageBox>

ModifyPage::ModifyPage(QWidget* parent) : QWidget(parent), currentMedia(nullptr), currentWidget(nullptr) {
    setupUI();
}

void ModifyPage::setupUI() {
    // Layout orizzontale principale
    QHBoxLayout* mainHLayout = new QHBoxLayout(this);
    mainHLayout->setContentsMargins(0, 0, 0, 0);
    mainHLayout->setSpacing(0);

    // Per dividere la pagina in barra laterale e area principale
    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->setMinimumSize(300, 0);

    // Widget per la barra laterale
    QWidget* sidebarWidget = new QWidget();
    sidebarWidget->setObjectName("sidebarWidget");

    // Layout verticale per la barra laterale
    QVBoxLayout* sidebarLayout = new QVBoxLayout(sidebarWidget);
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
    connect(backButton, &QPushButton::clicked, this, &ModifyPage::onBackButtonClicked);
    sidebarLayout->addWidget(backButton, 0, Qt::AlignTop | Qt::AlignLeft);

    // 2. Sezione centrale per l'immagine
    imagePreview = new QLabel("Nessuna immagine");
    imagePreview->setMinimumSize(220, 220);
    imagePreview->setMaximumSize(300, 300);
    imagePreview->setScaledContents(true);
    imagePreview->setAlignment(Qt::AlignCenter);
    imagePreview->setStyleSheet(
        "border: 1px dashed #666666;"
        "border-radius: 4px;"
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
    connect(uploadButton, &QPushButton::clicked, this, &ModifyPage::onUploadButtonClicked);
    
    QVBoxLayout* imageLayout = new QVBoxLayout();
    imageLayout->setContentsMargins(20, 20, 20, 20);
    imageLayout->addWidget(imagePreview, 1);
    imageLayout->addWidget(uploadButton, 0, Qt::AlignCenter);

    sidebarLayout->addLayout(imageLayout, 1);

    // 3. Pulsante "salva modifiche" in basso
    saveButton = new QPushButton("SALVA MODIFICHE");
    saveButton->setMinimumSize(190, 40);
    saveButton->setStyleSheet(
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
    connect(saveButton, &QPushButton::clicked, this, &ModifyPage::onSaveButtonClicked);
    sidebarLayout->addWidget(saveButton, 0, Qt::AlignBottom | Qt::AlignCenter);

    // Aggiungo la barra laterale al divisore
    splitter->addWidget(sidebarWidget);

    // Widget per l'area principale
    detailsStackedWidget = new QStackedWidget();

    // Aggiungi l'area principale al divisore
    splitter->addWidget(detailsStackedWidget);

    // Imposta la proporzione iniziale tra i due widget (1:2)
    splitter->setStretchFactor(0, 2);  // Sidebar (1/3)
    splitter->setStretchFactor(1, 3);  // Main area (2/3)
    
    // Aggiunge il divisore al layout principale
    mainHLayout->addWidget(splitter);

    setLayout(mainHLayout);

    currentImagePath = "";
}

void ModifyPage::setMedia(Media* media) {
    if (!media) {
        QMessageBox::warning(this, "Errore", "Media non valido");
        return;
    }
    
    try {
        // Salva il puntatore al media
        currentMedia = media;
        
        // Pulisci eventuali widget di dettaglio precedenti
        if (currentWidget) {
            detailsStackedWidget->removeWidget(currentWidget);
            delete currentWidget;
            currentWidget = nullptr;
        }
        
        // Crea il widget appropriato in base al tipo di media
        if (Film* film = dynamic_cast<Film*>(media)) {
            FilmWidget* filmWidget = new FilmWidget();
            filmWidget->setCurrentMedia(film);
            currentWidget = filmWidget;
        } 
        else if (Libro* libro = dynamic_cast<Libro*>(media)) {
            LibroWidget* libroWidget = new LibroWidget();
            libroWidget->setCurrentMedia(libro);
            currentWidget = libroWidget;
        } 
        else if (Vinile* vinile = dynamic_cast<Vinile*>(media)) {
            VinileWidget* vinileWidget = new VinileWidget();
            vinileWidget->setCurrentMedia(vinile);
            currentWidget = vinileWidget;
        } 
        else if (Rivista* rivista = dynamic_cast<Rivista*>(media)) {
            RivistaWidget* rivistaWidget = new RivistaWidget();
            rivistaWidget->setCurrentMedia(rivista);
            currentWidget = rivistaWidget;
        } 
        else if (GiocoDaTavolo* gioco = dynamic_cast<GiocoDaTavolo*>(media)) {
            GiocoWidget* giocoWidget = new GiocoWidget();
            giocoWidget->setCurrentMedia(gioco);
            currentWidget = giocoWidget;
        }
        else {
            QMessageBox::warning(this, "Errore", "Tipo di media non riconosciuto");
            return;
        }
        
        // Aggiungi il widget allo stack e mostralo
        detailsStackedWidget->addWidget(currentWidget);
        detailsStackedWidget->setCurrentWidget(currentWidget);
        
        // Carica l'immagine
        std::string imagePath = media->getImmagine();
        if (!imagePath.empty()) {
            currentImagePath = QString::fromStdString(imagePath);
            QPixmap pixmap(currentImagePath);
            if (!pixmap.isNull()) {
                // Ridimensiona l'immagine mantenendo le proporzioni
                QPixmap scaledPixmap = pixmap.scaled(imagePreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                imagePreview->setPixmap(scaledPixmap);
                imagePreview->setScaledContents(false);
            } else {
                imagePreview->setText("Immagine non disponibile");
            }
        } else {
            imagePreview->setText("Nessuna immagine");
        }
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Errore", "Si è verificato un errore durante il caricamento dei dati: " + QString(e.what()));
    }
    catch (...) {
        QMessageBox::warning(this, "Errore", "Si è verificato un errore sconosciuto durante il caricamento dei dati");
    }
}

void ModifyPage::onBackButtonClicked() {
    emit goBackToMainPage();
}

void ModifyPage::onSaveButtonClicked() {
    if (!currentMedia || !currentWidget) {
        QMessageBox::warning(this, "Errore", "Nessun media da salvare");
        return;
    }
    
    try {
        // Verifica che i dati siano validi
        if (!currentWidget->validateData()) {
            QMessageBox::warning(this, "Errore", "Dati non validi. Verifica tutti i campi.");
            return;
        }
        
        // Applica le modifiche direttamente all'oggetto media esistente
        if (currentWidget->applyChanges()) {
            // Imposta l'immagine se è stata modificata
            if (!currentImagePath.isEmpty()) {
                currentMedia->setImmagine(currentImagePath.toStdString());
            }
            
            QMessageBox::information(this, "Successo", "Modifiche salvate con successo");
            emit mediaEdited();
            emit goBackToMainPage();
        } 
        else {
            QMessageBox::warning(this, "Errore", "Non è stato possibile applicare le modifiche");
        }
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Errore", "Si è verificato un errore durante il salvataggio: " + QString(e.what()));
    }
    catch (...) {
        QMessageBox::warning(this, "Errore", "Si è verificato un errore sconosciuto durante il salvataggio");
    }
}

void ModifyPage::onUploadButtonClicked() {
    // Apri finestra di dialogo per selezionare un'immagine
    QString imagePath = QFileDialog::getOpenFileName(this, "Seleziona un'immagine", 
                                                   "", "Immagini (*.png *.jpg *.jpeg *.bmp)");
    
    if (imagePath.isEmpty()) {
        return;  // L'utente ha annullato la selezione
    }
    
    // Carica e mostra l'immagine selezionata
    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Errore", "Impossibile caricare l'immagine selezionata");
        return;
    }
    
    // Ridimensiona l'immagine mantenendo le proporzioni
    QPixmap scaledPixmap = pixmap.scaled(imagePreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imagePreview->setPixmap(scaledPixmap);
    imagePreview->setScaledContents(false);
    
    // Salva il percorso dell'immagine
    currentImagePath = imagePath;
}