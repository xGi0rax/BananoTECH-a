#include "../Headers/DetailsPage.h"
#include <QMessageBox>
#include <QPixmap>
#include <QFile>

DetailsPage::DetailsPage(QWidget *parent) : QWidget(parent), currentMedia(nullptr) {
    setupUI();
}

void DetailsPage::setupUI() {
    // Layout principale
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Pulsante indietro
    backButton = new QPushButton("Indietro", this);
    backButton->setStyleSheet("QPushButton { background-color: #0068C9; color: white; padding: 8px 20px; font-size: 14px; border: none; border-radius: 4px; } QPushButton:hover { background-color: #0B52BD; }");
    connect(backButton, &QPushButton::clicked, this, &DetailsPage::onBackButtonClicked);
    
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(backButton, 0, Qt::AlignLeft);
    mainLayout->addLayout(headerLayout);
    
    // Area principale con dettagli del media
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    
    QWidget *contentWidget = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setSpacing(20);
    
    // Layout orizzontale per immagine e dettagli base
    QHBoxLayout *mediaDetailsLayout = new QHBoxLayout();
    
    // Immagine
    imageLabel = new QLabel();
    imageLabel->setFixedSize(250, 350);
    imageLabel->setScaledContents(true);
    imageLabel->setStyleSheet("border: 1px solid #CCCCCC;");
    
    // Dettagli base
    QVBoxLayout *basicDetailsLayout = new QVBoxLayout();
    basicDetailsLayout->setSpacing(10);
    
    titleLabel = new QLabel();
    authorLabel = new QLabel();
    genreLabel = new QLabel();
    yearLabel = new QLabel();
    availabilityLabel = new QLabel();
    
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    authorLabel->setStyleSheet("font-size: 16px;");
    genreLabel->setStyleSheet("font-size: 14px;");
    yearLabel->setStyleSheet("font-size: 14px;");
    availabilityLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
    
    basicDetailsLayout->addWidget(titleLabel);
    basicDetailsLayout->addWidget(authorLabel);
    basicDetailsLayout->addWidget(genreLabel);
    basicDetailsLayout->addWidget(yearLabel);
    basicDetailsLayout->addSpacing(20);
    basicDetailsLayout->addWidget(availabilityLabel);
    
    // Pulsanti per prestito/restituzione
    borrowButton = new QPushButton("Prendi in prestito");
    returnButton = new QPushButton("Restituisci");
    
    borrowButton->setStyleSheet("QPushButton { background-color: #00A000; color: white; padding: 10px 20px; font-size: 14px; border: none; border-radius: 4px; } QPushButton:hover { background-color: #008000; }");
    returnButton->setStyleSheet("QPushButton { background-color: #C00000; color: white; padding: 10px 20px; font-size: 14px; border: none; border-radius: 4px; } QPushButton:hover { background-color: #A00000; }");
    
    connect(borrowButton, &QPushButton::clicked, this, &DetailsPage::onBorrowButtonClicked);
    connect(returnButton, &QPushButton::clicked, this, &DetailsPage::onReturnButtonClicked);
    
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(borrowButton);
    buttonsLayout->addWidget(returnButton);
    
    basicDetailsLayout->addLayout(buttonsLayout);
    basicDetailsLayout->addStretch(1);
    
    mediaDetailsLayout->addWidget(imageLabel);
    mediaDetailsLayout->addSpacing(20);
    mediaDetailsLayout->addLayout(basicDetailsLayout, 1);
    
    contentLayout->addLayout(mediaDetailsLayout);
    
    // Sezione per dettagli specifici
    QFrame *separatorLine = new QFrame();
    separatorLine->setFrameShape(QFrame::HLine);
    separatorLine->setFrameShadow(QFrame::Sunken);
    contentLayout->addWidget(separatorLine);
    
    QLabel *specificDetailsTitle = new QLabel("Dettagli specifici");
    specificDetailsTitle->setStyleSheet("font-size: 18px; font-weight: bold; margin-top: 10px;");
    contentLayout->addWidget(specificDetailsTitle);
    
    specificDetailsLayout = new QVBoxLayout();
    contentLayout->addLayout(specificDetailsLayout);
    
    contentLayout->addStretch(1);
    
    scrollArea->setWidget(contentWidget);
    mainLayout->addWidget(scrollArea, 1);
    
    // Inizialmente nascondo i pulsanti di prestito/restituzione
    borrowButton->setVisible(false);
    returnButton->setVisible(false);
}

void DetailsPage::setMedia(Media* media) {
    currentMedia = media;
    updateUI();
}

void DetailsPage::updateUI() {
    if (!currentMedia) {
        return;
    }
    
    // Aggiorno informazioni base
    titleLabel->setText(QString::fromStdString(currentMedia->getTitolo()));
    authorLabel->setText(QString::fromStdString(currentMedia->getAutore()));
    genreLabel->setText("Genere: " + QString::fromStdString(currentMedia->getGenere()));
    yearLabel->setText("Anno: " + QString::number(currentMedia->getAnno()));
    
    // Gestisco l'immagine
    QString imagePath = QString::fromStdString(currentMedia->getImmagine());
    if (imagePath.isEmpty() || !QFile::exists(imagePath)) {
        // Uso un'immagine di default se quella specificata non esiste
        imageLabel->setPixmap(QPixmap(":/images/default.png"));
    } else {
        imageLabel->setPixmap(QPixmap(imagePath));
    }
    
    // Aggiorno stato disponibilità
    if (currentMedia->getDisponibilita()) {
        availabilityLabel->setText("Disponibile");
        availabilityLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: green;");
        borrowButton->setVisible(true);
        returnButton->setVisible(false);
    } else {
        availabilityLabel->setText("Non disponibile");
        availabilityLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: red;");
        borrowButton->setVisible(false);
        returnButton->setVisible(true);
    }
    
    // Pulisco e ricreo i dettagli specifici
    clearSpecificDetails();
    setupSpecificDetails(currentMedia);
}

void DetailsPage::clearSpecificDetails() {
    // Cancello tutti gli elementi nel layout di dettagli specifici
    QLayoutItem *item;
    while ((item = specificDetailsLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void DetailsPage::setupSpecificDetails(Media* media) {
    if (!media) return;
    
    // Uso RTTI (Run-Time Type Information) per determinare il tipo di media
    if (Film* film = dynamic_cast<Film*>(media)) {
        setupFilmDetails(film);
    } else if (Libro* libro = dynamic_cast<Libro*>(media)) {
        setupLibroDetails(libro);
    } else if (Vinile* vinile = dynamic_cast<Vinile*>(media)) {
        setupVinileDetails(vinile);
    } else if (Rivista* rivista = dynamic_cast<Rivista*>(media)) {
        setupRivistaDetails(rivista);
    } else if (GiocoDaTavolo* gioco = dynamic_cast<GiocoDaTavolo*>(media)) {
        setupGiocoDetails(gioco);
    }
}

void DetailsPage::setupFilmDetails(Film* film) {
    // Durata
    QLabel *durationLabel = new QLabel("Durata: " + QString::number(film->getDurata()) + " minuti");
    durationLabel->setStyleSheet("font-size: 14px;");
    specificDetailsLayout->addWidget(durationLabel);
    
    // Cast
    const vector<string>& cast = film->getCast();
    if (!cast.empty()) {
        QLabel *castTitle = new QLabel("Cast:");
        castTitle->setStyleSheet("font-size: 14px; font-weight: bold;");
        specificDetailsLayout->addWidget(castTitle);
        
        QString castStr;
        for (size_t i = 0; i < cast.size(); ++i) {
            castStr += QString::fromStdString(cast[i]);
            if (i < cast.size() - 1) {
                castStr += ", ";
            }
        }
        
        QLabel *castLabel = new QLabel(castStr);
        castLabel->setWordWrap(true);
        castLabel->setStyleSheet("font-size: 14px;");
        specificDetailsLayout->addWidget(castLabel);
    }
}

void DetailsPage::setupLibroDetails(Libro* libro) {
    // ISBN
    QLabel *isbnLabel = new QLabel("ISBN: " + QString::fromStdString(libro->getIsbn()));
    isbnLabel->setStyleSheet("font-size: 14px;");
    specificDetailsLayout->addWidget(isbnLabel);
    
    // Editore
    QLabel *editorLabel = new QLabel("Editore: " + QString::fromStdString(libro->getEditore()));
    editorLabel->setStyleSheet("font-size: 14px;");
    specificDetailsLayout->addWidget(editorLabel);
    
    // Pagine
    QLabel *pagesLabel = new QLabel("Pagine: " + QString::number(libro->getNPagine()));
    pagesLabel->setStyleSheet("font-size: 14px;");
    specificDetailsLayout->addWidget(pagesLabel);
}

void DetailsPage::setupVinileDetails(Vinile* vinile) {
    // Numero di tracce
    QLabel *tracksLabel = new QLabel("Numero tracce: " + QString::number(vinile->getNTracce()));
    tracksLabel->setStyleSheet("font-size: 14px;");
    specificDetailsLayout->addWidget(tracksLabel);
    
    // Durata
    QLabel *durationLabel = new QLabel("Durata: " + QString::number(vinile->getDurata()) + " minuti");
    durationLabel->setStyleSheet("font-size: 14px;");
    specificDetailsLayout->addWidget(durationLabel);
}

void DetailsPage::setupRivistaDetails(Rivista* rivista) {
    // Editore
    QLabel *editorLabel = new QLabel("Editore: " + QString::fromStdString(rivista->getEditore()));
    editorLabel->setStyleSheet("font-size: 14px;");
    specificDetailsLayout->addWidget(editorLabel);
    
    // Pagine
    QLabel *pagesLabel = new QLabel("Pagine: " + QString::number(rivista->getNPagine()));
    pagesLabel->setStyleSheet("font-size: 14px;");
    specificDetailsLayout->addWidget(pagesLabel);
    
    // Data di pubblicazione
    QLabel *dateLabel = new QLabel("Data pubblicazione: " + QString::fromStdString(rivista->getDataPubb()));
    dateLabel->setStyleSheet("font-size: 14px;");
    specificDetailsLayout->addWidget(dateLabel);
    
    // Periodicità
    QLabel *periodicityLabel = new QLabel("Periodicità: " + QString::fromStdString(rivista->getPeriodicita()));
    periodicityLabel->setStyleSheet("font-size: 14px;");
    specificDetailsLayout->addWidget(periodicityLabel);
}

void DetailsPage::setupGiocoDetails(GiocoDaTavolo* gioco) {
    // Numero di giocatori
    QLabel *playersLabel = new QLabel("Giocatori: " + QString::number(gioco->getNGiocatori()));
    playersLabel->setStyleSheet("font-size: 14px;");
    specificDetailsLayout->addWidget(playersLabel);
    
    // Durata
    QLabel *durationLabel = new QLabel("Durata: " + QString::number(gioco->getDurata()) + " minuti");
    durationLabel->setStyleSheet("font-size: 14px;");
    specificDetailsLayout->addWidget(durationLabel);
    
    // Età minima
    QLabel *ageLabel = new QLabel("Età minima: " + QString::number(gioco->getEtaMinima()) + " anni");
    ageLabel->setStyleSheet("font-size: 14px;");
    specificDetailsLayout->addWidget(ageLabel);
    
    // Editore
    QLabel *editorLabel = new QLabel("Editore: " + QString::fromStdString(gioco->getEditore()));
    editorLabel->setStyleSheet("font-size: 14px;");
    specificDetailsLayout->addWidget(editorLabel);
}

void DetailsPage::onBackButtonClicked() {
    emit goBackToMainPage();
}

void DetailsPage::onBorrowButtonClicked() {
    if (currentMedia && currentMedia->getDisponibilita()) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, 
            "Conferma prestito", 
            "Confermi di voler prendere in prestito questo media?",
            QMessageBox::Yes | QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            // Aggiorno lo stato del media
            currentMedia->setDisponibilita(false);
           // currentMedia->incrementaPrestiti();
            
            // Aggiorno l'interfaccia
            updateUI();
            
            // Emetto un segnale per notificare che il media è stato prestato
            emit mediaBorrowed(currentMedia);
            
            QMessageBox::information(this, "Prestito", "Media preso in prestito con successo!");
        }
    }
}

void DetailsPage::onReturnButtonClicked() {
    if (currentMedia && !currentMedia->getDisponibilita()) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, 
            "Conferma restituzione", 
            "Confermi di voler restituire questo media?",
            QMessageBox::Yes | QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            // Aggiorno lo stato del media
            currentMedia->setDisponibilita(true);
            
            // Aggiorno l'interfaccia
            updateUI();
            
            // Emetto un segnale per notificare che il media è stato restituito
            emit mediaReturned(currentMedia);
            
            QMessageBox::information(this, "Restituzione", "Media restituito con successo!");
        }
    }
}