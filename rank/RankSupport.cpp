//Task 1 -- bit-vector rank
//Anton Goretsky
//Bioinformatics 858

#include "RankSupport.hpp"
using namespace sdsl;

RankSupport::RankSupport(bit_vector *input) {
    
    bit_vec = input;
    bv_size = bit_vec->size();

    //Length each block stretches of the bit vector
    rb_length = ceil(log2(bv_size));
    rs_length = pow(rb_length, 2);

    //Bits per cell (padded by 1)
    rs_bits = (int) ceil(log2(rs_length)) + 1;
    rb_bits = (int) ceil(log2(rb_length)) + 1;

    //Size here means number of "cells"
    //1.0 to prevent truncation too early
    rs_size = (int) ceil(bv_size * 1.0 / rs_length);
    rb_size = (int) ceil(bv_size * 1.0 / rb_length);

    //std::cout << "Superblock # of cells: " << rs_size << std::endl;
    //std::cout << "Block # of cells: " << rb_size << std::endl;
    //std::cout << "Superblock bits per cell: " << rs_bits << std::endl;
    //std::cout << "Block # bits per cell " << rb_bits << std::endl;
    //std::cout << "Superblock length: " << rs_length << std::endl;
    //std::cout << "Block length: " << rb_length << std::endl;

    //Initialize superblock and block int vector
    r_super = new int_vector<>(rs_size, 0, rs_bits);
    r_block = new int_vector<>(rb_size, 0, rb_bits);

    //std::cout << r_super->bit_size() + r_block->bit_size() << std::endl;
    

    //Populate r_super and r_block
    auto x = input->begin();
    int ctr = 0;
    int prev_super_ind = 0;
    int prev_block_ind = 0;
    while (x < input->end()) {

        int cur_r_super_ind = ctr / rs_length;
        int cur_r_block_ind = ctr / rb_length;
        //std::cout << ctr << ", " << cur_r_super_ind << ", " << cur_r_block_ind << std::endl;
        //std::cout << cur_r_super_ind << std::endl;
        //std::cout << cur_r_block_ind << std::endl;   
        //If a 1
        if (*x) {
            if (cur_r_super_ind != r_super->size()-1)
                (*r_super)[cur_r_super_ind+1]++;
            if (cur_r_block_ind != r_block->size()-1)   
                (*r_block)[cur_r_block_ind+1]++;
        }

        if (cur_r_block_ind != prev_block_ind) {
            //std::cout << "in here";
            (*r_block)[cur_r_block_ind] += (*r_block)[prev_block_ind];
        }
            
        if (cur_r_super_ind != prev_super_ind || ctr == 0) {
            (*r_super)[cur_r_super_ind] += (*r_super)[prev_super_ind];
            (*r_block)[cur_r_block_ind] = 0;
        }

        prev_super_ind = cur_r_super_ind;
        prev_block_ind = cur_r_block_ind;

        ctr++;
        x++;
    }

    //std::cout << r_super->bit_size() + r_block->bit_size() << std::endl;

    /*auto y = r_super->begin();
    while (y < r_super->end()) {
        std::cout << *y;
        y++;
    }
    std::cout << std::endl;
    y = r_block->begin();
    while (y < r_block->end()) {
        std::cout << *y;
        y++;
    }
    std::cout << std::endl; 
    */
}

RankSupport::RankSupport(bit_vector *input, int_vector<>* rs, int_vector<>* rb) {
    bit_vec = input;
    bv_size = bit_vec->size();

    //Length each block stretches of the bit vector
    rb_length = ceil(log2(bv_size));
    rs_length = pow(rb_length, 2);

    //Bits per cell (padded by 1)
    rs_bits = (int) ceil(log2(rs_length)) + 1;
    rb_bits = (int) ceil(log2(rb_length)) + 1;

    //Size here means number of "cells"
    rs_size = (int) ceil(bv_size / rs_length);
    rb_size = (int) ceil(bv_size / rb_length);

    //Initialize superblock and block int vector
    r_super = new int_vector<>(rs_size, 0, rs_bits);
    r_block = new int_vector<>(rb_size, 0, rb_bits);

    //Populate r_super and r_block
    auto x = input->begin();
    int ctr = 0;
    int prev_super_ind = 0;
    int prev_block_ind = 0;
    while (x < input->end()) {

        int cur_r_super_ind = ctr / rs_length;
        int cur_r_block_ind = ctr / rb_length;
        //std::cout << ctr << ", " << cur_r_super_ind << ", " << cur_r_block_ind << std::endl;
        //std::cout << cur_r_super_ind << std::endl;
        //std::cout << cur_r_block_ind << std::endl;   
        //If a 1
        if (*x) {
            if (cur_r_super_ind != r_super->size()-1)
                (*r_super)[cur_r_super_ind+1]++;
            if (cur_r_block_ind != r_block->size()-1)   
                (*r_block)[cur_r_block_ind+1]++;
        }

        if (cur_r_block_ind != prev_block_ind) {
            //std::cout << "in here";
            (*r_block)[cur_r_block_ind] += (*r_block)[prev_block_ind];
        }
            
        if (cur_r_super_ind != prev_super_ind || ctr == 0) {
            (*r_super)[cur_r_super_ind] += (*r_super)[prev_super_ind];
            (*r_block)[cur_r_block_ind] = 0;
        }

        prev_super_ind = cur_r_super_ind;
        prev_block_ind = cur_r_block_ind;

        ctr++;
        x++;
    }    
}

uint64_t RankSupport::rank1(uint64_t i) {

    uint64_t output = (*r_super)[i / rs_length] + (*r_block)[i / rb_length];
    //popcount couts the number of bits in the input machine word / number
    output += __builtin_popcount(bit_vec->get_int(i - (i % rb_length), i % rb_length + 1));

    return output;
}

uint64_t RankSupport::overhead() {
    uint64_t output = r_super->bit_size() + r_block->bit_size();
    //u_int64_t output = (rs_bits * rs_size) + (rb_bits * rb_size);
    return output;
}

void RankSupport::save(string& name) {
    std::fstream file;
    file.open(name);
    bit_vec->serialize(file);
    r_super->serialize(file);
    r_block->serialize(file);
    file.close();
}

RankSupport* RankSupport::load(string& name) {
    std::fstream file;
    file.open(name);
    bit_vector new_bit_vec;
    new_bit_vec.load(file);

    int_vector<> new_r_super;
    new_r_super.load(file);

    int_vector<> new_r_block;
    new_r_block.load(file);

    RankSupport* loaded = new RankSupport(bit_vec, &new_r_super, &new_r_block);
    file.close();
    return loaded;
}

RankSupport::~RankSupport() {}

/*
int main(int argc, char *argv[]) {
    std::cout << "Building Test Bit Vector\n";
    bit_vector test_vec = bit_vector(16, 0);
    test_vec[0] = 1;
    test_vec[3] = 1;
    test_vec[5] = 1;
    test_vec[6] = 1;
    test_vec[7] = 1;
    test_vec[9] = 1;
    test_vec[12] = 1;
    test_vec[14] = 1;
    auto x = test_vec.begin();
    while (x < test_vec.end()) {
        std::cout << *x;
        x++;
    }
    std::cout << "\nMaking Provided Rank Structure\n";
    rank_support_v<1,1> *provided = new rank_support_v<1, 1>(&test_vec);
    std::cout << provided->rank(4) << std::endl;
    std::cout << provided->rank(8) << std::endl;
    std::cout << "\nMaking My Rank Structure\n";
    RankSupport *mine = new RankSupport(&test_vec);
    std::cout << mine->rank1(4) << std::endl;
    std::cout << mine->rank1(8) << std::endl;
    std::cout << mine->overhead() << std::endl;
    std::string temp_file ("test_file");
    mine->save(temp_file);
    std::cout << mine->overhead() << std::endl;
    RankSupport *loaded = mine->load(temp_file);
    std::cout << loaded->rank1(4) << std::endl;
    std::cout << loaded->rank1(8) << std::endl;
    std::cout << mine->overhead() << std::endl;
    std::cout << loaded->overhead() << std::endl;
}
*/
