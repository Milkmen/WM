#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR(format, ...) fprintf(stderr, format, ##__VA_ARGS__)

Display* SSetupDisplay();

XButtonEvent buttonEvent;

int main(void)
{
    Display* display = SSetupDisplay();
    if(!display) return -1;

    XEvent event;

    while(1)
    {
        XNextEvent(display, &event);

        if(event.type == ButtonPress)
        {
            if(event.xbutton.subwindow != None)
            {
                XRaiseWindow(display, event.xbutton.subwindow);
            }
        }
    }

    XCloseDisplay(display);

    return 0;
}

int SErrorHandler(Display* display, XErrorEvent* error)
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

Display* SSetupDisplay()
{
    Display* display = XOpenDisplay(NULL);

    if(!display) 
    {
        ERROR("ERROR: Failed to open display\n");
        return 0;
    }

    XSetErrorHandler(SErrorHandler);

    Window root = DefaultRootWindow(display);

    XSelectInput(display, root, SubstructureRedirectMask | SubstructureNotifyMask);

    XGrabButton(display, 1, Mod1Mask, root, True,
        ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
        GrabModeAsync, GrabModeAsync, None, None);

    XSync(display, False);
    
    return display;
}