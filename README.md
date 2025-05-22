# BananoTECH-a

--> sistemare mainPage:
  - sistemare immagine mainPage
  - tasti modifica e rimuovi da "attaccare" ad ogni media della lista (non devono spostarsi con lo scroll)
  - collegare tasto per prendere in prestito (deve essere applicato a Json/Xml)
  - risolvere crash di approfondisci, SEMBRA FUNZIONARE
  - far funzionare barra di ricerca
  - far funzionare visualizzazione immagini in anteprima
  - modificare tasto esporta:
    - bisogna nominarlo "Salva modifiche"
    - deve sovrascrivere il file Json se selezionato all'inizio, altrimenti deve crearne uno nuovo (cosa che attualmente funziona)
      
--> sistemare DetailsPage:
  - sistemare grafica e dettagli specifici
  - posizionare i tasti e aggiungere "Richiedi ad altra biblioteca"
  - collegare Prendi in prestito e Restituisci (il valore di copie disponibili deve salvarsi nel Json/Xml)
  - aggiungere voce "collocazione" ai dettagli (dettaglio di ogni media)
  - quando si schiaccia restituisci devi comparire un pop-up che mostri tutti gli id di tutti i media con quel titolo e che permetta di inserire l'id del media che si vuole restituire, nel caso in cui questo id non faccia parte della biblioteca allora deve comparire un messaggio di errore (scrivere nella relazione che il fatto che nel pop-up compaiano tutti gli id è perchè si tratta di una biblioteca idelae, se fosse reale allora gli id sono riportati esclusivamente sull'ettichetta dei media)
  
--> nuovo pop-up che chiede se si è sicuri di uscire se non si hanno salvato le modifiche

## Modifiche minori:
- lag quando si seleziona un media dalla lista
- lag quando si ridimensiona la finestra mentre c'è un media selezionato
- colori vari
- controllare che segnali e slot siano corretti
- controllare tutti i commenti (rimuovere quelli superflui e aggiungerne per spiegare i vari metodi)
- controllare tutti i const
- controllare di non aver utilizzato getType
