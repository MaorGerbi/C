#ifndef SMART_HOME_KEY_HPP
#define SMART_HOME_KEY_HPP

#include <string>
#include <iostream>

namespace sh {

class Key {
public:
    Key(int a_type);
    virtual ~Key();

    //bool virtual operator<(const Key& a_other) const = 0;
    int Type() const;

private:
    int m_type;
};

} //sh

#endif //SMART_HOME_KEY_HPP

