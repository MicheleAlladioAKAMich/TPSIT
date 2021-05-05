import threading
import ipaddress
import time
import subprocess
import os
import queue
import init

init()

print_lock = threading.Lock()
net_addr = input("Accadere alla rete es(192.168.1.0/24): ")
startTime = time.time()
ip_net = ipaddress.ip_network(net_addr)
all_hosts = list(ip_net.hosts())

try:
    info=subprocess.STARTUPINFO()
    info.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    info.wShowWindow = subprocess.SW_HIDE
except Exception:
    pass

print(f"indirizzo di rete che vuoi pingare: {net_addr}")

def pingsweep(ip):
    if os.name == "nt":
        output = subprocess.Popen(["ping","-n","1","-w","150",str(all_hosts[ip])],stdout = subprocess.PIPE, startupinfo=info).communicate()[0]
    with print_lock:
        print(end='')
    if "Risposta" in output.decode("utf-8"):
        print(f"{str(all_hosts[ip])} is online")
    elif "host di destinazione non raggiungibile" in output.decode('utf-8'):
        pass
    elif "tempo per la richiesta scaduto" in output.decode('utf-8'):
        pass
    else:
        print("UNKNOW",end='')


def threader():
    while True: #prendo dalla coda un ping e il thread lo pinga
        worker = q.get()
        pingsweep(worker)
        q.task_done()

q=Queue()

threadList = [] #lista dei thread

for x in range(100):    #creo 100 thread
    t = threading.Thread(target=threader)
    t.daemon = True
    t.start()
    threadList.append(t)

for worker in range(len(all_hosts)):    #riempio la coda di ping
    q.put(worker)

for thread in threadList:   #superfluo dato che i thread sono dei daemon
    thread.join()   #chiudo tutti i thread


runtime = float("%0.2f"% (time.time()-startTime))
print(f"Runtime: {runtime}, seconds")