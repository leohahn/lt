#ifndef LT_DISPLAY_HPP
#define LT_DISPLAY_HPP

#include "lt_core.hpp"
#if defined(__unix__)
#include <sys/stat.h>
#include <X11/extensions/Xrandr.h>
#endif

namespace lt
{
void lt_get_display_dpi(i32 *x, i32 *y);
}

#endif
/* ============================================================
 *
 *
 *
 *
 *
 *                 Implementation
 *
 *
 *
 *
 *
 * =========================================================== */
#if defined(LT_DISPLAY_IMPL) && !defined(LT_DISPLAY_IMPL_DONE)
#define LT_DISPLAY_IMPL_DONE

void
lt::lt_get_display_dpi(i32 *x, i32 *y)
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

#endif // LT_DISPLAY_IMPL
