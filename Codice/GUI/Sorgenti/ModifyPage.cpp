#include "../Headers/ModifyPage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QFileDialog>
#include <QMessageBox>

ModifyPage::ModifyPage(QWidget* parent) : QWidget(parent), biblioteca(nullptr), currentMedia(nullptr), currentWidget(nullptr) {
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
    backButton->setMinimumSize(100, 30);
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

    uploadButton = new QPushButton("Carica immagine");
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

    // 3. Pulsante "conferma modifiche" in basso
    saveButton = new QPushButton("CONFERMA MODIFICHE");
    saveButton->setMinimumSize(190, 45);
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

        if (!currentMedia) {
            QMessageBox::warning(this, "Errore", "Media non più valido");
            return;
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
        
        // Gestisci immagine - GESTIONE CROSS-PLATFORM (come in DetailsPage)
        std::string imagePath = media->getImmagine();
        if (!imagePath.empty()) {
            currentImagePath = QString::fromStdString(imagePath);
            
            // Prova prima nel sistema di risorse Qt (per icone UI statiche)
            QString resourcePath = ":/Immagini/" + currentImagePath;
            QPixmap pixmap(resourcePath);
            
            // Se non trovata nelle risorse, prova nel filesystem
            if (pixmap.isNull()) {
                // Se il percorso è già assoluto, provalo direttamente
                if (QFile::exists(currentImagePath)) {
                    pixmap.load(currentImagePath);
                }
                
                // Se ancora non trovata, prova percorsi relativi
                if (pixmap.isNull()) {
                    QDir currentDir = QDir::current();
                    
                    // Prova diverse possibili ubicazioni
                    QStringList possiblePaths = {
                        currentDir.absoluteFilePath("Immagini/" + currentImagePath),           // ./Immagini/
                        currentDir.absoluteFilePath("../Immagini/" + currentImagePath),        // ../Immagini/
                        currentDir.absoluteFilePath("../../Immagini/" + currentImagePath),     // ../../Immagini/
                        currentDir.absoluteFilePath("GUI/Immagini/" + currentImagePath),       // ./GUI/Immagini/
                        currentDir.absoluteFilePath("../GUI/Immagini/" + currentImagePath),    // ../GUI/Immagini/
                    };
                    
                    // Prova ogni percorso finché non ne trova uno che funziona
                    for (const QString& path : possiblePaths) {
                        if (QFile::exists(path)) {
                            pixmap.load(path);
                        }
                    }
                }
            } else {
                // boh
            }
            
            // Imposta l'immagine o il placeholder
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

void ModifyPage::setBiblioteca(Biblioteca* biblio) {
    biblioteca = biblio;
}

void ModifyPage::onBackButtonClicked() {
    emit goBackToMainPage();
}

void ModifyPage::onSaveButtonClicked() {
    if (!currentMedia || !currentWidget) {
        QMessageBox::warning(this, "Errore", "Nessun media da salvare");
        return;
    }
    
    if (!currentWidget->validateData()) {
        QMessageBox::warning(this, "Errore", "Dati non validi. Verifica tutti i campi.");
        return;
    }

    QString newTitle = currentWidget->getTitolo(); 
    QString newAuthor = currentWidget->getAutore();
    int newYear = currentWidget->getAnno();

    // Controlla se i nuovi valori corrispondono a un media esistente DIVERSO da quello corrente
    if (biblioteca && biblioteca->esisteMedia(newTitle.toStdString(), newAuthor.toStdString(), newYear)) {
        Media* mediaEsistente = biblioteca->cercaMediaDaT_A_A(newTitle.toStdString(), newAuthor.toStdString(), newYear);
        
        // Verifica che non sia lo stesso media che stiamo modificando
        if (mediaEsistente && mediaEsistente != currentMedia) {
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Media già esistente", 
                "Un media con lo stesso titolo, autore e anno esiste già nella biblioteca. Vuoi aumentare il numero di copie di questo media invece di salvare le modifiche? \nIl media che stavi modificando verrà eliminato.", 
                QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                // Aumenta le copie del media esistente
                mediaEsistente->setNumeroCopie(mediaEsistente->getNumeroCopie() + 1);
                biblioteca->rimuoviMedia(currentMedia);
                currentMedia = nullptr; // Imposto a nullptr per evitare dangling pointer

                QMessageBox::information(this, "Salvataggio", "Numero copie del media aumentate con successo!");
                emit mediaCopiesIncreased();
                emit goBackToMainPage();
                return;
            } else if (reply == QMessageBox::No){
                // L'utente ha scelto No, rimane nella pagina di modifica
                return;
            }
        }
    }
    
    // Se arriviamo qui, possiamo procedere con le modifiche normali
    if (currentWidget->applyChanges()) {
        // Imposta l'immagine se è stata modificata
        if (!currentImagePath.isEmpty()) {
            currentMedia->setImmagine(currentImagePath.toStdString());
        }
        
        QMessageBox::information(this, "Successo", "Modifiche salvate con successo");
        emit mediaModified();
        emit goBackToMainPage();
    } 
    else {
        QMessageBox::warning(this, "Errore", "Non è stato possibile applicare le modifiche");
    }
}

void ModifyPage::onUploadButtonClicked() {
    QString imagePath = QFileDialog::getOpenFileName(this, "Seleziona un'immagine", 
                                                   "", "Immagini (*.png *.jpg *.jpeg *.bmp)");
    
    if (imagePath.isEmpty()) {
        return;
    }
    
    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Errore", "Impossibile caricare l'immagine selezionata");
        return;
    }
    
    QPixmap scaledPixmap = pixmap.scaled(imagePreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imagePreview->setPixmap(scaledPixmap);
    imagePreview->setScaledContents(false);
    
    // Crea la cartella Immagini se non esiste
    QDir appDir = QDir::current();
    if (!appDir.exists("Immagini")) {
        appDir.mkdir("Immagini");
    }
    
    // Gestisce nomi file duplicati
    QFileInfo fileInfo(imagePath);
    QString baseName = fileInfo.completeBaseName(); // Nome senza estensione
    QString extension = fileInfo.suffix(); // Estensione
    QString fileName = fileInfo.fileName();
    QString newPath = appDir.absoluteFilePath("Immagini/" + fileName);
    
    // Se il file esiste, aggiungi un numero progressivo
    int counter = 1;
    while (QFile::exists(newPath)) {
        fileName = QString("%1_%2.%3").arg(baseName).arg(counter).arg(extension);
        newPath = appDir.absoluteFilePath("Immagini/" + fileName);
        counter++;
    }
    
    // Copia il file con il nome definitivo
    if (QFile::copy(imagePath, newPath)) {
        currentImagePath = "Immagini/" + fileName;
    } else {
        // Fallback al percorso originale
        currentImagePath = imagePath;
    }
}