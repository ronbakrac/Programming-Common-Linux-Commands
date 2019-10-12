#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

void finfo(char *filein);

int main(int argc, char *argv[])
{
    if(argc > 4)
    {
       printf("Error in argument amounts.\n");
       return 1;
    }

    else if(argc == 1)
    {
        char cwd[100];
        struct dirent *pdir;
        getcwd(cwd, 100); 

        //dont need to pass in cwd but I do anyway. can just pass "." to open cwd as I'm already in the cwd.
        DIR *direc = opendir(cwd);

        if(direc == NULL)
        {
            printf("Directory not found.\n");
            return 1;
        }

        //iterating through direct reading every file/direct and printing the names
        else while((pdir = readdir(direc)) != NULL)
            printf("%s\n", pdir->d_name);

        return 0;   
    }

    else if(!strcmp(argv[1], "-l"))
    {

        struct dirent *pdir;
        DIR *direc;

        //we ls -l on cwd here since no directory specified
        if(argc==2)
        {
            direc = opendir(".");

            while((pdir = readdir(direc)) != NULL)
            {
                finfo(pdir->d_name);
                printf("\n");
            }
        }
        
        else
        {
            direc = opendir(argv[2]);

            if(direc == NULL)
            {
                printf("Directory not found.\n");
                return 1;
            }

            
            while((pdir = readdir(direc)) != NULL)
            {
                //passing the specified directory / pdir-name into finfo function. Stat() command only works on the
                //cwd so I must pass in the path/file. Later found out I can isntead change the working directory with
                //chdir function, but this works just as fine so I kept it.
                size_t direc_len = strlen(argv[2]);
                char *path = malloc(direc_len + 100);
                strcpy(path, argv[2]);
                path[direc_len] = '/';
                strcpy(path + direc_len + 1, pdir->d_name);
                finfo(path);
                printf("\n");
                free(path);
            }

        }   

        printf("\n");
        return 0;
    }


    printf("Eror in argument formatting. Closing...\n");
    return 0;
}


//basically the mystat.c file slightly modified
void finfo(char *filein)
{
    struct stat file;
    int i;

    if((stat(filein, &file)) < 0)
    {
        printf("big error\n");
        return;
    }

    printf("%s\n", filein);
    printf("File size: %d Bytes\n", file.st_size);
    printf("Blocks allocated: %d\n", file.st_blocks);
    printf("Links: %d\n", file.st_nlink);


    printf(S_ISDIR(file.st_mode) ? "d" : (S_ISLNK(file.st_mode) ? "l" : "-"));

    int k=256;
    for(i=9; i>0; i--)
    {
        printf(file.st_mode & k ? (i%3 == 0 ? "r" : (i%3 == 2 ? "w" : "x")) : "-");
        k = k>>1;
    }

    printf("\ninode number: %d\n", file.st_ino);
    return;
}
                 