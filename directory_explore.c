//  CITS2002 Project 2 2021
//  Name(s):             Kristijan Korunoski, Luke Kirkby
//  Student number(s):   22966841 (, 22885101)

#include "duplicates.h"

// Function to read through each entry in a directory and store some statistics about the entry
void directory_explore(char *dirname, bool a_arg)
{
    DIR             *dirp;
    struct dirent   *dp;
    char path[1000];
    char f_size[1000];

    //  ENSURE THAT WE CAN OPEN (read-only) THE REQUIRED DIRECTORY
    dirp       = opendir(dirname);
    if(dirp == NULL) {
        perror( dirname );
        exit(EXIT_FAILURE);
    }

    struct stat     stat_info;

    stat("./.", &stat_info); //Find the directory stat mode for later use
    
    int directory_value = stat_info.st_mode;

    //  READ FROM THE REQUIRED DIRECTORY, UNTIL WE REACH ITS END
    while((dp = readdir(dirp)) != NULL) {  
	    char fullpath[MAXPATHLEN];

        sprintf(fullpath, "%s/%s", dirname, dp->d_name );    

        //  DETERMINE ATTRIBUTES ABOUT THIS DIRECTORY ENTRY
        if(stat(fullpath, &stat_info) != 0) {
            perror( dp->d_name );
            exit(EXIT_FAILURE);
        }

        //Change the path varaible to include the current directory
        strcpy(path, dirname); 
        strcat(path, "/");
        strcat(path, dp->d_name);

        if (a_arg == false) { //If -a is not called skip all files starting with . 
            if (*dp->d_name == '.'){
                continue;
            } 
        }

        if (strcmp(dp->d_name, ".") == false || strcmp(dp->d_name, "..") == false) {
            //Skips . and .. directories
        } else if (stat_info.st_mode == directory_value) { //If the directory entry is another directory search thorugh this directory
            directory_explore(path, a_arg);
        } else {
            hashtable_add(path_hash, strSHA2(dp->d_name, dirname), path); //Store the file path in appropriate hashtable
            sprintf(f_size, "%ld", stat_info.st_size);
            hashtable_add(size_hash, strSHA2(dp->d_name, dirname), f_size); //Store the file size in appropriate hashtable

            numfiles++; //Increment total number of files
            total_size += stat_info.st_size; //Increment the total size of the directory
        }
    }

//  CLOSE THE DIRECTORY
    strcpy(path, dirname);
    closedir(dirp);
}

// Function to read through each entry in a directory and print its path if it has the same hash as the argument hash 
void h_directory(char *dirname, bool a_arg, char *hash)
{
    DIR             *dirp;
    struct dirent   *dp;
    char path_h[1000];

    //  ENSURE THAT WE CAN OPEN (read-only) THE REQUIRED DIRECTORY
    dirp       = opendir(dirname);
    if(dirp == NULL) {
        perror( dirname );
        exit(EXIT_FAILURE);
    }

    struct stat     stat_info;

    stat("./.", &stat_info); //Find the directory stat mode for later use
    
    int directory_value = stat_info.st_mode;

    //  READ FROM THE REQUIRED DIRECTORY, UNTIL WE REACH ITS END
    while((dp = readdir(dirp)) != NULL) {  
	    char fullpath[MAXPATHLEN];

        sprintf(fullpath, "%s/%s", dirname, dp->d_name );    

        //  DETERMINE ATTRIBUTES ABOUT THIS DIRECTORY ENTRY
        if(stat(fullpath, &stat_info) != 0) {
            perror( dp->d_name );
            exit(EXIT_FAILURE);
        }

        //Change the path varaible to include the current directory
        strcpy(path_h, dirname);
        strcat(path_h, "/");
        strcat(path_h, dp->d_name);

        if (a_arg == false) { //If -a is not called skip all files starting with .
            if (*dp->d_name == '.'){
                continue;
            } 
        }

        if (strcmp(dp->d_name, ".") == false || strcmp(dp->d_name, "..") == false) {
            //Skips . and .. directories
        } else if (stat_info.st_mode == directory_value) { //If the directory entry is another directory search thorugh this directory
            h_directory(path_h, a_arg, hash);
        } else if (strcmp(strSHA2(dp->d_name, dirname), hash) == false) { //If a file has a matching sha value
            printf("./");
            printf("%s\n", path_h); //Print the file path
            sim_hash_count++; //Increment the number of files found with the same hash
        }
    }

//  CLOSE THE DIRECTORY
    strcpy(path_h, dirname);
    closedir(dirp);
}