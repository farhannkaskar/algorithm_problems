#include <iostream>
#include <vector>

using namespace std;

class KMP {
public:
  vector<int>* buildLPSArray(const string& inputString) {
    if (inputString.empty()) {
      return NULL;
    }

    vector<int>* lps = new vector<int>(inputString.size(), 0);

    (*lps)[0] = 0;
    int lpsLength = 0;
    int charIndex = 1;

    while(charIndex < inputString.size()) {
      if (inputString[charIndex] == inputString[lpsLength]) {
        lpsLength++;
        (*lps)[charIndex] = lpsLength;
        charIndex++;
      } else {
        if (lpsLength  == 0) {
          (*lps)[charIndex] = 0;
          charIndex++;
        } else {
          lpsLength = (*lps)[lpsLength - 1];
        }
      }
    }

    return lps;
  }
};

int main() {
  KMP kmp;
  vector<int>* lps = kmp.buildLPSArray("AAACAAAAAC");

  if (lps != NULL) {
    for(auto each_entry:*lps) {
        cout << each_entry << ", ";
    }
  }
  return 0;
}
