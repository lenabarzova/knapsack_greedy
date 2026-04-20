#pragma once

#include <vector>
#include <string>

struct GreedyItem {
    int value;
    int weight;
};

struct GreedyResult {
    long long totalValue;
    long long totalWeight;
    std::vector<int> state;
};

bool readGreedyInputFile(const std::string& filename, int& n, int& capacity, std::vector<GreedyItem>& items);
GreedyResult solveKnapsackGreedy(int n, int capacity, const std::vector<GreedyItem>& items);
void printGreedyResult(const GreedyResult& result);
