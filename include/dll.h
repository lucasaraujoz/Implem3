#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

typedef struct _dlnode_ DLNode;
typedef struct _dllist_ DLList;
DLList *dllCreate();
int dllDestroy(DLList *l);
int dllInsertAsFirst(DLList *l, void *data);
void *dllGetFirst(DLList *l);
void *dllGetNext(DLList *l);
int dllInsertAsLast(DLList *l, void *data);
void *getFirst(DLList *l);
void *getNext(DLList *l);
void dllClearList(DLList *l);
void* dllGetSpecData(DLList *l, void *key, int(*cmp)(void *, void *));
void *dllRemoveSpec(DLList *l, void *key, int (*cmp)(void *, void *));
#endif