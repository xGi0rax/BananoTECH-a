#include "../Headers/LibraryChoicePage.h"
#include "../../Modello logico/Headers/JsonIO.h"
#include "../../Modello logico/Headers/XmlIO.h"
#include <QFileDialog>
#include <QMessageBox>

LibraryChoicePage::LibraryChoicePage(QWidget *parent) : QWidget(parent), biblioteca(nullptr) {
    setupUI();
}

void LibraryChoicePage::setupUI() {
    // Imposto lo sfondo
    this->setObjectName("libraryChoicePage");
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setAutoFillBackground(true);
    this->setStyleSheet("#libraryChoicePage {background-color: rgb(42, 68, 113);}");

    // Layout principale
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(50, 50, 50, 50);
    mainLayout->setSpacing(20);

    // Titolo
    titleLabel = new QLabel("Benvenuto in BananoTECH-a");
    titleLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: white;");
    titleLabel->setAlignment(Qt::AlignCenter);
    
    // Descrizione
    descriptionLabel = new QLabel("Scegli se caricare una biblioteca esistente o crearne una nuova");
    descriptionLabel->setStyleSheet("font-size: 16px; color: white;");
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setWordWrap(true);
    
    // Pulsante per caricare da file
    loadFileButton = new QPushButton("Carica da file");
    loadFileButton->setMinimumSize(300, 60);
    loadFileButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 104, 201);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   font-size: 18px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(11, 82, 189);"
        "}"
    );
    
    // Pulsante per creare una nuova biblioteca
    newLibraryButton = new QPushButton("Crea nuova biblioteca");
    newLibraryButton->setMinimumSize(300, 60);
    newLibraryButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(255, 208, 0);"
        "   color: black;"
        "   border: none;"
        "   border-radius: 8px;"
        "   font-size: 18px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(255, 170, 0);"
        "}"
    );
    
    // Pulsante per tornare al login
    QPushButton* backButton = new QPushButton("Indietro");
    backButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #555555;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   font-size: 16px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #444444;"
        "}"
    );
    connect(backButton, &QPushButton::clicked, this, &LibraryChoicePage::goToLoginPage);
    
    // Connessione dei segnali
    connect(loadFileButton, &QPushButton::clicked, this, &LibraryChoicePage::onLoadFileButtonClicked);
    connect(newLibraryButton, &QPushButton::clicked, this, &LibraryChoicePage::onNewLibraryButtonClicked);
    
    // Aggiunta dei widget al layout
    mainLayout->addStretch(1);
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(descriptionLabel, 0, Qt::AlignCenter);
    mainLayout->addSpacing(30);
    mainLayout->addWidget(loadFileButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(newLibraryButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(backButton, 0, Qt::AlignCenter);
    mainLayout->addStretch(1);
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
            
            // Creiamo un'istanza di Biblioteca
            string idBiblio = "VC";  // ID predefinito
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
                emit libraryReady(biblioteca);
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
    // Creiamo una biblioteca vuota
    string idBiblio = "VC";  // ID predefinito
    biblioteca = new Biblioteca(idBiblio);
    
    QMessageBox::information(this, "Biblioteca creata", 
        "Una nuova biblioteca vuota è stata creata con successo!");
    
    emit libraryReady(biblioteca);
}