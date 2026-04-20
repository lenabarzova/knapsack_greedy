#include "knapsack_greedy.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct SortedGreedyItem {
    int value;
    int weight;
    int originalIndex;
    double ratio;
};

bool readGreedyInputFile(const string& filename, int& n, int& capacity, vector<GreedyItem>& items) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        return false;
    }

    fin >> n >> capacity;

    items.resize(n);
    for (int i = 0; i < n; i++) {
        fin >> items[i].value >> items[i].weight;
    }

    fin.close();
    return true;
}

vector<SortedGreedyItem> buildSortedGreedyItems(const vector<GreedyItem>& items) {
    int n = static_cast<int>(items.size());
    vector<SortedGreedyItem> sorted(n);

    for (int i = 0; i < n; i++) {
        sorted[i].value = items[i].value;
        sorted[i].weight = items[i].weight;
        sorted[i].originalIndex = i;
        sorted[i].ratio = 0.0;

        if (items[i].weight > 0) {
            sorted[i].ratio = static_cast<double>(items[i].value) / static_cast<double>(items[i].weight);
        }
    }

    sort(sorted.begin(), sorted.end(),
        [](const SortedGreedyItem& a, const SortedGreedyItem& b) {
            if (a.ratio != b.ratio) {
                return a.ratio > b.ratio;
            }
            if (a.weight != b.weight) {
                return a.weight < b.weight;
            }
            return a.value > b.value;
        }
    );

    return sorted;
}

GreedyResult solveKnapsackGreedy(int n, int capacity, const vector<GreedyItem>& items) {
    GreedyResult result;
    result.totalValue = 0;
    result.totalWeight = 0;
    result.state.assign(n, 0);

    vector<SortedGreedyItem> sorted = buildSortedGreedyItems(items);

    for (int i = 0; i < n; i++) {
        int itemWeight = sorted[i].weight;
        int itemValue = sorted[i].value;
        int originalIndex = sorted[i].originalIndex;

        if (result.totalWeight + itemWeight <= capacity) {
            result.totalWeight += itemWeight;
            result.totalValue += itemValue;
            result.state[originalIndex] = 1;
        }
    }

    return result;
}

void printGreedyResult(const GreedyResult& result) {
    cout << "Greedy algorithm result" << endl;
    cout << "Value: " << result.totalValue << endl;
    cout << "Weight: " << result.totalWeight << endl;

    cout << "Chosen objects: ";
    for (int i = 0; i < static_cast<int>(result.state.size()); i++) {
        if (result.state[i] == 1) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;

    if (result.state.size() <= 100) {
        cout << "Binary vector: ";
        for (int i = 0; i < static_cast<int>(result.state.size()); i++) {
            cout << result.state[i] << " ";
        }
        cout << endl;
    }
}