#include <cstdint>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sdsl/suffix_arrays.hpp>
#include <iostream>
#include <bit>
#include "../rank/RankSupport.cpp"

using std::string;
using namespace sdsl;

#ifndef SELECT_SUPPORT_
#define SELECT_SUPPORT_

class SelectSupport {

    public:
        RankSupport *r;
        SelectSupport(RankSupport *input);
        SelectSupport(bit_vector *input);
        ~SelectSupport();
        uint64_t select1(uint64_t i);
        uint64_t overhead();
        void save(string& name);
        SelectSupport* load(string& name);

};

#endif
