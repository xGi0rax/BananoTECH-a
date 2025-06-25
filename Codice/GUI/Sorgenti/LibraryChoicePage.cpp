#include "../Headers/LibraryChoicePage.h"
#include "../../Modello logico/Headers/JsonIO.h"
#include "../../Modello logico/Headers/XmlIO.h"
#include <QFileDialog>
#include <QMessageBox>

LibraryChoicePage::LibraryChoicePage(QWidget *parent) : QWidget(parent), biblioteca(nullptr) {
    setupUI();
}

void LibraryChoicePage::setupUI() {
    // Imposto lo sfondo con lo stesso stile di LoginPage
    this->setObjectName("libraryChoicePage");
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setAutoFillBackground(true);
    this->setStyleSheet("#libraryChoicePage {"
                        " background-image: url(:/Immagini/SfondoLogin.jpg);"
                        " background-repeat: no-repeat;"
                        " background-position: center center;"
                        " background-attachment: fixed;"
                        "}"
    );

    // Creazione del Frame che contiene i campi di input e i bottoni
    QFrame *choiceFrame = new QFrame(this);
    choiceFrame->setFixedSize(450, 350);
    choiceFrame->setStyleSheet("QFrame { background-color:rgb(42, 68, 113); border: 2px solid #000000; border-radius: 10px; }");

    // Label di benvenuto
    QLabel *welcomeLabel = new QLabel("Benvenuto nella BananoTECH-a", choiceFrame);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("background-color: #333333; font-size: 24px; font-weight: bold; color: white;");
    // welcomeLabel->setFixedHeight(57);

    // Descrizione con migliore visibilità
    descriptionLabel = new QLabel("Vuoi caricare una biblioteca esistente o creane una nuova?", choiceFrame);
    descriptionLabel->setStyleSheet("font-size: 18px; color: white; border: none;");
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setWordWrap(true);
    
    // Pulsante per caricare da file
    loadFileButton = new QPushButton("Carica da file", choiceFrame);
    loadFileButton->setFixedSize(330, 50);
    loadFileButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(225, 192, 37);"
        "   color: black;"
        "   border: 1px solid #AAAAAA;"
        "   border-radius: 8px;"
        "   font-size: 18px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(184, 174, 90);"
        "}"
    );
    
    // Pulsante per creare una nuova biblioteca
    newLibraryButton = new QPushButton("Crea nuova biblioteca", choiceFrame);
    newLibraryButton->setFixedSize(330, 50);
    newLibraryButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(225, 192, 37);"
        "   color: black;"
        "   border: 1px solid #AAAAAA;"
        "   border-radius: 8px;"
        "   font-size: 18px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(184, 174, 90);"
        "}"
    );
    
    // Pulsante per tornare al login
    QPushButton* backButton = new QPushButton("Indietro", choiceFrame);
    backButton->setFixedSize(150, 45);
    backButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 104, 201);"
        "   color: white;"
        "   border: 1px solid black;"
        "   border-radius: 5px;"
        "   font-size: 16px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(11, 82, 189);"
        "}"
    );
    
    // Connessione dei segnali
    connect(loadFileButton, &QPushButton::clicked, this, &LibraryChoicePage::onLoadFileButtonClicked);
    connect(newLibraryButton, &QPushButton::clicked, this, &LibraryChoicePage::onNewLibraryButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &LibraryChoicePage::goToLoginPage);
    
    // Layout verticale per il contenuto del frame
    QVBoxLayout *choiceWidgetsLayout = new QVBoxLayout();
    choiceWidgetsLayout->setContentsMargins(10, 10, 10, 10);
    choiceWidgetsLayout->setSpacing(10); // Ridotto da 20 per adattarsi all'altezza minore
    
    choiceWidgetsLayout->addWidget(welcomeLabel);
    choiceWidgetsLayout->addWidget(descriptionLabel, 0, Qt::AlignCenter);
    choiceWidgetsLayout->addWidget(loadFileButton, 0, Qt::AlignCenter);
    choiceWidgetsLayout->addWidget(newLibraryButton, 0, Qt::AlignCenter);
    choiceWidgetsLayout->addWidget(backButton, 0, Qt::AlignCenter);
    
    choiceFrame->setLayout(choiceWidgetsLayout);
    
    // Layout esterno per centrare il frame
    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->addStretch();
    outerLayout->addWidget(choiceFrame, 0, Qt::AlignCenter);
    outerLayout->addStretch();
    
    this->setLayout(outerLayout);
}

void LibraryChoicePage::onLoadFileButtonClicked() {
    QFileDialog fileDialog(this);
    fileDialog.setWindowTitle("Seleziona un file Json o Xml");
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter("File supportati (*.json *.xml)");
    fileDialog.setViewMode(QFileDialog::Detail);
    
    if (fileDialog.exec()) {
        QStringList selectedFiles = fileDialog.selectedFiles();
        if (!selectedFiles.isEmpty()) {
            QString filePath = selectedFiles.first();
            
            // Elimina la biblioteca esistente se presente
            if (biblioteca) {
                delete biblioteca;
                biblioteca = nullptr;
            }
            
            // Crea una nuova biblioteca vuota
            string idBiblio = "VC";
            biblioteca = new Biblioteca(idBiblio);

            bool success = false;
            
            if (filePath.endsWith(".json", Qt::CaseInsensitive)) {
                JsonIO jsonLoader;
                success = jsonLoader.caricaDaFile(*biblioteca, filePath.toStdString());
            } else if (filePath.endsWith(".xml", Qt::CaseInsensitive)) {
                XmlIO xmlLoader;
                success = xmlLoader.caricaDaFile(*biblioteca, filePath.toStdString());
            }
            
            if (success) {
                QMessageBox::information(this, "Caricamento completato", 
                    "I dati della biblioteca sono stati caricati con successo!");
                
                // Si è caricata una biblioteca esistente -> isNewLibrary = false
                emit libraryReady(biblioteca, filePath, false);
            } else {
                QMessageBox::warning(this, "Errore di caricamento", 
                    "Impossibile caricare i dati dal file specificato.\nRiprova con un altro file o crea una biblioteca vuota.");
                delete biblioteca;
                biblioteca = nullptr;
            }
        }
    }
}

void LibraryChoicePage::onNewLibraryButtonClicked() {
    // Elimina la biblioteca esistente se presente
    if (biblioteca) {
        delete biblioteca;
        biblioteca = nullptr;
    }
    
    // Crea una nuova biblioteca completamente vuota
    string idBiblio = "VC";
    biblioteca = new Biblioteca(idBiblio);
    
    QMessageBox::information(this, "Biblioteca creata", "Una nuova biblioteca vuota è stata creata con successo!");
    
    // Quando viene creata una nuova biblioteca isNewLibrary = true e filePath vuoto
    emit libraryReady(biblioteca, "", true);
}