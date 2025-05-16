#include "../Headers/ModifyPage.h"
#include "../Headers/Widgets/FilmModifyWidget.h"
#include "../Headers/Widgets/LibroModifyWidget.h"
#include "../Headers/Widgets/VinileModifyWidget.h"
#include "../Headers/Widgets/RivistaModifyWidget.h"
#include "../Headers/Widgets/GiocoModifyWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QScrollArea>
#include <QMessageBox>
#include <QFileDialog>
#include <QSplitter>
#include <QDebug>
#include <QStackedWidget>

ModifyPage::ModifyPage(QWidget* parent) : QWidget(parent), currentMedia(nullptr), currentDetailsWidget(nullptr) {
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
    cancelButton = new QPushButton("Indietro");
    cancelButton->setMinimumSize(145, 30);
    cancelButton->setStyleSheet(
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
    connect(cancelButton, &QPushButton::clicked, this, &ModifyPage::onBackButtonClicked);
    sidebarLayout->addWidget(cancelButton, 0, Qt::AlignTop | Qt::AlignLeft);
      
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
    saveButton->setMinimumSize(200, 45);
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

    // Widget per l'area principale - Creiamo un StackedWidget
    detailsStackedWidget = new QStackedWidget();
    
    // Widget iniziale con messaggio
    QWidget* placeholderWidget = new QWidget();
    QVBoxLayout* placeholderLayout = new QVBoxLayout(placeholderWidget);
    QLabel* placeholderLabel = new QLabel("Seleziona un media dalla lista principale per modificarlo");
    placeholderLabel->setAlignment(Qt::AlignCenter);
    placeholderLabel->setStyleSheet("font-size: 18px; color: white;");
    placeholderLayout->addWidget(placeholderLabel);
    
    // Aggiungiamo il widget placeholder allo stack
    detailsStackedWidget->addWidget(placeholderWidget);

    // Imposta il colore di sfondo del pannello principale
    detailsStackedWidget->setStyleSheet("background-color: rgb(55, 58, 77);");

    // Aggiungi pannello principale al divisore
    splitter->addWidget(detailsStackedWidget);
    
    // Imposta la proporzione iniziale tra i due widget (1:2)
    splitter->setStretchFactor(0, 2);  // Sidebar (1/3)
    splitter->setStretchFactor(1, 3);  // Main area (2/3)
    
    // Aggiunge il divisore al layout principale
    mainHLayout->addWidget(splitter);
    
    setLayout(mainHLayout);
    
    // Salva il percorso dell'immagine corrente
    currentImagePath = "";
}

void ModifyPage::setMedia(Media* media) {
    qDebug() << "setMedia chiamato";
    
    if (!media) {
        qDebug() << "Media è null!";
        QMessageBox::warning(this, "Errore", "Media non valido");
        return;
    }
    
    try {
        // Salva il puntatore al media
        currentMedia = media;
        
        // Pulisci eventuali widget di dettaglio precedenti
        if (currentDetailsWidget) {
            detailsStackedWidget->removeWidget(currentDetailsWidget);
            delete currentDetailsWidget;
            currentDetailsWidget = nullptr;
        }
        
        // Crea il widget appropriato in base al tipo di media
        if (Film* film = dynamic_cast<Film*>(media)) {
            FilmModifyWidget* filmWidget = new FilmModifyWidget();
            filmWidget->setMedia(film);
            currentDetailsWidget = filmWidget;
        } 
        else if (Libro* libro = dynamic_cast<Libro*>(media)) {
            LibroModifyWidget* libroWidget = new LibroModifyWidget();
            libroWidget->setMedia(libro);
            currentDetailsWidget = libroWidget;
        } 
        else if (Vinile* vinile = dynamic_cast<Vinile*>(media)) {
            VinileModifyWidget* vinileWidget = new VinileModifyWidget();
            vinileWidget->setMedia(vinile);
            currentDetailsWidget = vinileWidget;
        } 
        else if (Rivista* rivista = dynamic_cast<Rivista*>(media)) {
            RivistaModifyWidget* rivistaWidget = new RivistaModifyWidget();
            rivistaWidget->setMedia(rivista);
            currentDetailsWidget = rivistaWidget;
        } 
        else if (GiocoDaTavolo* gioco = dynamic_cast<GiocoDaTavolo*>(media)) {
            GiocoModifyWidget* giocoWidget = new GiocoModifyWidget();
            giocoWidget->setMedia(gioco);
            currentDetailsWidget = giocoWidget;
        }
        else {
            QMessageBox::warning(this, "Errore", "Tipo di media non riconosciuto");
            return;
        }
        
        // Aggiungi il widget allo stack e mostralo
        detailsStackedWidget->addWidget(currentDetailsWidget);
        detailsStackedWidget->setCurrentWidget(currentDetailsWidget);
        
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
        
        qDebug() << "Tutti i campi popolati con successo";
    }
    catch (const std::exception& e) {
        qDebug() << "Eccezione durante il caricamento dei dati:" << e.what();
        QMessageBox::warning(this, "Errore", "Si è verificato un errore durante il caricamento dei dati: " + QString(e.what()));
    }
    catch (...) {
        qDebug() << "Eccezione sconosciuta durante il caricamento dei dati";
        QMessageBox::warning(this, "Errore", "Si è verificato un errore sconosciuto durante il caricamento dei dati");
    }
}

void ModifyPage::onBackButtonClicked() {
    emit goBackToMainPage();
}

void ModifyPage::onSaveButtonClicked() {
    if (!currentMedia || !currentDetailsWidget) {
        QMessageBox::warning(this, "Errore", "Nessun media da salvare");
        return;
    }
    
    try {
        // Verifica che i dati siano validi
        if (!currentDetailsWidget->validateData()) {
            QMessageBox::warning(this, "Errore", "Dati non validi. Verifica tutti i campi.");
            return;
        }
        
        // Applica le modifiche direttamente all'oggetto media esistente
        if (currentDetailsWidget->applyChanges()) {
            // Imposta l'immagine se è stata modificata
            if (!currentImagePath.isEmpty()) {
                currentMedia->setImmagine(currentImagePath.toStdString());
            }
            
            QMessageBox::information(this, "Successo", "Modifiche salvate con successo");
            emit goBackToMainPage();
        } 
        else {
            QMessageBox::warning(this, "Errore", "Non è stato possibile applicare le modifiche");
        }
    }
    catch (const std::exception& e) {
        qDebug() << "Eccezione durante il salvataggio:" << e.what();
        QMessageBox::warning(this, "Errore", "Si è verificato un errore durante il salvataggio: " + QString(e.what()));
    }
    catch (...) {
        qDebug() << "Eccezione sconosciuta durante il salvataggio";
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
    qDebug() << "Nuova immagine caricata:" << currentImagePath;
}