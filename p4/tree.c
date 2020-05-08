/**
* @file tree.c
* @author Bernardo zambrano && Alvaro Platon
* @date 8 May 2020
* @version 1.0
* @brief ej3
**
@details
**
@see
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "tree.h"


typedef struct _BTNode {
  void *info;
  struct _BTNode *left;
  struct _BTNode *right;
  } BTNode;


struct _BSTree {
  BTNode *root;
  destroy_element_function_type destroy_element;
  copy_element_function_type copy_element;
  print_element_function_type print_element;
  cmp_element_function_type cmp_element;
  };
/*** DECLARACIÓN DE FUNCIONES PRIVADAS ***/

// Create a BTNode
BTNode* bt_node_new();

// Free a BTNode
void bt_node_free (BTNode *pn, destroy_element_function_type free_elem);

//Recursive binary tree free
void tree_destroy_rec (BTNode *root, destroy_element_function_type free_elem);

//Recursive binary tree fun to det depth
int tree_depth_rec (const BTNode *root);

//Recursive  function fort printing in preOrder
void tree_preOrder_rec (FILE *f, const BTNode *root, print_element_function_type print_element);

//Recursive  function fort printing in inOrder
void tree_inOrder_rec (FILE *f, const BTNode *root, print_element_function_type print_element);

//Recursive  function fort printing in postOrder
void tree_postOrder_rec (FILE *f, const BTNode *root, print_element_function_type print_element);

/*** PRIMITIVAS PRIVADAS DE BT-NODOS ***/
BTNode * bt_node_new()
{
  BTNode* pn = NULL;
  pn = malloc(sizeof(BTNode));
  if (!pn) {
    fprintf (stderr,"%s\n", strerror (errno));
    return NULL;
  }
  pn->left = pn->right = NULL;
  pn->info = NULL;
  return pn;
}

void bt_node_free (BTNode *pn, destroy_element_function_type free_elem)
{
  if (!pn) return;
  free_elem(pn->info);
  free(pn);
}


/*** CREACIÓN Y LIBERACIÓN DE UN ÁRBOL ***/
/*Inicializa un árbol vacío.*/
BSTree* tree_init(destroy_element_function_type f1,
copy_element_function_type f2,
print_element_function_type f3,
cmp_element_function_type f4)
{
  BSTree* tree = malloc (sizeof(BSTree));
  if (!tree) {
    fprintf (stderr,"%s\n", strerror (errno));
    return NULL;
  }

  tree->root = NULL;
  tree->destroy_element=f1;
  tree->copy_element=f2;
  tree->print_element=f3;
  tree->cmp_element=f4;
  return tree;
}


/*Indica si el árbol está o no vacio*/
Bool tree_isEmpty( const BSTree *tree){

  if(!tree) return FALSE;

  if (tree->root == NULL) return TRUE;

  return FALSE;
}


/*Libera la memoria utilizada por un árbol.*/
void tree_destroy (BSTree *tree)
{
  if(!tree) return;

  if(tree_isEmpty(tree) == TRUE){
    bt_node_free(tree->root, tree->destroy_element);
    free(tree);
    return;
  }

  tree_destroy_rec(tree->root, tree->destroy_element);
  free(tree);
  return;
}

void tree_destroy_rec (BTNode *root, destroy_element_function_type free_elem)
{
  if(root != NULL){

    tree_destroy_rec(root->left, free_elem);
    tree_destroy_rec(root->right, free_elem);

    bt_node_free(root, free_elem);
  }

  return;
}


/*Indica la profundidad del árbo. Un árbol vacio profundidad -1*/
int tree_depth (const BSTree *tree)
{
  if(!tree) return -2;

  if(tree_isEmpty(tree) == TRUE) return -1;


  return tree_depth_rec(tree->root);
}

int tree_depth_rec (const BTNode *root)
{
  int ret=0;
  int aux=0;

  if(!root) return 0;

  ret += tree_depth_rec(root->right);

  aux += tree_depth_rec(root->left);

  if(ret<aux) ret = aux;

  ret++;

  return ret;
}

/*** INSERCIÓN ***/
/*Inserta un elemento en un árbol binario de búsqueda.*/
Status tree_insert (BSTree *tree, const void *elem)
{
  BTNode * n;
  BTNode * aux; /* nodo usado para buscar donde se insertara el nodo  */
  BTNode * aux2 = NULL; /* nodo usado para guardar el anterior a dicho nodo */

  if(!tree || !elem) return ERROR;

  n = bt_node_new();
  if(!n)  return ERROR;

  n->info = tree->copy_element(elem);
  if(n->info == NULL){
    bt_node_free(n, tree->destroy_element);
    return ERROR;
  }

  /**
  * Hasta aqui todo funciona perfecto
  */

  aux = tree->root;


  while(aux != NULL){
    aux2 = aux;
    if(tree->cmp_element(elem, aux->info) < 0){
      aux = aux->left;
    }
    else{
      aux = aux->right;
    }
  }

  /**
  * Si la raiz es null producira este valor y se insertara directamente a la raiz
  */
  if(!aux2) {
    tree->root = bt_node_new();

    tree->root->info = tree->copy_element(elem);
    bt_node_free(n, tree->destroy_element);

    return OK;
  }
  if(tree->cmp_element(elem, aux2->info) < 0){
    aux2->left = n;
  }
  else{
    aux2->right = n;
  }

  return OK;
}


/*** RECORRIDOS ***/
/*Recorre un árbol en orden previo.*/
void tree_preOrder (FILE *f, const BSTree *tree)
{
  if(!f || !tree) return;

  return tree_preOrder_rec (f, tree->root, tree->print_element);
}

void tree_preOrder_rec (FILE *f, const BTNode *root, print_element_function_type print_element)
{

  if(!root) return;

  print_element(f, root->info);

  if(root->left != NULL){
    tree_preOrder_rec (f, root->left, print_element);
  }

  if(root->right != NULL){
    tree_preOrder_rec (f, root->right, print_element);
  }


    return;
}

/*Recorre un árbol en orden medio.*/
void tree_inOrder (FILE *f, const BSTree *tree)
{
  if(!f || !tree) return;

  return tree_inOrder_rec (f, tree->root, tree->print_element);
}

void tree_inOrder_rec (FILE *f, const BTNode *root, print_element_function_type print_element)
{

  if(!root) return;


  if(root->left != NULL){
    tree_inOrder_rec (f, root->left, print_element);
  }

  print_element(f, root->info);

  if(root->right != NULL){
    tree_inOrder_rec (f, root->right, print_element);
  }

    return;
}

/*Recorre un árbol en orden posterior.*/
void tree_postOrder (FILE *f, const BSTree *tree){
  if(!f || !tree) return;

  tree_postOrder_rec (f, tree->root, tree->print_element);

  return;
}

void tree_postOrder_rec (FILE *f, const BTNode *root, print_element_function_type print_element)
{

  if(!root) return;

  if(root->left != NULL)
    tree_postOrder_rec (f, root->left, print_element);

  if(root->right != NULL)
    tree_postOrder_rec (f, root->right, print_element);

  print_element(f, root->info);

    return;
}
