#include <functional>
#include <iostream>
#include <string>
#include <vector>

using string_value_JSON = std::unordered_map<std::string, std::string>;
using double_value_JSON = std::unordered_map<std::string, double>;

namespace ParserUtils {
struct KeyValue {
  std::string key = "";
  std::string value = "";

  friend std::ostream& operator<<(std::ostream& out, const KeyValue& rhs) {
    out << rhs.key << " : " << rhs.value << "\n";

    return out;
  }
};
#define SPLIT_DEFINITION                   \
  std::vector<std::string> result;         \
  std::string curr;                        \
  for (char character : phrase) {          \
    if (character == delimiter) {          \
      result.push_back(curr);              \
      curr = "";                           \
    } else                                 \
      curr += character;                   \
  }                                        \
  if (curr.size()) result.push_back(curr); \
                                           \
  return result;

std::vector<std::string> Split(std::string&& phrase, char delimiter) {
  SPLIT_DEFINITION;
}
std::vector<std::string> Split(const std::string& phrase, char delimiter) {
  SPLIT_DEFINITION;
}
#define TRIM_LEADING_CHARACTER_DEFINITION               \
  int n = phrase.size();                                \
  size_t i = 0;                                         \
  while (i < phrase.size() && phrase[i] == character) { \
    i++;                                                \
  }                                                     \
  return phrase.substr(i, n - i);

std::string TrimLeadingCharacters(std::string&& phrase, char character) {
  TRIM_LEADING_CHARACTER_DEFINITION;
}
std::string TrimLeadingCharacters(const std::string& phrase, char character) {
  TRIM_LEADING_CHARACTER_DEFINITION;
}

#define TRIM_TRAILING_CHARACTER_DEFINITION              \
  size_t i = phrase.size() - 1;                         \
  while (i < phrase.size() && phrase[i] == character) { \
    i--;                                                \
  }                                                     \
  return phrase.substr(0, i + 1);

std::string TrimTrailingCharacters(std::string&& phrase, char character) {
  TRIM_TRAILING_CHARACTER_DEFINITION;
}
std::string TrimTrailingCharacters(const std::string& phrase, char character) {
  TRIM_TRAILING_CHARACTER_DEFINITION;
}

std::string TrimCharacters(std::string&& phrase, char character) {
  std::string removedTrailing = TrimTrailingCharacters(std::move(phrase), character);
  std::string removedTrailingAndLeading = TrimLeadingCharacters(std::move(removedTrailing), character);

  return removedTrailingAndLeading;
}

std::string TrimCharacters(const std::string& phrase, char character) {
  std::string removedTrailing = TrimTrailingCharacters(phrase, character);
  std::string removedTrailingAndLeading = TrimLeadingCharacters(removedTrailing, character);

  return removedTrailingAndLeading;
}

KeyValue parseKeyValue(const std::string& phrase) {
  int location = phrase.find(":");
  if (location == -1) {
    return KeyValue();
  }
  std::string key = phrase.substr(0, location);
  key = TrimCharacters(key, ',');
  key = TrimCharacters(key, ' ');
  key = TrimCharacters(key, '"');
  std::string value = phrase.substr(location + 1, phrase.size() - location);
  value = TrimCharacters(value, ',');
  value = TrimCharacters(value, ' ');
  value = TrimCharacters(value, '"');

  return KeyValue{key, value};
}

template <typename any>
bool includes(const std::vector<any>& list, const any& item) {
  return std::find(list.begin(), list.end(), item) != list.end();
}

}  // namespace ParserUtils