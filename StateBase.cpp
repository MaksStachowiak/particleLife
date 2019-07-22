#include "StateBase.h"

#include "Application.h"

namespace State
{
    StateBase::StateBase(Application& app)
    :   m_p_application (&app)
    {

    }
}