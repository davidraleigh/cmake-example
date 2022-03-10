#include <iostream>
#include <string>
#include <thread>
#include <memory>
#include <random>
#include "cpp_maps.h"

int main(int argc, char *argv[]) {
    int length = 8;
    int test_val = 16;

    int seed = 1999;
    if (argc > 1) {
        seed = atoi(argv[1]);
    }
    std::mt19937_64 prng;
    prng.seed(seed);
    std::cout << "seed = " << seed << std::endl;

    int loop_count = 6;
    if (argc > 2) {
        loop_count = atoi(argv[2]);
    }
    std::cout << "loop_count = " << loop_count << std::endl;

    std::uniform_int_distribution<> indices{ 0, length };
    rle_int_map actual(length + 1, test_val);

    for (int count{ 1 }; count <= loop_count; ++count)
    {
        if (actual.run_count() == 1) {
            test_val += 32;
        }
        int index = indices(prng);
        int value = test_val;

        std::cout << "setting value " << value << " at index " << index << std::endl;
        actual.set(index, value);

        std::cout << "values: ";
        for (int i = 0; i < actual.size(); i++) {
            std::cout << " " << actual.get(i);
        }
        std::cout << std::endl;

        std::cout << "run count: " << actual.run_count() << std::endl << std::endl;
    }

    return 0;
}
