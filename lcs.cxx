#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class LCSSolution {
public:
  int lcsUtil(const string& s1, const string& s2, const int s1EndIndex, const int s2EndIndex) {
    const bool isInputValid = !s1.empty() && !s2.empty() &&
                              s1EndIndex >=0 && s1EndIndex < s1.size() &&
                              s2EndIndex >=0 && s2EndIndex < s2.size();
    if (!isInputValid) return 0;

    if (s1[s1EndIndex] == s2[s2EndIndex]) {
      return 1 + lcsUtil(s1, s2, s1EndIndex - 1, s2EndIndex - 1);
    } else {
      return std::max(lcsUtil(s1, s2, s1EndIndex - 1, s2EndIndex),
                      lcsUtil(s1, s2, s1EndIndex, s2EndIndex - 1));
    }
  }

  int lcs(const string& s1, const string& s2) {
    if (s1.empty() || s2.empty()) return 0;
    return lcsUtil(s1, s2, s1.size() - 1, s2.size() - 1);
  }

  int GetData(const vector<vector<int> >& dpMatrix, const int row, const int col) {
      const bool isInputValid = !dpMatrix.empty() && row >=0 &&  row < dpMatrix.size() &&
                                col >=0 && col < dpMatrix[row].size();
      if (!isInputValid) return 0;
      return dpMatrix[row][col];
  }

  void printLcsUtil(const string& s1, const string& s2, const vector<vector<int> >& dpMatrix, const int row, const int col, std::stack<char>& backtrace) {
    const bool isInputValid = row >=0 && row < s2.size() && col >=0 && col < s1.size();
    if (!isInputValid) return;

    if (s2[row] == s1[col]) {
      backtrace.push(s1[col]);
      printLcsUtil(s1, s2, dpMatrix, row-1, col-1, backtrace);
    } else {
      if (GetData(dpMatrix, row - 1, col) > GetData(dpMatrix, row, col - 1)) {
        printLcsUtil(s1, s2, dpMatrix, row-1, col, backtrace);
      } else {
        printLcsUtil(s1, s2, dpMatrix, row, col-1, backtrace);
      }
    }
  }

  void printLcs(const string& s1, const string& s2, const vector<vector<int> >& dpMatrix) {
    if(dpMatrix.empty()) return;

    int row = dpMatrix.size() - 1;
    int col = dpMatrix[row].size() - 1;
    std:stack<char> backtrace;

    printLcsUtil(s1, s2, dpMatrix, row, col, backtrace);

    while(!backtrace.empty()) {
      cout << backtrace.top();
      backtrace.pop();
    }
    cout << endl;
  }

  int lcsUsingDynamicProgramming(const string& s1, const string& s2) {
    if (s1.empty() || s2.empty()) return 0;

    vector<vector<int> > dpMatrix(s2.size(), vector<int>(s1.size(), 0));

    for (int s2Index = 0; s2Index < s2.size(); ++s2Index) {
      for (int s1Index = 0; s1Index < s1.size(); ++s1Index) {
        if (s1[s1Index] == s2[s2Index]) {
          dpMatrix[s2Index][s1Index] = 1 + GetData(dpMatrix, s2Index - 1, s1Index - 1);
        } else {
          dpMatrix[s2Index][s1Index] = std::max(GetData(dpMatrix, s2Index, s1Index - 1),
                                                GetData(dpMatrix, s2Index - 1, s1Index));
        }
      }
    }

    printLcs(s1, s2, dpMatrix);
    return dpMatrix[s2.size()-1][s1.size()-1];
  }
};

int main(int argc, char** argv) {
  const string s1 = "abcdef";
  const string s2 = "bidexf";
  cout << endl;
  cout << LCSSolution().lcs(s1, s2) << endl;
  cout << LCSSolution().lcsUsingDynamicProgramming(s1, s2) << endl;
  return 0;
}

//
// Time Complexity:
//  1) Using Naive Approach [call to lcs()]: O(2^(mn))
//  2) Using dynamic programming [call to lcsUsingDynamicProgramming()]: O(mxn)
//
