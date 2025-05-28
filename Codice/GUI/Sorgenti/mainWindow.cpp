#include "../Headers/MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {

    // Configurazione dello QStackedWidget
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Configurazione della pagina di login
    setupLoginPage();

    // Mostro inizialmente la pagina di login
    stackedWidget->setCurrentWidget(loginPage);

    setWindowTitle("BananoTECH-a");
    resize(900, 650);
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
    
    // Connetti il segnale libraryReady
    connect(libraryChoicePage, &LibraryChoicePage::libraryReady, this, &MainWindow::onLibraryReady);
    
    // Aggiungi questa connessione per il pulsante indietro
    connect(libraryChoicePage, &LibraryChoicePage::goToLoginPage, this, &MainWindow::switchToLoginPage);
}

void MainWindow::setupMainPage(Biblioteca* biblio) {
    biblioteca = biblio;

    // Creazione della pagina principale con la biblioteca fornita
    mainPage = new MainPage(this, biblioteca);
    
    // Imposta il file corrente SOLO se non è una nuova biblioteca
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
    
    // VERIFICA CHE QUESTA CONNESSIONE ESISTA E SIA CORRETTA
    connect(mainPage, &MainPage::unsavedChangesUpdated, this, [this](bool hasChanges) {
        qDebug() << "=== MainWindow riceve unsavedChangesUpdated ===";
        qDebug() << "Nuovo valore hasChanges:" << hasChanges;
        qDebug() << "Valore precedente hasUnsavedChanges:" << hasUnsavedChanges;
        hasUnsavedChanges = hasChanges;
        qDebug() << "hasUnsavedChanges aggiornato a:" << hasUnsavedChanges;
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
    loginPage->resetToDefaultState();
    stackedWidget->setCurrentWidget(loginPage); // Cambia alla pagina di login
}

void MainWindow::switchToLibraryChoicePage() {
    // DEBUG DETTAGLIATO
    qDebug() << "=== CONTROLLO USCITA switchToLibraryChoicePage ===";
    qDebug() << "hasUnsavedChanges:" << hasUnsavedChanges;
    qDebug() << "isNewLibrary:" << isNewLibrary;
    qDebug() << "loadedFilePath:" << loadedFilePath;
    
    // Controlla SOLO se ci sono modifiche non salvate
    if (hasUnsavedChanges) {
        qDebug() << "CONDIZIONE VERA: Mostrando pop-up per modifiche non salvate";
        
        QMessageBox::StandardButton reply = QMessageBox::question(this, 
            "Modifiche non salvate", 
            "Ci sono modifiche non salvate. Sei sicuro di voler uscire senza salvare?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        
        if (reply == QMessageBox::No || reply == QMessageBox::Cancel) {
            qDebug() << "Utente ha scelto di non uscire";
            return; // Non uscire
        }
        qDebug() << "Utente ha confermato l'uscita";
        // Se Yes, continua con l'uscita
    } else {
        qDebug() << "CONDIZIONE FALSA: Nessuna modifica non salvata, uscita diretta";
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
    stackedWidget->setCurrentWidget(detailsPage);
}

void MainWindow::switchToModifyPage(Media* media) {
    modifyPage->setMedia(media);
    stackedWidget->setCurrentWidget(modifyPage);
}

void MainWindow::onLoginButtonClicked() {
    QString username = loginPage->getUsername();
    QString password = loginPage->getPassword();

    if (validateLogin(username, password)) {
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
    // Per ora, accettiamo qualsiasi combinazione di username e password
    // altrimenti, scrivere:
    //return username == "admin" && password == "admin";
    return !username.isEmpty() && !password.isEmpty();
}

void MainWindow::prendiInPrestitoMedia(Media* media) {
    qDebug() << "=== INIZIO prendiInPrestitoMedia ===";
    
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
    qDebug() << "Prestito effettuato - hasUnsavedChanges MainWindow impostato a:" << hasUnsavedChanges;
    
    // Notifica anche MainPage
    if (mainPage) {
        mainPage->setHasUnsavedChanges(true);
    }
    
    qDebug() << "=== FINE prendiInPrestitoMedia ===";
}

void MainWindow::restituisciMedia(Media* media) {
    qDebug() << "=== INIZIO restituisciMedia ===";
    
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
    qDebug() << "Restituzione effettuata - hasUnsavedChanges MainWindow impostato a:" << hasUnsavedChanges;
    
    // Notifica anche MainPage
    if (mainPage) {
        mainPage->setHasUnsavedChanges(true);
    }
    
    qDebug() << "=== FINE restituisciMedia ===";
}