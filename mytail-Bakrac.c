#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
       printf("Error in argument amount.\n");
       return 1;
    }

    else
    {
        int i=0;
        char *size = argv[1];
        
        if(size[0] != '-')
        {
            printf("Incorrect argument parameters. Size must begin with '-'\n");
            return 1;
        }

        i = atoi(size+1);

        struct stat file;
        if((stat(argv[2], &file)) < 0)
        {
            printf("File not found in current working directory.\n");
            return 1;
        }
        
        if(i > file.st_size)
        {
            printf("Cannot read larger than file size.\n");
            return 1;
        }

        int fsize = file.st_size;
        int fileopen;

        //open file as read only
        if((fileopen = open(argv[2], O_RDONLY)) < 0)
        {
            printf("File not found.\n");
            return 1;
        }

        if(lseek(fileopen, -i , SEEK_END) < 0)
        {
            close(fileopen);
            return 1;
        }

        char buffer[i+1];

        //read last 'i' bytes
        if(read(fileopen, buffer, i) < 0)
             printf("error occured.\n");
        
        //append a null to end of our buffer then print out bufffer
        else
        {
            buffer[i] = '\0';
            printf("%s\n", buffer);
        }

        close(fileopen);
    }

     return 0;
}
