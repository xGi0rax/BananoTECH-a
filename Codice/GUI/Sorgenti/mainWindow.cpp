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
    loginPage->setObjectName("loginPage");
    loginPage->setStyleSheet("#loginPage {background-image: url(:/Immagini/Sfondo1Definitivo.jpg);"
                            "background-repeat: no-repeat;"
                            "background-position: center;"
                            "background-attachment: fixed; }");

    // Creazione del riquadro che contiene i campi di input e il bottone
    QFrame *loginFrame = new QFrame(loginPage);
    loginFrame->setStyleSheet("QFrame {"
                               "background-color:rgb(42, 68, 113);"
                               "border: 2px solid #000000;"
                               "border-radius: 10px;"
                               "}");
    loginFrame->setFixedSize(450, 350);
    loginFrame->setAttribute(Qt::WA_OpaquePaintEvent, true);

    // Campi di input per username e password e bottone per accedere
    usernameField = new QLineEdit(loginFrame);
    usernameField->setPlaceholderText("Username");
    usernameField->setFixedWidth(330);
    usernameField->setFixedHeight(40);
    usernameField->setStyleSheet("QLineEdit { background-color: #FFFFFF; border: 1px solid #AAAAAA; border-radius: 5px; padding: 5px; font-size: 16px; selection-background-color: #4a90e2; }");
        
    passwordField = new QLineEdit(loginFrame);
    passwordField->setPlaceholderText("Password");
    passwordField->setEchoMode(QLineEdit::Password);
    passwordField->setFixedWidth(330);
    passwordField->setFixedHeight(40);
    passwordField->setStyleSheet("QLineEdit { background-color: #FFFFFF; border: 1px solid #AAAAAA; border-radius: 5px; padding: 5px; font-size: 16px; selection-background-color: #4a90e2; }");

    loginButton = new QPushButton("Accedi", loginFrame);
    loginButton->setFixedWidth(160);
    loginButton->setFixedHeight(45);
    loginButton->setStyleSheet("QPushButton { background-color:rgb(245, 225, 48); border: 1px solid #AAAAAA; border-radius: 5px; padding: 8px 16px; font-size: 18px;}"
        "QPushButton:hover { background-color: rgb(215, 205, 113); }");

    // Label per messaggi di errore
    errorLabel = new QLabel(loginFrame);
    errorLabel->setStyleSheet("QLabel { color:rgb(230, 229, 229); padding: 5px; font-size: 16px;}");
    errorLabel->setAlignment(Qt::AlignCenter);
    errorLabel->setText("Inserisci Username e Password per accedere.");

    // Layout verticale per i widget di login
    QVBoxLayout *loginWidgetsLayout = new QVBoxLayout();

    loginWidgetsLayout->setContentsMargins(10, 10, 10, 10); // Margini interni
    loginWidgetsLayout->setSpacing(10); // Spaziatura tra i widget

    QLabel *welcomeLabel = new QLabel("Benvenuto in BananoTECH-a", loginFrame);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("background-color: #333333; font-size: 24px; font-weight: bold; color: white;");

    loginWidgetsLayout->addWidget(welcomeLabel);
    loginWidgetsLayout->addWidget(usernameField, 0, Qt::AlignCenter);
    loginWidgetsLayout->addWidget(passwordField, 0, Qt::AlignCenter);
    loginWidgetsLayout->addWidget(loginButton, 0, Qt::AlignCenter);
    loginWidgetsLayout->addWidget(errorLabel);

    loginFrame->setLayout(loginWidgetsLayout);
    loginFrame->setAutoFillBackground(true);

    // Layout esterno per centrare i widget
    QVBoxLayout *outerLayout = new QVBoxLayout(loginPage);
    outerLayout->setContentsMargins(0, 0, 0, 0); // Rimuovo i margini
    outerLayout->addStretch(); // Aggiungo uno spazio flessibile sopra
    outerLayout->addWidget(loginFrame, 0, Qt::AlignCenter); // Aggiungo il layout interno
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
        errorLabel->setStyleSheet("color: red; font-weight: bold; font-size: 16px;");
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