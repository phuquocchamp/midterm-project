#include <stdio.h>
#include <dirent.h>   // directory
#include <sys/stat.h> // file info (size, permission,..)
#include <string.h>   //
#include "ls_utils.h"

void print_file_info(const char *path, struct dirent *entry, int long_format)
{
    if (long_format)
    {
        struct stat file_stat;
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        if (stat(fullpath, &file_stat) == 0)
        {
            printf("%10lld %s\n", (long long)file_stat.st_size, entry->d_name);
        }
        else
        {
            perror("stat");
        }
    }
    else
    {
        printf("%s\n", entry->d_name);
    }
}

int list_directory(const char *path, int show_hidden, int recursive, int long_format)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        return -1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (!show_hidden && entry->d_name[0] == '.')
        {
            continue; // Bỏ qua tệp ẩn nếu không có tùy chọn -a
        }
        print_file_info(path, entry, long_format);
    }

    closedir(dir);

    // Nếu có tùy chọn đệ quy (recursive)
    if (recursive)
    {
        dir = opendir(path);
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                printf("\n%s/%s:\n", path, entry->d_name);
                char subdir[1024];
                snprintf(subdir, sizeof(subdir), "%s/%s", path, entry->d_name);
                list_directory(subdir, show_hidden, recursive, long_format);
            }
        }
        closedir(dir);
    }

    return 0;
}
