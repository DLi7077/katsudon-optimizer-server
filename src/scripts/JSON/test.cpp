#include <functional>
#include <iostream>
#include <string>

#include "./JSONObject.cpp"

template <typename any>
void testEqual(any a, any b, bool expected) {
  bool result = (a == b);
  std::cout << (a) << " ?= "
            << b << " "
            << (result ? "true" : "false")
            << " expected : " << (expected ? "true" : "false")
            << "\n";
}

void testing() {
  std::string x = "{\r\n  \"element\": \"ex: Pyro\",\r\n  \"base_attack\": 0,\r\n  \"base_hp\": 0,\r\n  \"flat_attack\": 0,\r\n  \"attack_percent\": 0,\r\n  \"flat_hp\": 0,\r\n  \"hp_percent\": 0,\r\n  \"flat_def\": 0,\r\n  \"def_percent\": 0,\r\n  \"elemental_mastery\": 0,\r\n  \"energy_recharge\": 0,\r\n  \"crit_rate\": 0,\r\n  \"crit_damage\": 0,\r\n  \"damage_bonus_elemental\": 0,\r\n  \"damage_bonus_all\": 0,\r\n  \"melt_bonus\": 0,\r\n  \"talent_stat\": \"ex: total_attack\",\r\n  \"talent_percent\": 0,\r\n  \"enemy_level\": 0,\r\n  \"affected_element\": \"ex: Cryo\",\r\n  \"resistance_to_damage_element\": 0,\r\n  \"defense_percent_drop\": 0,\r\n  \"bonus_stat_gain\": [\r\n    {\r\n      \"source_stat\": \"ex: total_hp\",\r\n      \"target_stat\": \"ex: Flat Attack\",\r\n      \"source_offset\": 0,\r\n      \"percent_gain\": 0,\r\n      \"max_gain\": 0\r\n    },\r\n    {\r\n      \"source_stat\": \"ex: total_hp\",\r\n      \"target_stat\": \"ex: Flat Attack\",\r\n      \"source_offset\": 0,\r\n      \"percent_gain\": 0,\r\n      \"max_gain\": 0\r\n    }\r\n  ]\r\n}\r\n";
  Json::JsonObject t(x);
  std::cout << "testing\n";
  std::string so = t["bonus_stat_gain"][0]["source_offset"].string_value();
  testEqual(so, (std::string) "0", true);

  Json::JsonObject obj1("{a:b,c:d}");
  Json::JsonObject obj2("{c:d,a:b}");
  testEqual(obj1, obj2, true);

  Json::JsonObject arr1("[{a:b,c:d}, \"asda\"]");
  Json::JsonObject arr2("[{a:b,c:d}, \"asd\"]");
  testEqual(arr1, arr2, false);
}