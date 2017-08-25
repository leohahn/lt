#ifndef INCLUDE_LT_CORE_HPP
#define INCLUDE_LT_CORE_HPP

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Make type names more consistent and easier to write.
typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;

typedef int8_t      i8;
typedef int16_t     i16;
typedef int32_t     i32;
typedef int64_t     i64;
typedef i32         b32;

typedef float       f32;
typedef double      f64;

typedef size_t      usize;
typedef ptrdiff_t   isize;

static_assert(sizeof(u8) == 1, "u8 should have 1 byte");
static_assert(sizeof(u16) == 2, "u16 should have 2 bytes");
static_assert(sizeof(u32) == 4, "u16 should have 4 bytes");
static_assert(sizeof(u64) == 8, "u16 should have 8 bytes");

static_assert(sizeof(i8) == 1, "i8 should have 1 byte");
static_assert(sizeof(i16) == 2, "i16 should have 2 bytes");
static_assert(sizeof(i32) == 4, "i16 should have 4 bytes");
static_assert(sizeof(i64) == 8, "i16 should have 8 bytes");
static_assert(sizeof(b32) == 4, "b32 should have 4 bytes");

static_assert(sizeof(f32) == 4, "f32 should have 4 byte");
static_assert(sizeof(f64) == 8, "f64 should have 8 bytes");

/////////////////////////////////////////////////////////
//
// General Macros and Functions
//
// Macros that make working with c either better or more consistent.
//

#ifndef global_variable
#define global_variable static  // Global variables
#endif
#ifndef internal
#define internal        static  // Internal linkage
#endif
#ifndef local_persist
#define local_persist   static  // Local persisting variables
#endif

#ifndef LT_Unused
#define LT_Unused(x) ((void)(x))
#endif

#ifndef LT_Count
#define LT_Count(arr) (sizeof((arr))/sizeof((arr)[0]))
#endif

#ifndef LT_Abs
#define LT_Abs(x) (((x) < 0) ? -(x) : (x))
#endif

#ifndef lt_in_open_interval
#define lt_in_open_interval(x, min, max)  ((min) < (x) && (x) < (max))
#endif

#ifndef lt_in_closed_interval
#define lt_in_closed_interval(x, min, max)  ((min) <= (x) && (x) <= (max))
#endif

#ifndef LT_Free
#define LT_Free(p) do { \
        free(p);        \
        p = NULL;       \
    } while(0)
#endif

#ifndef LT_Fail
#  ifdef LT_DEBUG
#    define LT_Fail(...) do {                                        \
        fprintf(stderr, "****** RUNTIME FAILURE ******\n");          \
        fprintf(stderr, "%s(line %d)", __FILE__, __LINE__);          \
        fprintf(stderr, __VA_ARGS__);                                \
        fprintf(stderr, "*****************************\n");          \
        fflush(stderr);                                              \
        __builtin_trap();                                            \
    } while(0)
#  else
#    define LT_Fail(...)
#  endif // LT_DEBUG
#endif // LT_Fail

#ifndef LT_Assert
#  ifdef LT_DEBUG
#    define LT_Assert2(cond, file, number) do {                         \
        if (!(cond)) {                                                  \
            fprintf(stderr, "******************************\n");        \
            fprintf(stderr, "*********** ASSERT ***********\n");        \
            fprintf(stderr, "**                            \n");        \
            fprintf(stderr, "**  Condition: %s\n", #cond);              \
            fprintf(stderr, "**  %s (line %d)\n", file, number);        \
            fprintf(stderr, "**                            \n");        \
            fprintf(stderr, "******************************\n");        \
            fprintf(stderr, "******************************\n");        \
            fflush(stderr);                                             \
            __builtin_trap();                                           \
        }                                                               \
    } while(0)
#    define LT_Assert(cond) LT_Assert2(cond, __FILE__, __LINE__)
#  else
#    define LT_Assert(cond)
#  endif // LT_DEBUG
#endif // LT_Assert

internal inline bool
lt_is_little_endian()
{
    i32 num = 1;
    return (*(char*)&num == 1);
}

void get_display_dpi(i32 *x, i32 *y);

#endif // INCLUDE_LT_H


/* =========================================================================
 *
 *
 *
 *
 *
 *
 *  Implementation
 *
 *
 *
 *
 *
 *
 * ========================================================================= */

#if defined(LT_IMPLEMENTATION) && !defined(LT_IMPLEMENTATION_DONE)
#define LT_IMPLEMENTATION_DONE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(__unix__)
#include <sys/stat.h>
#include <X11/extensions/Xrandr.h>
#endif

///////////////////////////////////////////////////////
//
// Utils
//

void
lt_get_display_dpi(i32 *x, i32 *y)
{
#ifdef __unix__
    i32 scr = 0; /* Screen number */

    if ((NULL == x) || (NULL == y)) { return; }

    char *displayname = NULL;
    Display *dpy = XOpenDisplay(displayname);

    /*
     * there are 2.54 centimeters to an inch; so there are 25.4 millimeters.
     *
     *     dpi = N pixels / (M millimeters / (25.4 millimeters / 1 inch))
     *         = N pixels / (M inch / 25.4)
     *         = N * 25.4 pixels / M inch
     */
    f64 xres = ((((f64) DisplayWidth(dpy,scr)) * 25.4) /
                ((f64) DisplayWidthMM(dpy,scr)));
    f64 yres = ((((f64) DisplayHeight(dpy,scr)) * 25.4) /
                ((f64) DisplayHeightMM(dpy,scr)));

    *x = (i32)(xres + 0.5);
    *y = (i32)(yres + 0.5);

    XCloseDisplay (dpy);
#else
    _Static_assert(false, "Not Implemented");
#endif
}

#endif // LT_IMPLEMENTATION
