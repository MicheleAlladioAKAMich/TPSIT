'''
5 filosofi sono a tavola per mangiare. Per mangiare occorrono 2 forchette (variabile condivisa):
alla destra di ciascun filosofo c'è una forchetta (totale bacchette 5). Per mangiare il filosofo prende sia la
forchetta alla sua destra che la forchetta alla sua sinistra. Dopo aver mangiato il filosofo mette a posto le
forchette e pensa per un po'. Poi gli viene ancora fame e cerca di mangiare.
Vincoli del problema:
1) Evidentemente non potranno mangiare tutti contemporaneamente ma occorre assicurare
il massimo grado di parallelismo. Cioè devo permettere che 2 filosofi (non adiacenti) mangino assieme
utilizzando 4 delle 5 forchette.
2) Contemporaneamente andrebbe evitato il deadlock: se ciascun filosofo prende la forchetta
di sinistra quella di destra verrà messa in attesa, si bloccano tutti indefinitamente. Se si accorgono del
blocco e tutti posano assieme la loro forchetta e poi riprendono assieme allora potrebbero non mangiare
mai nessuno.
Come evitare il deadlock:
1. Prendere due forchette assieme, solo quando sono libere entrambe;
2. Prendere le forchette in ordine diverso.
'''
import threading, time, logging, random

class Filosofo(threading.Thread):
    running = True  

    def __init__(self, name, forkOnLeft, forkOnRight):
        threading.Thread.__init__(self)
        self.name = name
        self.forkOnLeft = forkOnLeft
        self.forkOnRight = forkOnRight
    
    def run(self):
        while(self.running):
            time.sleep(random.uniform(1,5)) #probabilità di estrazione uniforme
            print(f"{self.name} ha fame")
            self.dinner()

    def dinner(self):
        fork1, fork2 = self.forkOnLeft, self.forkOnRight
        while self.running:
            fork1.acquire() #acquire brutale -> se la risorsa è libera la si prende, altrimenti si aspetta
            locked = fork2.acquire(False)   #acquire false -> se la risorsa è libera la si prende locked = True, altrimenti continua il codice e locked viene posto a False
            if locked:
                break   #salto dopo la else
            fork1.release()
            print(f"{self.name} scambia le forchette")
            fork1, fork2 = fork2, fork1 #scambio per una quuestione di probabilità
        else:   #quando la condizione del while non è più vera
            return
        print(f"{self.name} inizia a mangiare")
        time.sleep(random.uniform(1,3))
        print(f"{self.name} finisce di mangiare e torna pensare")
        fork1.release()
        fork2.release()

        

def main():
    forks = [threading.Lock() for n in range(5)]
    philosopherName = ('Aristotele', 'Kant', 'Buddha', 'Marx', 'Russel')
    philosopher = [Filosofo(philosopherName[i], forks[i%5], forks[(i+1)%5]) for i in range(5)]
    Filosofo.running = True 

    for p in philosopher:
        p.start()

    time.sleep(60)
    Filosofo.running = False 
    print("Ora abbiamo finito")   


if __name__ == "__main__":
    main()