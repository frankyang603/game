#ifndef PLATFORM_H
#define PLATFORM_H

#include "fplat.h"

class platform : public fplat
{
public:
    platform();
    virtual void create(int x,int y);
};

#endif // PLATFORM_H
