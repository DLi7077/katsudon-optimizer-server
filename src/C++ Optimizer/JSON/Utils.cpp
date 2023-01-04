#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace JSONUtils {
// key value pair

#define TRIM_LEADING_CHARACTER_DEFINITION               \
  int n = phrase.size();                                \
  size_t i = 0;                                         \
  while (i < phrase.size() && phrase[i] == character) { \
    i++;                                                \
  }                                                     \
  return phrase.substr(i, n - i);

string TrimLeadingCharacters(string&& phrase, char character) {
  TRIM_LEADING_CHARACTER_DEFINITION;
}
string TrimLeadingCharacters(const string& phrase, char character) {
  TRIM_LEADING_CHARACTER_DEFINITION;
}

#define TRIM_TRAILING_CHARACTER_DEFINITION              \
  size_t i = phrase.size() - 1;                         \
  while (i < phrase.size() && phrase[i] == character) { \
    i--;                                                \
  }                                                     \
  return phrase.substr(0, i + 1);

string TrimTrailingCharacters(string&& phrase, char character) {
  TRIM_TRAILING_CHARACTER_DEFINITION;
}
string TrimTrailingCharacters(const string& phrase, char character) {
  TRIM_TRAILING_CHARACTER_DEFINITION;
}

string TrimCharacters(string&& phrase, char character) {
  string removedTrailing = TrimTrailingCharacters(move(phrase), character);
  string removedTrailingAndLeading = TrimLeadingCharacters(move(removedTrailing), character);

  return removedTrailingAndLeading;
}

string TrimCharacters(const string& phrase, char character) {
  string removedTrailing = TrimTrailingCharacters(phrase, character);
  string removedTrailingAndLeading = TrimLeadingCharacters(removedTrailing, character);

  return removedTrailingAndLeading;
}

string wrap(string phrase, string wrapper) {
  return wrapper + phrase + wrapper;
}

template <typename any>
bool includes(const vector<any>& list, any item) {
  return find(list.begin(), list.end(), item) != list.end();
}
}  // namespace JSONUtils