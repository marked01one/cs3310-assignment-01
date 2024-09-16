// #include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <ostream>
#include <vector>

using namespace std;

struct Result {
    int maxSum;
    int left;
    int right;
};

Result maxSum3Loops(vector<int>& arr) {
    Result result;
    result.maxSum = numeric_limits<int>::min();

    for (int i = 0; i < arr.size(); ++i) {
        for (int j = i; j < arr.size(); ++j) {
            int thisSum = 0;

            for (int k = i; k <= j; ++k) 
                thisSum += arr[k];

            if (thisSum > result.maxSum) {
                result.maxSum = thisSum;
                result.left = i;
                result.right = j;
            }
        }
    }
    return result;
}


Result maxSum2Loops(vector<int>& arr) {
    Result result;
    result.maxSum = numeric_limits<int>::min();

    for (int i = 0; i < arr.size(); ++i) {
        int thisSum = 0;
        for (int j = i; j < arr.size(); j++) {
            thisSum += arr[j];
            if (result.maxSum < thisSum) {
                result.maxSum = thisSum;
                result.left = i;
                result.right = j;
            }
        }
    }
    return result;
}


Result maxSumRecursive(vector<int>& arr, int left, int right) {
    Result result;
    
    if (left == right) {
        result.maxSum = arr[left];
        result.left = left, result.right = left;
        return result;
    } 

    int center = (left+right) / 2;
    Result maxLeftSum = maxSumRecursive(arr, left, center);
    Result maxRightSum = maxSumRecursive(arr, center+1, right);

    int maxLeftBorderSum = numeric_limits<int>::min();
    int leftBorderSum = 0;
    for (int i = center; i >= left; --i) {
        leftBorderSum += arr[i];
        if (leftBorderSum > maxLeftBorderSum) {
            maxLeftBorderSum = leftBorderSum;
            result.left = i;
        }
    }

    int maxRightBorderSum = numeric_limits<int>::min();
    int rightBorderSum = 0;
    for (int j = center; j <= right; ++j) {
        rightBorderSum += arr[j];
        if (rightBorderSum > maxRightBorderSum) {
            maxRightBorderSum = rightBorderSum;
            result.right = j;
        }
    }

    int maxBorderSum = maxLeftBorderSum+maxRightBorderSum;

    if (maxBorderSum > max(maxLeftSum.maxSum, maxRightSum.maxSum)) {
        result.maxSum = maxBorderSum;
        return result;
    } 
    else {
        return (maxLeftSum.maxSum > maxRightSum.maxSum) ? maxLeftSum : maxRightSum;
    }
}

Result maxSumDP(vector<int>& arr) {
    Result result;
    result.maxSum = arr[0];
    result.left = 0, result.right = 0;
    
    Result current;
    current.maxSum = arr[0];
    current.left = 0, current.right = 0;    

    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] > current.maxSum+arr[i]) {
            current.left = i, current.right = i;
            current.maxSum = arr[i];
        }
        else {
            current.maxSum += arr[i];
            current.right = i;
        }

        if (current.maxSum >= result.maxSum) {
            result = current;
        }
    }
    return result;
}


// Driver code
int main() {
    vector<int> positives(1000);
    vector<int> negatives(1000);

    for (int i = 0; i < positives.size(); ++i) {
        positives[i] = rand() % 10000;
        negatives[i] = (rand() % 10000) * -1;
    }

    Result resPositive, resNegative;
    chrono::time_point start = chrono::high_resolution_clock::now();
    chrono::time_point end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed;

    start = chrono::high_resolution_clock::now();  
    resPositive = maxSum3Loops(positives);
    resNegative = maxSum3Loops(negatives);
    end = chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "\nTime taken (Algorithm #1): " << elapsed.count() * 1000 << "\tmiliseconds" << std::endl;


    start = chrono::high_resolution_clock::now();
    resPositive = maxSum2Loops(positives);
    resNegative = maxSum2Loops(negatives);
    end = chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken (Algorithm #2): " << elapsed.count() * 1000 << "\tmiliseconds" << std::endl;
    
    start = chrono::high_resolution_clock::now();
    resPositive = maxSumRecursive(positives, 0, positives.size()-1);
    resNegative = maxSumRecursive(negatives, 0, negatives.size()-1);
    end = chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken (Algorithm #3): " << elapsed.count() * 1000 << "\tmiliseconds" << std::endl;
    
    start = chrono::high_resolution_clock::now();
    resPositive = maxSumDP(positives);
    resNegative = maxSumDP(negatives);
    end = chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken (Algorithm #4): " << elapsed.count() * 1000 << "\tmiliseconds" << std::endl;
    
    return 0;
}
