#include "SparseArray.hpp"

SparseArray::SparseArray(uint64_t size) {
    create(size);
}

SparseArray::SparseArray(bit_vector *input) {
    b = input;
}

void SparseArray::create(uint64_t size) {
    b = new bit_vector(size);
}

bool SparseArray::buildRank() {
    rs = new RankSupport(b);
    rank_updated = true;
    return rank_updated;
}

void SparseArray::append(string elem, uint64_t pos) {
    if (pos < b->size() && (*b)[pos] != 1) {
        (*b)[pos] = 1;
        els.push_back(elem);
    }
    else {
        throw std::invalid_argument("Pos didn't match appropriate params");
    }
    rank_updated = false;
}

bool SparseArray::get_at_rank(uint64_t r, string& elem) {
    if (r < els.size()) {
        elem = els[r];
        return true;
    }
    return false;
}

bool SparseArray::get_at_index(uint64_t r, string& elem) {
    if (r < b->size() && (*b)[r] == 1) {
        if (!rank_updated) {
            rs = new RankSupport(b);
            rank_updated = true;
        }
        //std::cout << "r: " << r << std::endl;
        //std::cout << "bsize: " << b->size() << std::endl;
        uint64_t rank = rs->rank1(r);
        //std::cout << "rank: " << rank << std::endl;
        elem = els[rs->rank1(r)-1];
        return true;
    }
    return false;
}

uint64_t SparseArray::num_elem_at(uint64_t r) {
    if (!rank_updated) {
        rs = new RankSupport(b);
        rank_updated = true;
    }
    return rs->rank1(r);
}

uint64_t SparseArray::size() {
    return b->size();
}

uint64_t SparseArray::num_elem() {
    return els.size();
}

void SparseArray::save(string& name) {
    rs->save(name);
}

SparseArray* SparseArray::load(string& name) {
    rs->load(name);
    SparseArray *output = new SparseArray(rs->bit_vec);
    output->rs = rs;
    output->rank_updated = true;
    return output;
}

/*
int main(int argc, char *argv[]) {
    SparseArray *mine = new SparseArray(10);
    mine->append("foo", 1);
    mine->append("bar", 5);
    mine->append("baz", 9);
    auto x = mine->b->begin();
    while (x < mine->b->end()) {
        std::cout << *x;
        x++;
    }
    std::cout << std::endl;
    auto y = mine->els.begin();
    while (y < mine->els.end()) {
        std::cout << *y << " ";
        y++;
    }
    std::cout << std::endl;
    string e;
    std::cout << mine->get_at_rank(1, e) << " " << e << std::endl;
    std::cout << mine->get_at_index(3, e) << " " << e << std::endl;  
    std::cout << mine->get_at_index(5, e) << " " << e << std::endl; 
}
*/
