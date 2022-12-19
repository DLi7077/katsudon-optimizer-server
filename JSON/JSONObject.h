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

class JSONObject {
  enum TYPE {
    ARRAY,
    STRING,
    OBJECT
  };

 private:
  unordered_map<string, string> object;
  vector<string> array;
  TYPE object_type_;
  inline static vector<char> openNesters = {'{', '['};
  inline static vector<char> closeNesters = {'}', ']'};
  inline static unordered_map<char, char> closer = {
      {'{', '}'},
      {'[', ']'},
  };

 public:
  JSONObject() {}

  JSONObject(string&& rawJSON) {
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
      vector<JSONUtils::KeyValuePair> keyValuePairs = scrapeObject(jsonString);
      for (const JSONUtils::KeyValuePair& pair : keyValuePairs) {
        object[pair.key_] = pair.value_;
      }
      return;
    }

    if (isArray) {
      object_type_ = ARRAY;
      array = scrapeArray(jsonString);
      return;
    }
  }

  // scrapes key-value pairs from a string representation of an object
  // assumed correct nesting and balanced
  static vector<JSONUtils::KeyValuePair> scrapeObject(const string& jsonString) {
    vector<string> parts;
    string curr;
    int nested = 0;
    int nestLevel = 1;
    for (const char& x : jsonString) {
      if (JSONUtils::includes(openNesters, x)) {
        if (++nested > nestLevel) curr += x;
        continue;
      }
      if (JSONUtils::includes(closeNesters, x)) {
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

    vector<JSONUtils::KeyValuePair> result;
    for (string& pair : parts) {
      JSONUtils::KeyValuePair kvPair = JSONUtils::scrapeKeyValuePair(std::move(pair));
      result.push_back(kvPair);
    }

    return result;
  }

  static vector<string> scrapeArray(const string& jsonString) {
    vector<string> result;
    string curr;
    int nested = 0;
    int nestLevel = 1;
    for (const char& x : jsonString) {
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
  friend ostream& operator<<(ostream& out, JSONObject& rhs) {
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