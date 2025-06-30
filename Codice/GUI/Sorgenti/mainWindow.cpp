#include "../Headers/MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {

    // Configurazione dello QStackedWidget
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Configurazione della pagina di login
    setupLoginPage();

    // Inizialmente viene mostrata la pagina di login
    stackedWidget->setCurrentWidget(loginPage);

    setWindowTitle("BananoTECH-a");
    resize(900, 600);
}

MainWindow::~MainWindow() {
    // Deallocazione delle pagine
    delete loginPage;
    delete libraryChoicePage;
    if (mainPage) delete mainPage;
    if (addPage) delete addPage;
    if (detailsPage) delete detailsPage;
    if (modifyPage) delete modifyPage;
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
    
    // Connessione segnale libraryReady e pulsante indietro
    connect(libraryChoicePage, &LibraryChoicePage::libraryReady, this, &MainWindow::onLibraryReady);
    connect(libraryChoicePage, &LibraryChoicePage::goToLoginPage, this, &MainWindow::switchToLoginPage);
}

void MainWindow::setupMainPage(Biblioteca* biblio) {
    biblioteca = biblio;

    // Creazione della pagina principale con la biblioteca fornita
    mainPage = new MainPage(this, biblioteca);
    
    // Impostazione del file corrente solo se non è una nuova biblioteca
    if (!isNewLibrary && !loadedFilePath.isEmpty()) {
        mainPage->setCurrentFile(loadedFilePath);
    }
    
    // Passa le informazioni sulla biblioteca alla MainPage
    mainPage->setLibraryInfo(isNewLibrary, hasUnsavedChanges);
    
    stackedWidget->addWidget(mainPage);

    // Connessioni esistenti...
    connect(mainPage, &MainPage::goToChoicePage, this, &MainWindow::switchToLibraryChoicePage);
    connect(mainPage, &MainPage::goToLoginPage, this, &MainWindow::switchToLoginPage);
    connect(mainPage, &MainPage::goToAddPage, this, &MainWindow::switchToAddPage);
    connect(mainPage, &MainPage::goToModifyPage, this, &MainWindow::switchToModifyPage);
    connect(mainPage, &MainPage::goToDetailsPage, this, &MainWindow::switchToDetailsPage);
    connect(mainPage, &MainPage::borrowMedia, this, &MainWindow::prendiInPrestitoMedia);
    connect(mainPage, &MainPage::returnMedia, this, &MainWindow::restituisciMedia);
    
    
    // C'è un FUNTORE, BISOGNA MODIFICARE

    // VERIFICA CHE QUESTA CONNESSIONE ESISTA E SIA CORRETTA
    connect(mainPage, &MainPage::unsavedChangesUpdated, this, [this](bool hasChanges) {
        hasUnsavedChanges = hasChanges;
    });
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

void MainWindow::setupModifyPage(){
    // Creazione della pagina di modifica media
    modifyPage = new ModifyPage(this);

    stackedWidget->addWidget(modifyPage);

    // Connetto il segnale per tornare alla pagina principale
    connect(modifyPage, &ModifyPage::goBackToMainPage, this, &MainWindow::switchToMainPage);

    // Connetto il segnale per la modifica del media
    connect(modifyPage, &ModifyPage::mediaEdited, mainPage, &MainPage::onMediaEdited);
}

void MainWindow::setupDetailsPage(){
    // Creazione della pagina di dettaglio media
    detailsPage = new DetailsPage(this);

    stackedWidget->addWidget(detailsPage);

    // Connetto il segnale per tornare alla pagina principale
    connect(detailsPage, &DetailsPage::goBackToMainPage, this, &MainWindow::switchToMainPage);
    
    // AGGIUNGI QUESTE CONNESSIONI MANCANTI:
    connect(detailsPage, &DetailsPage::mediaBorrowed, this, &MainWindow::prendiInPrestitoMedia);
    connect(detailsPage, &DetailsPage::mediaReturned, this, &MainWindow::restituisciMedia);
}

void MainWindow::switchToLoginPage() {
    hasUnsavedChanges = false; 
    isNewLibrary = false;
    loadedFilePath = "";

    loginPage->resetToDefaultState();
    stackedWidget->setCurrentWidget(loginPage); // Cambia alla pagina di login
}

void MainWindow::switchToLibraryChoicePage() {
    // Usa il metodo helper per controllare le modifiche non salvate
    if (!checkUnsavedChanges()) {
        return; // L'utente ha cancellato l'operazione
    }
    
    // Reset delle variabili
    isNewLibrary = false;
    hasUnsavedChanges = false;
    loadedFilePath = "";
    
    stackedWidget->setCurrentWidget(libraryChoicePage);
}

void MainWindow::onLibraryReady(Biblioteca* biblio, const QString& filePath, bool isNew) {
    // Salva le informazioni sulla biblioteca
    loadedFilePath = filePath;
    isNewLibrary = isNew;
    hasUnsavedChanges = false; // Inizialmente nessuna modifica
    
    // Quando la biblioteca è pronta, configuriamo le altre pagine e passiamo a MainPage
    setupMainPage(biblio);
    setupAddPage();
    setupDetailsPage();
    setupModifyPage();

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
    stackedWidget->setCurrentWidget(detailsPage); // Cambia alla pagina di dettagli del media
}

void MainWindow::switchToModifyPage(Media* media) {
    modifyPage->setMedia(media);
    stackedWidget->setCurrentWidget(modifyPage); // Cambia alla pagina di modifica del media
}

void MainWindow::onLoginButtonClicked() {
    QString username = loginPage->getUsername();
    QString password = loginPage->getPassword();

    if (validateLogin(username, password)) {
        hasUnsavedChanges = false;
        isNewLibrary = false;
        loadedFilePath = "";

        // Login riuscito, mostra la pagina di scelta biblioteca
        loginPage->clearErrorMessage();
        setupLibraryChoicePage();
        switchToLibraryChoicePage();
    } else {
        // Login fallito, mostra un messaggio di errore
        loginPage->showErrorMessage("Username o password errati. Riprova.");
    }
}

bool MainWindow::validateLogin(const QString &username, const QString &password) {
    //return username == "admin" && password == "admin";
    return !username.isEmpty() && !password.isEmpty();
}

void MainWindow::prendiInPrestitoMedia(Media* media) {
    if (!media) {
        QMessageBox::warning(this, "Errore", "Media non valido.");
        return;
    }
    
    // Verifica se ci sono copie disponibili
    int copieTotali = media->getNumeroCopie();
    int copieInPrestito = media->getInPrestito();
    int copieDisponibili = copieTotali - copieInPrestito;
    
    if (copieDisponibili <= 0) {
        QMessageBox::warning(this, "Prestito non disponibile", 
            QString("Tutte le copie di '%1' sono già in prestito.").arg(QString::fromStdString(media->getTitolo())));
        return;
    }
    
    // Incrementa il numero di copie in prestito
    media->setInPrestito(copieInPrestito + 1);
    
    QMessageBox::information(this, "Prestito effettuato", 
        QString("Hai preso in prestito '%1' con successo!").arg(QString::fromStdString(media->getTitolo())));
    
    // NOTIFICA LA MODIFICA ALLA BIBLIOTECA:
    hasUnsavedChanges = true;
    
    // Notifica anche MainPage
    if (mainPage) {
        mainPage->setHasUnsavedChanges(true);
    }
}

void MainWindow::restituisciMedia(Media* media) {
    if (!media) {
        QMessageBox::warning(this, "Errore", "Media non valido.");
        return;
    }
    
    // Verifica se ci sono copie in prestito
    int copieInPrestito = media->getInPrestito();
    
    if (copieInPrestito <= 0) {
        QMessageBox::warning(this, "Restituzione non disponibile", 
            QString("Nessuna copia di '%1' risulta in prestito.").arg(QString::fromStdString(media->getTitolo())));
        return;
    }
    
    // Decrementa il numero di copie in prestito
    media->setInPrestito(copieInPrestito - 1);
    
    // Se il media era non disponibile, ora lo rendiamo disponibile
    if (!media->getDisponibilita()) {
        media->setDisponibilita(true);
    }
    
    QMessageBox::information(this, "Restituzione effettuata", 
        QString("Hai restituito '%1' con successo!").arg(QString::fromStdString(media->getTitolo())));
    
    // NOTIFICA LA MODIFICA ALLA BIBLIOTECA:
    hasUnsavedChanges = true;
    
    // Notifica anche MainPage
    if (mainPage) {
        mainPage->setHasUnsavedChanges(true);
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    // Controlla se ci sono modifiche non salvate prima di chiudere
    if (!checkUnsavedChanges()) {
        event->ignore(); // Impedisce la chiusura
        return;
    }
    
    // Se non ci sono modifiche non salvate o l'utente ha confermato, procedi con la chiusura
    event->accept();
}

bool MainWindow::checkUnsavedChanges() {
    if (hasUnsavedChanges) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, 
            "Modifiche non salvate", 
            "Ci sono modifiche non salvate. Sei sicuro di voler uscire senza salvare?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        
        if (reply == QMessageBox::No || reply == QMessageBox::Cancel) {
            return false; // L'utente ha cancellato l'operazione
        }
    }
    
    return true; // Procedi con l'operazione
}