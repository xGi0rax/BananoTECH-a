# BananoTECH-a

## Gestione polimorfismo
### creare un'unica classe widget per tutti i tipi di media (es. FilmWidget.h e FilmWidget.cpp) che contenga tutti i metodi per approfondimento/modifica/aggiunta, modificare quindi tutte le pagine di approfondimento/modifica/aggiunta che devono essere adattate alla struttura delle varie pagine per i widget

## Cose da sistemare ASSOLUTAMENTE
--> sistemare pagina di LibraryChoice:
  -  deve avere lo stesso stile della LoginPage
  -  collegare tasto indietro
    
--> sistemare mainPage:
  - collegare tasto indietro della mainPage alla LibraryChoicePage e non alla LoginPage
  - cambiare proporzioni e colori della mainPage
  - tasti modifica e rimuovi da "attaccare" ad ogni media della lista (non devono spostarsi con lo scroll)
  - collegare tasto per prendere in prestito (deve essere applicato a Json/Xml)
  - collegare tasto modifica media alla ModifyPage
  - risolvere crash di approfondisci
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
    
--> sistemare ModifyPage:
    - sistemare colori vari (ti prego)
    - le modifiche salvate devo essere visibili nella mainPage
    - aggiungere voce collocazione
  
--> nuovo pop-up che chiede se si è sicuri di uscire se non si hanno salvato le modifiche

--> popolare file xml con un po' di esempi con relative immagini corrette (almeno 2 x ogni genere di ogni media)

## Modifiche minori:
- label con scritta "Inserire username e password" che quando si torna indietro da mainpage scompare
- lag quando si seleziona un media dalla lista
- lag quando si ridimensiona la finestra mentre c'è un media selezionato
- colori vari
- controllare che segnali e slot siano corretti
- controllare tutti i commenti (rimuovere quelli superflui e aggiungerne per spiegare i vari metodi)
- controllare di non aver utilizzato getType
