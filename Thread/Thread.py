import logging  
import threading
import time

def thread_function(name):
    logging.info(f"Thread {name}: inizio")
    time.sleep(2)#mette una pausa il thread per 2 secondi
    logging.info(f"Thread {name}: fine")

def main():
    format = "%(asctime)s: %(message)s"
    #logging registra degli errori di script
    logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")  #si crea un logging -> format è il tipo di stampa ora: stringa 
                                                                                #logging.INFO è il formato della stampa del logging 
                                                                                #datefm tdefinisce il formato della data                                                                              

    logging.info("Main      : creo il thread")
    x = threading.Thread(target=thread_function, args=(1,), daemon=True)    #cerazione di un'istanza x tramite il costruttore che prende il nome della funzione (target)
                                                                            #gli argomenti 
                                                                            #il thread demone (facoltativo) in questo caso il thread termina con il processo
    logging.info("Main      : eseguo i thread")
    x.start()   #avvio del thread x -> biforcazione in due flussi (uno del main e l'altro il flusso del thread)
    logging.info("Main      : attendere che il thread finisca")
    x.join()    #attendere che il thread x termini e da qua in poi finisce la biforcazione
    logging.info("Main      : fine")

if __name__ == '__main__':
    main()