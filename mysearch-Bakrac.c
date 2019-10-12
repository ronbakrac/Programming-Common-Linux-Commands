#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void recsearch(char *path);

int main(int argc, char *argv[])
{
    if(argc > 2)
    {
       printf("Error in argument amount.\n");
       return 1;
    }

    else if(argc ==2)
    {
        struct stat first;

        if(stat(argv[1], &first) < 0)
        {
            printf("Unable to find specified path in current directory.\n");
            return 1;
        }

        else if(S_ISDIR(first.st_mode))
            recsearch(argv[1]);
    }

    else
    {
        recsearch(".");
    }
    


    return 0;
}

void recsearch(char *path)
{
    DIR *direct;

    struct dirent *pdir;
    struct stat file;
    if((direct = opendir(path)) == NULL)
    {
        printf("Unable open a certain directory. Check permissions.\n");
        return;
    }
    chdir(path);

    //ignores first 2 folders of every directory which are "." and ".." representing current and prev directory
    pdir = readdir(direct);
    pdir = readdir(direct);

    while((pdir = readdir(direct)) != NULL)
    {
        if(stat(pdir->d_name, &file) < 0)
        {
            printf("Unable to find some file in a directory.\n");
            return;
        }

        if(S_ISDIR(file.st_mode))
        {
            recsearch(pdir->d_name);
            chdir("..");
        }
        
        else
        {
            printf("%s\n", pdir->d_name);
        }
        
    }

    return;

}