#ifndef _FILE_H_
#define _FILE_H_

#include <efi.h>

#define MAX_FILENAME_LEN 4
#define MAX_FILE_NUM     32
#define MAX_FILE_BUF     1024

struct File {
    CHAR16 name[MAX_FILENAME_LEN];
};

struct Filelist {
    UINTN file_count;
    struct File files[MAX_FILE_NUM];
};

extern struct Filelist filelist;

#endif
