#include "MouseCore/DataStructures/LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

struct mouse_listNode_t_prv
{
	mouse_listNode* next;
    mouse_listNode* prev;
};

struct mouse_linkedList_t
{
    mouse_listNode* head;
    mouse_listNode* tail;
    int nodeCount;
};

static mouse_listNode* mouse_listNode_create(void* data , size_t dataSize)
{
    mouse_listNode* node = malloc(sizeof(mouse_listNode));
    
	node->data = data;
    node->dataSize = dataSize;
	
	node->prv = malloc(sizeof(mouse_listNode_prv));
    
    node->prv->next = NULL;
    node->prv->prev = NULL;
	
    return node;
}

static void mouse_listNode_delete(mouse_listNode* self)
{
	free(self->prv);
    free(self);
}

static void mouse_listNode_link(mouse_listNode* firstNode, mouse_listNode* secondNode)
{
    firstNode->prv->next = secondNode;
    secondNode->prv->prev = firstNode;
}

mouse_listNode* mouse_listNode_getNext(mouse_listNode* self)
{
	return self->prv->next;
}

mouse_listNode* mouse_listNode_getPrev(mouse_listNode* self)
{
	return self->prv->prev;
}

mouse_linkedList* mouse_linkedList_create()
{
    mouse_linkedList* list = malloc(sizeof(mouse_linkedList));
    list->head = NULL;
    list->tail = NULL;
    list->nodeCount = 0;
    return list;
}

void mouse_linkedList_delete(mouse_linkedList* self)
{
    free(self);
}

static mouse_linkedListClear* mouse_linkedListClear_create(int dataCount)
{
	mouse_linkedListClear* clear = malloc(sizeof(mouse_linkedListClear));
	clear->dataCount = dataCount;
	clear->datas = malloc(sizeof(void*) * dataCount);
	return clear;
}

mouse_linkedListClear* mouse_linkedList_clear(mouse_linkedList* self)
{
	if(self->nodeCount == 0) { return NULL; }
	
	mouse_linkedListClear* clearResult = mouse_linkedListClear_create(self->nodeCount);
	
	mouse_listNode* node = self->head;
	
	int i = 0;
	while(node != NULL)
	{
		mouse_listNode* deleteNode = node;
		node = node->prv->next;
		
		clearResult->datas[i] = deleteNode->data;
		
		mouse_listNode_delete(deleteNode);
		i++;
	}
	self->head = NULL;
	self->tail = NULL;
	self->nodeCount = 0;
	
	return clearResult;
}

void mouse_linkedListClear_delete(mouse_linkedListClear* self)
{
	free(self->datas);
	free(self);
}

mouse_listNode* mouse_linkedList_getHead(mouse_linkedList* self)
{
	return self->head;
}
	
mouse_listNode* mouse_linkedList_getTail(mouse_linkedList* self)
{
	return self->tail;
}

int mouse_linkedList_getNodeCount(mouse_linkedList* self)
{
    return self->nodeCount;
}

void mouse_linkedList_insertFront(mouse_linkedList* self, void* data, size_t dataSize)
{
    mouse_listNode* node = mouse_listNode_create(data, dataSize);
    
    if(self->head == NULL)
    {
        self->head = node;
        self->tail = node;
    }
    else
    {
        mouse_listNode_link(node, self->head);
        self->head = node;
    }
    self->nodeCount++;
}

void mouse_linkedList_insertBack(mouse_linkedList* self, void* data, size_t dataSize)
{
    mouse_listNode* node = mouse_listNode_create(data, dataSize);

    if(self->tail == NULL)
    {
        self->head = node;
        self->tail = node;
    }
    else
    {
        mouse_listNode_link(self->tail, node);
        self->tail = node;
    }
    self->nodeCount++;
}

void mouse_linkedList_insertAt(mouse_linkedList* self, void* data, size_t dataSize, int index)
{
	mouse_listNode* insertionNode = mouse_linkedList_get(self, index);
	if (insertionNode == NULL)
	{
		if(index == 0)
		{
			mouse_linkedList_insertFront(self, data, dataSize);
		}
		else
		{
			mouse_linkedList_insertBack(self, data, dataSize);
		}
	}
	else
	{
		mouse_linkedList_insert(self, data, dataSize, insertionNode);
	}
}

void mouse_linkedList_insert(mouse_linkedList* self, void* data, size_t dataSize, mouse_listNode* insertionNode)
{
	mouse_listNode* node = mouse_listNode_create(data, dataSize);
	mouse_listNode* insertionNodePrev = insertionNode->prv->prev;
	if(insertionNodePrev != NULL)
	{
		mouse_listNode_link(insertionNodePrev, node);
	}
	else
	{
		node->prv->prev = NULL;
	}
	mouse_listNode_link(node, insertionNode);
	self->nodeCount++;
}

void* mouse_linkedList_removeFront(mouse_linkedList* self)
{
    return mouse_linkedList_removeNode(self, self->head);
}

void* mouse_linkedList_removeBack(mouse_linkedList* self)
{
    return mouse_linkedList_removeNode(self, self->tail);
}

void* mouse_linkedList_removeAt(mouse_linkedList* self, int index)
{
    if(index >= self->nodeCount) { return NULL; }

    mouse_listNode* node = self->head;
    for(int i=0; i<index; i++)
    {
        node = node->prv->next;
    }
    
    return mouse_linkedList_removeNode(self, node);
}

void* mouse_linkedList_remove(mouse_linkedList* self, void* data)
{
    return mouse_linkedList_removeNode(self, mouse_linkedList_getFirstOf(self, data));
}

void* mouse_linkedList_removeNode(mouse_linkedList* self, mouse_listNode* node)
{
    if(node == NULL) { return NULL; }
	
	void* data = node->data;
    if(node == self->head)
    {
        if(node->prv->next != NULL)
        {
            self->head = node->prv->next;
            self->head->prv->prev = NULL;
        }
        else
        {
            self->head = NULL;
            self->tail = NULL;
        }
    }
    else if(node == self->tail)
    {
        if(node->prv->prev != NULL)
        {
            self->tail = node->prv->prev;
            self->tail->prv->next = NULL;
        }
        else
        {
            self->tail = NULL;
            self->head = NULL;
        }
    }
    else
    {
        mouse_listNode_link(node->prv->prev, node->prv->next);
    }
    mouse_listNode_delete(node);
    self->nodeCount--;
	
	return data;
}

mouse_listNode* mouse_linkedList_get(mouse_linkedList* self, int index)
{
    if(index >= self->nodeCount || index < 0)
    {
        return NULL;
    }
    mouse_listNode* node = self->head;
    for(int i=0; i<index; i++)
    {
        node = node->prv->next;
    }
    return node;
}

mouse_listNode* mouse_linkedList_getFirstOf(mouse_linkedList* self, void* data)
{
    mouse_listNode* node = self->head;
    while(node != NULL)
    {
        if(node->data == data)
        {
            return node;
        }
        node = node->prv->next;
    }
    return NULL;
}
