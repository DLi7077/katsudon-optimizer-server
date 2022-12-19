#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "../Game/Character/Attributes.h"
#include "./Utils.cpp"
#define STRING_FIELDS       \
  {                         \
    "element",              \
        "talent_stat",      \
        "affected_element", \
        "source_stat",      \
        "target_stat",      \
  }

using string_value_JSON = std::unordered_map<std::string, std::string>;
using double_value_JSON = std::unordered_map<std::string, double>;
using bonus_gain_JSON = std::unordered_map<std::string, Attributes::BonusStatGain>;

namespace JSONParser {

struct StringToInt {
  std::string string_key_;
  int int_value_;

  StringToInt(std::string &&string, int integer)
      : string_key_(string), int_value_(integer) {}
  StringToInt(const std::string &string, int integer)
      : string_key_(string), int_value_(integer) {}
};

struct StringToString {
  std::string string_key_;
  std::string string_value_;

  StringToString(std::string &&string, std::string &&string2)
      : string_key_(string), string_value_(string2) {}
  StringToString(const std::string &string, const std::string &string2)
      : string_key_(string), string_value_(string2) {}
};

std::vector<std::string> stringFields = {
    "element",
    "talent_stat",
    "affected_element",
    "source_stat",
    "target_stat",
};

std::vector<std::string> doubleFields = {
    "base_attack",
    "base_hp",
    "crit_damage",
    "flat_attack",
    "attack_percent",
    "flat_hp",
    "hp_percent",
    "flat_def",
    "def_percent",
    "elemental_mastery",
    "energy_recharge",
    "damage_bonus_elemental",
    "damage_bonus_all",
    "talent_percent",
    "enemy_level",
    "resistance_to_damage_element",
};

string_value_JSON stringValues;
double_value_JSON doubleValues;
bonus_gain_JSON bonusGainValues;

void addStringValue(
    const std::string &key, const std::string &value) {
  stringValues[key] = value;
}

void addDoubleValue(
    const std::string &key, const std::string &value) {
  doubleValues[key] = std::stod(value);
}

void addBonusGain(const std::string &key, const Attributes::BonusStatGain &gain) {
  bonusGainValues[key] = gain;
}

std::vector<std::string> parseArrayToString(const std::string &json, std::string prefixKey) {
  int location = json.find(prefixKey);
  if (location == -1) {
    std::cout << json << "\n";
    std::cout << "location at " << location << "\n";
    return {};
  }

  // extract array of bonuses
  std::string curr;
  std::vector<std::string> result;
  std::stack<char> nesters;

  size_t i = location + prefixKey.size() - 1;
  while (i < json.size()) {
    if (json[i] == '[') {
      nesters.push('['), i++;
      continue;
    }
    if (json[i] == ']') {
      if (nesters.top() == '[') nesters.pop();
      i++;
      if (nesters.empty()) break;
      continue;
    }
    if (json[i] == '{') {
      nesters.push('{'), i++;
      continue;
    }
    if (json[i] == '}') {
      if (nesters.top() == '{') nesters.pop();
      i++;
      if (nesters.empty() || nesters.top() == '[') {
        curr = ParserUtils::TrimCharacters(curr, ',');
        curr = ParserUtils::TrimCharacters(curr, ' ');
        curr = ParserUtils::TrimCharacters(curr, '\n');
        curr = ParserUtils::TrimCharacters(curr, '\r');
        result.push_back(curr);
        curr = "";
      }
      continue;
    }

    curr += json[i];
    i++;
  }

  return result;
}

}  // namespace JSONParser

int main(int argc, char **argv) {
  std::string jsonObject = argv[1];
  std::vector<std::string> lines = ParserUtils::Split(jsonObject, '\n');

  std::vector<std::string> bonusStatArray = JSONParser::parseArrayToString(jsonObject, "bonus_stat_gain\": ");
  // populate
  for (std::string &s : bonusStatArray) {
    std::cout << s << "\n";
  }
  size_t i = 0;
  for (; i < lines.size(); i++) {
    std::string trimmedLine;
    trimmedLine = ParserUtils::TrimCharacters(lines[i], ' ');
    trimmedLine = ParserUtils::TrimCharacters(trimmedLine, ',');

    ParserUtils::KeyValue pair = ParserUtils::parseKeyValue(trimmedLine);
    std::string key = pair.key;
    std::string value = pair.key;

    if (key == "bonus_stat_gain") break;

    if (ParserUtils::includes(JSONParser::stringFields, key)) {
      JSONParser::addStringValue(key, pair.value);
    }
    if (ParserUtils::includes(JSONParser::doubleFields, key)) {
      JSONParser::addDoubleValue(key, pair.value);
    }
  }

  // for (auto p : JSONParser::stringValues) {
  //   std::cout << p.first << " : " << p.second << '\n';
  // }
  // for (auto p : JSONParser::doubleValues) {
  //   std::cout << p.first << " : " << p.second << '\n';
  // }

  std::cout << " ";

  return 0;
}
