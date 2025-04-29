#include "../Headers/DetailsPage.h"
#include <QPainter>
#include <QResizeEvent>
#include <QSpacerItem>
#include <QFont>
#include <QFrame>
#include <QScrollArea>

DetailsPage::DetailsPage(QWidget *parent) : QWidget(parent), currentMedia(nullptr) {
    setupUI();
}

void DetailsPage::setupUI() {
    // Layout orizzontale principale
    QHBoxLayout *mainHLayout = new QHBoxLayout(this);
    mainHLayout->setContentsMargins(0, 0, 0, 0);
    mainHLayout->setSpacing(0);

    // Per dividere la pagina in barra laterale e area principale
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->setMinimumSize(300, 0);

    // Widget per la barra laterale
    QWidget *sidebarWidget = new QWidget();
    sidebarWidget->setObjectName("sidebarWidget");
    sidebarWidget->setStyleSheet("#sidebarWidget { background-color: rgb(42, 68, 113); }");

    // Layout verticale per la barra laterale
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
    connect(backButton, &QPushButton::clicked, this, &DetailsPage::onBackButtonClicked);
    sidebarLayout->addWidget(backButton, 0, Qt::AlignTop | Qt::AlignLeft);
      
    // 2. Sezione centrale per l'immagine grande
    imageLabel = new QLabel("Nessuna immagine disponibile");
    imageLabel->setMinimumSize(250, 250);
    imageLabel->setMaximumSize(400, 400);
    imageLabel->setScaledContents(true);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet(
        "border: 1px solid black;"
        "background-color: white;"
        "color: gray;"
        "padding: 5px;"
    );
    sidebarLayout->addWidget(imageLabel, 1);

    // 3. Pulsanti per le azioni disponibili
    QVBoxLayout *buttonsLayout = new QVBoxLayout();
    
    // Indicatore di copie disponibili
    availableCopiesLabel = new QLabel("Copie disponibili: 0");
    availableCopiesLabel->setAlignment(Qt::AlignCenter);
    availableCopiesLabel->setStyleSheet(
        "font-size: 16px;"
        "font-weight: bold;"
        "color: white;"
        "background-color: rgb(60, 85, 140);"
        "border-radius: 4px;"
        "padding: 8px;"
        "margin-bottom: 10px;"
    );
    buttonsLayout->addWidget(availableCopiesLabel);
    
    // Pulsante per prendere in prestito
    borrowButton = new QPushButton("Prendi in prestito");
    borrowButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 128, 0);"
        "   color: white;"
        "   border: 2px solid rgb(119, 114, 114);"
        "   border-radius: 6px;"
        "   font-size: 16px;"
        "   padding: 8px;"
        "   margin: 5px 0;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(0, 100, 0);"
        "}"
        "QPushButton:disabled {"
        "   background-color: rgb(150, 150, 150);"
        "   color: rgb(200, 200, 200);"
        "}"
    );
    connect(borrowButton, &QPushButton::clicked, this, &DetailsPage::onBorrowButtonClicked);
    buttonsLayout->addWidget(borrowButton);
    
    // Pulsante per restituire
    returnButton = new QPushButton("Restituisci");
    returnButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(255, 208, 0);"
        "   color: black;"
        "   border: 2px solid rgb(119, 114, 114);"
        "   border-radius: 6px;"
        "   font-size: 16px;"
        "   padding: 8px;"
        "   margin: 5px 0;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(255, 170, 0);"
        "}"
        "QPushButton:disabled {"
        "   background-color: rgb(150, 150, 150);"
        "   color: rgb(200, 200, 200);"
        "}"
    );
    connect(returnButton, &QPushButton::clicked, this, &DetailsPage::onReturnButtonClicked);
    buttonsLayout->addWidget(returnButton);
    
    // Pulsante per richiedere il media a una biblioteca affiliata
    requestButton = new QPushButton("Richiedi ad una biblioteca affiliata");
    requestButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(0, 104, 201);"
        "   color: white;"
        "   border: 2px solid rgb(119, 114, 114);"
        "   border-radius: 6px;"
        "   font-size: 16px;"
        "   padding: 8px;"
        "   margin: 5px 0;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(11, 82, 189);"
        "}"
        "QPushButton:disabled {"
        "   background-color: rgb(150, 150, 150);"
        "   color: rgb(200, 200, 200);"
        "}"
    );
    connect(requestButton, &QPushButton::clicked, this, &DetailsPage::onRequestButtonClicked);
    buttonsLayout->addWidget(requestButton);
    
    sidebarLayout->addLayout(buttonsLayout);
    sidebarLayout->addStretch();
    
    // Aggiungo la barra laterale al divisore
    splitter->addWidget(sidebarWidget);

    // Widget centrale per i dettagli del media
    QWidget *detailsWidget = new QWidget();
    detailsWidget->setStyleSheet("background-color: rgb(81, 125, 187);");
    
    // Layout per i dettagli
    QVBoxLayout *detailsLayout = new QVBoxLayout(detailsWidget);
    detailsLayout->setContentsMargins(20, 20, 20, 20);
    
    // Scroll area per contenere tutti i dettagli
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("background: transparent;");
    
    QWidget *scrollContent = new QWidget();
    scrollContent->setStyleSheet("background: transparent;");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setSpacing(15);
    
    // Titolo del media
    mediaTitleLabel = new QLabel("Titolo del Media");
    mediaTitleLabel->setStyleSheet(
        "font-size: 28px; "
        "font-weight: bold; "
        "color: white; "
        "background-color: rgba(0, 0, 0, 120); "
        "padding: 10px; "
        "border-radius: 5px;"
    );
    mediaTitleLabel->setAlignment(Qt::AlignCenter);
    scrollLayout->addWidget(mediaTitleLabel);
    
    // Tipo di media
    mediaTypeLabel = new QLabel("Tipo: ");
    mediaTypeLabel->setStyleSheet(
        "font-size: 18px; "
        "color: white; "
        "background-color: rgba(0, 0, 0, 80); "
        "padding: 5px; "
        "border-radius: 3px;"
    );
    mediaTypeLabel->setAlignment(Qt::AlignCenter);
    scrollLayout->addWidget(mediaTypeLabel);
    
    // Separatore
    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setStyleSheet("background-color: white;");
    scrollLayout->addWidget(separator);
    
    // Sezione dettagli comuni
    QFormLayout *commonDetailsLayout = new QFormLayout();
    commonDetailsLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    commonDetailsLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    commonDetailsLayout->setHorizontalSpacing(20);
    commonDetailsLayout->setVerticalSpacing(12);
    
    QString labelStyle = "font-size: 16px; font-weight: bold; color: white;";
    QString valueStyle = "font-size: 16px; color: white;";
    
    QLabel *authorTitleLabel = new QLabel("Autore:");
    authorTitleLabel->setStyleSheet(labelStyle);
    authorLabel = new QLabel("");
    authorLabel->setStyleSheet(valueStyle);
    commonDetailsLayout->addRow(authorTitleLabel, authorLabel);
    
    QLabel *genreTitleLabel = new QLabel("Genere:");
    genreTitleLabel->setStyleSheet(labelStyle);
    genreLabel = new QLabel("");
    genreLabel->setStyleSheet(valueStyle);
    commonDetailsLayout->addRow(genreTitleLabel, genreLabel);
    
    QLabel *yearTitleLabel = new QLabel("Anno:");
    yearTitleLabel->setStyleSheet(labelStyle);
    yearLabel = new QLabel("");
    yearLabel->setStyleSheet(valueStyle);
    commonDetailsLayout->addRow(yearTitleLabel, yearLabel);
    
    QLabel *languageTitleLabel = new QLabel("Lingua:");
    languageTitleLabel->setStyleSheet(labelStyle);
    languageLabel = new QLabel("");
    languageLabel->setStyleSheet(valueStyle);
    commonDetailsLayout->addRow(languageTitleLabel, languageLabel);
    
    QLabel *ratingTitleLabel = new QLabel("Valutazione:");
    ratingTitleLabel->setStyleSheet(labelStyle);
    ratingLabel = new QLabel("");
    ratingLabel->setStyleSheet(valueStyle);
    commonDetailsLayout->addRow(ratingTitleLabel, ratingLabel);
    
    scrollLayout->addLayout(commonDetailsLayout);
    
    // Separatore
    QFrame *separator2 = new QFrame();
    separator2->setFrameShape(QFrame::HLine);
    separator2->setFrameShadow(QFrame::Sunken);
    separator2->setStyleSheet("background-color: white;");
    scrollLayout->addWidget(separator2);
    
    // Container per dettagli specifici del tipo di media
    specificDetailsContainer = new QWidget();
    specificDetailsLayout = new QVBoxLayout(specificDetailsContainer);
    specificDetailsLayout->setContentsMargins(0, 0, 0, 0);
    scrollLayout->addWidget(specificDetailsContainer);
    
    // Aggiungi spazio vuoto alla fine
    scrollLayout->addStretch();
    
    scrollArea->setWidget(scrollContent);
    detailsLayout->addWidget(scrollArea);
    
    // Aggiungi il widget dei dettagli al divisore
    splitter->addWidget(detailsWidget);
    
    // Imposta la proporzione iniziale tra i due widget (1:2)
    splitter->setStretchFactor(0, 2);  // Sidebar (1/3)
    splitter->setStretchFactor(1, 3);  // Main details area (2/3)
    
    // Aggiunge il divisore al layout principale
    mainHLayout->addWidget(splitter);
    
    setLayout(mainHLayout);
    
    // Inizialmente disabilita i pulsanti
    borrowButton->setEnabled(false);
    returnButton->setEnabled(false);
    requestButton->setEnabled(false);
}

void DetailsPage::setMedia(Media* media) {
    currentMedia = media;
    if (currentMedia) {
        updateUI();
        updateAvailability();
        displaySpecificDetails();
    }
}

void DetailsPage::updateUI() {
    if (!currentMedia) return;
    
    // Aggiorna il titolo
    mediaTitleLabel->setText(QString::fromStdString(currentMedia->getTitolo()));
    
    // Determina il tipo di media e imposta l'etichetta
    QString mediaType;
    if (dynamic_cast<Libro*>(currentMedia)) {
        mediaType = "Libro";
    } else if (dynamic_cast<Film*>(currentMedia)) {
        mediaType = "Film";
    } else if (dynamic_cast<Vinile*>(currentMedia)) {
        mediaType = "Vinile";
    } else if (dynamic_cast<GiocoDaTavolo*>(currentMedia)) {
        mediaType = "Gioco da Tavolo";
    } else if (dynamic_cast<Rivista*>(currentMedia)) {
        mediaType = "Rivista";
    } else {
        mediaType = "Media";
    }
    mediaTypeLabel->setText("Tipo: " + mediaType);
    
    // Aggiorna le informazioni comuni
    authorLabel->setText(QString::fromStdString(currentMedia->getAutore()));
    genreLabel->setText(QString::fromStdString(currentMedia->getGenere()));
    yearLabel->setText(QString::number(currentMedia->getAnno()));
    languageLabel->setText(QString::fromStdString(currentMedia->getLingua()));
    
    // Aggiorna il rating con le stelline
    double rating = currentMedia->getRating();
    QString stars = QString("%1 %2").arg(QString("★").repeated(static_cast<int>(rating))).arg(QString::number(rating, 'f', 1));
    ratingLabel->setText(stars);
    
    // Aggiorna l'immagine
    QPixmap pixmap(QString::fromStdString(currentMedia->getImmagine()));
    if (!pixmap.isNull()) {
        originalPixmap = pixmap;
        updateImageSize();
    } else {
        imageLabel->setText("Immagine non disponibile");
    }
}

void DetailsPage::updateAvailability() {
    if (!currentMedia) return;
    
    int totalCopies = currentMedia->getNumeroCopie();
    int borrowedCopies = currentMedia->getInPrestito(); // Correzione qui
    int availableCopies = totalCopies - borrowedCopies;
    
    availableCopiesLabel->setText(QString("Copie disponibili: %1/%2").arg(availableCopies).arg(totalCopies));
    
    // Aggiorna lo stile in base alla disponibilità
    if (availableCopies > 0) {
        availableCopiesLabel->setStyleSheet(
            "font-size: 16px;"
            "font-weight: bold;"
            "color: white;"
            "background-color: rgb(0, 128, 0);"
            "border-radius: 4px;"
            "padding: 8px;"
            "margin-bottom: 10px;"
        );
    } else {
        availableCopiesLabel->setStyleSheet(
            "font-size: 16px;"
            "font-weight: bold;"
            "color: white;"
            "background-color: rgb(200, 0, 0);"
            "border-radius: 4px;"
            "padding: 8px;"
            "margin-bottom: 10px;"
        );
    }
    
    // Abilita o disabilita i pulsanti in base alla disponibilità
    borrowButton->setEnabled(availableCopies > 0);
    returnButton->setEnabled(borrowedCopies > 0);
    requestButton->setEnabled(availableCopies == 0);
}

void DetailsPage::displaySpecificDetails() {
    // Rimuovi i widget esistenti dal layout
    QLayoutItem* item;
    while ((item = specificDetailsLayout->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    
    if (!currentMedia) return;
    
    QFormLayout* specificForm = new QFormLayout();
    specificForm->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    specificForm->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    specificForm->setHorizontalSpacing(20);
    specificForm->setVerticalSpacing(12);
    
    QString labelStyle = "font-size: 16px; font-weight: bold; color: white;";
    QString valueStyle = "font-size: 16px; color: white;";
    
    QLabel* specificDetailsTitle = new QLabel("Dettagli specifici");
    specificDetailsTitle->setStyleSheet(
        "font-size: 20px; "
        "font-weight: bold; "
        "color: white; "
        "background-color: rgba(0, 0, 0, 80); "
        "padding: 5px; "
        "border-radius: 3px;"
    );
    specificDetailsTitle->setAlignment(Qt::AlignCenter);
    specificDetailsLayout->addWidget(specificDetailsTitle);
    
    // Determina il tipo di media e mostra i dettagli specifici
    if (Libro* libro = dynamic_cast<Libro*>(currentMedia)) {
        QLabel* isbnLabel = new QLabel("ISBN:");
        isbnLabel->setStyleSheet(labelStyle);
        QLabel* isbnValue = new QLabel(QString::fromStdString(libro->getIsbn()));
        isbnValue->setStyleSheet(valueStyle);
        specificForm->addRow(isbnLabel, isbnValue);
        
        QLabel* editorLabel = new QLabel("Editore:");
        editorLabel->setStyleSheet(labelStyle);
        QLabel* editorValue = new QLabel(QString::fromStdString(libro->getEditore()));
        editorValue->setStyleSheet(valueStyle);
        specificForm->addRow(editorLabel, editorValue);
        
        QLabel* pagesLabel = new QLabel("Pagine:");
        pagesLabel->setStyleSheet(labelStyle);
        QLabel* pagesValue = new QLabel(QString::number(libro->getNPagine())); // Correzione qui
        pagesValue->setStyleSheet(valueStyle);
        specificForm->addRow(pagesLabel, pagesValue);
        
        QLabel* locationLabel = new QLabel("Collocazione:");
        locationLabel->setStyleSheet(labelStyle);
        QLabel* locationValue = new QLabel(QString::fromStdString(libro->getCollocazione()));
        locationValue->setStyleSheet(valueStyle);
        specificForm->addRow(locationLabel, locationValue);
    }
    else if (Film* film = dynamic_cast<Film*>(currentMedia)) {
        QLabel* durationLabel = new QLabel("Durata:");
        durationLabel->setStyleSheet(labelStyle);
        QLabel* durationValue = new QLabel(QString("%1 minuti").arg(film->getDurata()));
        durationValue->setStyleSheet(valueStyle);
        specificForm->addRow(durationLabel, durationValue);
        
        QLabel* castLabel = new QLabel("Cast:");
        castLabel->setStyleSheet(labelStyle);
        QString castList;
        for (const auto& actor : film->getCast()) {
            if (!castList.isEmpty()) castList += ", ";
            castList += QString::fromStdString(actor);
        }
        QLabel* castValue = new QLabel(castList);
        castValue->setStyleSheet(valueStyle);
        castValue->setWordWrap(true);
        specificForm->addRow(castLabel, castValue);
        
        QLabel* locationLabel = new QLabel("Collocazione:");
        locationLabel->setStyleSheet(labelStyle);
        QLabel* locationValue = new QLabel(QString::fromStdString(film->getCollocazione()));
        locationValue->setStyleSheet(valueStyle);
        specificForm->addRow(locationLabel, locationValue);
    }
    else if (Vinile* vinile = dynamic_cast<Vinile*>(currentMedia)) {
        QLabel* tracksLabel = new QLabel("Numero tracce:");
        tracksLabel->setStyleSheet(labelStyle);
        QLabel* tracksValue = new QLabel(QString::number(vinile->getNTracce())); 
        tracksValue->setStyleSheet(valueStyle);
        specificForm->addRow(tracksLabel, tracksValue);
        
        QLabel* durationLabel = new QLabel("Durata:");
        durationLabel->setStyleSheet(labelStyle);
        QLabel* durationValue = new QLabel(QString("%1 minuti").arg(vinile->getDurata()));
        durationValue->setStyleSheet(valueStyle);
        specificForm->addRow(durationLabel, durationValue);
        
        QLabel* locationLabel = new QLabel("Collocazione:");
        locationLabel->setStyleSheet(labelStyle);
        QLabel* locationValue = new QLabel(QString::fromStdString(vinile->getCollocazione()));
        locationValue->setStyleSheet(valueStyle);
        specificForm->addRow(locationLabel, locationValue);
    }
    else if (GiocoDaTavolo* gioco = dynamic_cast<GiocoDaTavolo*>(currentMedia)) {
        
        QLabel* durationLabel = new QLabel("Durata:");
        durationLabel->setStyleSheet(labelStyle);
        QLabel* durationValue = new QLabel(QString("%1 minuti").arg(gioco->getDurata()));
        durationValue->setStyleSheet(valueStyle);
        specificForm->addRow(durationLabel, durationValue);
        
        QLabel* creatorLabel = new QLabel("Creatore:");
        creatorLabel->setStyleSheet(labelStyle);
        QLabel* creatorValue = new QLabel(QString::fromStdString(gioco->getEditore()));
        creatorValue->setStyleSheet(valueStyle);
        specificForm->addRow(creatorLabel, creatorValue);
        
        QLabel* locationLabel = new QLabel("Collocazione:");
        locationLabel->setStyleSheet(labelStyle);
        QLabel* locationValue = new QLabel(QString::fromStdString(gioco->getCollocazione()));
        locationValue->setStyleSheet(valueStyle);
        specificForm->addRow(locationLabel, locationValue);
    }
    else if (Rivista* rivista = dynamic_cast<Rivista*>(currentMedia)) {
        QLabel* editorLabel = new QLabel("Editore:");
        editorLabel->setStyleSheet(labelStyle);
        QLabel* editorValue = new QLabel(QString::fromStdString(rivista->getEditore()));
        editorValue->setStyleSheet(valueStyle);
        specificForm->addRow(editorLabel, editorValue);
        
        QLabel* pagesLabel = new QLabel("Pagine:");
        pagesLabel->setStyleSheet(labelStyle);
        QLabel* pagesValue = new QLabel(QString::number(rivista->getNPagine())); 
        pagesValue->setStyleSheet(valueStyle);
        specificForm->addRow(pagesLabel, pagesValue);
        
        QLabel* pubDateLabel = new QLabel("Data pubblicazione:");
        pubDateLabel->setStyleSheet(labelStyle);
        QLabel* pubDateValue = new QLabel(QString::fromStdString(rivista->getDataPubb()));
        pubDateValue->setStyleSheet(valueStyle);
        specificForm->addRow(pubDateLabel, pubDateValue);
        
        QLabel* periodLabel = new QLabel("Periodicità:");
        periodLabel->setStyleSheet(labelStyle);
        QLabel* periodValue = new QLabel(QString::fromStdString(rivista->getPeriodicita()));
        periodValue->setStyleSheet(valueStyle);
        specificForm->addRow(periodLabel, periodValue);
        
        QLabel* locationLabel = new QLabel("Collocazione:");
        locationLabel->setStyleSheet(labelStyle);
        QLabel* locationValue = new QLabel(QString::fromStdString(rivista->getCollocazione()));
        locationValue->setStyleSheet(valueStyle);
        specificForm->addRow(locationLabel, locationValue);
    }
    
    specificDetailsLayout->addLayout(specificForm);
}

void DetailsPage::updateImageSize() {
    if (originalPixmap.isNull()) return;
    
    int maxWidth = imageLabel->width();
    int maxHeight = imageLabel->height();
    
    QPixmap scaledPixmap = originalPixmap.scaled(
        maxWidth, 
        maxHeight, 
        Qt::KeepAspectRatio, 
        Qt::SmoothTransformation
    );
    
    imageLabel->setPixmap(scaledPixmap);
}

void DetailsPage::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    updateImageSize();
}

void DetailsPage::onBackButtonClicked() {
    emit goBackToMainPage();
}

void DetailsPage::onBorrowButtonClicked() {
    if (!currentMedia) return;
    
    int totalCopies = currentMedia->getNumeroCopie();
    int borrowedCopies = currentMedia->getInPrestito(); // Correzione qui
    
    if (borrowedCopies < totalCopies) {
        currentMedia->setInPrestito(borrowedCopies + 1); // Correzione qui
        updateAvailability();
        
        QString message = QString("Il media \"%1\" è stato dato in prestito.\nCopie disponibili rimanenti: %2")
                              .arg(QString::fromStdString(currentMedia->getTitolo()))
                              .arg(totalCopies - borrowedCopies - 1);
        QMessageBox::information(this, "Prestito effettuato", message);
        
        emit mediaBorrowed(currentMedia);
    } else {
        QMessageBox::warning(this, "Errore", "Nessuna copia disponibile per il prestito.");
    }
}

void DetailsPage::onReturnButtonClicked() {
    if (!currentMedia) return;
    
    int borrowedCopies = currentMedia->getInPrestito(); // Correzione qui
    
    if (borrowedCopies > 0) {
        currentMedia->setInPrestito(borrowedCopies - 1); // Correzione qui
        updateAvailability();
        
        QString message = QString("Il media \"%1\" è stato restituito.\nCopie disponibili ora: %2")
                              .arg(QString::fromStdString(currentMedia->getTitolo()))
                              .arg(currentMedia->getNumeroCopie() - borrowedCopies + 1);
        QMessageBox::information(this, "Restituzione registrata", message);
        
        emit mediaReturned(currentMedia);
    } else {
        QMessageBox::warning(this, "Errore", "Non ci sono copie di questo media in prestito da restituire.");
    }
}

void DetailsPage::onRequestButtonClicked() {
    if (!currentMedia) return;
    
    QString message = QString("Richiesta di \"%1\" inviata alle biblioteche affiliate.\nRiceverai una notifica quando sarà disponibile.")
                          .arg(QString::fromStdString(currentMedia->getTitolo()));
    QMessageBox::information(this, "Richiesta inoltrata", message);
}