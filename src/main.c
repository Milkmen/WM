#include "TaskBar.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR(format, ...) fprintf(stderr, format, ##__VA_ARGS__)

Display* SetupDisplay();

Xstuff_t xstuff;

int main(void)
{
    xstuff.display = SetupDisplay();
    if(!xstuff.display) return -1;

    TaskBar_Create();

    XEvent event;
    while(1)
    {
        XNextEvent(xstuff.display, &event);

        if(event.type == ButtonPress)
        {
            if(event.xbutton.subwindow != None)
            {
                XRaiseWindow(xstuff.display, event.xbutton.subwindow);
            }
        }

        if(event.type == MapRequest)
        {
            TaskBar_AddWindow(event.xmaprequest.window);
        }
    }

    XCloseDisplay(xstuff.display);

    return 0;
}

int ErrorHandler(Display* display, XErrorEvent* error)
{
    switch (error->type)
    {
    case BadAccess:
        ERROR("X11 ERROR: BadAccess\n");
        break;
    
    default:
        ERROR("X11 ERROR: Unknown\n");
        break;
    }

    exit(-1);
}

Display* SetupDisplay()
{
    Display* display = XOpenDisplay(NULL);

    if(!display) 
    {
        ERROR("ERROR: Failed to open display\n");
        return 0;
    }

    XSetErrorHandler(ErrorHandler);

    Window root = DefaultRootWindow(display);

    XSelectInput(display, root, SubstructureRedirectMask | SubstructureNotifyMask);

    XGrabButton(display, 1, Mod1Mask, root, True,
        ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
        GrabModeAsync, GrabModeAsync, None, None);

    XSync(display, False);
    
    return display;
}