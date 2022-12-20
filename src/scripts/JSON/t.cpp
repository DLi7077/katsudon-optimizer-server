#include "./JSONObject.cpp"

int main() {
  string x = "{\r\n  \"element\": \"ex: Pyro\",\r\n  \"base_attack\": 0,\r\n  \"base_hp\": 0,\r\n  \"flat_attack\": 0,\r\n  \"attack_percent\": 0,\r\n  \"flat_hp\": 0,\r\n  \"hp_percent\": 0,\r\n  \"flat_def\": 0,\r\n  \"def_percent\": 0,\r\n  \"elemental_mastery\": 0,\r\n  \"energy_recharge\": 0,\r\n  \"crit_rate\": 0,\r\n  \"crit_damage\": 0,\r\n  \"damage_bonus_elemental\": 0,\r\n  \"damage_bonus_all\": 0,\r\n  \"melt_bonus\": 0,\r\n  \"talent_stat\": \"ex: total_attack\",\r\n  \"talent_percent\": 0,\r\n  \"enemy_level\": 0,\r\n  \"affected_element\": \"ex: Cryo\",\r\n  \"resistance_to_damage_element\": 0,\r\n  \"defense_percent_drop\": 0,\r\n  \"bonus_stat_gain\": [\r\n    {\r\n      \"source_stat\": \"ex: total_hp\",\r\n      \"target_stat\": \"ex: Flat Attack\",\r\n      \"source_offset\": 0,\r\n      \"percent_gain\": 0,\r\n      \"max_gain\": 0\r\n    },\r\n    {\r\n      \"source_stat\": \"ex: total_hp\",\r\n      \"target_stat\": \"ex: Flat Attack\",\r\n      \"source_offset\": 0,\r\n      \"percent_gain\": 0,\r\n      \"max_gain\": 0\r\n    }\r\n  ]\r\n}\r\n";
  Json::JsonObject t(x);
  Json::JsonObject test = t["bonus_stat_gain"][0];
  LOG(test);
  return 0;
}