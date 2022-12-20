#pragma once

#include "JSONObject.h"

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "./Utils.cpp"
#define LOG(x) std::cout << x << "\n";
#define ERROR_LOG(x) std::cerr << x << "\n";
#define LOG_LIST(x) \
  for (auto v : x) std::cout << v << "\n";

namespace Json {

int LOG_NEST_LEVEL = 0;
char TAB = ' ';

// default
JsonObject::JsonObject() {}

// 1 param
JsonObject::JsonObject(std::string&& rawJSON) {
  std::stringstream reader(rawJSON);
  std::string phrase;
  std::string jsonString;
  while (reader >> phrase) {
    jsonString += phrase;
  }

  bool isObject = jsonString.size() && jsonString[0] == '{';
  bool isArray = jsonString.size() && jsonString[0] == '[';
  bool isString = jsonString.size() && jsonString[0] == '"';

  if (isObject) {
    object_type_ = TYPE::OBJECT;
    std::vector<KeyValuePair> keyValuePairs = scrapeObject(jsonString);
    for (const KeyValuePair& pair : keyValuePairs) {
      // recursively generate sub-json object
      object_[pair.key_] = new JsonObject(std::move(pair.value_));
    }
    return;
  }

  if (isArray) {
    object_type_ = TYPE::ARRAY;
    array = scrapeArray(jsonString);
    return;
  }

  if (isString) {
    object_type_ = TYPE::STRING;
    text = jsonString;
    return;
  }
}

// 1 param
JsonObject::JsonObject(const std::string& rawJSON) {
  stringstream reader(rawJSON);
  std::string phrase;
  std::string jsonString;
  while (reader >> phrase) {
    jsonString += phrase;
  }

  bool isObject = jsonString.size() && jsonString[0] == '{';
  bool isArray = jsonString.size() && jsonString[0] == '[';

  if (isObject) {
    object_type_ = TYPE::OBJECT;
    std::vector<KeyValuePair> keyValuePairs = scrapeObject(jsonString);
    for (const KeyValuePair& pair : keyValuePairs) {
      // recursively generate sub-json object
      object_[pair.key_] = new JsonObject(pair.value_);
    }
    return;
  }

  if (isArray) {
    object_type_ = TYPE::ARRAY;
    array = scrapeArray(jsonString);
    return;
  }
  // consider as std::string
  else {
    object_type_ = TYPE::STRING;
    text = jsonString;
    return;
  }
}

// copy constructor
JsonObject::JsonObject(const JsonObject& rhs) {
  object_ = rhs.object_;
  array = rhs.array;
  text = rhs.text;
  object_type_ = rhs.object_type_;
}

// move constructor
JsonObject::JsonObject(JsonObject&& rhs) {
  object_ = std::move(rhs.object_);
  array = std::move(rhs.array);
  text = std::move(rhs.text);
  object_type_ = std::move(rhs.object_type_);
}

JsonObject& JsonObject::operator=(const JsonObject& rhs) {
  JsonObject copy = rhs;
  std::swap(*this, copy);

  return *this;
}

JsonObject& JsonObject::operator=(JsonObject&& rhs) {
  std::swap(object_, rhs.object_);
  std::swap(array, rhs.array);
  std::swap(text, rhs.text);
  std::swap(object_type_, rhs.object_type_);

  return *this;
}

JsonObject::~JsonObject() = default;

// scrape key value pair from a std::string in format : "<key>:<value>"
KeyValuePair JsonObject::scrapeKeyValuePair(std::string&& instance) {
  int colonLocation = instance.find(':');
  if (colonLocation == -1) return KeyValuePair();

  std::string key = instance.substr(0, colonLocation);
  key = JSONUtils::TrimCharacters(key, '"');
  std::string value = instance.substr(colonLocation + 1, instance.size() - colonLocation - 1);
  return KeyValuePair(key, value);
}

/**
 * @brief scrapes array of key-value pairs from a std::string representation of an json object_
 * @format: "{<k1>:<v1>,<k2:v2>,..]"
 * @assumes: assumed correct nesting and balanced
 * @param jsonString the json object_ in the form of a std::string
 * @return std::vector<KeyValuePair>
 */

#define SCRAPE_OBJECT_DEFINITION                                     \
  std::vector<std::string> parts;                                    \
  std::string curr;                                                  \
  int nested = 0;                                                    \
  int nestLevel = 1;                                                 \
  for (char x : jsonString) {                                        \
    if (JSONUtils::includes<char>(openNesters, x)) {                 \
      if (++nested > nestLevel) curr += x;                           \
      continue;                                                      \
    }                                                                \
    if (JSONUtils::includes(closeNesters, x)) {                      \
      if (nested > nestLevel) curr += x;                             \
      if (nested-- == nestLevel) {                                   \
        parts.push_back(curr);                                       \
        curr = "";                                                   \
      }                                                              \
      continue;                                                      \
    }                                                                \
    if (x == ',' && nested == nestLevel) {                           \
      parts.push_back(curr);                                         \
      curr = "";                                                     \
      continue;                                                      \
    }                                                                \
    curr += x;                                                       \
  }                                                                  \
                                                                     \
  std::vector<KeyValuePair> result;                                  \
  for (std::string & pairString : parts) {                           \
    if (!pairString.size()) continue;                                \
                                                                     \
    KeyValuePair kvPair = scrapeKeyValuePair(std::move(pairString)); \
    result.push_back(kvPair);                                        \
  }                                                                  \
                                                                     \
  return result;

std::vector<KeyValuePair> JsonObject::scrapeObject(const std::string& jsonString) {
  SCRAPE_OBJECT_DEFINITION;
}

std::vector<KeyValuePair> JsonObject::scrapeObject(std::string&& jsonString) {
  SCRAPE_OBJECT_DEFINITION;
}

/**
 * @brief scrapes array of strings from a std::string representation of a std::string[]
 * @format: "[<a>,<b>,<c>]"
 * @assumes: assumed correct nesting and balanced
 * @param jsonString the std::string array in the form of a std::string
 * @return std::vector<JsonObject>
 */
std::vector<JsonObject*> JsonObject::scrapeArray(const std::string& jsonString) {
  std::vector<JsonObject*> result;
  std::string curr;
  int nested = 0;
  int nestLevel = 1;
  for (char x : jsonString) {
    if (JSONUtils::includes(openNesters, x)) {
      if (++nested > nestLevel) curr += x;
      continue;
    }
    if (JSONUtils::includes(closeNesters, x)) {
      if (nested > nestLevel) curr += x;
      if (--nested == nestLevel) {
        if (!curr.size()) continue;
        result.push_back(new JsonObject(std::move(curr)));
        curr = "";
      }
      continue;
    }
    if (x == ',' && nested == nestLevel) {
      if (!curr.size()) continue;
      result.push_back(new JsonObject(std::move(curr)));
      curr = "";
      continue;
    }
    curr += x;
  }
  if (curr.size()) result.push_back(new JsonObject(std::move(curr)));

  return result;
}

std::vector<JsonObject*> JsonObject::scrapeArray(std::string&& jsonString) {
  std::vector<JsonObject*> result;
  std::string curr;
  int nested = 0;
  int nestLevel = 1;
  for (char x : jsonString) {
    if (JSONUtils::includes(openNesters, x)) {
      if (++nested > nestLevel) curr += x;
      continue;
    }
    if (JSONUtils::includes(closeNesters, x)) {
      if (nested > nestLevel) curr += x;
      if (--nested == nestLevel) {
        if (!curr.size()) continue;
        result.push_back(new JsonObject(std::move(curr)));
        curr = "";
      }
      continue;
    }
    if (x == ',' && nested == nestLevel) {
      if (!curr.size()) continue;
      result.push_back(new JsonObject(std::move(curr)));
      curr = "";
      continue;
    }
    curr += x;
  }
  if (curr.size()) result.push_back(new JsonObject(std::move(curr)));

  return result;
}

JsonObject* JsonObject::operator[](std::string&& key) {
  return object_[key];
}

JsonObject* JsonObject::operator[](size_t idx) {
  if (idx < 0 && idx >= array.size()) {
    ERROR_LOG(" index " << idx << " out of bounds, size of array is " << array.size());
    abort();
  }
  return array[idx];
}

std::string JsonObject::type() {
  switch (object_type_) {
    case TYPE::OBJECT:
      return "JsonObject";
    case TYPE::ARRAY:
      return "Array";
    case TYPE::STRING:
      return "String";
    default:
      return "Undefined";
  }
}

// extract std::string value - only for type std::string.
std::string JsonObject::string_value() {
  if (object_type_ != TYPE::STRING) {
    ERROR_LOG("TYPE IS NOT STRING:\n"
              << *this);
    return "";
  }

  return text;
}

// TODO: log out in form of JSONStringify
std::ostream& operator<<(std::ostream& out, JsonObject& rhs) {
  if (rhs.object_type_ == TYPE::OBJECT) {
    if (!rhs.object_.size()) {
      out << "{}";
      return out;
    }
    out << "{" << (rhs.object_.size() ? "\n" : "");

    LOG_NEST_LEVEL++;
    size_t i = 0;
    for (auto [x, y] : rhs.object_) {
      bool lastItem = i++ == (rhs.object_.size() - 1);

      out << std::string(LOG_NEST_LEVEL * 2, TAB);
      out << x << ": " << *y
          << (lastItem ? "" : ",")
          << "\n";
    }
    LOG_NEST_LEVEL--;
    out << std::string(LOG_NEST_LEVEL * 2, TAB);
    out << "}";

    return out;
  }

  if (rhs.object_type_ == TYPE::ARRAY) {
    out << "[\n";
    LOG_NEST_LEVEL++;
    out << std::string(LOG_NEST_LEVEL * 2, TAB);
    for (size_t i = 0; i < rhs.array.size(); i++) {
      bool lastItem = i == (rhs.array.size() - 1);
      JsonObject*& obj = rhs.array[i];
      out << *obj
          << (lastItem ? "" : ",")
          << "\n"
          << (lastItem ? "" : std::string(LOG_NEST_LEVEL * 2, TAB));
    }
    LOG_NEST_LEVEL--;
    out << std::string(LOG_NEST_LEVEL * 2, TAB);
    out << "]";

    return out;
  }

  if (rhs.object_type_ == TYPE::STRING) {
    cout << rhs.text;
    return out;
  }

  return out;
}

}  // namespace Json