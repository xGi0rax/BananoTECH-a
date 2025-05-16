#include "../../Headers/Widgets/MediaModifyWidget.h"

MediaModifyWidget::MediaModifyWidget(QWidget* parent) : QWidget(parent), currentMedia(nullptr) {
}

void MediaModifyWidget::setupBaseUI(const QString& title) {
    // Layout verticale principale
    QVBoxLayout* layout = new QVBoxLayout(this);
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

    // Titolo della pagina di modifica
    titleLabel = new QLabel(title, this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Aggiungo i campi comuni
    addStandardFields();

    // Aggiungo i campi specifici (implementato dalle classi derivate)
    addSpecificFields();

    // Aggiungo spazio vuoto in fondo
    formLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    
    // Imposto la struttura dello scroll
    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea, 1);
}

void MediaModifyWidget::addStandardFields() {
    // Campi comuni
    titleEdit = new QLineEdit(scrollWidget);
    titleEdit->setStyleSheet(getInputStyle());
    titleEdit->setMinimumWidth(400);
    
    authorEdit = new QLineEdit(scrollWidget);
    authorEdit->setStyleSheet(getInputStyle());
    
    genreComboBox = new QComboBox(scrollWidget); // da popolare poi nelle classi derivate
    genreComboBox->setStyleSheet(getInputStyle());
    
    yearEdit = new QSpinBox(scrollWidget);
    yearEdit->setRange(1880, 2100);
    yearEdit->setStyleSheet(getInputStyle());
    
    languageEdit = new QLineEdit(scrollWidget);
    languageEdit->setStyleSheet(getInputStyle());
    
    ratingEdit = new QDoubleSpinBox(scrollWidget);
    ratingEdit->setRange(1.0, 5.0);
    ratingEdit->setDecimals(1); // Permette di inserire valori decimali con una cifra decimale
    ratingEdit->setSingleStep(0.1); // Incremento/decremento di 0.1
    ratingEdit->setStyleSheet(getInputStyle());
    
    // Valori di default
    yearEdit->setValue(QDate::currentDate().year());
    ratingEdit->setValue(3.0);
    
    // Se abbiamo già un media, impostiamo i valori comuni
    if (currentMedia) {
        titleEdit->setText(QString::fromStdString(currentMedia->getTitolo()));
        authorEdit->setText(QString::fromStdString(currentMedia->getAutore()));
        yearEdit->setValue(currentMedia->getAnno());
        languageEdit->setText(QString::fromStdString(currentMedia->getLingua()));
        ratingEdit->setValue(currentMedia->getRating());
    }
    
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