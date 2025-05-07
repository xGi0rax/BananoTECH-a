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
    backButton = new QPushButton("Indietro");
    backButton->setMinimumSize(100, 30); // Stesse dimensioni degli altri pulsanti
    backButton->setCursor(Qt::PointingHandCursor);
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
    imageLabel->setStyleSheet("border: 1px rgb(60, 58, 58);");
    
    // Dettagli base
    QVBoxLayout *basicDetailsLayout = new QVBoxLayout();
    basicDetailsLayout->setSpacing(15);
    
    titleLabel = new QLabel();
    authorLabel = new QLabel();
    genreLabel = new QLabel();
    yearLabel = new QLabel();
    availabilityLabel = new QLabel();
    copiesLabel = new QLabel();
    
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    authorLabel->setStyleSheet("font-size: 16px;");
    genreLabel->setStyleSheet("font-size: 14px;");
    yearLabel->setStyleSheet("font-size: 14px;");
    availabilityLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
    copiesLabel->setStyleSheet("font-size: 14px; font-weight: bold;"); 

    basicDetailsLayout->addWidget(titleLabel);
    basicDetailsLayout->addWidget(authorLabel);
    basicDetailsLayout->addWidget(genreLabel);
    basicDetailsLayout->addWidget(yearLabel);
    basicDetailsLayout->addWidget(copiesLabel); 
    basicDetailsLayout->addSpacing(10);
    basicDetailsLayout->addWidget(availabilityLabel);
    
    // Pulsanti per prestito/restituzione
    borrowButton = new QPushButton("Prendi in prestito");
    returnButton = new QPushButton("Restituisci");
    
    borrowButton->setStyleSheet("QPushButton { background-color: #00A000; color: white; padding: 10px 20px; font-size: 14px; border: none; border-radius: 4px; } QPushButton:hover { background-color: #008000; } QPushButton:disabled { background-color: #888888; }");
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
    
    // Sezione per dettagli specifici, da sistemare
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
    
    // Calcolo e visualizzo le copie disponibili
    int totalCopies = currentMedia->getNumeroCopie();
    int loanedCopies = currentMedia->getInPrestito();
    int availableCopies = totalCopies - loanedCopies;
    
    copiesLabel->setText("Copie disponibili: " + QString::number(availableCopies) + 
                         " su " + QString::number(totalCopies) + " totali");
    
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
        if (availableCopies > 0) {
            availabilityLabel->setText("Disponibile");
            availabilityLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: green;");
        } else {
            availabilityLabel->setText("Non disponibile (tutte le copie in prestito)");
            availabilityLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: orange;");
        }
    } else {
        availabilityLabel->setText("Non disponibile");
        availabilityLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: red;");
    }
    
    // Mostro sempre entrambi i pulsanti, ma li abilito/disabilito in base alla disponibilità
    borrowButton->setVisible(true);
    returnButton->setVisible(true);
    
    // Pulsante "Prendi in prestito" abilitato solo se ci sono copie disponibili
    borrowButton->setEnabled(availableCopies > 0);
    
    // Pulsante "Restituisci" abilitato solo se ci sono copie in prestito
    returnButton->setEnabled(loanedCopies > 0);
    
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
    
    currentDetailsWidget = nullptr;
}

void DetailsPage::setupSpecificDetails(Media* media) {
    if (!media) return;
    
    // Crea un widget appropriato in base al tipo di media
    currentDetailsWidget = createViewWidgetForMedia(media);
    
    if (currentDetailsWidget) {
        // Imposta alcune proprietà per la visualizzazione
        currentDetailsWidget->setProperty("viewOnly", true);
        specificDetailsLayout->addWidget(currentDetailsWidget);
    }
}

QWidget* DetailsPage::createViewWidgetForMedia(Media* media) {
    QWidget* widget = nullptr;
    
    if (Film* film = dynamic_cast<Film*>(media)) {
        // Crea un FilmDetailsWidget e configuralo per la visualizzazione
        FilmDetailsWidget* filmWidget = new FilmDetailsWidget();
        filmWidget->setMedia(film);
        filmWidget->setReadOnly(true);  // Imposta la modalità sola lettura
        widget = filmWidget;
    } 
    else if (Libro* libro = dynamic_cast<Libro*>(media)) {
        LibroDetailsWidget* libroWidget = new LibroDetailsWidget();
        libroWidget->setMedia(libro);
        libroWidget->setReadOnly(true);
        widget = libroWidget;
    } 
    else if (Vinile* vinile = dynamic_cast<Vinile*>(media)) {
        VinileDetailsWidget* vinileWidget = new VinileDetailsWidget();
        vinileWidget->setMedia(vinile);
        vinileWidget->setReadOnly(true);
        widget = vinileWidget;
    } 
    else if (Rivista* rivista = dynamic_cast<Rivista*>(media)) {
        RivistaDetailsWidget* rivistaWidget = new RivistaDetailsWidget();
        rivistaWidget->setMedia(rivista);
        rivistaWidget->setReadOnly(true);
        widget = rivistaWidget;
    } 
    else if (GiocoDaTavolo* gioco = dynamic_cast<GiocoDaTavolo*>(media)) {
        GiocoDetailsWidget* giocoWidget = new GiocoDetailsWidget();
        giocoWidget->setMedia(gioco);
        giocoWidget->setReadOnly(true);
        widget = giocoWidget;
    }
    
    return widget;
}

void DetailsPage::onBackButtonClicked() {
    emit goBackToMainPage();
}

void DetailsPage::onBorrowButtonClicked() {
    if (!currentMedia) return;
    
    // Verifico che il media sia disponibile e che ci siano copie disponibili
    int availableCopies = currentMedia->getNumeroCopie() - currentMedia->getInPrestito();
    
    if (currentMedia->getDisponibilita() && availableCopies > 0) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, 
            "Conferma prestito", 
            "Confermi di voler prendere in prestito questo media?",
            QMessageBox::Yes | QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            // Aggiorno lo stato del media
            currentMedia->setInPrestito(currentMedia->getInPrestito() + 1); // Incremento il contatore dei prestiti
            
            // Se era l'ultima copia disponibile, imposto il media come non disponibile
            if (currentMedia->getNumeroCopie() - currentMedia->getInPrestito() == 0) {
                currentMedia->setDisponibilita(false);
            }
            
            // Aggiorno l'interfaccia
            updateUI();
            
            // Emetto un segnale per notificare che il media è stato prestato
            emit mediaBorrowed(currentMedia);
            
            QMessageBox::information(this, "Prestito", "Media preso in prestito con successo!");
        }
    } else {
        QMessageBox::warning(this, "Prestito non disponibile", 
            "Questo media non è attualmente disponibile per il prestito.");
    }
}

void DetailsPage::onReturnButtonClicked() {
    if (!currentMedia) return;
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, 
        "Conferma restituzione", 
        "Confermi di voler restituire questo media?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Aggiorno lo stato del media
        if (currentMedia->getInPrestito() > 0) {
            currentMedia->setInPrestito(currentMedia->getInPrestito() - 1); // Decremento il contatore dei prestiti
            
            // Se il media era segnato come non disponibile, ora lo rendiamo disponibile
            if (!currentMedia->getDisponibilita()) {
                currentMedia->setDisponibilita(true);
            }
            
            // Aggiorno l'interfaccia
            updateUI();
            
            // Emetto un segnale per notificare che il media è stato restituito
            emit mediaReturned(currentMedia);
            
            QMessageBox::information(this, "Restituzione", "Media restituito con successo!");
        } else {
            QMessageBox::warning(this, "Errore", "Nessuna copia di questo media risulta in prestito!");
        }
    }
}