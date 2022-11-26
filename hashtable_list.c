//  CITS2002 Project 2 2021
//  Name(s):             Kristijan Korunoski, Luke Kirkby
//  Student number(s):   22966841 (, 22885101)

#include "duplicates.h"

#define	HASHTABLE_SIZE		112321 //Possible number of diffrent hash values

//  FUNCTION hash_string() ACCEPTS A STRING PARAMETER,
//  AND RETURNS AN UNSIGNED 32-BIT INTEGER AS ITS RESULT
#if	defined(__linux__)
extern	char	*strdup(char *string);
#endif

u_int32_t hash_string(char *string)
{
    u_int32_t hash = 0;
    int i = 1;

    while(*string != '\0') { //Hash based on the characters in the string
        hash += i*(*string);
        ++string;
        ++i;
    }

    hash -= 99840;
    return hash;
}

//  ALLOCATE SPACE FOR A NEW HASHTABLE (AND ARRAY OF LISTS)
HASHTABLE *hashtable_new(void)
{
    HASHTABLE   *new = malloc(HASHTABLE_SIZE * sizeof(LIST *));

    CHECK_ALLOC(new);
    return new;
}

//  ADD A NEW STRING TO A GIVEN HASHTABLE
void hashtable_add(HASHTABLE *hashtable, char *key, char *value)
{
    u_int32_t h   = hash_string(key) % HASHTABLE_SIZE;    // choose list

    hashtable[h] = list_add(hashtable[h], value);
}

//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
bool hashtable_find(HASHTABLE *hashtable, char *string) // i changed this might not need to be changed tho 
{
    u_int32_t h	= hash_string(string) % HASHTABLE_SIZE;     // choose list

    return list_find(hashtable[h], string);
}
//  ---------------------------------------------------------------------

//  'CREATE' A NEW, EMPTY LIST - JUST A NULL POINTER
LIST *list_new(void)
{
    return NULL;
}

//  DETERMINE IF A REQUIRED ITEM (A STRING) IS STORED IN A GIVEN LIST
bool list_find(LIST *list, char *wanted)
{
    while(list != NULL) {
	if(strcmp(list->string, wanted) == 0) {
	    return true;
	}
	list	= list->next;
    }
    return false;
}

//  ALLOCATE SPACE FOR A NEW LIST ITEM, TESTING THAT ALLOCATION SUCCEEDS
LIST *list_new_item(char *newstring)
{
    LIST *new       = malloc( sizeof(LIST) );
    CHECK_ALLOC(new);
    new->string     =  strdup(newstring);
    CHECK_ALLOC(new->string);
    new->next       =  NULL;
    return new;
}

//  ADD A NEW (STRING) ITEM TO AN EXISTING LIST
LIST *list_add(LIST *list, char *newstring)
{
    if(list_find(list, newstring)) {            // only add each item once
        return list;
    }
    else {                                      // add new item to head of list
        LIST *new   = list_new_item(newstring);
        new->next   = list;
        return new;
    }
}

//  PRINT EACH ITEM (A STRING) IN A GIVEN LIST TO stdout 
//  ONLY IF THERE IS MORE THAN ONE ITEM IN LIST
void dupe_list_print(LIST *list) 
{
    if (list != NULL) {
        if (list->next == NULL) {

        } else {
            while(list != NULL) {
                printf("./");
                printf("%s", list->string);
                if(list->next != NULL) {
                    printf("\t");
                    }
                list	= list->next;
            }
            printf("\n");
        }
	
    }
}

// Find the size of an element in the hashtable
int size_list_count(LIST *list)
{
    int t_size = 0;
    if(list != NULL) {
	    t_size = atoi(list->string);
    }
    return t_size;
}
