# BananoTECH-a

--> generali:
  - ha senso tenere l'id della biblioteca?
  - crash nel salvataggio della biblioteca dopo una modifica
  - crash quando provo a ricare un nuova biblioteca da file dopo essere tornato indietro dopo averne caricata già una
  - crash dopo aver eliminato un media, salvato la bibioteca, cercato di modificare un media e schiacciato su "salva media"
  - errore di caricamento da file json
  - quando si schiaccia "salva" e non ci sono modifiche da salvare dovrebbe dire "non ci sono modifiche da salvare" o "la biblioteca è già stata salvata"

  - modificare "data pubblicazione" nei media rivista in modo che sia nel formato gg-MM-aaaa

--> sistemare mainPage:
  - sistemare ridimensionamento finestra mainPage
  - far funzionare visualizzazione immagini in anteprima
  - riposizionerei i pulsanti di modifica ed elimina in modo che escano sempre attaccati al bordo destro della lista
  - quando schiaccio su elimina filtri deve cancellarsi anche il testo nella barra di ricerca
      
--> sistemare DetailsPage:
  - quando si schiaccia restituisci devi comparire un pop-up che mostri tutti gli id di tutti i media con quel titolo e che permetta di inserire l'id del media che si vuole restituire, nel caso in cui questo id non faccia parte della biblioteca allora deve comparire un messaggio di errore (scrivere nella relazione che il fatto che nel pop-up compaiano tutti gli id è perchè si tratta di una biblioteca idelae, se fosse reale allora gli id sono riportati esclusivamente sull'ettichetta dei media)

--> tasti modifica e rimozione dovrebbero comparire sempre a destra e andare sopra il testo se necessario

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
