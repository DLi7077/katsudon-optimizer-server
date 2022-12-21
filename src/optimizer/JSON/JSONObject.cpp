#pragma once

#include "JSONObject.h"

#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "./Utils.cpp"
#define LOG(x) std::cout << x;
#define LOG_LINE(x) std::cout << x << "\n";
#define LOG_ERROR(x) std::cout << x << "\n";
#define LOG_LIST(x) \
  for (auto v : x) std::cout << v << "\n";

namespace Json {
int LOG_NEST_LEVEL = 0;
char TAB = ' ';

// default
JsonObject::JsonObject() {}

// 1 param r-value
JsonObject::JsonObject(std::string&& rawJSON) {
  std::stringstream reader(rawJSON);
  std::string phrase;
  std::string jsonString;
  while (getline(reader, phrase)) {
    jsonString += JSONUtils::TrimCharacters(phrase, ' ');
  }

  bool isObject = jsonString.size() && jsonString[0] == '{';
  bool isArray = jsonString.size() && jsonString[0] == '[';
  bool isString = jsonString.size() && jsonString[0] == '"';

  if (isObject) {
    object_type_ = TYPE::OBJECT;
    std::vector<KeyValuePair> keyValuePairs = scrapeObject(std::move(jsonString));
    for (const KeyValuePair& pair : keyValuePairs) {
      // recursively generate sub-json object
      object_[pair.key_] = new JsonObject(std::move(pair.value_));
    }
    return;
  }
  if (isArray) {
    object_type_ = TYPE::ARRAY;
    array_ = scrapeArray(std::move(jsonString));
    return;
  }
  if (isString) {
    object_type_ = TYPE::STRING;
    text_ = JSONUtils::TrimCharacters(jsonString, '"');
    return;
  }

  // default to be double
  object_type_ = TYPE::DOUBLE;
  double_ = std::stod(jsonString);
  return;
}

// 1 param r-value
JsonObject::JsonObject(const std::string& rawJSON) {
  stringstream reader(rawJSON);
  std::string phrase;
  std::string jsonString;
  while (getline(reader, phrase)) {
    jsonString += JSONUtils::TrimCharacters(phrase, ' ');
  }

  bool isObject = jsonString.size() && jsonString[0] == '{';
  bool isArray = jsonString.size() && jsonString[0] == '[';
  bool isString = jsonString.size() && jsonString[0] == '"';

  if (isObject) {
    object_type_ = TYPE::OBJECT;
    std::vector<KeyValuePair> keyValuePairs = scrapeObject(std::move(jsonString));
    for (const KeyValuePair& pair : keyValuePairs) {
      // recursively generate sub-json object
      object_[pair.key_] = new JsonObject(pair.value_);
    }
    return;
  }
  if (isArray) {
    object_type_ = TYPE::ARRAY;
    array_ = scrapeArray(std::move(jsonString));
    return;
  }
  if (isString) {
    object_type_ = TYPE::STRING;
    text_ = JSONUtils::TrimCharacters(jsonString, '"');
    return;
  }

  // default to be double
  object_type_ = TYPE::DOUBLE;
  double_ = std::stod(jsonString);
  return;
}

// copy constructor
JsonObject::JsonObject(const JsonObject& rhs) {
  object_ = rhs.object_;
  double_ = rhs.double_;
  array_ = rhs.array_;
  text_ = rhs.text_;
  object_type_ = rhs.object_type_;
}

// move constructor
JsonObject::JsonObject(JsonObject&& rhs) {
  object_ = std::move(rhs.object_);
  array_ = std::move(rhs.array_);
  double_ = std::move(rhs.double_);
  text_ = std::move(rhs.text_);
  object_type_ = std::move(rhs.object_type_);
}

JsonObject& JsonObject::operator=(const JsonObject& rhs) {
  JsonObject copy = rhs;
  std::swap(*this, copy);

  return *this;
}

JsonObject& JsonObject::operator=(JsonObject&& rhs) {
  std::swap(array_, rhs.array_);
  std::swap(double_, rhs.double_);
  std::swap(object_, rhs.object_);
  std::swap(text_, rhs.text_);
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
 * @brief scrapes array_ of key-value pairs from a std::string representation of an json object_
 * @format: "{<k1>:<v1>,<k2:v2>,..]"
 * @assumes: assumed correct nesting and balanced
 * @param jsonString the json object_ in the form of a std::string
 * @return std::vector<KeyValuePair>
 */
std::vector<KeyValuePair> JsonObject::scrapeObject(std::string&& jsonString) {
  std::vector<std::string> parts;
  std::string curr;
  int nested = 0;
  int nestLevel = 1;
  for (char x : jsonString) {
    if (JSONUtils::includes<char>(openNesters, x)) {
      if (++nested > nestLevel) curr += x;
      continue;
    }
    if (JSONUtils::includes(closeNesters, x)) {
      if (nested > nestLevel) curr += x;
      if (nested-- == nestLevel) {
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

  std::vector<KeyValuePair> result;
  for (std::string& pairString : parts) {
    if (!pairString.size()) continue;

    KeyValuePair kvPair = scrapeKeyValuePair(std::move(pairString));
    result.push_back(kvPair);
  }

  return result;
}

/**
 * @brief scrapes array_ of strings from a std::string representation of a std::string[]
 * @format: "[<a>,<b>,<c>]"
 * @assumes: assumed correct nesting and balanced
 * @param jsonString the std::string array_ in the form of a std::string
 * @return std::vector<JsonObject>
 */
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

JsonObject& JsonObject::operator[](std::string&& key) {
  if (object_.find(key) == object_.end()) {
    LOG_ERROR(key << " is not a valid key");
    LOG_ERROR("valid keys:");
    for (auto [key, _] : object_) {
      LOG(key << ",");
    }
    LOG("abortting")
    abort();
  }
  return *object_[key];
}

JsonObject& JsonObject::operator[](const std::string& key) {
  if (object_.find(key) == object_.end()) {
    LOG_ERROR(key << " is not a valid key");
    LOG_ERROR("valid keys:");
    for (auto [key, _] : object_) {
      LOG(key << ",");
    }
    LOG("abortting")
    abort();
  }
  return *object_[key];
}

JsonObject& JsonObject::operator[](size_t idx) {
  if (idx < 0 && idx >= array_.size()) {
    LOG_ERROR(" index " << idx << " out of bounds, size of array_ is " << array_.size());
    abort();
  }
  return *array_[idx];
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
    LOG_ERROR("TYPE IS NOT STRING:\n"
              << *this);
    abort();
  }

  return text_;
}

double JsonObject::double_value() {
  if (object_type_ != TYPE::DOUBLE) {
    LOG_ERROR("TYPE IS NOT DOUBLE:\n"
              << *this);
    abort();
  }

  return double_;
}

// overloads

bool JsonObject::operator==(JsonObject& rhs) {
  if (object_type_ == TYPE::OBJECT && rhs.object_type_ == TYPE::OBJECT) {
    return equalObject(*this, rhs);
  }
  if (object_type_ == TYPE::ARRAY && rhs.object_type_ == TYPE::ARRAY) {
    return equalArray(*this, rhs);
  }
  if (object_type_ == TYPE::STRING && rhs.object_type_ == TYPE::STRING) {
    return equalArray(*this, rhs);
  }

  return false;
}

bool JsonObject::operator!=(JsonObject& rhs) {
  return !(*this == rhs);
}

bool JsonObject::equalObject(JsonObject& a, JsonObject& b) {
  if (a.object_type_ != TYPE::OBJECT || b.object_type_ != TYPE::OBJECT)
    return false;

  for (auto [key, nestedValue] : a.object_) {
    bool b_has_key = !!b.object_[key];
    if (!b_has_key) return false;
    if (b[key] != a[key]) return false;
  }

  return true;
}

bool JsonObject::equalArray(JsonObject& a, JsonObject& b) {
  if (a.array_.size() != b.array_.size()) return false;
  std::vector<JsonObject*> a_items, b_items;
  for (JsonObject*& item : a.array_) a_items.push_back(item);
  for (JsonObject*& item : b.array_) b_items.push_back(item);

  std::sort(a_items.begin(), a_items.end());
  std::sort(b_items.begin(), b_items.end());

  for (size_t i = 0; i < a_items.size(); i++) {
    if (*a_items[i] != *b_items[i]) return false;
  }
  return true;
}

bool JsonObject::equalString(JsonObject& a, JsonObject& b) {
  return a.text_ == b.text_;
}

bool JsonObject::equalDouble(JsonObject& a, JsonObject& b) {
  return a.double_ == b.double_;
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
    for (auto [key, nestedObj] : rhs.object_) {
      bool lastItem = i++ == (rhs.object_.size() - 1);

      out << std::string(LOG_NEST_LEVEL * 2, TAB);
      out << JSONUtils::wrap(key, "\"") << ": " << *nestedObj
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
    for (size_t i = 0; i < rhs.array_.size(); i++) {
      bool lastItem = i == (rhs.array_.size() - 1);
      JsonObject& obj = rhs[i];
      out << obj
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
    out << rhs.text_;
    return out;
  }

  if (rhs.object_type_ == TYPE::DOUBLE) {
    out << rhs.double_;
    return out;
  }

  return out;
}

}  // namespace Json