#ifndef TASKBAR_H
#define TASKBAR_H

#include "Xstuff.h"

#define TASK_BAR_MAX_BUTTONS 32

typedef struct
{
    Window window;
    char* title;
}
TaskButton_t;

void TaskBar_Create();
void TaskBar_AddWindow(Window newWindow);

#endif // TASKBAR_H