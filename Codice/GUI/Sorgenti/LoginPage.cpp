#include "../Headers/LoginPage.h"

LoginPage::LoginPage(QWidget *parent) : QWidget(parent) {

    // Imposto backgound e stile della pagina di login
    this->setObjectName("loginPage");
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setAutoFillBackground(true);
    this->setStyleSheet("#loginPage {background-image: url(:/Immagini/Sfondo1Definitivo.jpg); background-repeat: no-repeat; background-position: center; background-attachment: fixed; }");

    // Creazione del Frame che contiene i campi di input e il bottone
    QFrame *loginFrame = new QFrame(this);
    loginFrame->setFixedSize(450, 350);
    loginFrame->setStyleSheet("QFrame { background-color:rgb(42, 68, 113); border: 2px solid #000000; border-radius: 10px; }");

    // Label di benvenuto
    QLabel *welcomeLabel = new QLabel("Benvenuto nella BananoTECH-a", loginFrame);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("background-color: #333333; font-size: 24px; font-weight: bold; color: white;");

    // Campi di input per username e password e bottone per accedere
    usernameField = new QLineEdit(loginFrame);
    usernameField->setPlaceholderText("Username");
    usernameField->setFixedSize(330, 40);
    usernameField->setStyleSheet("QLineEdit { background-color:rgb(237, 235, 235); border: 1px solid #AAAAAA; border-radius: 5px; padding: 5px; font-size: 16px; selection-background-color: #4a90e2; }");
        
    passwordField = new QLineEdit(loginFrame);
    passwordField->setPlaceholderText("Password");
    passwordField->setEchoMode(QLineEdit::Password);
    passwordField->setFixedSize(330, 40);
    passwordField->setStyleSheet("QLineEdit { background-color: rgb(237, 235, 235); border: 1px solid #AAAAAA; border-radius: 5px; padding: 5px; font-size: 16px; selection-background-color: #4a90e2; }");

    loginButton = new QPushButton("Accedi", loginFrame);
    loginButton->setFixedSize(150, 45);
    loginButton->setStyleSheet("QPushButton { background-color:rgb(230, 209, 26); border: 1px solid #AAAAAA; border-radius: 5px; padding: 8px 16px; font-size: 18px;}"
        "QPushButton:hover { background-color: rgb(184, 174, 90); }");
    
        // Collegamento del pulsante di login
    connect(loginButton, &QPushButton::clicked, this, &LoginPage::onLoginButtonClicked);

    // Label per messaggi di errore
    errorLabel = new QLabel(loginFrame);
    errorLabel->setStyleSheet("QLabel { color:rgb(230, 230, 230); font-size: 16px; border: 0px;}");
    errorLabel->setAlignment(Qt::AlignCenter);
    errorLabel->setText("Inserisci Username e Password per accedere.");

    // Layout verticale per il contenuto del frame
    QVBoxLayout *loginWidgetsLayout = new QVBoxLayout();

    loginWidgetsLayout->setContentsMargins(10, 10, 10, 10); 
    loginWidgetsLayout->setSpacing(10); // Spaziatura tra i widget

    loginWidgetsLayout->addWidget(welcomeLabel);
    loginWidgetsLayout->addWidget(usernameField, 0, Qt::AlignCenter);
    loginWidgetsLayout->addWidget(passwordField, 0, Qt::AlignCenter);
    loginWidgetsLayout->addWidget(loginButton, 0, Qt::AlignCenter);
    loginWidgetsLayout->addWidget(errorLabel);

    loginFrame->setLayout(loginWidgetsLayout);

    // Layout esterno per centrare i widget
    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0); // Rimuovo i margini
    outerLayout->addStretch(); // Aggiungo uno spazio flessibile sopra
    outerLayout->addWidget(loginFrame, 0, Qt::AlignCenter); 
    outerLayout->addStretch(); // Aggiungo uno spazio flessibile sotto

    this->setLayout(outerLayout);

    
}

QString LoginPage::getUsername() const {
    return usernameField->text();
}

QString LoginPage::getPassword() const {
    return passwordField->text();
}

void LoginPage::showErrorMessage(const QString &message) {
    errorLabel->setText(message);
    errorLabel->setStyleSheet("QLabel { color: rgb(255, 0, 0); padding: 5px; font-size: 16px;}"); // Rosso per errore
}

void LoginPage::clearErrorMessage() {
    errorLabel->clear();
    errorLabel->setStyleSheet("QLabel { color: rgb(230, 230, 230); padding: 5px; font-size: 16px; border: 0px;}"); // Colore originale
}

void LoginPage::onLoginButtonClicked() {
    emit loginAttempted(); // Emissione del segnale di tentativo di login
}

void LoginPage::keyPressEvent(QKeyEvent *event) {
    if ((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) && !usernameField->text().isEmpty() && !passwordField->text().isEmpty()) {
        emit loginAttempted(); // Emissione del segnale di tentativo di login
    }else{
        QWidget::keyPressEvent(event);
    }
}