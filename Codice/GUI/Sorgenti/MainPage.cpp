#include "../Headers/MainPage.h"

MainPage::MainPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void MainPage::setupUI(){
    // Barra superiore
    backButton = new QPushButton("Indietro");
    addMediaButton = new QPushButton("Aggiungi Media");
    editModeButton = new QPushButton("Modalità Modifica");
    backButton->setMinimumSize(100, 30);
    addMediaButton->setMinimumSize(100, 30);
    editModeButton->setMinimumSize(100, 30);

    topBarLayout = new QHBoxLayout();
    topBarLayout->addWidget(backButton);
    topBarLayout->addWidget(addMediaButton);
    topBarLayout->addWidget(editModeButton);


    // Menu filtri
    mediaTypeComboBox = new QComboBox();
    mediaTypeComboBox->addItem("Qualsiasi");
    mediaTypeComboBox->addItem("Libro");
    mediaTypeComboBox->addItem("Film");
    mediaTypeComboBox->addItem("Vinile");
    mediaTypeComboBox->addItem("Gioco da tavolo");
    mediaTypeComboBox->addItem("Rivista");

    minYearLineEdit = new QLineEdit();
    minYearLineEdit->setPlaceholderText("Anno min");
    maxYearLineEdit = new QLineEdit();
    maxYearLineEdit->setPlaceholderText("Anno max");
    
    languageLineEdit = new QLineEdit();
    languageLineEdit->setPlaceholderText("Lingua");

    filtersLayout = new QVBoxLayout();
    filtersLayout->addWidget(new QLabel("Tipo media:"));
    filtersLayout->addWidget(mediaTypeComboBox);
    filtersLayout->addWidget(new QLabel("Anno minimo:"));
    filtersLayout->addWidget(minYearLineEdit);
    filtersLayout->addWidget(new QLabel("Anno massimo:"));
    filtersLayout->addWidget(maxYearLineEdit);
    filtersLayout->addWidget(new QLabel("Lingua:"));
    filtersLayout->addWidget(languageLineEdit);

    QGroupBox *filtersGroupBox = new QGroupBox("Filtri");
    filtersGroupBox->setLayout(filtersLayout);
    filtersGroupBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // Barra di ricerca e lista media
    searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Cerca per titolo...");
    mediaList = new QListWidget();

    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->addWidget(searchBar);
    centerLayout->addWidget(mediaList);

    // Sezione destra
    mediaImageLabel = new QLabel();
    mediaImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mediaImageLabel->setAlignment(Qt::AlignCenter);
    mediaImageLabel->setStyleSheet("border: 1px solid black;");
    mediaImageLabel->setMinimumSize(150, 150);

    mediaInfoLabel = new QLabel("Seleziona un media per vedere i dettagli");
    borrowButton = new QPushButton("Prendi in prestito");
    detailsButton = new QPushButton("Approfondisci");

    previewLayout = new QVBoxLayout();
    previewLayout->addWidget(mediaImageLabel);
    previewLayout->addWidget(mediaInfoLabel);
    previewLayout->addWidget(borrowButton);
    previewLayout->addWidget(detailsButton);

    QGroupBox *previewGroupBox = new QGroupBox("Anteprima");
    previewGroupBox->setLayout(previewLayout);
    previewGroupBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // Layout principale
    contentLayout = new QHBoxLayout();
    contentLayout->addWidget(filtersGroupBox, 1);
    contentLayout->addLayout(centerLayout, 3);
    contentLayout->addWidget(previewGroupBox, 2);

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topBarLayout);
    mainLayout->addLayout(contentLayout);

    setLayout(mainLayout);
}

void MainPage::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    updateImageSize();
}

void MainPage::updateImageSize() {
    if (!mediaImageLabel->pixmap().isNull()) {
        QPixmap original = mediaImageLabel->pixmap();
        QPixmap scaled = original.scaled(mediaImageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        mediaImageLabel->setPixmap(scaled);
    }
}