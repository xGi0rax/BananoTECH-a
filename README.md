# BananoTECH-a

## Modifiche maggiori:
 - Problema quando si modifica un media inserendo titolo anno e genere uguali a un media già presente:
    dovrebbe venire richiesto se si vuole incrementare il numero di copie del media presente o se continuare la modifica

 - modificare metodo cercaMediadaT_A_G in Biblioteca in modo che al posto di anno si ricerchi per autore

 - eliminare getNumeroTotaleMedia da classe Biblioteca

 - modificare metodo restituzione in MainWindow in modo che utilizzi quello di Biblioteca

 - segnale mediaRequestedFromAffiliate emesso ma mai utilizzato -> commentare e inserirla nella relazione come futura implementazione

 - segnale onLibraryModified di MainPage mai usato

## Modifiche minori:
- controllare che segnali e slot siano corretti
- controllare tutti i commenti (rimuovere quelli superflui e aggiungerne per spiegare i vari metodi)
- controllare tutti i const
- controllare di non aver utilizzato getType
- controllare di usare delete in modo appropriato
- ricordarsi di cambiare username e password per effettuare il login
