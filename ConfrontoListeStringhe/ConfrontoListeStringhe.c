#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo
{
    char *parola;
    struct nodo *next;
}nodo;

//Definisco il tipo di dato "lista_stringhe", in alternativa si può omettere
//semplicemente mettendo all'atto della creazione della lista "nodo *lista"
typedef nodo *lista_stringhe;

nodo *crea_nuovo_nodo(char *p)
{
    nodo *nuovo_nodo = (nodo *)malloc(sizeof(nodo));
    //Bisogna istanziare lo spazio per la parole nel nodo.
    //Per la lunghezza della parola uso strlen + 1 per il carattere terminatore.
    nuovo_nodo->parola = (char *)malloc(sizeof(char) * (strlen(p) + 1));
    //Copio la stringa da p al nuovo nodo.
    strcpy(nuovo_nodo->parola, p);
    nuovo_nodo->next = NULL;
    return nuovo_nodo;
}

lista_stringhe aggiungi_nodo(lista_stringhe lista, char *p)
{
    //Ottengo la copia del puntatore della lista.
    nodo *nodo_corrente = lista;
    
    //Questo controllo serve per l'inserimento del primo oggetto nella lista in quanto null.
    if(!lista)
    {
        //Ritorno direttamente il nuovo nodo.
        return crea_nuovo_nodo(p);
    }
    
    //Scorro la lista fino alla fine.
    while (nodo_corrente->next)
    {
        nodo_corrente = nodo_corrente->next;
    }
    //Inserisco il nodo infondo.
    nodo *nuovo_nodo = crea_nuovo_nodo(p);
    nodo_corrente->next = nuovo_nodo;
    //Ritorno la lista. Potrebbe essere omesso ma lo lascio per chiarezza.
    return lista;
}

int lunghezza_lista(lista_stringhe lista)
{
    //Ritorno il numero di elementi nella lista
    //Nel caso sia vuota cioè null ritorno 0.
    if(lista)
    {
        nodo *nodo_corrente = lista;
        int lunghezza = 1;
        while (nodo_corrente->next)
        {
            nodo_corrente = nodo_corrente->next;
            lunghezza++;
        }
        return lunghezza;
    }
    return 0;
}

int is_valid_index_for_list(lista_stringhe l, int indice)
{
    if(indice >= 0 && indice < lunghezza_lista(l))
    {
        return 1;
    }
    return 0;
}

char *parola_at_index(lista_stringhe l, int indice)
{
    //Ritorno la parola all'indice corrente. Ovviamente indice a base 0.
    if(is_valid_index_for_list(l, indice))
    {
        nodo *nodo_corrente = l;
        for(int i = 0; i < indice; i++)
        {
            nodo_corrente = nodo_corrente->next;
        }
        //Una volta all'indice desiderato restituisco la parola.
        return nodo_corrente->parola;
    }
    //Ritorno null se la lista è vuota.
    return NULL;
}

int confronta_liste(lista_stringhe l1, lista_stringhe l2)
{
    int uguali = 0;
    //Scorro la lista 1.
    for(int i = 0; i < lunghezza_lista(l1); i++)
    {
        //Se l'indice è valido anche per la lista2
        //E' necessario perchè se l1 > l2 non posso accedere a determinati elementi di l2 in quanto non esistono
        //per quell'indice.
        if(is_valid_index_for_list(l2, i))
        {
            //Se le due parole nella stessa posizione sono uguali.
            if(!strcmp(parola_at_index(l1, i), parola_at_index(l2, i)))
            {
                uguali++;//Incremento
            }
        }
    }
    return uguali;
}

int main(int argc, const char * argv[])
{
    lista_stringhe lista1 = NULL;
    lista1 = aggiungi_nodo(lista1, "ciao");
    lista1 = aggiungi_nodo(lista1, "cane");
    lista1 = aggiungi_nodo(lista1, "bruschi");
    lista1 = aggiungi_nodo(lista1, "rebosio");
    lista1 = aggiungi_nodo(lista1, "merda");
    lista1 = aggiungi_nodo(lista1, "elefante");
    lista1 = aggiungi_nodo(lista1, "mandrillo");
    
    lista_stringhe lista2 = NULL;
    lista2 = aggiungi_nodo(lista2, "ciao");
    lista2 = aggiungi_nodo(lista2, "toletti");
    lista2 = aggiungi_nodo(lista2, "curcio");
    lista2 = aggiungi_nodo(lista2, "rebosio");
    lista2 = aggiungi_nodo(lista2, "merda");
    lista2 = aggiungi_nodo(lista2, "dilibero");
    lista2 = aggiungi_nodo(lista2, "mandrillo");
    
    
    printf("Lunghezza lista1: %d\n", lunghezza_lista(lista1));
    printf("Lunghezza lista2: %d\n", lunghezza_lista(lista2));
    
    for(nodo *nodo_corrente = lista1; nodo_corrente->next; nodo_corrente = nodo_corrente->next)
    {
        printf("Lista 1: %s\n", nodo_corrente->parola);
    }
    
    for(nodo *nodo_corrente = lista2; nodo_corrente->next; nodo_corrente = nodo_corrente->next)
    {
        printf("Lista 2: %s\n", nodo_corrente->parola);
    }
    
    printf("Parole uguali: %d\n", confronta_liste(lista1, lista2));
    
    return 0;
}
