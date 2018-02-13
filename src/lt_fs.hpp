#ifndef LT_FS_HPP
#define LT_FS_HPP

#include <string>
#include "lt_core.hpp"

enum FileError
{
    FileError_None,

    FileError_Read,
    FileError_Seek,
    FileError_NotExists,
    FileError_Unknown,

    FileError_Count,
};

struct FileContents
{
    void     *data;
    isize     size;
    FileError error;
};

FileContents *file_read_contents(const char *filename);
void          file_free_contents(FileContents *fc);
isize         file_get_size(const char *filename);

namespace ltfs
{

std::string absolute_path(const char *relative_path, bool *error = nullptr);
bool        file_exists(const std::string &path);
std::string join(const std::string &p1, const std::string &p2);

}

#endif
