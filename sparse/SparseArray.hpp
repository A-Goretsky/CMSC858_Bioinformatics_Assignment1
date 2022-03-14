#include <cstdint>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sdsl/suffix_arrays.hpp>
#include <iostream>
#include <bit>
#include "../select/SelectSupport.cpp"

using std::string;
using namespace sdsl;

#ifndef SPARSE_ARRAY_
#define SPARSE_ARRAY_

class SparseArray {

    public:
        bool rank_updated = false;
        bit_vector *b;
        RankSupport *rs;
        std::vector<string> els;
        //SparseArray(RankSupport *input);
        SparseArray(bit_vector *input);
        SparseArray(uint64_t size);
        ~SparseArray();
        bool buildRank();
        void create(uint64_t size);
        void append(string elem, uint64_t pos);
        bool get_at_rank(uint64_t r, string& elem);
        bool get_at_index(uint64_t r, string& elem);
        uint64_t num_elem_at(uint64_t r);
        uint64_t size();
        uint64_t num_elem();
        void save(string& name);
        SparseArray* load(string& name);

};

#endif
