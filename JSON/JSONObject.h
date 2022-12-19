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
 private:
  unordered_map<string, string> object;
  inline static vector<char> openNesters = {'{', '['};
  inline static vector<char> closeNesters = {'}', ']'};
  inline static unordered_map<char, char> closer = {
      {'{', '}'},
      {'[', ']'},
  };

 public:
  JSONObject() {
  }
  JSONObject(string&& rawJSON) {
    stringstream reader(rawJSON);
    string phrase;
    string jsonString;
    while (reader >> phrase) {
      jsonString += phrase;
    }

    LOG(jsonString);

    vector<JSONUtils::KeyValuePair> keyValuePairs = key_value_pairs(jsonString);
    for (const JSONUtils::KeyValuePair& pair : keyValuePairs) {
      object[pair.key_] = pair.value_;
    }
  }

  static vector<JSONUtils::KeyValuePair> key_value_pairs(const string& jsonString) {
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

  friend ostream& operator<<(ostream& out, JSONObject& rhs) {
    for (auto [x, y] : rhs.object) {
      out << x << " : " << y << "\n";
    }

    return out;
  }
};