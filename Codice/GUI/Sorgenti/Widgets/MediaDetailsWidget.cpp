#include "../../Headers/Widgets/MediaDetailsWidget.h"

MediaDetailsWidget::MediaDetailsWidget(QWidget *parent) : QWidget(parent) {}

void MediaDetailsWidget::setupBaseUI(const QString &detailsTitle) {
    // Layout verticale principale
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 20, 20, 30);
    
    // ScrollArea
    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("background: transparent;");
    
    // Widget per il contenuto scrollabile
    scrollWidget = new QWidget();
    formLayout = new QFormLayout(scrollWidget);
    formLayout->setSpacing(15);
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    formLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    
    // Titolo della pagina di dettaglio
    titleLabel = new QLabel(detailsTitle, scrollWidget);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    formLayout->addRow(titleLabel);
    
    // Aggiungo campi comuni
    addStandardFields();
    
    // Aggiungo campi specifici (implementato dalle classi derivate)
    addSpecificFields();
    
    // Aggiungo spazio vuoto in fondo
    formLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    
    // Imposto la struttura dello scroll
    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea, 1);
    
    // Aggiungo il pulsante di annullamento
    cancelButton = new QPushButton("Annulla", this);
    cancelButton->setMinimumSize(150, 45);
    
    cancelButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgb(200, 0, 0);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "   padding: 8px 16px;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(150, 0, 0);"
        "}"
    );
    
    connect(cancelButton, &QPushButton::clicked, this, &MediaDetailsWidget::onCancelClicked);

    // Layout per il pulsante
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();
    
    // Aggiungi il pulsante sotto l'area di scroll
    layout->addSpacing(10);
    layout->addLayout(buttonLayout);
}

void MediaDetailsWidget::addStandardFields() {
    // Campi comuni
    titleEdit = new QLineEdit(scrollWidget);
    titleEdit->setStyleSheet(getInputStyle());
    titleEdit->setMinimumWidth(400);

    authorEdit = new QLineEdit(scrollWidget);
    authorEdit->setStyleSheet(getInputStyle());

    genreComboBox = new QComboBox(scrollWidget);
    genreComboBox->setStyleSheet(getInputStyle());

    yearEdit = new QSpinBox(scrollWidget);
    yearEdit->setRange(1880, 2100);
    yearEdit->setValue(2025);
    yearEdit->setStyleSheet(getInputStyle());
    
    languageEdit = new QLineEdit(scrollWidget);
    languageEdit->setStyleSheet(getInputStyle());
    
    ratingEdit = new QDoubleSpinBox(scrollWidget);
    ratingEdit->setRange(1.0, 5.0);
    ratingEdit->setDecimals(1); // Permette di inserire valori decimali con una cifra decimale
    ratingEdit->setSingleStep(0.1); // Incremento/decremento di 0.1
    ratingEdit->setStyleSheet(getInputStyle());
    
    // Etichette con stile
    QLabel *titleLbl = new QLabel("Titolo:");
    titleLbl->setStyleSheet(getLabelStyle());
    QLabel *authorLbl = new QLabel("Autore:");
    authorLbl->setStyleSheet(getLabelStyle());
    QLabel *genreLbl = new QLabel("Genere:");
    genreLbl->setStyleSheet(getLabelStyle());
    QLabel *yearLbl = new QLabel("Anno:");
    yearLbl->setStyleSheet(getLabelStyle());
    QLabel *languageLbl = new QLabel("Lingua:");
    languageLbl->setStyleSheet(getLabelStyle());
    QLabel *ratingLbl = new QLabel("Valutazione:");
    ratingLbl->setStyleSheet(getLabelStyle());

    // Aggiungi i campi al form
    formLayout->addRow(titleLbl, titleEdit);
    formLayout->addRow(authorLbl, authorEdit);
    formLayout->addRow(genreLbl, genreComboBox);
    formLayout->addRow(yearLbl, yearEdit);
    formLayout->addRow(languageLbl, languageEdit);
    formLayout->addRow(ratingLbl, ratingEdit);
}

void MediaDetailsWidget::onCancelClicked() {
    emit cancelled();
}