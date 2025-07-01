#include "../Headers/LibraryChoicePage.h"
#include "../../Modello logico/Headers/JsonIO.h"
#include "../../Modello logico/Headers/XmlIO.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFrame>

// ========================================
// COSTRUTTORE E DISTRUTTORE
// ========================================
LibraryChoicePage::LibraryChoicePage(QWidget *parent) : QWidget(parent), biblioteca(nullptr) {
    setupUI();
    setupStyles();
    setupConnections();
}

LibraryChoicePage::~LibraryChoicePage() {
    if (biblioteca) {
        delete biblioteca;
        biblioteca = nullptr;
    }
}

// ========================================
// METODI DI INIZIALIZZAZIONE
// ========================================
void LibraryChoicePage::setupUI() {
    // Configurazione background pagina
    setObjectName("libraryChoicePage");
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);

    // Creazione frame principale
    QFrame *choiceFrame = new QFrame(this);
    choiceFrame->setFixedSize(450, 350);
    choiceFrame->setObjectName("choiceFrame");

    // Label di benvenuto
    QLabel *welcomeLabel = new QLabel("Benvenuto nella BananoTECH-a", choiceFrame);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setObjectName("welcomeLabel");

    // Descrizione
    descriptionLabel = new QLabel("Vuoi caricare una biblioteca esistente o creane una nuova?", choiceFrame);
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setObjectName("descriptionLabel");
    
    // Pulsante carica da file
    loadFileButton = new QPushButton("Carica da file", choiceFrame);
    loadFileButton->setFixedSize(330, 50);
    loadFileButton->setObjectName("primaryButton");
    
    // Pulsante nuova biblioteca
    newLibraryButton = new QPushButton("Crea nuova biblioteca", choiceFrame);
    newLibraryButton->setFixedSize(330, 50);
    newLibraryButton->setObjectName("primaryButton");
    
    // Pulsante indietro
    QPushButton* backButton = new QPushButton("Indietro", choiceFrame);
    backButton->setFixedSize(150, 45);
    backButton->setObjectName("secondaryButton");
    
    // Layout interno frame
    QVBoxLayout *choiceWidgetsLayout = new QVBoxLayout();
    choiceWidgetsLayout->setContentsMargins(10, 10, 10, 10);
    choiceWidgetsLayout->setSpacing(15);
    
    choiceWidgetsLayout->addWidget(welcomeLabel);
    choiceWidgetsLayout->addWidget(descriptionLabel, 0, Qt::AlignCenter);
    choiceWidgetsLayout->addWidget(loadFileButton, 0, Qt::AlignCenter);
    choiceWidgetsLayout->addWidget(newLibraryButton, 0, Qt::AlignCenter);
    choiceWidgetsLayout->addWidget(backButton, 0, Qt::AlignCenter);
    
    choiceFrame->setLayout(choiceWidgetsLayout);
    
    // Layout esterno per centratura
    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->addStretch();
    outerLayout->addWidget(choiceFrame, 0, Qt::AlignCenter);
    outerLayout->addStretch();
    
    setLayout(outerLayout);
}

void LibraryChoicePage::setupStyles() {
    setStyleSheet(
        // Background pagina
        "#libraryChoicePage {"
        "   background-image: url(:/Immagini/SfondoLogin.jpg);"
        "   background-repeat: no-repeat;"
        "   background-position: center center;"
        "   background-attachment: fixed;"
        "}"
        
        // Frame principale
        "#choiceFrame {"
        "   background-color: rgb(42, 68, 113);"
        "   border: 2px solid #000000;"
        "   border-radius: 10px;"
        "}"
        
        // Label benvenuto
        "#welcomeLabel {"
        "   background-color: #333333;"
        "   font-size: 24px;"
        "   font-weight: bold;"
        "   color: white;"
        "   padding: 10px;"
        "   border-radius: 5px;"
        "}"
        
        // Label descrizione
        "#descriptionLabel {"
        "   font-size: 18px;"
        "   color: white;"
        "   border: none;"
        "   margin: 10px 0px;"
        "}"
        
        // Pulsanti principali
        "#primaryButton {"
        "   background-color: rgb(225, 192, 37);"
        "   color: black;"
        "   border: 1px solid #AAAAAA;"
        "   border-radius: 8px;"
        "   font-size: 18px;"
        "}"
        "#primaryButton:hover {"
        "   background-color: rgb(184, 174, 90);"
        "}"
        "#primaryButton:pressed {"
        "   background-color: rgb(150, 140, 60);"
        "}"
        
        // Pulsante secondario
        "#secondaryButton {"
        "   background-color: rgb(0, 104, 201);"
        "   color: white;"
        "   border: 1px solid black;"
        "   border-radius: 5px;"
        "   font-size: 16px;"
        "}"
        "#secondaryButton:hover {"
        "   background-color: rgb(11, 82, 189);"
        "}"
        "#secondaryButton:pressed {"
        "   background-color: rgb(8, 65, 150);"
        "}"
    );
}

void LibraryChoicePage::setupConnections() {
    connect(loadFileButton, &QPushButton::clicked, 
            this, &LibraryChoicePage::onLoadFileButtonClicked);
    connect(newLibraryButton, &QPushButton::clicked, 
            this, &LibraryChoicePage::onNewLibraryButtonClicked);
    
    // Connessione diretta al segnale per il pulsante indietro
    connect(findChild<QPushButton*>("secondaryButton"), &QPushButton::clicked, 
            this, &LibraryChoicePage::goToLoginPage);
}

// ========================================
// SLOTS
// ========================================
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
            
            resetBiblioteca();
            
            if (loadFromFile(filePath)) {
                QMessageBox::information(this, "Caricamento completato", 
                    "I dati della biblioteca sono stati caricati con successo!");
                
                emit libraryReady(biblioteca, filePath, false);
            } else {
                QMessageBox::warning(this, "Errore di caricamento", 
                    "Impossibile caricare i dati dal file specificato.\n"
                    "Riprova con un altro file o crea una biblioteca vuota.");
                
                resetBiblioteca();
            }
        }
    }
}

void LibraryChoicePage::onNewLibraryButtonClicked() {
    resetBiblioteca();
    
    QMessageBox::information(this, "Biblioteca creata", 
        "Una nuova biblioteca vuota è stata creata con successo!");
    
    emit libraryReady(biblioteca, "", true);
}

// ========================================
// HELPER METHODS
// ========================================
void LibraryChoicePage::resetBiblioteca() {
    if (biblioteca) {
        delete biblioteca;
        biblioteca = nullptr;
    }
    
    biblioteca = new Biblioteca();
}

bool LibraryChoicePage::loadFromFile(const QString& filePath) {
    if (!biblioteca) {
        return false;
    }
    
    bool success = false;
    
    if (filePath.endsWith(".json", Qt::CaseInsensitive)) {
        JsonIO jsonLoader;
        success = jsonLoader.caricaDaFile(*biblioteca, filePath.toStdString());
    } else if (filePath.endsWith(".xml", Qt::CaseInsensitive)) {
        XmlIO xmlLoader;
        success = xmlLoader.caricaDaFile(*biblioteca, filePath.toStdString());
    }
    
    return success;
}