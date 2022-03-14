#include "SelectSupport.hpp"

using namespace sdsl;

SelectSupport::SelectSupport(RankSupport *input) {
    r = input;
}

SelectSupport::SelectSupport(bit_vector *input) {
    r = new RankSupport(input);
}

SelectSupport::~SelectSupport() {}

uint64_t SelectSupport::select1(uint64_t i) {
    int left = 0;
    int right = r->bit_vec->size()-1;

    //basically just binary search within another context
    while (left <= right) {
        int index = left + (right - left) / 2;
        int rank = r->rank1(index);
        if (rank == i) {
            return index;
        }
        else if (i >= rank) {
            left = index + 1;
            //right = index + 1;
        }
        else {
            right = index - 1;
            //left = index + 1;
        }
    }
    return -1;
}

uint64_t SelectSupport::overhead() {
    return r->overhead();
}
void SelectSupport::save(string& name) {
    r->save(name);
}
SelectSupport* SelectSupport::load(string& name) {
    r->load(name);
    return this;
}
/*
int main (int argc, char* argv[]) {
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
    std::cout << "\nMaking Provided Select Structure\n";
    select_support_mcl<1,1> *provided = new select_support_mcl<1,1>(&test_vec);
    std::cout << provided->select(2) << std::endl;
    std::cout << provided->select(5) << std::endl;
    std::cout << "\nMaking My Select Structure\n";
    SelectSupport *mine = new SelectSupport(&test_vec);
    std::cout << mine->select1(2) << std::endl;
    std::cout << mine->select1(5) << std::endl;
    std::cout << mine->overhead() << std::endl;
    std::string temp_file ("test_file");
    mine->save(temp_file);
    std::cout << mine->overhead() << std::endl;
}
*/
