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
#define LOG(x) std::cout << x << "\n";

using string_value_JSON = std::unordered_map<std::string, std::string>;
using double_value_JSON = std::unordered_map<std::string, double>;

namespace JSONParser {
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
std::vector<Attributes::BonusStatGain> bonusStatGains;

void addStringValue(const std::string &key, const std::string &value) {
  stringValues[key] = value;
}

void addDoubleValue(const std::string &key, const std::string &value) {
  doubleValues[key] = std::stod(value);
}

void createBonusStatGains(const std::string &jsonObject) {
  std::vector<std::string> bonusStatArray = JSONParser::parseArrayToString(jsonObject, "bonus_stat_gain\": ");
  // populate bonus stat buffs
  for (const std::string &bonusStatString : bonusStatArray) {
    std::vector<std::string> attributes = ParserUtils::Split(bonusStatString, ',');
    Attributes::BonusStatGain currentBonus;

    for (std::string &attribute : attributes) {
      attribute = ParserUtils::TrimCharacters(attribute, ' ');
      attribute = ParserUtils::TrimCharacters(attribute, '\n');
      attribute = ParserUtils::TrimCharacters(attribute, ' ');
      ParserUtils::KeyValue pair = ParserUtils::parseKeyValue(attribute);

      if (pair.key == "source_stat") {
        currentBonus.source_stat_ = pair.value;
      } else if (pair.key == "target_stat") {
        currentBonus.target_stat_ = pair.value;
      } else if (pair.key == "source_offset") {
        currentBonus.source_offset_ = std::stod(pair.value);
        continue;
      } else if (pair.key == "percent_gain") {
        currentBonus.percent_gain_ = std::stod(pair.value);
      } else if (pair.key == "max_gain") {
        currentBonus.max_gain_ = std::stod(pair.value);
      }
    }

    bonusStatGains.push_back(currentBonus);
  }
}

void createStatValues(const std::string &jsonObject) {
  std::vector<std::string> lines = ParserUtils::Split(jsonObject, '\n');

  for (std::string &line : lines) {
    std::string trimmedLine = line;
    trimmedLine = ParserUtils::TrimCharacters(trimmedLine, ' ');
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
}

}  // namespace JSONParser

int main(int argc, char **argv) {
  std::string jsonObject = argv[1];
  JSONParser::createBonusStatGains(jsonObject);
  JSONParser::createStatValues(jsonObject);

  for (auto p : JSONParser::stringValues) {
    LOG(p.first << " " << p.second);
  }
  for (auto p : JSONParser::doubleValues) {
    LOG(p.first << " " << p.second);
  }
  for (auto p : JSONParser::bonusStatGains) {
    LOG(p);
  }

  return 0;
}
