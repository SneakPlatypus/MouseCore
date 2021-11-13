#pragma once

#include <stddef.h>

typedef struct mouse_listNode_t mouse_listNode;
typedef struct mouse_listNode_t_prv mouse_listNode_prv;

struct mouse_listNode_t
{
    void* data;
    size_t dataSize;
	mouse_listNode_prv* prv;
};

typedef struct mouse_linkedList_t mouse_linkedList;

typedef struct mouse_linkedListClear_t
{
	void** datas;
	int dataCount;
} mouse_linkedListClear;

mouse_listNode* mouse_listNode_getNext(mouse_listNode* self);
mouse_listNode* mouse_listNode_getPrev(mouse_listNode* self);

mouse_linkedList* mouse_linkedList_create();
void mouse_linkedList_delete(mouse_linkedList* self);
mouse_linkedListClear* mouse_linkedList_clear(mouse_linkedList* self);

void mouse_linkedListClear_delete(mouse_linkedListClear* self);

mouse_listNode* mouse_linkedList_getHead(mouse_linkedList* self);
mouse_listNode* mouse_linkedList_getTail(mouse_linkedList* self);
int mouse_linkedList_getNodeCount(mouse_linkedList* self);

void mouse_linkedList_insertFront(mouse_linkedList* self, void* data, size_t dataSize);
void mouse_linkedList_insertBack(mouse_linkedList* self, void* data, size_t dataSize);
void mouse_linkedList_insertAt(mouse_linkedList* self, void* data, size_t dataSize, int index);
void mouse_linkedList_insert(mouse_linkedList* self, void* data, size_t dataSize, mouse_listNode* insertionNode);

void* mouse_linkedList_removeFront(mouse_linkedList* self);
void* mouse_linkedList_removeBack(mouse_linkedList* self);
void* mouse_linkedList_removeAt(mouse_linkedList* self, int index);
void* mouse_linkedList_remove(mouse_linkedList* self, void* data);
void* mouse_linkedList_removeNode(mouse_linkedList* self, mouse_listNode* node);

mouse_listNode* mouse_linkedList_get(mouse_linkedList* self, int index);
mouse_listNode* mouse_linkedList_getFirstOf(mouse_linkedList* self, void* data);