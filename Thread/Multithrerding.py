import threading, time, logging

def thread_function(name):
    logging.info(f"Thread {name}: inizio")
    time.sleep(2)#mette una pausa il thread per 2 secondi
    logging.info(f"Thread {name}: fine")

class FakeDatabase:
    def __init__(self):
        self.value = 0  #quando il thread inizia FakeDatabase.value = 0
        self.lock = threading.Lock()

    def lockedUpdate(self, name):
        logging.info(f"Thread {name}: avvio dell'aggiornamento del DB")
        local_copy = self.value #copia il valore zero nella variabile locale
        local_copy += 1 #incrementa il valore di 1
        time.sleep(2)
        self.value = local_copy
        logging.debug(f"Thread {name}: sta per rilasciare il lock")
        logging.debug(f"Thread {name}: rilascio del lock")
        logging.info(f"Thread {name}: termine dell'aggiornamento del DB")

def main():
    format = "%(asctime)s: %(message)s"
    logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")  
    logging.getLogger().setLevel(logging.DEBUG)

    database = FakeDatabase()
    threads = list()
    logging.info(f"Valore iniziale del DB è {database.value}.")

    for index in range(3):
        logging.info(f"Main    :  creo ed avvio il thread {index}")
        x = threading.Thread(target=database.lockedUpdate, args=(index,))
        threads.append(x)
        x.start()

    for index, thread in enumerate(threads):
        logging.info(f"Main    :  in attesa del thread {index}")
        thread.join()
        logging.info(f"Main    :  thread {index} terminato.")
    
    logging.info(f"Valore finale del DB è {database.value}")

if __name__ == "__main__":
    main()