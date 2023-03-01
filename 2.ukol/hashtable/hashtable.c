/*
 * Tabuľka s rozptýlenými položkami
 *
 * S využitím dátových typov zo súboru hashtable.h a pripravených kostier
 * funkcií implementujte tabuľku s rozptýlenými položkami s explicitne
 * zreťazenými synonymami.
 *
 * Pri implementácii uvažujte veľkosť tabuľky HT_SIZE.
 */

#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

int HT_SIZE = MAX_HT_SIZE;

/*
 * Rozptyľovacia funkcia ktorá pridelí zadanému kľúču index z intervalu
 * <0,HT_SIZE-1>. Ideálna rozptyľovacia funkcia by mala rozprestrieť kľúče
 * rovnomerne po všetkých indexoch. Zamyslite sa nad kvalitou zvolenej funkcie.
 */
int get_hash(char *key) {
  int result = 1;
  int length = strlen(key);
  for (int i = 0; i < length; i++) {
    result += key[i];
  }
  return (result % HT_SIZE);
}

/*
 * Inicializácia tabuľky — zavolá sa pred prvým použitím tabuľky.
 */
void ht_init(ht_table_t *table) {
  for (size_t i = 0; i < HT_SIZE; i++)
  {
    (*table)[i] = NULL;
  }
  
}

/*
 * Vyhľadanie prvku v tabuľke.
 *
 * V prípade úspechu vráti ukazovateľ na nájdený prvok; v opačnom prípade vráti
 * hodnotu NULL.
 */
ht_item_t *ht_search(ht_table_t *table, char *key) {
  int index = get_hash(key);
  ht_item_t *search = (*table)[index];
  while (search != NULL)
  {
    if(strcmp(search->key, key) == 0)
    {
      return search;
    }
    search = search->next;
  }
  return NULL;
}

/*
 * Vloženie nového prvku do tabuľky.
 *
 * Pokiaľ prvok s daným kľúčom už v tabuľke existuje, nahraďte jeho hodnotu.
 *
 * Pri implementácii využite funkciu ht_search. Pri vkladaní prvku do zoznamu
 * synonym zvoľte najefektívnejšiu možnosť a vložte prvok na začiatok zoznamu.
 */
void ht_insert(ht_table_t *table, char *key, float value) {
  ht_item_t* insert = ht_search(table, key);
  if (insert == NULL)
  {
    ht_item_t* new = malloc(sizeof(ht_item_t));
    {
      new->key = key;
      new->value = value;
      new->next = (*table)[get_hash(key)];
      (*table)[get_hash(key)] = new;
    }
    
  }
  else
  {
    insert->value = value;
    return;
  }
}

/*
 * Získanie hodnoty z tabuľky.
 *
 * V prípade úspechu vráti funkcia ukazovateľ na hodnotu prvku, v opačnom
 * prípade hodnotu NULL.
 *
 * Pri implementácii využite funkciu ht_search.
 */
float *ht_get(ht_table_t *table, char *key) {
  ht_item_t* get = ht_search(table, key);
  if (get == NULL)
  {
    return NULL;
  }
  else
  {
    return &(get->value);
  }
  
}

/*
 * Zmazanie prvku z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje priradené k danému prvku.
 * Pokiaľ prvok neexistuje, nerobte nič.
 *
 * Pri implementácii NEVYUŽÍVAJTE funkciu ht_search.
 */
void ht_delete(ht_table_t *table, char *key) {
  ht_item_t* delete = (*table)[get_hash(key)];
  ht_item_t* prev = NULL;
  while (delete != NULL)
  {
    if (delete->key == key)
    {
      if (prev == NULL)
      {
        (*table)[get_hash(key)] = delete->next;
      }
      else
      {
        prev->next = delete->next;
      }
      free(delete);
      return;
    }
    prev = delete;
    delete = delete->next;
  }
  
  
}

/*
 * Zmazanie všetkých prvkov z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje a uvedie tabuľku do stavu po
 * inicializácii.
 */
void ht_delete_all(ht_table_t *table) {
  for (size_t i = 0; i < HT_SIZE; i++)
  {
    ht_item_t* deleteAll = (*table)[i];
    while (deleteAll != NULL)
    {
      ht_item_t* next = deleteAll->next;
      free(deleteAll);
      deleteAll = next;
    }
    (*table)[i] = NULL;
  }
  
}
