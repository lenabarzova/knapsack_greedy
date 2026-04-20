#include <iostream>
#include <vector>
#include "knapsack_greedy.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: knapsack_greedy.exe <input_file>" << endl;
        return 1;
    }

    int n = 0;
    int capacity = 0;
    vector<GreedyItem> items;

    bool ok = readGreedyInputFile(argv[1], n, capacity, items);
    if (!ok) {
        cout << "File open error" << endl;
        return 1;
    }

    GreedyResult result = solveKnapsackGreedy(n, capacity, items);
    printGreedyResult(result);

    return 0;
}