#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class LISSolution {
public:
  int lis(const vector<int>& inputArray) {
    if (inputArray.empty()) return 0;
    vector<int> log(inputArray.size(), 1);

    for (int index = 1; index < inputArray.size(); ++index) {
      for(int start=0; start < index; ++start) {
        if (inputArray[index] > inputArray[start]) {
          log[index] = std::max(log[index], 1 + log[start]);
        }
      }
    }
    int maxLis = inputArray[0];
    for(int index = 1; index < inputArray.size(); ++index) {
      maxLis = std::max(maxLis, log[index]);
    }
    return maxLis;
  }

  int lisUsingPatienceSorting(const vector<int>& inputArray) {
    if (inputArray.empty()) return 0;

    vector<int> pile;
    pile.push_back(inputArray.front());

    for (int index = 1; index < inputArray.size(); ++index) {
      const int currentElement = inputArray[index];
      if (currentElement > pile.back()) {
        pile.push_back(currentElement);
      } else {
        auto itr = std::upper_bound(pile.begin(), pile.end(), currentElement);
        *itr = currentElement;
      }
    }

    return pile.size();
  }
};

int main(int argc, char** argv) {
  std::vector<int> v{ 2, 5, 3, 7, 11, 8, 10, 13, 6 };
  cout << LISSolution().lis(v) << endl;
  cout << LISSolution().lisUsingPatienceSorting(v) << endl;
  return 0;
}

//
// Time complexity:
//  1) Naive Approach [call to lis()] : O(n^2)
//  2) Using Patience Sorting [call to lisUsingPatienceSorting()]: O(n log n)
//      -> log (n) because we will have to do binary search each time
//
