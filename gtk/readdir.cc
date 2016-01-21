#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void dump_entry(struct dirent *entry)
{
    int type = entry->d_type;
    char *text = "???";
 
    if (type == DT_BLK)
        text = "block device";

    if (type == DT_CHR)
        text = "character device";

    if (type ==  DT_DIR)
        text = "directory";

    if (type == DT_FIFO)
        text = "named pipe";

    if (type == DT_LNK)
        text = "symbolic link";

    if (type == DT_REG)
        text = "regular file";

    if (type == DT_SOCK)
        text = "unix domain socket";

    if (type == DT_UNKNOWN)
        text = "unknown";
 
    printf("%24s\t%s\n", entry->d_name, text);
}
 
int main(int argc, char** argv)
{
    int error;
    DIR *dir;
    struct dirent entry;
    struct dirent *result;

    dir = opendir(argv[1]);
    for (;;) {
        error = readdir_r(dir, &entry, &result);
        if (error != 0) {
            perror("readdir_r");
            return EXIT_FAILURE;
        }

        // readdir_r returns NULL in *result if the end 
        // of the directory stream is reached
        if (result == NULL)
            break;

        dump_entry(result);
    }
    closedir(dir);
    return 0;
}
