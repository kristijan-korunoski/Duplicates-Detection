//  CITS2002 Project 2 2021
//  Name(s):             Kristijan Korunoski, Luke Kirkby
//  Student number(s):   22966841 (, 22885101)

#include        <stdio.h>
#include        <stdlib.h>
#include        <stdbool.h>
#include        <string.h>
#include        <unistd.h>
#include        <fcntl.h>
#include        <sys/types.h>
#include        <sys/stat.h>
#include        <dirent.h>
#include        <sys/param.h>

//  strSHA2 function to develop hash string
extern char     *strSHA2(char *filename, char *filepath);

//  function to read through directory finding every file
extern void     directory_explore(char *dirname, bool a_arg);

//  function to read through directory finding every file and printing if file hash code is equal to "hash"
extern void     h_directory(char *dirname, bool a_arg, char *hash);

//  A HELPFUL PREPROCESSOR MACRO TO CHECK IF ALLOCATIONS WERE SUCCESSFUL
#define CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

//  OUR SIMPLE LIST DATATYPE - A DATA ITEM, AND A POINTER TO ANOTHER LIST
typedef struct _list {
     char           *string;
     struct _list   *next;
} LIST;

//  'CREATE' A NEW, EMPTY LIST
extern	LIST	*list_new(void);

//  ADD A NEW (STRING) ITEM TO AN EXISTING LIST
extern	LIST	*list_add(  LIST *list, char *newstring);

//  DETERMINE IF A REQUIRED ITEM (A STRING) IS STORED IN A GIVEN LIST
extern	bool	 list_find (LIST *list, char *wanted);

//  PRINT EACH ITEM (A STRING) IN A GIVEN LIST TO stdout
extern	void	 dupe_list_print(LIST *list);

//  ACCUMULATE THE TOTAL SIZE OF 
extern    int   size_list_count(LIST *list);

//  WE DEFINE A HASHTABLE AS A (WILL BE, DYNAMICALLY ALLOCATED) ARRAY OF LISTs
typedef	LIST * HASHTABLE;

//   HASH FUNCTION
extern    u_int32_t  hash_string(char *string);

//  ALLOCATE SPACE FOR A NEW HASHTABLE (AND ARRAY OF LISTS)
extern	HASHTABLE	*hashtable_new(void);

//  ADD A NEW STRING TO A GIVEN HASHTABLE
extern	void		 hashtable_add( HASHTABLE *, char *key, char *value);

//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
extern	bool		 hashtable_find(HASHTABLE *, char *string);

// GLOBAL VARIABLES
extern DIR          *dirp;
extern char         sha_path[];
extern HASHTABLE    *path_hash;
extern int          numfiles;
extern HASHTABLE    *size_hash;
extern int          total_size;
extern int          sim_hash_count;
