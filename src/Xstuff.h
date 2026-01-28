#ifndef XSTUFF_H
#define XSTUFF_H

#include <X11/Xlib.h>

typedef struct
{
    Display* display;
    Window root;
}   
Xstuff_t;

extern Xstuff_t xstuff;

#endif // XSTUFF_H