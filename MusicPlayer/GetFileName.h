//
// Created by wws on 17-7-19.
//

#ifndef FIRST_GETFILENAME_H
#define FIRST_GETFILENAME_H

#include <iostream>
#include <vector>
#include "MMFile.h"

class MMPlayer;

class GetFileName {

public:
    static void getFileName(std::vector<MMFile> &v, const char *d,class MMPlayer *player);
};


#endif //FIRST_GETFILENAME_H
