#  CITS2002 Project 2 2021
#  Name(s):             Kristijan Korunoski, Luke Kirkby
#  Student number(s):   22966841 (, 22885101)
#  Makefile to build 'duplicates' project

duplicates : duplicates.o directory_explore.o strSHA2.o hashtable_list.o
	cc -std=c11 -Wall -Werror -pedantic -o duplicates duplicates.o  directory_explore.o strSHA2.o hashtable_list.o -lm


duplicates.o : duplicates.c duplicates.h
	cc -std=c11 -Wall -Werror -pedantic -c duplicates.c

directory_explore.o : directory_explore.c duplicates.h
	cc -std=c11 -Wall -Werror -pedantic -c directory_explore.c

strSHA2.o : strSHA2.c duplicates.h
	cc -std=c11 -Wall -Werror -pedantic -c strSHA2.c

hashtable_list.o : hashtable_list.c duplicates.h
	cc -std=c11 -Wall -Werror -pedantic -c hashtable_list.c