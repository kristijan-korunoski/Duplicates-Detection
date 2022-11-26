//  CITS2002 Project 2 2021
//  Name(s):             Kristijan Korunoski, Luke Kirkby
//  Student number(s):   22966841 (, 22885101)

#include "duplicates.h"

// compile with "make"
// run with "./duplicates "

// A set of flobal variables
char        sha_path[1000];
HASHTABLE   *path_hash;
HASHTABLE   *size_hash;
int         numfiles;
int         unique_files;
int         unique_size;
int         total_size;
int         sim_hash_count;

int main(int argc, char *argv[])
{
    if(argc == 1) {
        exit(EXIT_FAILURE);
    }

    path_hash = hashtable_new();
    size_hash = hashtable_new();
    numfiles = 0;
    unique_files = 0;
    total_size = 0;
    sim_hash_count = 0;
    bool a_exist = false; // Boolean storing whether the -a argument has been called

    strcpy(sha_path, "./");

    if(argc == 2){ //If no arguments are given other than the target directory 
        directory_explore(argv[argc-1], false); //Goes through the directory storing data about files
        //Generate output by getting data from hashtables
        for (int i = 0; i < 112321; i++) {
            unique_size += size_list_count(size_hash[i]); //For each new file with different hash increment the minimum size
            if (path_hash[i] != NULL){
                unique_files++; //For each new file with different hash increment the nubmer of unique files
            }
        }
        printf("%i\n", numfiles);
        printf("%i\n", total_size);
        printf("%i\n", unique_files);
        printf("%i\n", unique_size);
        exit(EXIT_SUCCESS);
    }
    
    for (int j = 1; j < argc-1; j++) { //Iterate through command line argument
        if(strcmp(argv[j], "-a") == false && argc == 3){ //If only -a argument is given
            directory_explore(argv[argc-1], true); //Goes through the directory storing data about files
            //Generate output by getting data from hashtables
            for (int i = 0; i < 112321; i++) {
                unique_size += size_list_count(size_hash[i]); //For each new file with different hash increment the minimum size
                if (path_hash[i] != NULL){
                    unique_files++; //For each new file with different hash increment the nubmer of unique files
                }
            }
            printf("%i\n", numfiles);
            printf("%i\n", total_size);
            printf("%i\n", unique_files);
            printf("%i\n", unique_size);
            exit(EXIT_SUCCESS);
        }
        else if(strcmp(argv[j], "-A") == false){ //Advanced version not attempted, EXIT_FAILURE
            exit(EXIT_FAILURE);
        }
        else if(strcmp(argv[j], "-m") == false){ //Advanced version not attempted, EXIT_FAILURE
            exit(EXIT_FAILURE);
        }
        else if(strcmp(argv[j], "-f") == false){ //If -f is given as a command line argument
            if (argc <= 3) { //If -f is given without a file exit with EXIT_FAILURE
                exit(EXIT_FAILURE);
            }
            for (int k = 1; k < argc-1; k++){ //Check if -a is ever given as a command line argument
                if(strcmp("-a", argv[k]) == false){
                    a_exist = true;
                }
            }
            //strSHA is called to find the hash of the file
            h_directory(argv[argc-1], a_exist, strSHA2(argv[j+1], ".")); //Goes through the directory printing file directory with the same hash
            if (sim_hash_count == 0) { //Check if any files were found and exit with appropriate value
                exit(EXIT_FAILURE);
            } else {
                exit(EXIT_SUCCESS);
            }
        }
        else if(strcmp(argv[j], "-l") == false){ //If -l is ever given as a command line argument
            for (int k = 1; k < argc-1; k++){ //Check if -a is ever given as a command line argument
                if(strcmp("-a", argv[k]) == false){
                    a_exist = true;
                }
            }
            directory_explore(argv[argc-1], a_exist); //Goes through the directory storing data about files
            // Generate output by getting data from hashtable
            for (int i = 0; i < 112321; i++) {
                dupe_list_print(path_hash[i]); //Prints paths of duplicate files if they are duplicates
            }
            exit(EXIT_SUCCESS);
        }
        else if(strcmp(argv[j], "-h") == false){ //If -h is ever given as a command line argument
            if (argc <= 3) { //If -f is given without a hash value exit with EXIT_FAILURE
                exit(EXIT_FAILURE);
            }
            for (int k = 1; k < argc-1; k++){ //Check if -a is ever given as a command line argument
                if(strcmp("-a", argv[k]) == false){
                    a_exist = true;
                }
            }
            h_directory(argv[argc-1], a_exist, argv[j+1]); //Goes through the directory printing file directory with the same hash
            if (sim_hash_count == 0) { //Check if any files were found and exit with appropriate value
                exit(EXIT_FAILURE);
            } else {
                exit(EXIT_SUCCESS);
            }
        }
        else if(strcmp(argv[j], "-q") == false){ //If -q is ever given as a command line argument
            directory_explore(argv[argc-1], false); //Goes through the directory storing data about files
            for (int i = 0; i < 112321; i++) { //Generate data by getting data from hashtables
                if (path_hash[i] != NULL){
                    unique_files++; //For each new file with different hash increment the nubmer of unique files
                }
            }
            if (unique_files == numfiles) { //If there are duplicate files exit with EXIT_FAILURE
                exit(EXIT_SUCCESS);
            } else {
                exit(EXIT_FAILURE);
            }
        }
    }
}
