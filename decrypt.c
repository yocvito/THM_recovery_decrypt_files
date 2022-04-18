#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

// you can change the code to read the key from argv
const char key[] = "AdsipPewFlfkmll";

static void
usage(const char * cmd)
{
    fprintf(stderr, "Usage: %s <file>\n", cmd);
    exit(1);
}

int
main(int argc, char **argv)
{
    if (argc != 2)
        usage(argv[0]);

    const size_t keysize = strlen(key);
    printf("key: %s\n", key);

    int decrypt_fd = open(argv[1], O_RDWR);
    if (decrypt_fd < 0)
    {
        perror("open");
        exit(1);
    }

    int fdecrypt_size = lseek(decrypt_fd, 0, SEEK_END);
    lseek(decrypt_fd, 0, SEEK_SET);

    char *file = mmap(NULL, fdecrypt_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_SHARED, decrypt_fd, 0);
    if (file == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }

    for (int i = 0; i < fdecrypt_size; i++)
    {
        file[i] = file[i] ^ key[i % keysize];
    }
    
    if (munmap(file, fdecrypt_size) < 0)
    {
        perror("munmap");
        exit(1);
    }
    
    close(decrypt_fd);
    
    return 0;
}
