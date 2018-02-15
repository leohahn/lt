#include "lt_fs.hpp"

#include <cstdio>
#include <cstring>
#include <cstdlib>

#if LT_PLATFORM_UNIX
#include <sys/stat.h>
#endif

#if LT_OS_LINUX
#include <climits>
#endif

std::string
ltfs::absolute_path(const std::string &relative_path, bool *error)
{
#if LT_OS_LINUX
    char *buf = realpath(relative_path.c_str(), nullptr);
    if (!buf)
    {
        if (error) *error = true;
        return relative_path;
    }

    std::string abs_path(buf);
    free(buf);
    if (error) *error = false;
    return abs_path;
#else
#error "Not yet defined on other operating systems"
#endif
}

bool
ltfs::file_exists(const std::string &path)
{
#if LT_PLATFORM_UNIX
    struct stat buf;
    return (stat(path.c_str(), &buf) == 0);
#else
#error "Currently only implemented on UNIX systems."
#endif
}

std::string
ltfs::join(const std::string &p1, const std::string &p2)
{
#if LT_PLATFORM_UNIX
    std::string res(p1);

    if (res[res.size()-1] != '/') res += '/';
    if (p2[0] == '/') res.append(p2, 1, std::string::npos);
    else res.append(p2);

    return res;
#else
#error "Currently only implemented on UNIX systems."
#endif
}

FileContents *
file_read_contents(const char *filename)
{
    FILE *fp = fopen(filename, "rb"); // open in binary mode.
    void *file_data = NULL;

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
