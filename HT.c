//#include "secure.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACITY 50000

unsigned long Hash_Function(char* str) {
    unsigned  hash = 0;
    for (int i = 0; i < strlen(str); i++){
        hash += (int)str[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

typedef struct HashTableItem HashTableItem;

struct HashTableItem {
    int key;
    char* username;
    char* password;
};

typedef struct HashTable HashTable;

struct HashTable {
    HashTableItem** items;
    int size;
    int count;
};

HashTableItem* Create_item(char* username, char* password) {
    HashTableItem* item = (HashTableItem*) malloc(sizeof(HashTableItem));
    item -> username = (char*) malloc (sizeof(strlen(username)+1));
    item -> password = (char*) malloc (sizeof(strlen(password)+1));
    strcpy(item->username, username);
    strcpy(item->password, password);
    return item;
}

HashTable* Create_table(int size){
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (HashTableItem**) calloc (table->size, sizeof(HashTableItem*));
    for (int i = 0; i < table->size; i++){
        table->items[i] = NULL;
    }
    return table;
}

void Free_Item(HashTableItem* item) {
    free(item->username);
    free(item->password);
    free(item);
}

void Free_Table(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        HashTableItem* item = table->items[i];
        if (item != NULL){
            Free_Item(item);
        }
    }
    free(table->items);
    free(table);
}

void HashTable_Insert(HashTable* table, char* username, char* password){
    long pwd = Hash_Function(password);    
    char var[100];
    sprintf(var, "%ld", pwd);
    HashTableItem* item = Create_item(username, var);
    HashTableItem* current_item = table->items[table->count];
    if (current_item == NULL){
        if(table->count == table->size){
            printf("Insert error: Table is full!\n");
            Free_Item(item);
            return;
        }
        table->items[table->count] = item;
        table->count++;
    }
    else {
        if (strcmp(current_item->password, password) == 0){
            strcpy(table->items[table->count]->username, username);
            return;
        }
    }
}

void print_table(HashTable* table) {
    printf("\nHash Table\n-------------------\n");
    for (int i = 0; i < table->count; i++) {
        if (table->items[i]) {
            printf("ID:%d, Username:%s, Password:%s\n",i, table->items[i]->username, table->items[i]->password);
        }
    }
    printf("-------------------\n\n");
}
    
int main(){
    HashTable* ht = Create_table(CAPACITY);
    HashTable_Insert(ht, "admin", "admin");
    HashTable_Insert(ht, "USER1", "qwerty111");
    HashTable_Insert(ht, "USER2", "asdfgh21");
    print_table(ht);
    Free_Table(ht);
    return 0;
}




















