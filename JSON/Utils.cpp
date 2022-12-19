#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace JSONUtils {
// key value pair
struct KeyValuePair {
  string key_;
  string value_;
  KeyValuePair() {}
  KeyValuePair(string key, string value)
      : key_(key), value_(value) {}
};

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

KeyValuePair scrapeKeyValuePair(string&& instance) {
  int colonLocation = instance.find(':');
  if (colonLocation == -1) return KeyValuePair();

  string key = instance.substr(0, colonLocation);
  key = TrimCharacters(key, '"');
  string value = instance.substr(colonLocation + 1, instance.size() - colonLocation - 1);
  value = TrimCharacters(value, '"');

  return KeyValuePair(key, value);
}

template <typename any>
bool includes(const std::vector<any>& list, const any& item) {
  return std::find(list.begin(), list.end(), item) != list.end();
}

}  // namespace JSONUtils