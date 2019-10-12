#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Incorrect arguments. Only include 1 file or directory to use stat\n");
        return 1;
    }

    struct stat file;
    int i;

    //stat takes string of file/directory, returns data in a stat struct 'file'
    if((stat(argv[1], &file)) < 0)
        return 1;

    printf("%s\n", argv[1]);
    printf("File size: %d Bytes\n", file.st_size);
    printf("Blocks allocated: %d\n", file.st_blocks);
    printf("Links: %d\n", file.st_nlink);


    //pritns if file is a directory, link, or file.
    printf(S_ISDIR(file.st_mode) ? "d" : (S_ISLNK(file.st_mode) ? "l" : "-") );


    //last 9 bits of st_mode correspond to owner, group, and other permissions (rwx)
    //this loop checks each of the 9 bits by bit shifting the number 256 (9th bit 1)
    //and determines whether the permission was a r, w or x (by the %)
    int k=256;
    for(i=9; i>0; i--)
    {
        printf(file.st_mode & k ? (i%3 == 0 ? "r" : (i%3 == 2 ? "w" : "x")) : "-");
        k = k>>1;
    }

    printf("\ninode number: %d\n", file.st_ino);
    return 0;
}
