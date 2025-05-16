#include "../Headers/MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {

    // Configurazione dello QStackedWidget
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Configurazione delle pagine
    setupLoginPage();
    setupLibraryChoicePage(); // Aggiunta della pagina di scelta biblioteca

    // Mostra inizialmente la pagina di login
    stackedWidget->setCurrentWidget(loginPage);

    setWindowTitle("BananoTECH-a");
    resize(900, 650);
}

MainWindow::~MainWindow() {
    // Deallocazione delle pagine
    delete loginPage;
    delete libraryChoicePage; // Deallocazione della pagina di scelta biblioteca
    if (mainPage) delete mainPage;
    if (addPage) delete addPage;
    if (detailsPage) delete detailsPage; // Deallocazione della pagina di dettagli media
    delete stackedWidget;
}

void MainWindow::setupLoginPage(){
    // Creazione della pagina di login
    loginPage = new LoginPage(this);

    stackedWidget->addWidget(loginPage);

    connect(loginPage, &LoginPage::loginAttempted, this, &MainWindow::onLoginButtonClicked);
}

void MainWindow::setupLibraryChoicePage() {
    // Creazione della nuova pagina di scelta biblioteca
    libraryChoicePage = new LibraryChoicePage(this);
    stackedWidget->addWidget(libraryChoicePage);
    
    connect(libraryChoicePage, &LibraryChoicePage::libraryReady, this, &MainWindow::onLibraryReady);
}

void MainWindow::setupMainPage(Biblioteca* biblioteca){
    // Creazione della pagina principale con la biblioteca fornita
    mainPage = new MainPage(this, biblioteca); // Passa la biblioteca caricata
    
    stackedWidget->addWidget(mainPage);

    // Connetto il segnale allo slot per tornare alla pagina di login
    connect(mainPage, &MainPage::goToLoginPage, this, &MainWindow::switchToLoginPage);

    // Connetto il segnale per passare alla pagina di aggiunta media
    connect(mainPage, &MainPage::goToAddPage, this, &MainWindow::switchToAddPage);

    // Connetto il segnale per passare alla pagina di dettaglio media
    connect(mainPage, &MainPage::goToDetailsPage, this, &MainWindow::switchToDetailsPage);
}

void MainWindow::setupAddPage(){
    // Creazione della pagina di aggiunta media
    addPage = new AddPage(this);

    stackedWidget->addWidget(addPage);

    // Connetto il segnale per tornare alla pagina principale
    connect(addPage, &AddPage::goBackToMainPage, this, &MainWindow::switchToMainPage);

    // Connetto il segnale per la creazione del media
    connect(addPage, &AddPage::mediaCreated, mainPage, &MainPage::onNewMediaCreated);
}

void MainWindow::setupDetailsPage(){
    // Creazione della pagina di dettaglio media
    detailsPage = new DetailsPage(this);

    stackedWidget->addWidget(detailsPage);

    // Connetto il segnale per tornare alla pagina principale
    connect(detailsPage, &DetailsPage::goBackToMainPage, this, &MainWindow::switchToMainPage);
}

void MainWindow::switchToLoginPage() {
    stackedWidget->setCurrentWidget(loginPage); // Cambia alla pagina di login
}

void MainWindow::switchToLibraryChoicePage() {
    stackedWidget->setCurrentWidget(libraryChoicePage); // Cambia alla pagina di scelta biblioteca
}

void MainWindow::onLibraryReady(Biblioteca* biblioteca) {
    // Quando la biblioteca è pronta, configuriamo le altre pagine e passiamo a MainPage
    setupMainPage(biblioteca); // Passiamo la biblioteca ricevuta
    setupAddPage();
    setupDetailsPage();
    switchToMainPage();
}

void MainWindow::switchToMainPage() {
    stackedWidget->setCurrentWidget(mainPage); // Cambia alla pagina principale
}

void MainWindow::switchToAddPage() {
    stackedWidget->setCurrentWidget(addPage); // Cambia alla pagina di aggiunta media
}

void MainWindow::switchToDetailsPage(Media* media) {
    detailsPage->setMedia(media);
    stackedWidget->setCurrentWidget(detailsPage);
}

void MainWindow::onLoginButtonClicked() {
    QString username = loginPage->getUsername();
    QString password = loginPage->getPassword();

    if (validateLogin(username, password)) {
        // Login riuscito, mostra la pagina di scelta biblioteca
        loginPage->clearErrorMessage();
        switchToLibraryChoicePage(); // Ora andiamo alla pagina di scelta biblioteca
        
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