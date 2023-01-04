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

JsonObject::JsonObject(TYPE type, std::string value = "") {
  object_type_ = type;
  switch (type) {
    case TYPE::DOUBLE:
      double_ = std::stod(value);
      break;
    case TYPE::STRING:
      text_ = value;
      break;
    case TYPE::ARRAY:
      array_ = JsonObject::scrapeArray(std::move(value));
      break;
    // TODO: handle object
    default:
      break;
  }
}

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

// 1 param double constructor
JsonObject::JsonObject(double decimal) {
  object_type_ = TYPE::DOUBLE;
  double_ = decimal;
}

// copy constructor
JsonObject::JsonObject(const JsonObject& rhs) {
  double_ = rhs.double_;
  array_ = rhs.array_;
  text_ = rhs.text_;
  object_type_ = rhs.object_type_;

  std::unordered_map<std::string, JsonObject*> copyObject;
  for (auto [key, obj] : rhs.object_) {
    copyObject[key] = new JsonObject(*obj);
  }
  object_ = copyObject;
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
  object_type_ = TYPE::OBJECT;
  bool keyExists = object_.find(key) != object_.end();
  if (!keyExists) object_[key] = new JsonObject();

  return *object_[key];
}

JsonObject& JsonObject::operator[](const std::string& key) {
  object_type_ = TYPE::OBJECT;
  bool keyExists = object_.find(key) != object_.end();
  if (!keyExists) object_[key] = new JsonObject();

  return *object_[key];
}

JsonObject& JsonObject::operator[](size_t idx) {
  if (idx < 0 && idx >= array_.size()) {
    LOG_LINE("index " << idx << " out of bounds, size of array_ is " << array_.size());
    abort();
  }
  return *array_[idx];
}

JsonObject& JsonObject::push_back(const JsonObject& rhs) {
  object_type_ = TYPE::ARRAY;
  JsonObject* copy = new JsonObject(rhs);
  array_.push_back(copy);

  return *this;
}

JsonObject& JsonObject::push_back(JsonObject&& rhs) {
  object_type_ = TYPE::ARRAY;
  JsonObject* copy = new JsonObject(std::move(rhs));
  array_.push_back(copy);

  return *this;
}

std::string JsonObject::type() {
  switch (object_type_) {
    case TYPE::ARRAY:
      return "Array";
    case TYPE::DOUBLE:
      return "Double";
    case TYPE::STRING:
      return "String";
    case TYPE::OBJECT:
      return "JsonObject";
    default:
      return "null";
  }
}

// extract std::string value - only for type std::string.
std::string JsonObject::string_value() {
  if (object_type_ != TYPE::STRING) {
    LOG_LINE("TYPE IS NOT STRING:\n"
             << *this);
    abort();
  }

  return text_;
}

double JsonObject::double_value() {
  if (object_type_ != TYPE::DOUBLE) {
    LOG_LINE("TYPE IS NOT DOUBLE:\n"
             << *this);
    abort();
  }

  return double_;
}

std::vector<JsonObject> JsonObject::array_value() {
  std::vector<JsonObject> result;
  for (JsonObject*& obj : array_) {
    result.push_back(JsonObject(*obj));
  }

  return result;
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
  }

  else if (rhs.object_type_ == TYPE::ARRAY) {
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
  }

  else if (rhs.object_type_ == TYPE::STRING) {
    out << JSONUtils::wrap(rhs.text_, "\"");
  }

  else if (rhs.object_type_ == TYPE::DOUBLE) {
    out << rhs.double_;
  }

  else {
    out << "null";
  }

  return out;
}

}  // namespace Json