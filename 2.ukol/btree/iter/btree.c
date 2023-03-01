/*
 * Binárny vyhľadávací strom — iteratívna varianta
 *
 * S využitím dátových typov zo súboru btree.h, zásobníkov zo súborov stack.h a
 * stack.c a pripravených kostier funkcií implementujte binárny vyhľadávací
 * strom bez použitia rekurzie.
 */

#include "../btree.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Inicializácia stromu.
 *
 * Užívateľ musí zaistiť, že incializácia sa nebude opakovane volať nad
 * inicializovaným stromom. V opačnom prípade môže dôjsť k úniku pamäte (memory
 * leak). Keďže neinicializovaný ukazovateľ má nedefinovanú hodnotu, nie je
 * možné toto detegovať vo funkcii.
 */
void bst_init(bst_node_t **tree) {
  *tree = NULL;
}

/*
 * Nájdenie uzlu v strome.
 *
 * V prípade úspechu vráti funkcia hodnotu true a do premennej value zapíše
 * hodnotu daného uzlu. V opačnom prípade funckia vráti hodnotu false a premenná
 * value ostáva nezmenená.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
bool bst_search(bst_node_t *tree, char key, int *value) {
  while(tree != NULL)
  {
    if(tree->key == key)
    {
      *value = tree->value;
      return true;
    }
    else if(tree->key > key)
    {
      tree = tree->left;
    }
    else
    {
      tree = tree->right;
    }
  }
  return false;
}

/*
 * Vloženie uzlu do stromu.
 *
 * Pokiaľ uzol so zadaným kľúčom v strome už existuje, nahraďte jeho hodnotu.
 * Inak vložte nový listový uzol.
 *
 * Výsledný strom musí spĺňať podmienku vyhľadávacieho stromu — ľavý podstrom
 * uzlu obsahuje iba menšie kľúče, pravý väčšie.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
void bst_insert(bst_node_t **tree, char key, int value) {
  bst_node_t *new_node = malloc(sizeof(bst_node_t));
  new_node->key = key;
  new_node->value = value;
  new_node->left = NULL;
  new_node->right = NULL;
  if(*tree == NULL)
  {
    *tree = new_node;
    return;
  }
  bst_node_t *tmp = *tree;
  while(tmp != NULL)
  {
    if(tmp->key == key)
    {
      tmp->value = value;
      free(new_node);
      return;
    }
    else if(tmp->key > key)
    {
      if(tmp->left == NULL)
      {
        tmp->left = new_node;
        return;
      }
      else
      {
        tmp = tmp->left;
      }
    }
    else
    {
      if(tmp->right == NULL)
      {
        tmp->right = new_node;
        return;
      }
      else
      {
        tmp = tmp->right;
      }
    }
  }
}

/*
 * Pomocná funkcia ktorá nahradí uzol najpravejším potomkom.
 *
 * Kľúč a hodnota uzlu target budú nahradené kľúčom a hodnotou najpravejšieho
 * uzlu podstromu tree. Najpravejší potomok bude odstránený. Funkcia korektne
 * uvoľní všetky alokované zdroje odstráneného uzlu.
 *
 * Funkcia predpokladá že hodnota tree nie je NULL.
 *
 * Táto pomocná funkcia bude využitá pri implementácii funkcie bst_delete.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree) {
  bst_node_t *item = *tree;
  bst_node_t *item2 = NULL;
  while (item->right != NULL)
  {
    item2 = item;
    item = item->right;
  }
  target->key = item->key;
  target->value = item->value;
  if(item2 == NULL)
  {
    *tree = item->left;
  }
  else
  {
    item2->right = item->left;
  }
  free(item);
  
}

/*
 * Odstránenie uzlu v strome.
 *
 * Pokiaľ uzol so zadaným kľúčom neexistuje, funkcia nič nerobí.
 * Pokiaľ má odstránený uzol jeden podstrom, zdedí ho otec odstráneného uzla.
 * Pokiaľ má odstránený uzol oba podstromy, je nahradený najpravejším uzlom
 * ľavého podstromu. Najpravejší uzol nemusí byť listom!
 * Funkcia korektne uvoľní všetky alokované zdroje odstráneného uzlu.
 *
 * Funkciu implementujte iteratívne pomocou bst_replace_by_rightmost a bez
 * použitia vlastných pomocných funkcií.
 */
void bst_delete(bst_node_t **tree, char key) {
  bst_node_t *item = *tree;
  bst_node_t *item2 = NULL;
  while(item != NULL)
  {
    if(item->key == key)
    {
      if(item->left == NULL && item->right == NULL)
      {
        if(item2 == NULL)
        {
          *tree = NULL;
        }
        else if(item2->left == item)
        {
          item2->left = NULL;
        }
        else
        {
          item2->right = NULL;
        }
        free(item);
        return;
      }
      else if(item->left == NULL)
      {
        if(item2 == NULL)
        {
          *tree = item->right;
        }
        else if(item2->left == item)
        {
          item2->left = item->right;
        }
        else
        {
          item2->right = item->right;
        }
        free(item);
        return;
      }
      else if(item->right == NULL)
      {
        if(item2 == NULL)
        {
          *tree = item->left;
        }
        else if(item2->left == item)
        {
          item2->left = item->left;
        }
        else
        {
          item2->right = item->left;
        }
        free(item);
        return;
      }
      else
      {
        bst_replace_by_rightmost(item, &item->left);
        return;
      }
    }
    else if(item->key > key)
    {
      item2 = item;
      item = item->left;
    }
    else
    {
      item2 = item;
      item = item->right;
    }
  }
}

/*
 * Zrušenie celého stromu.
 *
 * Po zrušení sa celý strom bude nachádzať v rovnakom stave ako po
 * inicializácii. Funkcia korektne uvoľní všetky alokované zdroje rušených
 * uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_dispose(bst_node_t **tree) {
  if(*tree == NULL)
  {
    return;
  }
  stack_bst_t stack;
  stack_bst_init(&stack);
  bst_node_t *item = *tree;
  while(item != NULL)
  {
    if(item->left != NULL)
    {
      stack_bst_push(&stack, item);
      item = item->left;
    }
    else if(item->right != NULL)
    {
      stack_bst_push(&stack, item);
      item = item->right;
    }
    else
    {
      if(stack_bst_empty(&stack))
      {
        free(item);
        *tree = NULL;
        return;
      }
      bst_node_t *item2 = stack_bst_top(&stack);
      stack_bst_pop(&stack);
      if(item2->left == item)
      {
        free(item);
        item = item2;
        item->left = NULL;
      }
      else
      {
        free(item);
        item = item2;
        item->right = NULL;
      }
    }
  }
  
}

/*
 * Pomocná funkcia pre iteratívny preorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu.
 * Nad spracovanými uzlami zavola bst_print_node a uloží ich do zásobníku uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_preorder(bst_node_t *tree, stack_bst_t *to_visit) {
  bst_node_t *item = tree;
  while (item != NULL)
  {
    stack_bst_push(to_visit, item);
    bst_print_node(item);
    item = item->left;
  }
}

/*
 * Preorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_preorder a
 * zásobníku uzlov bez použitia vlastných pomocných funkcií.
 */
void bst_preorder(bst_node_t *tree) { //root, left, right (R, L, Ri)
  stack_bst_t toVisit;
  stack_bst_init(&toVisit);
  bst_leftmost_preorder(tree, &toVisit);
  while (!stack_bst_empty(&toVisit))
  {
    tree = stack_bst_top(&toVisit);
    stack_bst_pop(&toVisit);
    if (tree->right != NULL)
    {
      bst_leftmost_preorder(tree->right, &toVisit);
      tree = tree->right;
    }
    
  }
}

/*
 * Pomocná funkcia pre iteratívny inorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu a ukladá uzly do
 * zásobníku uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_inorder(bst_node_t *tree, stack_bst_t *to_visit) {
  bst_node_t *item = tree;
  while (item != NULL)
  {
    stack_bst_push(to_visit, item);
    item = item->left;
  }
}

/*
 * Inorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_inorder a
 * zásobníku uzlov bez použitia vlastných pomocných funkcií.
 */
void bst_inorder(bst_node_t *tree) { // left, root, right (L, R, Ri)
  stack_bst_t toVisit;
  stack_bst_init(&toVisit);
  bst_leftmost_inorder(tree, &toVisit);
  while (!stack_bst_empty(&toVisit))
  {
    tree = stack_bst_top(&toVisit);
    stack_bst_pop(&toVisit);
    bst_print_node(tree);
    if (tree->right != NULL)
    {
      bst_leftmost_inorder(tree->right, &toVisit);
      tree = tree->right;
    }
  }
}

/*
 * Pomocná funkcia pre iteratívny postorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu a ukladá uzly do
 * zásobníku uzlov. Do zásobníku bool hodnôt ukladá informáciu že uzol
 * bol navštívený prvý krát.
 *
 * Funkciu implementujte iteratívne pomocou zásobníkov uzlov a bool hodnôt a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_postorder(bst_node_t *tree, stack_bst_t *to_visit, stack_bool_t *first_visit) {
  bst_node_t *item = tree;
  while (item != NULL)
  {
    stack_bst_push(to_visit, item);
    stack_bool_push(first_visit, true);
    item = item->left;
  }
}
/*
 * Postorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_postorder a
 * zásobníkov uzlov a bool hodnôt bez použitia vlastných pomocných funkcií.
 */
void bst_postorder(bst_node_t *tree) { // left, right, root (L, Ri, R)
  stack_bst_t toVisit;
  stack_bool_t visited;
  stack_bst_init(&toVisit);
  stack_bool_init(&visited);
  bst_leftmost_postorder(tree, &toVisit, &visited);
  while (!stack_bst_empty(&toVisit))
  {
    bst_node_t *curr = stack_bst_top(&toVisit);
    bool firstVisit = stack_bool_top(&visited);
    stack_bst_pop(&toVisit);
    stack_bool_pop(&visited);
    if (firstVisit)
    {
      stack_bst_push(&toVisit, curr);
      stack_bool_push(&visited, false);
      bst_leftmost_postorder(curr->right, &toVisit, &visited);
    }
    else
    {
      bst_print_node(curr);
    }
  }
}
