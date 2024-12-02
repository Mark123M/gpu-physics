#ifndef _COLLIDER_
#define _COLLIDER_

#include <string>

class Collider {
public:
    virtual void draw();
    virtual std::string stringify();
};

#endif