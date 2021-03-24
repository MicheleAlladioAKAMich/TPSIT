"""
Author: Michele Alladio
es: verificare se, in una stringa, l'ordine delle parentesi è corretto. Utilizzando le pile.
"""

def main():
    pila = []
    ok = True
    stringa = input("inserisci una stringa con parentesi: ")

    for lettera in stringa:
        if lettera == '(' or lettera == '[' or lettera == '{':
            pila.append(lettera)
        elif lettera == ')':
            #if pila.pop() != NULL:
            if pila.pop() != '(':
                ok = False
                break
        elif lettera == ']':
            #if pila.pop() != NULL:
            if pila.pop() != '[':
                ok = False
                break
        elif lettera == '}':
            #if pila.pop() != NULL:
            if pila.pop() != '{':
                ok = False
                break

    if ok == True:
        print("Ordine parentesi corretto")
    else:
        print("Ordine parentesi errato")

if __name__ == "__main__":
    main()