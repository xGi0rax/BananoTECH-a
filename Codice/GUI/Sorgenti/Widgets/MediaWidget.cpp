#include "../../Headers/Widgets/MediaWidget.h"

MediaWidget::MediaWidget(QWidget *parent) : QWidget(parent), currentMedia(nullptr) {
}

void MediaWidget::setupBaseUI(const QString &title) {
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
    titleLabel = new QLabel(title, this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);
    
    // Aggiungo campi comuni
    addStandardFields();
    
    // Aggiungo campi specifici (implementato dalle classi derivate)
    addSpecificFields();
    
    // Aggiungo spazio vuoto in fondo
    formLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    
    // Imposto la struttura dello scroll
    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea, 1);
}

void MediaWidget::addStandardFields() {
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
    yearEdit->setValue(QDate::currentDate().year());
    yearEdit->setStyleSheet(getInputStyle());
    
    languageEdit = new QLineEdit(scrollWidget);
    languageEdit->setStyleSheet(getInputStyle());
    
    ratingEdit = new QDoubleSpinBox(scrollWidget);
    ratingEdit->setRange(1.0, 5.0);
    ratingEdit->setDecimals(1);
    ratingEdit->setSingleStep(0.1);
    ratingEdit->setStyleSheet(getInputStyle());
    
    setCurrentValues();

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


void MediaWidget::setCurrentValues() {
    if (currentMedia) {
        titleEdit->setText(QString::fromStdString(currentMedia->getTitolo()));
        authorEdit->setText(QString::fromStdString(currentMedia->getAutore()));
        yearEdit->setValue(currentMedia->getAnno());
        languageEdit->setText(QString::fromStdString(currentMedia->getLingua()));
        ratingEdit->setValue(currentMedia->getRating());
    }
}

QString MediaWidget::getLabelStyle() const {
    return "QLabel { font-size: 14px; }";
}

QString MediaWidget::getInputStyle() const {
    return "QLineEdit, QSpinBox, QDoubleSpinBox, QComboBox { "
           "border: 1px solid #ccc; "
           "border-radius: 4px; "
           "padding: 5px; "
           "font-size: 14px; }";
}