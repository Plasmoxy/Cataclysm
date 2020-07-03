#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define TABLESIZE 5

// hash fun. returnuje cislo medzi 0 a TABLESIZE - 1
unsigned int hash(const char* key) {
	unsigned long val = 0;
	unsigned int key_len = strlen(key);

	for (unsigned int i = 0; i < key_len; i++) {
		val = val * 37 + key[i];
	}

	return val % TABLESIZE;
}

// alt. djb2 hash func
unsigned long hash_djb2(const char *str){
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % TABLESIZE;
}

// hash table impl...

// + linked list for entries
typedef struct entry {
	char* key;
	char* val;
	struct entry* next;
} entry;

typedef struct ht {
	entry** entries;
} ht;

entry* ht_pair(const char* key, const char* value) {
	entry* e = malloc(sizeof(entry));
	e->key = malloc(strlen(key) + 1); strcpy(e->key, key);
	e->val = malloc(strlen(value) + 1); strcpy(e->val, value);
	e->next = NULL; // nelinkujeme este ked vytvarame pair
	return e;
}

ht* ht_create() {
	// init table and a total of TABLESIZE entries
	ht* table = malloc(sizeof(ht) * 1);
	table->entries = calloc(TABLESIZE, sizeof(entry*));
	return table;
}

void ht_set(ht* table, const char* key, const char* value) {
	unsigned int slot = hash(key);

	entry* e = table->entries[slot];

	// ak je grabnuta entry null, tak pohoda je to empty slot a mozem tam trepnut ten pair
	if (e == NULL) {
		table->entries[slot] = ht_pair(key, value);
		return;
	}

	// ak nie, BUD uz tam je ten key a potrebujeme updatovat hodnotu ALEBO mame koliziu = 2 kluce hesuju do rovnakeho slotu
	entry* prev = NULL;
	while (e != NULL) {
		// matched
		if (strcmp(e->key, key) == 0) {
			free(e->val);
			e->val = malloc(strlen(value) + 1); strcpy(e->val, value);
			return;
		}

		// walk to next
		prev = e;
		e = prev->next;
	}

	prev->next = ht_pair(key, value);
}

char* ht_get(ht* table, const char* key) {
	unsigned int slot = hash(key);

	entry* e = table->entries[slot];
	if (e == NULL) return NULL;

	while (e != NULL) {
		if (strcmp(e->key, key) == 0) {
			return e->val;
		}

		e = e->next;
	}

	return NULL;
}

void ht_dump(ht *hashtable) {
	for (int i = 0; i < TABLESIZE; ++i) {
		entry *e = hashtable->entries[i];

		if (e == NULL) {
			continue;
		}

		printf("slot[%4d]: ", i);

		for(;;) {
			printf("%s=%s ", e->key, e->val);

			if (e->next == NULL) {
				break;
			}

			e = e->next;
		}

		printf("\n");
	}
}

int main() {
	ht* t = ht_create();
	ht_set(t, "name1", "Seb");
	ht_set(t, "name2", "Laila");
	ht_set(t, "name3", "George");
	ht_set(t, "name4", "Betty");
	ht_set(t, "name5", "Susan");

	ht_dump(t);

	return 0;
}