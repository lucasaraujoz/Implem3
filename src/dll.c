#include "dll.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
typedef struct _dlnode_
{
    struct _dlnode_ *next;
    struct _dlnode_ *prev;
    void *data;
} DLNode;

typedef struct _dllist_
{
    DLNode *first;
    DLNode *cur;
} DLList;

DLList *dllCreate()
{
    DLList *l;
    l = (DLList *)malloc(sizeof(DLList));
    if (l != NULL)
    {
        l->cur = NULL;
        l->first = NULL;
        return l;
    }
    return NULL;
}

int dllDestroy(DLList *l)
{
    if (l != NULL)
    {
        if (l->first == NULL) // so vazia 
        {
            free(l);
            return 1;
        }
    }
    return 0;
}

int dllDestroyNotEmpty(DLList *l, int *(*myfree)(void *))
{
    return 0;
}

int dllInsertAsFirst(DLList *l, void *data)
{
    DLNode *newnode;
    if (l != NULL)
    {
        newnode = (DLNode *)malloc(sizeof(DLNode));
        if (newnode != NULL)
        {
            newnode->data = data;
            newnode->prev = NULL;
            newnode->next = l->first; // se o lista estiver vazia, o next é NULL
            // if list is empty
            if (l->first != NULL)
            {
                l->first->prev = newnode; // update prev of first node
            }
            l->first = newnode;
            return 1;
        }
    }
    return 0;
}

void *getFirst(DLList *l)
{
    if (l != NULL)
    {
        if (l->first != NULL) // se existe algo na lista
        {
            l->cur = l->first;
            return l->cur->data;
        }
    }
    return NULL;
}

void *getNext(DLList *l)
{
    if (l != NULL)
    {
        l->cur = l->cur->next; //ou caminha pro proximo ou l->cur = vira null se chegar no fim
        if (l->cur != NULL)
        {
            return l->cur->data; // pega o void * do atual
        }
    }
    return NULL;
}

void dllClearList(DLList *l)
{
    DLNode *aux;
    if (l != NULL)
    {
        while (l->first != NULL)
        {
            aux = l->first;
            l->first = l->first->next;
            free(aux);
        }
        l->first = NULL;
        l->cur = NULL;
    }
}

void *dllGetSpecData(DLList *l, void *key, int (*cmp)(void *, void *))
{
    DLNode *spec;
    int stat;
    if (l != NULL)
    {
        if (l->first != NULL)
        {
            spec = l->first;
            stat = cmp(spec->data, key); // spec->data {nome, matricula, nota} == key
            while (spec->next != NULL && stat != true)
            {
                spec = spec->next;
                stat = cmp(spec->data, key);
            }
            if (stat == true)
            {
                return spec->data;
            }
        }
    }
    return NULL;
}

void *dllRemoveSpec(DLList *l, void *key, int (*cmp)(void *, void *))
{
    DLNode *spec, *prev;
    int stat;
    if (l != NULL)
    {
        if (l->first != NULL)
        {
            spec = l->first;
            prev = NULL;
            stat = cmp(spec->data, key);
            while (spec->next != NULL && stat != true)
            {
                prev = spec;
                spec = spec->next;
                stat = cmp(spec->data, key);
            }
            void *data;
            if (stat == true)
            {
                data = spec->data;
                if (prev != NULL)
                {
                    prev->next = spec->next;
                }
                else
                {
                    l->first = spec->next;
                }
                free(spec);
                return data;
            }
        }
    }
    return NULL;
}