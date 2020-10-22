#include "key.hpp"

namespace sh {

Key::Key(int a_type)
: m_type(a_type)
{
}

Key::~Key(){
}

int Key::Type() const {
    return m_type;
}

}//sh