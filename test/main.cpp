//
// Created by David Raleigh on 3/6/22.
//

#include <string>

#include <thread>

#include "cpp_maps.h"
#include "gtest/gtest.h"
#include <cstdlib>
#include <memory>
#include <random>

namespace {
    class CppMapTest : public ::testing::Test {
    protected:
        CppMapTest() {

        }

        void test_run_size(rle_int_map m, const std::string& s) {
            std::vector<int> vals;
            vals.push_back(m.get(0));
            for (int i = 1; i < m.size(); i++) {
                if (vals.back() != m.get(i)) {
                    vals.push_back(m.get(i));
                }
            }
            EXPECT_EQ(m.run_count(), vals.size()) << s;
        }

        virtual ~CppMapTest() {
        }
    };

    TEST_F(CppMapTest, TEST_INT_MAP){
        int_map m(30, 4);

        EXPECT_EQ(4, m.get(0));
        EXPECT_EQ(4, m.get(29));

        m.set(0, 5);
        EXPECT_EQ(5, m.get(0));
        EXPECT_EQ(4, m.get(1));
        EXPECT_EQ(4, m.get(29));
    }

    TEST_F(CppMapTest, TEST_RLE_INT_MAP_INDEX_0){
        rle_int_map m(30, 4);

        for (int i = 0; i < 30; i++) {
            EXPECT_EQ(4, m.get(i));
        }
        test_run_size(m, "1 run");

        m.set(0, 5);
        for (int i = 0; i < 30; i++) {
            if (i == 0) {
                EXPECT_EQ(5, m.get(i));
            } else {
                EXPECT_EQ(4, m.get(i));
            }
        }
        test_run_size(m, "2 runs");

        m.set(0, 6);
        for (int i = 0; i < 30; i++) {
            if (i == 0) {
                EXPECT_EQ(6, m.get(i));
            } else {
                EXPECT_EQ(4, m.get(i));
            }
        }
        test_run_size(m, "2 runs");
    }

    TEST_F(CppMapTest, TEST_RLE_INT_MAP_INDEX_1){
        rle_int_map m(30, 4);

        m.set(1, 5);
        for (int i = 0; i < 30; i++) {
            if (i == 1) {
                EXPECT_EQ(5, m.get(i));
            } else {
                EXPECT_EQ(4, m.get(i));
            }
        }
        test_run_size(m, "3 runs");

        m.set(1, 6);
        for (int i = 0; i < 30; i++) {
            if (i == 1) {
                EXPECT_EQ(6, m.get(i));
            } else {
                EXPECT_EQ(4, m.get(i));
            }
        }
        test_run_size(m, "3 runs");
    }

    TEST_F(CppMapTest, TEST_RLE_INT_MAP_INDEX_LAST){
        rle_int_map m(30, 4);

        m.set(29, 5);
        for (int i = 0; i < 30; i++) {
            if (i == 29) {
                EXPECT_EQ(5, m.get(i)) << i;
            } else {
                EXPECT_EQ(4, m.get(i)) << i;
            }
        }
        test_run_size(m, "2 runs");

        m.set(29, 6);
        for (int i = 0; i < 30; i++) {
            if (i == 29) {
                EXPECT_EQ(6, m.get(i));
            } else {
                EXPECT_EQ(4, m.get(i));
            }
        }
        test_run_size(m, "2 runs");
    }

    TEST_F(CppMapTest, TEST_RLE_INT_MAP_RECOVER_MEM){
        rle_int_map m(3, 4);

        m.set(1, 5);
        for (int i = 0; i < 3; i++) {
            if (i == 1) {
                EXPECT_EQ(5, m.get(i));
            } else {
                EXPECT_EQ(4, m.get(i));
            }
        }
        test_run_size(m, "3 runs");

        m.set(1, 4);
        for (int i = 0; i < 3; i++) {
            if (i == 1) {
                EXPECT_EQ(4, m.get(i));
            } else {
                EXPECT_EQ(4, m.get(i));
            }
        }
        test_run_size(m, "1 run");

        m.set(0, 5);
        EXPECT_EQ(5, m.get(0));
        test_run_size(m, "2 runs");

        m.set(0, 4);
        EXPECT_EQ(4, m.get(0));
        test_run_size(m, "1 run");

        m.set(2, 5);
        EXPECT_EQ(5, m.get(2));
        test_run_size(m, "2 runs");

        m.set(2, 4);
        EXPECT_EQ(4, m.get(2));
        test_run_size(m, "1 runs");
    }

    TEST_F(CppMapTest, TEST_RLE_INT_MAP_COMPLEX) {
        rle_int_map m(8, 4);
        m.set(0, 5);
        EXPECT_EQ(5, m.get(0));
        // 2
        test_run_size(m, "2 runs");


        EXPECT_EQ(4, m.get(1));
        m.set(1, 5);
        EXPECT_EQ(5, m.get(1));
        // 2
        test_run_size(m, "2 runs");

        EXPECT_EQ(4, m.get(3));
        m.set(3, 5);
        EXPECT_EQ(5, m.get(3));
        // 4
        test_run_size(m, "4 runs");

        EXPECT_EQ(4, m.get(5));
        m.set(5, 5);
        EXPECT_EQ(5, m.get(5));
        // 5
        test_run_size(m, "6 runs");

        EXPECT_EQ(4, m.get(7));
        m.set(7, 5);
        EXPECT_EQ(5, m.get(7));
        // 6
        test_run_size(m, "8 runs");

        EXPECT_EQ(4, m.get(6));
        m.set(6, 5);
        EXPECT_EQ(5, m.get(6));
        // 4
        test_run_size(m, "6 runs");

        EXPECT_EQ(4, m.get(4));
        m.set(4, 5);
        EXPECT_EQ(5, m.get(4));
        // 3
        test_run_size(m, "4 runs");

        EXPECT_EQ(4, m.get(2));
        m.set(2, 5);
        EXPECT_EQ(5, m.get(2));
        // 1
        test_run_size(m, "2 rruns");
    }

    TEST_F(CppMapTest, TEST_RLE_INT_MAP_RANDOM) {
        int seed = 1999;
        std::mt19937 mt(seed);
        int max_length = 12;
        int test_val = max_length + 4;

        for (int length {1}; length < max_length; ++length)
        {
            std::uniform_int_distribution<> indices{ 0, length };
            rle_int_map actual(length + 1, test_val);
            int_map expected(length + 1, test_val);

            for (int count{ 1 }; count <= 400; ++count)
            {
                if (actual.run_count() == 1) {
                    test_val += 2;
                }
                int index = indices(mt);
                int value = test_val;
                if (count % 2 != 0 && count % 3 != 0 && count != 1)
                    value = test_val - 1;

                actual.set(index, value);
                expected.set(index, value);

                for (int test_index { 1 }; test_index <= length; test_index++) {
                    EXPECT_EQ(expected.get(test_index), actual.get(test_index));
                }

                std::string message = "seed: " + std::to_string(seed) + ", iteration: " + std::to_string(count);
                test_run_size(actual, message);
            }
        }
    }
}