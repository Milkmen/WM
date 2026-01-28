#include "TaskBar.h"
#include <string.h>

#define TASKBAR_HEIGHT 32
#define TASK_BUTTON_WIDTH 128

typedef struct 
{
    Window window;
    TaskButton_t buttons[TASK_BAR_MAX_BUTTONS];
    int buttonCount;
}
TaskBar_t;

TaskBar_t taskBar;

static void TaskBar_Draw();

void TaskBar_Create()
{
    int screen = DefaultScreen(xstuff.display);
    Window root = DefaultRootWindow(xstuff.display);
    int screenWidth = DisplayWidth(xstuff.display, screen);
    int screenHeight = DisplayHeight(xstuff.display, screen);

    taskBar.window = XCreateSimpleWindow(
        xstuff.display, root,
        0, screenHeight - TASKBAR_HEIGHT,
        screenWidth, TASKBAR_HEIGHT,
        0, BlackPixel(xstuff.display, screen), 
        WhitePixel(xstuff.display, screen)
    );

    XSelectInput(xstuff.display, taskBar.window, ExposureMask | ButtonPressMask);
    XMapWindow(xstuff.display, taskBar.window);
    TaskBar_Draw();
}

void TaskBar_AddWindow(Window newWindow)
{
    if(taskBar.buttonCount >= TASK_BAR_MAX_BUTTONS) return;

    if(!XFetchName(xstuff.display, newWindow, &taskBar.buttons[taskBar.buttonCount].title))
    {
        taskBar.buttons[taskBar.buttonCount].title = "No name";
    }

    taskBar.buttons[taskBar.buttonCount].window = newWindow;
    
    taskBar.buttonCount++;

    TaskBar_Draw();
}

static void TaskBar_Draw()
{
    XClearWindow(xstuff.display, taskBar.window);

    GC gc = XCreateGC(xstuff.display, taskBar.window, 0, 0);

    for(int i = 0; i < taskBar.buttonCount; ++i)
    {
        int x = 160 + i * TASK_BUTTON_WIDTH;

        XSetForeground(xstuff.display, gc, 0xCCCCCC);
        XFillRectangle(xstuff.display, taskBar.window, gc, x, 0, TASK_BUTTON_WIDTH, TASKBAR_HEIGHT);

        XSetForeground(xstuff.display, gc, 0x000000);
        XDrawRectangle(xstuff.display, taskBar.window, gc, x, 0, TASK_BUTTON_WIDTH, TASKBAR_HEIGHT);

        XDrawString(xstuff.display, taskBar.window, gc, x + 5, TASKBAR_HEIGHT / 2, taskBar.buttons[i].title, strlen(taskBar.buttons[i].title));
    }

    XFreeGC(xstuff.display, gc);
}

void TaskBar_RemoveWindow(Window oldWindow)
{
    int index = -1;
    for(int i = 0; i < taskBar.buttonCount; ++i)
    {
        if(taskBar.buttons[i].window = oldWindow)
        {
            index = i;
            break;
        }
    }

    if(index < 0) return;

    for(int i = index; i < taskBar.buttonCount - 1; ++i)
    {
        taskBar.buttons[i] = taskBar.buttons[i + 1];
    }

    TaskBar_Draw();
}