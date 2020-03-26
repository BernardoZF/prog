#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#define MAXQUEUE 1024

/* ----------- queue.c -------------- */
struct _Queue {
    void* items [MAXQUEUE];
    int front;
    int rear;
    int size;

    free_element_function_type fd;
    copy_element_function_type fc;
    print_element_function_type fp;
};


Queue *queue_init (free_element_function_type fd,
copy_element_function_type fc,
print_element_function_type fp) 
{
    Queue *q = NULL;
    int i;
    if (!fd || !fc || !fp) return NULL;
    q =(Queue *) malloc (sizeof (Queue));
    if (!q) {
        fprintf(stderr, "%s", strerror(errno));
        return NULL;
    }

    /*Assign pointer functions*/
    q->fc = fc;
    q->fd = fd;
    q->fp = fp;

    /*Assign array pointers*/
    for (i=0; i < MAXQUEUE; i++)
        q->items[i] = NULL;

    q->front = q->rear = 0;
    q->size = 0;

    return q;
}



void queue_free(Queue *q)
{
    void * aux;

    if(!q)
        return;
    while (queue_isEmpty(q)!= TRUE){
        aux = queue_extract(q);
        q->fd(aux);
    }
    free(q);

    return;
}



Bool queue_isEmpty(const Queue *q)
{
    if(!q)
        return FALSE;
    if(q->front == q->rear){ 
        return TRUE;
    }
    return FALSE;
}



Status queue_insert(Queue *q, const void* pElem)
{
    if(!q || !pElem)
        return ERROR;
    
    if (q->size == (MAXQUEUE - 1)){
        fprintf(stderr, "ERROR, COLA LLENA");
        return ERROR; 
    }

    q->items[q->rear] = q->fc(pElem);
        if(q->items[q->rear]==NULL){
            fprintf(stderr, "ERROR AL COPIAR EL ELEMENTO");
            return ERROR; 
        }
    q->rear = (q->rear + 1) % MAXQUEUE;
    q->size++;

    return OK;
}



void * queue_extract(Queue *q){
    void *aux;

    if(!q)
        return NULL;
    if(queue_isEmpty(q) == TRUE){
        fprintf(stderr, "ERROR, COLA VACIA");
        return NULL;
    }
    aux = q->items[q->front];
    q->items[q->front]=NULL;

    q->front = (q->front + 1) % MAXQUEUE;
    q->size--;

    return aux;
}


int queue_size (const Queue *q)
{
    if(!q)
        return -1;
    return q->size;
}


int queue_print(FILE *pf, const Queue *q)
{
    int i;
    int ret = 0;
    if(!pf || !q){
        fprintf(stderr, "ERROR EN LA IMPRESION\n");
        return -1;
    }

    for(i=0;i<q->size;i++){
        ret+=q->fp(pf, q->items[i]);
    }

    return ret;
}

