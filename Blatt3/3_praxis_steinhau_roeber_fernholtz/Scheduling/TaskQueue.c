#include "../Tasks/Task.h"
#include "../Tasks/TaskPool.h"
#include "TaskQueue.h"
#include <stdio.h>
#include <stdlib.h>

/*
*	Simple Queue, deren Elemente Task-Pointer speichern
*	Methoden: 
*		enqueue (neuen Task einreihen)
*		dequeue (Task vom Kopf der Queue ausgeben und löschen)
*		getHead (Task vom Kopf der Queue ausgeben)
*		printQueue (nicht verwendet, nur zum Debuggen gedacht)
*		isEmpty (testes auf leere Queue)
*		freeQueue (Queue löschen und Speicher freigeben)
*/


void enqueue(Queue* queue, Task* task){
	if(task==NULL){
		return;
	}
	Q_Elem* new_elem = (Q_Elem*) malloc(sizeof(Q_Elem));
	if(new_elem==NULL){
		perror("Malloc Error");
		exit(1);
	}
	new_elem->task = task;
	new_elem->previous = NULL;
	new_elem->next = queue->tail;
	if(queue->size==0){
		queue->head = new_elem;
	}else{
		queue->tail->previous = new_elem;
	}
	queue->tail = new_elem;
	queue->size++;
}

Task* dequeue(Queue* queue){
	if(queue->size==0){
		return NULL;
	}
	Q_Elem* elem = queue->head;
	Task* task = elem->task;
	queue->head = elem->previous;
	free(elem);
	queue->size--;
	return task;
}

Task* getHead(Queue* queue){
	if(queue->size==0){
		return NULL;
	}
	return queue->head->task;
}

void printQueue(Queue* queue){
	if(queue->size==0){
		return;
	}
	Q_Elem* temp = queue->head;
	printf("Queue: ");
	while(temp!=NULL){
		printTask(temp->task);
		printf(" | ");
		temp = temp->previous;
	}
	printf("\n");
}

bool isEmpty(Queue* queue){
	if(queue->head==NULL){
		return true;
	}else{
		return false;
	}
}

void freeQueue(Queue* queue){
	if(queue->size==0){
		free(queue);
		return;
	}
	Q_Elem* temp = queue->head;
	Q_Elem* temp2 = temp;
	while(temp != NULL){
		temp2 = temp;
		temp = temp->previous;
		free(temp2);
	}
	free(queue);
}