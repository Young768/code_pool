#include <unistd.h>
#include <fcntl.h>
 
int main(void)
{
    int filedesc = open("testfile.txt", O_WRONLY | O_CREAT,0666);
    char *c = "8";
    write(filedesc, c , 1);
    
    close(filedesc);
 
    return 0;
}
