#include "../Headers/mainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {

    // Configurazione dello QStackedWidget
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Configurazione delle pagine
    setupLoginPage();
    setupMainPage();

    // Mostra inizialmente la pagina di login
    stackedWidget->setCurrentWidget(loginPage);

    setWindowTitle("BananoTECH-a");
    resize(800, 600);
}

MainWindow::~MainWindow() {
    delete biblioteca;
}

void MainWindow::setupLoginPage(){
    // Creazione della pagina di login
    loginPage = new QWidget(this);
    loginPage->setStyleSheet("background-image: url(:/Immagini/sfondo1.jpeg);"
                            "background-repeat: no-repeat;"
                            "background-position: center;"
                            "background-attachment: fixed;"
                            "background-size: cover;");

    // Campi di input per username e password e bottone per accedere
    usernameField = new QLineEdit(loginPage);
    usernameField->setPlaceholderText("Username");
    usernameField->setFixedWidth(300);

    passwordField = new QLineEdit(loginPage);
    passwordField->setPlaceholderText("Password");
    passwordField->setEchoMode(QLineEdit::Password);
    passwordField->setFixedWidth(300);

    loginButton = new QPushButton("Accedi", loginPage);
    loginButton->setFixedWidth(200);

    // Label per messaggi di errore
    errorLabel = new QLabel(loginPage);
    errorLabel->setStyleSheet("color: red;");
    errorLabel->setAlignment(Qt::AlignCenter);
    errorLabel->setText("");

    // Layout verticale per i widget di login
    QVBoxLayout *loginWidgetsLayout = new QVBoxLayout();
    QLabel *welcomeLabel = new QLabel("Benvenuto in BananoTECH-a", loginPage);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    loginWidgetsLayout->addWidget(welcomeLabel);
    loginWidgetsLayout->addWidget(usernameField, 0, Qt::AlignCenter);
    loginWidgetsLayout->addWidget(passwordField, 0, Qt::AlignCenter);
    loginWidgetsLayout->addWidget(loginButton, 0, Qt::AlignCenter);
    loginWidgetsLayout->addWidget(errorLabel);

    // Layout esterno per centrare i widget
    QVBoxLayout *outerLayout = new QVBoxLayout(loginPage);
    outerLayout->addStretch(); // Aggiungo uno spazio flessibile sopra
    outerLayout->addLayout(loginWidgetsLayout); // Aggiungo il layout interno
    outerLayout->addStretch(); // Aggiungo uno spazio flessibile sotto

    loginPage->setLayout(outerLayout);

    // Aggiungo la pagina di login al QStackedWidget
    stackedWidget->addWidget(loginPage);

    // Collegamento del pulsante di login
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);
}


void MainWindow::setupMainPage(){
    // Creazione della pagina principale
    mainPage = new QWidget(this);

    welcomeLabel = new QLabel("Benvenuto nella schermata principale!", mainPage);

    mainLayout = new QVBoxLayout(mainPage);
    mainLayout->addWidget(welcomeLabel);

    mainPage->setLayout(mainLayout);

    // Aggiungo la pagina principale al QStackedWidget
    stackedWidget->addWidget(mainPage);
}


void MainWindow::onLoginButtonClicked() {
    QString username = usernameField->text();
    QString password = passwordField->text();

    if (validateLogin(username, password)) {
        // Login riuscito, mostra la pagina principale
        stackedWidget->setCurrentWidget(mainPage);
        errorLabel->setText("");
    } else {
        // Login fallito, mostra un messaggio di errore
        errorLabel->setText("Username o password errati.");
    }
}


bool MainWindow::validateLogin(const QString &username, const QString &password) {
    // Qui puoi implementare la logica di validazione del login
    // Per ora, accettiamo qualsiasi combinazione di username e password
    // altrimenti, scrivere:
    //return username == "admin" && password == "admin";
    return !username.isEmpty() && !password.isEmpty();
}