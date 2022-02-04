#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

typedef struct _dlnode_ DLNode;
typedef struct _dllist_ DLList;
DLList *dllCreate();
int dllDestroy(DLList *l);
int dllInsertAsFirst(DLList *l, void *data);
int dllInsertAsLast(DLList *l, void *data, int (*cmp)(void *, void *));
void *getFirst(DLList *l);
void *getNext(DLList *l);
void* dllGetSpecData(DLList *l, void *key, int(*cmp)(void *, void *));
void* dllGetDataIndex(DLList*l, int key);
void *dllRemoveSpec(DLList *l, void *key, int (*cmp)(void *, void *));
void* dllRemoveAt(DLList *l, int key);
void dllClearList(DLList *l);
#endif