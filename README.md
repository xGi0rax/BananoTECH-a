# BananoTECH-a

--> sistemare mainPage:
  - sistemare immagine mainPage
  - risolvere crash di approfondisci, SEMBRA FUNZIONARE
  - far funzionare visualizzazione immagini in anteprima
  - modificare tasto salvataggio:
    - quando si salva un Json questo viene duplicato, da capire come far funzionare il tutto
    - deve sovrascrivere il file Json se selezionato all'inizio, altrimenti deve crearne uno nuovo (cosa che attualmente funziona)
    - ulteriore problema che consiste nel fatto che quando si crea una biblioteca da capo questa contiene comunque dei media, cosa che invece NON dovrebbe accadere
      
--> sistemare DetailsPage:
  - aggiungere voce "collocazione" ai dettagli (dettaglio di ogni media)
  - quando si schiaccia restituisci devi comparire un pop-up che mostri tutti gli id di tutti i media con quel titolo e che permetta di inserire l'id del media che si vuole restituire, nel caso in cui questo id non faccia parte della biblioteca allora deve comparire un messaggio di errore (scrivere nella relazione che il fatto che nel pop-up compaiano tutti gli id è perchè si tratta di una biblioteca idelae, se fosse reale allora gli id sono riportati esclusivamente sull'ettichetta dei media)
  - controllare timer del tasto per richiedere copia ad altra biblioteca
  - diminuire l'interspazio tra i vari campi dei dettagli
  
--> nuovo pop-up che chiede se si è sicuri di uscire se non si hanno salvato le modifiche

--> voce editore per riviste da aggiungere nel file Json
## Modifiche minori:
- lag quando si seleziona un media dalla lista
- lag quando si ridimensiona la finestra mentre c'è un media selezionato
- colori vari
- controllare che segnali e slot siano corretti
- controllare tutti i commenti (rimuovere quelli superflui e aggiungerne per spiegare i vari metodi)
- controllare tutti i const
- controllare di non aver utilizzato getType
