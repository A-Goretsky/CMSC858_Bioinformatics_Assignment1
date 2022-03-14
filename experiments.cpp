#include "sparse/SparseArray.cpp"
#include <chrono>

using namespace std::chrono;

int part1() {
    int sizes[] = {1000, 10000, 100000, 1000000};

    std::fstream p1_create;
    p1_create.open("./p1_create.csv", std::fstream::out);
    p1_create << "Iter,Time,Size\n";
    
    std::fstream p1_query;
    p1_query.open("./p1_query.csv", std::fstream::out);
    p1_query << "Iter,Time,Size\n";

    std::fstream p1_overhead;
    p1_overhead.open("./p1_overhead.csv", std::fstream::out);
    p1_overhead << "Iter,Overhead,Size\n";

    for (int x = 0; x < 10; x++) {

        std::cout << "Iter: " << x << std::endl;
        high_resolution_clock::time_point start;
        high_resolution_clock::time_point end;
        duration<double, std::milli> diff;

        //Creation
        for (int size = 0; size < 4; size++) {
            bit_vector *b = new bit_vector(sizes[size]);
            start = high_resolution_clock::now();
            RankSupport* sup = new RankSupport(b);
            end = high_resolution_clock::now();
            diff = end - start;
            p1_create << x << "," << diff.count() << ',' << sizes[size] << "\n";

            //Query
            start = high_resolution_clock::now();
            for (int op = 0; op < 10; op++) {
                sup->rank1(rand() % b->size());
            }
            end = high_resolution_clock::now();
            diff = end - start;
            p1_query << x << "," << diff.count() << ',' << sizes[size] << "\n";

            //Overhead
            p1_overhead << x << ',' << sup->overhead() << ',' << sizes[size] << "\n";
        }
    }
    p1_create.close();
    p1_query.close();
    p1_overhead.close();
    return 1;
}

int part2() {
    int sizes[] = {1000, 10000, 100000, 1000000};

    std::fstream p2_create;
    p2_create.open("./p2_create.csv", std::fstream::out);
    p2_create << "Iter,Time,Size\n";
    
    std::fstream p2_query;
    p2_query.open("./p2_query.csv", std::fstream::out);
    p2_query << "Iter,Time,Size\n";

    std::fstream p2_overhead;
    p2_overhead.open("./p2_overhead.csv", std::fstream::out);
    p2_overhead << "Iter,Overhead,Size\n";

    for (int x = 0; x < 10; x++) {

        std::cout << "Iter: " << x << std::endl;
        high_resolution_clock::time_point start;
        //std::cout << "before end";
        high_resolution_clock::time_point end;
        //std::cout << "before diff";
        duration<double, std::milli> diff;
        //std::cout << "before creation";
        //Creation
        for (int size = 0; size < 4; size++) {
            bit_vector *b = new bit_vector(sizes[size]);
            //std::cout << "about to create select";
            start = high_resolution_clock::now();
            SelectSupport* sup = new SelectSupport(b);
            end = high_resolution_clock::now();
            //std::cout << "created select";
            diff = end - start;
            p2_create << x << "," << diff.count() << ',' << sizes[size] << "\n";

            //Query
            start = high_resolution_clock::now();
            for (int op = 0; op < 10; op++) {
                sup->select1(rand() % b->size());
            }
            end = high_resolution_clock::now();
            diff = end - start;
            p2_query << x << "," << diff.count() << ',' << sizes[size] << "\n";

            //Overhead
            p2_overhead << x << ',' << sup->overhead() << ',' << sizes[size] << "\n";
        }
    }
    p2_create.close();
    p2_query.close();
    p2_overhead.close();

    return 1;
}

int part3() {
    int sizes[] = {1000, 10000, 100000, 1000000};
    double sparsity[] = {.01, .05, .1};

    std::fstream p3_getAtRank;
    p3_getAtRank.open("./p3_getAtRank.csv", std::fstream::out);
    p3_getAtRank << "Iter,Time,Size,Sparsity\n";
    
    std::fstream p3_getAtIndex;
    p3_getAtIndex.open("./p3_getAtIndex.csv", std::fstream::out);
    p3_getAtIndex << "Iter,Time,Size,Sparsity\n";

    std::fstream p3_numElAt;
    p3_numElAt.open("./p3_numElAt.csv", std::fstream::out);
    p3_numElAt << "Iter,Overhead,Size,Sparsity\n";

    for (int x = 0; x < 10; x++) {

        std::cout << "Iter: " << x << std::endl;
        high_resolution_clock::time_point start;
        high_resolution_clock::time_point end;
        duration<double, std::milli> diff;

        for (int sparseness = 0; sparseness < 3; sparseness++) {

            for (int size = 0; size < 4; size++) {

                SparseArray* cur = new SparseArray(sizes[size]);
                //Fill the array to the desired level of sparseness
                for (int el = 0; el < sparsity[sparseness] * sizes[size]; el++) {
                    bool appended = false;
                    while (!appended) {
                        try {
                            cur->append(std::to_string(el), rand() % sizes[size]);
                            appended = true;
                        }
                        catch (std::invalid_argument& e) {
                            appended = false;
                        }
                    }
                }

                //Build up rank separately to not include in operation timing
                cur->buildRank();

                //get_at_rank
                start = high_resolution_clock::now();
                for (int i = 0; i < 20; i++) {
                    string storage;
                    cur->get_at_rank(rand() % (int) (sparsity[sparseness] * sizes[size]), storage);
                }
                end = high_resolution_clock::now();
                diff = end - start;
                p3_getAtRank << x << "," << diff.count() << "," << sizes[size] << "," << sparsity[sparseness] << "\n";

                //get_at_index
                start = high_resolution_clock::now();
                for (int i = 0; i < 20; i++) {
                    string storage;
                    cur->get_at_index(rand() % sizes[size], storage);
                }
                end = high_resolution_clock::now();
                diff = end - start;
                p3_getAtIndex << x << "," << diff.count() << "," << sizes[size] << "," << sparsity[sparseness] << "\n";
            
                start = high_resolution_clock::now();
                for (int i = 0; i < 20; i++) {
                    string storage;
                    cur->num_elem_at(rand() % sizes[size]);
                }
                end = high_resolution_clock::now();
                diff = end - start;
                p3_numElAt << x << "," << diff.count() << "," << sizes[size] << "," << sparsity[sparseness] << "\n";
            }
        }
    }
    p3_getAtRank.close();
    p3_getAtIndex.close();
    p3_numElAt.close();

    return 1;
}

int main(int argc, char* argv[]) {
    part1();
    part2();
    part3();
}
