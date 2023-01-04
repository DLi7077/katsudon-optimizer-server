#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
namespace Json {

struct KeyValuePair {
  std::string key_;
  std::string value_;
  KeyValuePair() {}
  KeyValuePair(std::string key, std::string value)
      : key_(key), value_(value) {}
};
enum TYPE {
  ARRAY,
  DOUBLE,
  STRING,
  OBJECT,
};

std::vector<char> openNesters = {'{', '['};
std::vector<char> closeNesters = {'}', ']'};

std::unordered_map<char, char> closer = {
    {'{', '}'},
    {'[', ']'},
};

class JsonObject {
 private:
  std::unordered_map<std::string, JsonObject*> object_;
  std::vector<JsonObject*> array_;
  std::string text_;
  double double_;
  TYPE object_type_;

 public:
  // default
  JsonObject();
  JsonObject(TYPE t, std::string value);

  // 1 param - default for parsing
  JsonObject(std::string&& rawJSON);
  JsonObject(const std::string& rawJSON);
  JsonObject(double decimal);

  // copy constructor
  JsonObject(const JsonObject& rhs);
  // move constructor
  JsonObject(JsonObject&& rhs);

  // copy assignment
  JsonObject& operator=(const JsonObject& rhs);
  // move assignment
  JsonObject& operator=(JsonObject&& rhs);

  ~JsonObject();

  // scrape key value pair from a std::string in format : "<key>:<value>"
  static KeyValuePair scrapeKeyValuePair(std::string&& instance);

  /**
   * @brief scrapes array of key-value pairs from a std::string representation of an json object_
   * @format: "{<k1>:<v1>,<k2:v2>,..]"
   * @assumes: assumed correct nesting and balanced
   * @param jsonString the json object_ in the form of a std::string
   * @return std::vector<KeyValuePair>
   */
  static std::vector<KeyValuePair> scrapeObject(std::string&& jsonString);

  /**
   * @brief scrapes array of strings from a std::string representation of a std::string[]
   * @format: "[<a>,<b>,<c>]"
   * @assumes: assumed correct nesting and balanced
   * @param jsonString the std::string array in the form of a std::string
   * @return std::vector<JsonObject>
   */
  // static std::vector<JsonObject> scrapeArray(const std::string& jsonString);
  static std::vector<JsonObject*> scrapeArray(std::string&& jsonString);

  /**
   * @brief return reference to object in map
   * creates and returns a new object if invalid key
   * @param key the string key to look up
   * @return JsonObject& reference to the mapped object
   */
  JsonObject& operator[](std::string&& key);
  JsonObject& operator[](const std::string& key);

  // index overload for array
  JsonObject& operator[](size_t idx);

  JsonObject& push_back(const JsonObject& rhs);
  JsonObject& push_back(JsonObject&& rhs);

  // object, array, or std::string
  std::string type();

  // extract std::string value - only for type std::string.
  std::string string_value();

  // extract double value - only for type std::string.
  double double_value();

  std::vector<JsonObject> array_value();

  bool operator!=(JsonObject& rhs);
  bool operator==(JsonObject& rhs);
  bool equalArray(JsonObject& a, JsonObject& b);
  bool equalDouble(JsonObject& a, JsonObject& b);
  bool equalString(JsonObject& a, JsonObject& b);
  bool equalObject(JsonObject& a, JsonObject& b);

  friend std::ostream& operator<<(std::ostream& out, JsonObject& rhs);
};

}  // namespace Json