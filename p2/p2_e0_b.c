#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#include "stack_types.h"
#include "node.h"

int main(){

    Node *n =NULL;
    Stack *snode =NULL;
    Stack *sstr=NULL;
    char *c;
    Node *naux;
    
    /*Inicializamos el nodo y hacemos le correspondiente control de errores*/
    n=node_init();
    if(!n) return -1;
    
    /*Establecemos los valores de nuestro "primer" nodo*/
    node_setName(n, "first");
    node_setId(n, 111);
    node_setLabel(n, WHITE);

    /*Inicializamos pilas*/
    snode=stack_init(node_free, node_copy, node_print);
    if(!snode) return -1;

    sstr=stack_init(string_free, string_copy, string_print);
    if(!sstr) return -1;

    /*Extraemos valores de nuestras pilas*/
    stack_push(snode, (const void*)n);
    stack_push(sstr, (const void*)node_getName(n));

    /*Establecemos los valores de nuestro "primer" nodo*/
    node_setName(n, "second");
    node_setId(n, 222);
    /*Extraemos valores de nuestras pilas yb los mostramos por pantalla*/
    stack_push(snode, (const void*)n);
    stack_push(sstr, (const void*)node_getName(n));
    fprintf(stdout, "Print Stack nodes: \n");
    stack_print(stdout, snode);
    fprintf(stdout, "Print Stack string: \n");
    stack_print(stdout, sstr);
    
    /*Mientras que nuestra pila sigue con valores, */
    /*liberamos cada valor de los nodos individuales almacenados en nuetra pila de nodos*/
    fprintf(stdout, "Poping nodes.... \n");
    while(stack_isEmpty(snode)==FALSE){
      naux = (Node*)stack_pop(snode);
      node_print(stdout, naux);
      node_free(naux);
    }
    /*Mientras que nuestra pila sigue con valores, */
    /*liberamos cada valor de los nodos individuales almacenados en nuetra pila de strings*/
    fprintf(stdout, "\nPoping nodes-names.... \n");
    while(stack_isEmpty(sstr)==FALSE){
      c = (char *)stack_pop(sstr);
      fprintf(stdout, "%c", *c);
      free(c);
    }
    
    /*Liberamos nodos y pilas*/
    node_free(n);
    stack_free(snode);
    stack_free(sstr);

    return 0;
}
