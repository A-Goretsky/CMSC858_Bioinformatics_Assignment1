#include <cstdint>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sdsl/suffix_arrays.hpp>
#include <iostream>
#include <bit>

using std::string;
using namespace sdsl;

#pragma once

#ifndef RANK_SUPPORT_
#define RANK_SUPPORT_

class RankSupport {

    public:
        int bv_size;
        int rs_size;
        int rb_size;
        int rb_length;
        int rs_length;
        int rs_bits;
        int rb_bits;
        bit_vector *bit_vec;
        int_vector<> *r_super;
        int_vector<> *r_block;
        RankSupport(bit_vector *input);
        RankSupport(bit_vector *input, int_vector<>* rs, int_vector<>* rb);
        ~RankSupport();
        uint64_t rank1(uint64_t i);
        uint64_t overhead();
        void save(string& name);
        RankSupport* load(string& name);

};

#endif
