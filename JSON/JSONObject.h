#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "./Utils.cpp"
#define LOG(x) cout << x << "\n";
#define LOG_LIST(x) \
  for (auto v : x) cout << v << "\n";

using namespace std;

namespace JSON {

struct KeyValuePair {
  string key_;
  string value_;
  KeyValuePair() {}
  KeyValuePair(string key, string value)
      : key_(key), value_(value) {}
};

enum TYPE {
  ARRAY,
  STRING,
  OBJECT
};
vector<char> openNesters = {'{', '['};
vector<char> closeNesters = {'}', ']'};
unordered_map<char, char> closer = {
    {'{', '}'},
    {'[', ']'},
};

namespace JSONScrape {
// scrape key value pair from a string in format : "<key>:<value>"
KeyValuePair scrapeKeyValuePair(string&& instance) {
  int colonLocation = instance.find(':');
  if (colonLocation == -1) return KeyValuePair();

  string key = instance.substr(0, colonLocation);
  key = JSONUtils::TrimCharacters(key, '"');
  string value = instance.substr(colonLocation + 1, instance.size() - colonLocation - 1);
  value = JSONUtils::TrimCharacters(value, '"');

  return KeyValuePair(key, value);
}

/**
 * @brief scrapes array of key-value pairs from a string representation of an json object
 * @format: "{<k1>:<v1>,<k2:v2>,..]"
 * @assumes: assumed correct nesting and balanced
 * @param jsonString the json object in the form of a string
 * @return vector<KeyValuePair>
 */
vector<KeyValuePair> scrapeObject(const string& jsonString) {
  vector<string> parts;
  string curr;
  int nested = 0;
  int nestLevel = 1;
  for (char x : jsonString) {
    if (JSONUtils::includes<char>(JSON::openNesters, x)) {
      if (++nested > nestLevel) curr += x;
      continue;
    }
    if (JSONUtils::includes(JSON::closeNesters, x)) {
      if (nested >= nestLevel) curr += x;
      if (--nested == nestLevel) {
        parts.push_back(curr);
        curr = "";
      }
      continue;
    }
    if (x == ',' && nested == nestLevel) {
      parts.push_back(curr);
      curr = "";
      continue;
    }
    curr += x;
  }

  vector<KeyValuePair> result;
  for (string& pair : parts) {
    KeyValuePair kvPair = JSONScrape::scrapeKeyValuePair(std::move(pair));
    result.push_back(kvPair);
  }

  return result;
}

/**
 * @brief scrapes array of strings from a string representation of a string[]
 * @format: "[<a>,<b>,<c>]"
 * @assumes: assumed correct nesting and balanced
 * @param jsonString the string array in the form of a string
 * @return vector<string>
 */
vector<string> scrapeArray(const string& jsonString) {
  vector<string> result;
  string curr;
  int nested = 0;
  int nestLevel = 1;
  for (char x : jsonString) {
    if (JSONUtils::includes(openNesters, x)) {
      if (++nested > nestLevel) curr += x;
      continue;
    }
    if (JSONUtils::includes(closeNesters, x)) {
      if (nested >= nestLevel) curr += x;
      if (--nested == nestLevel) {
        result.push_back(curr);
        curr = "";
      }
      continue;
    }
    if (x == ',' && nested == nestLevel) {
      result.push_back(curr);
      curr = "";
      continue;
    }
    curr += x;
  }

  return result;
}
}  // namespace JSONScrape

class Object {
 private:
  unordered_map<string, string> object;
  vector<string> array;
  TYPE object_type_;

 public:
  Object() {}
  Object(string&& rawJSON) {
    stringstream reader(rawJSON);
    string phrase;
    string jsonString;
    while (reader >> phrase) {
      jsonString += phrase;
    }

    bool isObject = jsonString.size() && jsonString[0] == '{';
    bool isArray = jsonString.size() && jsonString[0] == '[';
    bool isString = jsonString.size() && jsonString[0] == '"';

    if (isObject) {
      object_type_ = OBJECT;
      vector<KeyValuePair> keyValuePairs = JSONScrape::scrapeObject(jsonString);
      for (const KeyValuePair& pair : keyValuePairs) {
        object[pair.key_] = pair.value_;
      }
      return;
    }

    if (isArray) {
      object_type_ = ARRAY;
      array = JSONScrape::scrapeArray(jsonString);
      return;
    }
  }

  string operator[](string&& key) {
    return object[key];
  }

  string operator[](size_t idx) {
    if (idx < 0 && idx >= array.size()) {
      cerr << " index " << idx << " out of bounds, size of array is " << array.size() << "\n";
      abort();
    }
    return array[idx];
  }

  string getType() {
    switch (object_type_) {
      case OBJECT:
        return "Object";

      case ARRAY:
        return "Array";

      case STRING:
        return "String";

      default:
        return "Undefined";
    }
  }
  // TODO: log out in form of JSONStringify
  friend ostream& operator<<(ostream& out, Object& rhs) {
    if (rhs.object_type_ == TYPE::OBJECT) {
      if (!rhs.object.size()) {
        LOG("empty object");
      } else {
        for (auto [x, y] : rhs.object) {
          out << x << " : " << y << "\n";
        }
      }
    }
    if (rhs.object_type_ == TYPE::ARRAY) {
      cout << ('[');
      for (auto x : rhs.array) cout << x << " ";
      cout << (']');
    }

    return out;
  }
};

}  // namespace JSON
