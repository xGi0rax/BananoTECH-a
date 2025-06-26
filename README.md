# BananoTECH-a

--> generali:
  - ha senso tenere l'id della biblioteca?
  - crash dopo aver eliminato un media, salvato la bibioteca, cercato di modificare un media e schiacciato su "salva media"
  - modificare "data pubblicazione" nei media rivista in modo che sia nel formato gg-MM-aaaa
  - popolare campo Editore nei file json e xml

--> sistemare mainPage:
  - sistemare ridimensionamento finestra mainPage
  - far funzionare visualizzazione immagini in anteprima

## Modifiche minori:
- lag quando si seleziona un media dalla lista
- lag quando si ridimensiona la finestra mentre c'è un media selezionato
- colori vari
- controllare che segnali e slot siano corretti
- controllare tutti i commenti (rimuovere quelli superflui e aggiungerne per spiegare i vari metodi)
- controllare tutti i const
- controllare di non aver utilizzato getType
- controllare di usare delete in modo appropriato
- ricordarsi di cambiare username e password per effettuare il login

## Varie ed eventuali:
- (DetailsPage) quando si schiaccia restituisci devi comparire un pop-up che mostri tutti gli id di tutti i media con quel titolo e che permetta di inserire l'id del media che si vuole restituire, nel caso in cui questo id non faccia parte della biblioteca allora deve comparire un messaggio di errore (scrivere nella relazione che il fatto che nel pop-up compaiano tutti gli id è perchè si tratta di una biblioteca ideale, se fosse reale allora gli id sono riportati esclusivamente sull'ettichetta dei media)

- (MainPage) tasti modifica e rimozione dovrebbero comparire sempre a destra e andare sopra il testo se necessario
