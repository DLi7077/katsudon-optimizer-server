#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#define LOG(x) cout << x << "\n";
#define LOG_LIST(x) \
  for (auto v : x) cout << v << "\n";

using namespace std;

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

class JsonObject {
 private:
  unordered_map<string, JsonObject*> object_;
  std::vector<JsonObject> array;
  string text;
  TYPE object_type_;

 public:
  // default
  JsonObject();

  // 1 param
  JsonObject(string&& rawJSON);
  JsonObject(const string& rawJSON);

  // copy constructor
  JsonObject(const JsonObject& rhs);
  // move constructor
  JsonObject(JsonObject&& rhs);

  // copy assignment
  JsonObject& operator=(const JsonObject& rhs);
  // move assignment
  JsonObject& operator=(JsonObject&& rhs);

  ~JsonObject();

  // scrape key value pair from a string in format : "<key>:<value>"
  static KeyValuePair scrapeKeyValuePair(string&& instance);

  /**
   * @brief scrapes array of key-value pairs from a string representation of an json object_
   * @format: "{<k1>:<v1>,<k2:v2>,..]"
   * @assumes: assumed correct nesting and balanced
   * @param jsonString the json object_ in the form of a string
   * @return vector<KeyValuePair>
   */
  static vector<KeyValuePair> scrapeObject(const string& jsonString);
  static vector<KeyValuePair> scrapeObject(string&& jsonString);

  /**
   * @brief scrapes array of strings from a string representation of a string[]
   * @format: "[<a>,<b>,<c>]"
   * @assumes: assumed correct nesting and balanced
   * @param jsonString the string array in the form of a string
   * @return vector<JsonObject>
   */
  static vector<JsonObject> scrapeArray(const string& jsonString);
  static vector<JsonObject> scrapeArray(string&& jsonString);

  JsonObject operator[](string&& key);

  JsonObject operator[](size_t idx);


  string getType();
  // TODO: log out in form of JSONStringify
  friend ostream& operator<<(ostream& out, JsonObject& rhs);
};
