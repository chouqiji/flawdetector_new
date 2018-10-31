#include "component/utility.h"

namespace Component {

static int cursorPos = 0;

int getCursorPos()
{
    return cursorPos;
}

void setCursorPos(int newPos)
{
    cursorPos = newPos;
}

}
