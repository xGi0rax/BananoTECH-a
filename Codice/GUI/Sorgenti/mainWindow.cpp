#include "../Headers/MainWindow.h"

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
    loginPage = new LoginPage(this);

    stackedWidget->addWidget(loginPage);

    connect(loginPage, &LoginPage::loginAttempted, this, &MainWindow::onLoginButtonClicked);
}


void MainWindow::setupMainPage(){
    // Creazione della pagina principale
    mainPage = new MainPage(this);

    stackedWidget->addWidget(mainPage);

    // Connetti il segnale al nuovo slot
    connect(mainPage, &MainPage::goToLoginPage, this, &MainWindow::showLoginPage);
}

void MainWindow::showLoginPage() {
    stackedWidget->setCurrentWidget(loginPage); // Cambia alla pagina di login
}

void MainWindow::onLoginButtonClicked() {
    QString username = loginPage->getUsername();
    QString password = loginPage->getPassword();

    if (validateLogin(username, password)) {
        // Login riuscito, mostra la pagina principale
        loginPage->clearErrorMessage();
        stackedWidget->setCurrentWidget(mainPage);
    } else {
        // Login fallito, mostra un messaggio di errore
        loginPage->showErrorMessage("Username o password errati. Riprova.");
    }
}


bool MainWindow::validateLogin(const QString &username, const QString &password) {
    // Qui puoi implementare la logica di validazione del login
    // Per ora, accettiamo qualsiasi combinazione di username e password
    // altrimenti, scrivere:
    //return username == "admin" && password == "admin";
    return !username.isEmpty() && !password.isEmpty();
}

/*
connect(MainPage, &MainPage::editMediaRequested, this, [this](const QString &mediaId) {
    // Qui creerai e mostrerai la pagina di modifica
    qDebug() << "Apri modifica per media:" << mediaId;
    // Esempio:
    // EditPage *editPage = new EditPage(mediaId, this);
    // stackedWidget->addWidget(editPage);
    // stackedWidget->setCurrentWidget(editPage);
});*/