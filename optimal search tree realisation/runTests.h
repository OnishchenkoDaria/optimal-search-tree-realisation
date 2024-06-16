#pragma once
#include <iostream>
#include "runTests.h"
#include "OptimalBST.h"
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;

/// @file runTests.h
/// @brief Defines the runTests class for running tests on OptimalBST.

/// @class runTests
/// @brief Class for running sequential and parallel tests on OptimalBST.
///
/// This class reads a dataset from a file, stores it in memory, and executes both sequential
/// and parallel tests on the OptimalBST using the data.
class runTests
{
public:
    /// @brief Constructs a runTests object and executes tests.
    /// @param filename Name of the file containing test data.
    runTests(const string& filename) {
        OptimalBST* bst = OptimalBST::getInstance(4);
        ifstream infile(filename);
        string line;

        //for the read dataset
        vector<vector<Rational>> testCases;
        vector<string> indices;

        //reading the file content and storing it in memory to avoid reading issues during multithreading
        while (getline(infile, line)) {
            stringstream ss(line);
            string index;
            getline(ss, index, ':');
            vector<Rational> m;
            string rational;
            while (getline(ss, rational, ';')) {
                int num, denom;
                stringstream rs(rational);
                rs >> num >> denom;
                m.emplace_back(num, denom);
            }
            indices.push_back(index);
            testCases.push_back(m);
        }

        cout << "Executing Sequential Tests:" << endl;
        auto sequential_start = chrono::high_resolution_clock::now();
        for (size_t i = 0; i < testCases.size(); ++i) {
            cout << "Testing set " << indices[i] << endl;
            bst->testSequential(testCases[i]);
        }
        auto sequential_finish = chrono::high_resolution_clock::now();
        chrono::duration<double> sequential_worktime = sequential_finish - sequential_start;
        auto sequential_microtime = chrono::duration_cast<chrono::milliseconds>(sequential_worktime);
        cout << "TOTAL DURATION OF SEQUENTIAL TESTS : " << sequential_microtime.count() << " ms" << endl;

        cout << "\nExecuting Parallel Tests:" << endl;

        //determine the number of threads to use
        int num_threads = 4;
        size_t data_size = testCases.size();
        size_t chunk_size = (data_size + num_threads - 1) / num_threads;

        //vector to hold the thread objects
        vector<thread> threads;

        auto parallel_start = chrono::high_resolution_clock::now();

        //launch threads to process parts of data
        for (int t = 0; t < num_threads; ++t) {
            threads.emplace_back([bst, &testCases, t, chunk_size, data_size, &indices]() {
                size_t start_idx = t * chunk_size;
                size_t end_idx = min(start_idx + chunk_size, data_size);

                for (size_t i = start_idx; i < end_idx; ++i) {
                    cout << "Testing set " << indices[i] << endl;
                    bst->testParallel(testCases[i], 4);
                }
                });
        }

        //wait for all threads to finish
        for (auto& thread : threads) {
            thread.join();
        }

        auto parallel_finish = chrono::high_resolution_clock::now();
        chrono::duration<double> parallel_worktime = parallel_finish - parallel_start;
        auto parallel_microtime = chrono::duration_cast<chrono::milliseconds>(parallel_worktime);
        cout << "TOTAL DURATION OF PARALLEL TESTS: " << parallel_microtime.count() << " ms" << endl;
    }
};

