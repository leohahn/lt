#include "lt_fs.hpp"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined(__unix__)
#include <sys/stat.h>
#endif

FileContents *
file_read_contents(const char *filename)
{
    FILE *fp = fopen(filename, "rb"); // open in binary mode.
    void *file_data = NULL;

    // TODO(leo), @Robustness: Actually check if the file exists before trying to open it.
    if (!fp)
    {
        FileContents *ret = (FileContents*)malloc(sizeof(*ret));
        ret->error = FileError_NotExists;
        ret->data = NULL;
        ret->size = -1;
        return ret;
    }

    isize file_size = file_get_size(filename);

    if (file_size == -1)
    {
        fclose(fp);
        FileContents *ret = (FileContents*)malloc(sizeof(*ret));
        ret->error = FileError_Unknown;
        ret->data = NULL;
        ret->size = -1;
        return ret;
    }

    file_data = (char*)malloc(sizeof(char) * file_size);

    if (!file_data)
    {
        LT_Fail("Failed allocating memory\n");
    }

    isize newlen = fread(file_data, sizeof(u8), file_size, fp);
    if (newlen < 0)
    {
        FileContents *ret = (FileContents*)malloc(sizeof(*ret));
        ret->error = FileError_Read;
        ret->data = NULL;
        ret->size = -1;
        fclose(fp);
        LT_Free(file_data);
        return ret;
    }

    LT_Assert(newlen == file_size);

    if (ferror(fp) != 0)
    {
        fputs("Error reading file\n", stderr);
        fclose(fp);
        free(file_data);

        FileContents *ret = (FileContents*)malloc(sizeof(*ret));
        ret->error = FileError_Read;
        ret->data = NULL;
        ret->size = -1;
        return ret;
    }
    fclose(fp);

    FileContents *ret = (FileContents*)malloc(sizeof(*ret));
    ret->error = FileError_None;
    ret->data = file_data;
    ret->size = file_size;
    return ret;
}

void
file_free_contents(FileContents *fc)
{
    LT_Free(fc->data);
    LT_Free(fc);
}

isize
file_get_size(const char *filename)
{
#if defined(__unix__)
    struct stat st;
    if (stat(filename, &st) < 0) {
        return -1;
    } else {
        return st.st_size;
    }
#else
#  error "Still not implemented"
#endif
}
