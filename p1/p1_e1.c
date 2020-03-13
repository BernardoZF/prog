/**
* @file p1_e1.c
* @author Bernardo Zambrano && Alvaro Platon
* @date 4 Frebuary 2020
* @version 1.0
* @brief Test of TAD Node
**
@details
**
@see
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "node.h"

int main (int argc, char** argv){
    Node * n1;
    Node * n2;
    int aux1=0;
    char aux2[NAME_L];
    
    fprintf(stdout,"\n");
    
    n1=node_init();
    if(!n1) return -1;
    
    n2=node_init();
    if(!n2) {
        node_free(n1);
        return -1;
    }
    
    if(node_setId(n1,111)==ERROR){
        fprintf(stdout,"ERROR while setting Id1\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }
    
    if(node_setId(n2,222)==ERROR){
        fprintf(stdout,"ERROR while setting Id2\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }
    
    if(node_setName(n1,"first")==ERROR){
        fprintf(stdout,"ERROR while setting name1\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }
    
    if(node_setName(n2,"second")==ERROR){
        fprintf(stdout,"ERROR while setting name2\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }
    
    if(node_setNConnect(n1,0)==ERROR){
        fprintf(stdout,"ERROR while setting connections\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }
    
    if(node_setNConnect(n2,0)==ERROR){
        fprintf(stdout,"ERROR while setting connections\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }

    if(node_setLabel(n1,WHITE)==ERROR){
        fprintf(stdout,"ERROR while setting labels\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }
    
    if(node_setLabel(n2,WHITE)==ERROR){
        fprintf(stdout,"ERROR while setting labels\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }
    
    node_print(stdout,n1);
    node_print(stdout,n2);
    fprintf(stdout,"\n");

    
    fprintf(stdout,"Son iguales? ");
    if(node_cmp(n1,n2)==0){
        fprintf(stdout,"Sí.\n\n");
    }else fprintf(stdout,"No.\n\n");
    
    

    
    aux1=node_getId(n1);
    if(aux1==0) {
        fprintf(stdout,"ERROR while getting Id1\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }else fprintf(stdout,"Id del primer nodo: %d\n",aux1);
    
    strcpy(aux2,node_getName(n2));
    if(aux2==NULL) {
        fprintf(stdout,"ERROR while getting name2\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }else fprintf(stdout,"Nombre del segundo nodo: %s\n\n",aux2);
    
    node_free(n2);
    n2=node_copy(n1);
    if(!n2){
        fprintf(stdout,"ERROR while copying nodes\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }
    
    
    node_print(stdout,n1);
    node_print(stdout,n2);
    fprintf(stdout,"\n");
    
    
    fprintf(stdout,"Son iguales? ");
    if(node_cmp(n1,n2)==0){
        fprintf(stdout,"Sí.\n");
    }else fprintf(stdout,"No.\n");
    
    
    node_free(n1);
    node_free(n2);
    return 0;
}

