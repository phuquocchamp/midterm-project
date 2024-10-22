#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ls_utils.h"

int main(int argc, char *argv[])
{
    int show_hidden = 0;
    int recursive = 0;
    int long_format = 0;
    char *path = "."; // Mặc định là thư mục hiện tại

    // Xử lý các tùy chọn dòng lệnh
    int opt;
    while ((opt = getopt(argc, argv, "alR")) != -1)
    {
        switch (opt)
        {
        case 'a':
            show_hidden = 1;
            break;
        case 'l':
            long_format = 1;
            break;
        case 'R':
            recursive = 1;
            break;
        default:
            fprintf(stderr, "Usage: %s [-a] [-l] [-R] [path]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Nếu có đường dẫn thư mục
    if (optind < argc)
    {
        path = argv[optind];
    }

    if (list_directory(path, show_hidden, recursive, long_format) != 0)
    {
        fprintf(stderr, "Failed to list directory: %s\n", path);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
