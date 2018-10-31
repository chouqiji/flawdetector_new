#include "component/utility.h"

namespace Component {

static double step = 0;

double getGlobalStep()
{
    return step;
}

void setGlobalStep(double newStep)
{
    step = newStep;
}

}
