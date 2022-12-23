#include "./Constants/pch.h"
#include "./JSON/JSONObject.cpp"
#include "./Utils/optimize.cpp"

namespace Parser {
Character CreateCharacter(Json::JsonObject& characterJson) {
  Json::JsonObject stats = characterJson["stats"];
  std::string characterElement = stats["element"].string_value();
  double level = stats["level"].double_value();
  // base stats
  double base_attack = stats["base_attack"].double_value();
  double base_hp = stats["base_hp"].double_value();
  double base_def = stats["base_def"].double_value();

  // bonus attack
  double flat_attack = stats["flat_attack"].double_value();
  double attack_percent = stats["attack_percent"].double_value();

  // bonus hp
  double flat_hp = stats["flat_hp"].double_value();
  double hp_percent = stats["hp_percent"].double_value();

  // bonus def
  double flat_def = stats["flat_def"].double_value();
  double def_percent = stats["def_percent"].double_value();

  // dmg bonuses
  double energy_recharge = stats["energy_recharge"].double_value();
  double elemental_mastery = stats["elemental_mastery"].double_value();
  double crit_rate = stats["crit_rate"].double_value();
  double crit_damage = stats["crit_damage"].double_value();
  double damage_bonus_elemental = stats["damage_bonus_elemental"].double_value();
  double damage_bonus_all = stats["damage_bonus_all"].double_value();
  double melt_bonus = stats["melt_bonus"].double_value();
  double base_damage_bonus = stats["base_damage_bonus"].double_value();
  double defense_shred = stats["defense_shred"].double_value();
  double quicken_bonus = stats["quicken_bonus"].double_value();

  Character character(characterElement);
  character.setLevel(level);

  character.setStat(BASE_ATK, base_attack);
  character.setStat(BASE_HP, base_hp);
  character.setStat(BASE_DEFENSE, base_def);

  character.setStat(FLAT_ATK, flat_attack);
  character.setStat(ATK_PERCENT, attack_percent);
  character.setStat(FLAT_HP, flat_hp);

  character.setStat(HP_PERCENT, hp_percent);
  character.setStat(FLAT_DEF, flat_def);
  character.setStat(DEF_PERCENT, def_percent);

  character.setStat(ELEMENTAL_MASTERY, elemental_mastery);
  character.setStat(ENERGY_RECHARGE, energy_recharge);

  character.setStat(CRIT_RATE, crit_rate);
  character.setStat(CRIT_DAMAGE, DEFAULT_CRIT_DAMAGE + crit_damage);

  character.setDamageBonus(characterElement, damage_bonus_elemental);
  character.setDamageBonus(ALL, damage_bonus_all);  // other dmg bonus
  character.setStat("base_damage_bonus", base_damage_bonus);
  character.setStat("defense_shred", defense_shred);
  character.setStat("quicken_bonus", quicken_bonus);

  character.setStat(MELT_BONUS, melt_bonus);

  // add talent scalings

  std::vector<Json::JsonObject> talentScalings = characterJson["talent_scalings"].array_value();
  for (Json::JsonObject& scaling : talentScalings) {
    std::string talent_stat = scaling["talent_stat"].string_value();
    double talent_percent = scaling["talent_percent"].double_value();
    Attributes::TalentScaling scalingInstance(talent_stat, talent_percent);
    character.addTalentScaling(scalingInstance);
  }

  // add bonuses
  std::vector<Json::JsonObject> bonusStatGains = characterJson["bonus_stat_gain"].array_value();
  for (Json::JsonObject& bonusStatGain : bonusStatGains) {
    std::string source_stat = bonusStatGain["source_stat"].string_value();
    std::string target_stat = bonusStatGain["target_stat"].string_value();
    double source_offset = bonusStatGain["source_offset"].double_value();
    double percent_gain = bonusStatGain["percent_gain"].double_value();
    double max_gain = bonusStatGain["max_gain"].double_value();

    Attributes::BonusStatGain statGain(
        source_stat,
        target_stat,
        source_offset,
        percent_gain,
        max_gain);

    character.addBonusStatGain(statGain);
  }

  return character;
}

Enemy CreateEnemy(Json::JsonObject& enemyJson) {
  std::string affected_element = enemyJson["affected_element"].string_value();
  std::string incoming_damage_element = enemyJson["incoming_damage_element"].string_value();
  double enemy_level = enemyJson["level"].double_value();
  double resistance_to_damage_element = enemyJson["resistance_to_damage_element"].double_value();
  double defense_percent_dropped = enemyJson["defense_percent_dropped"].double_value();

  Enemy enemy;
  enemy.setLevel(enemy_level);
  enemy.setAffectedElement(affected_element);
  enemy.setResistance(incoming_damage_element, resistance_to_damage_element);
  enemy.setDefensePercentDropped(defense_percent_dropped);
  return enemy;
}

Initial::StatPreference CreateStatPreferences(Json::JsonObject& preferenceJson) {
  Initial::StatPreference result;
  std::vector<Json::JsonObject> substats = preferenceJson["substats"].array_value();
  std::vector<Json::JsonObject> flower_main_stats = preferenceJson["flower_main_stats"].array_value();
  std::vector<Json::JsonObject> feather_main_stats = preferenceJson["feather_main_stats"].array_value();
  std::vector<Json::JsonObject> sands_main_stats = preferenceJson["sands_main_stats"].array_value();
  std::vector<Json::JsonObject> goblet_main_stats = preferenceJson["goblet_main_stats"].array_value();
  std::vector<Json::JsonObject> circlet_main_stats = preferenceJson["circlet_main_stats"].array_value();

  for (Json::JsonObject& substat : substats) {
    result.substat_preferences_.push_back(substat.string_value());
  }
  for (Json::JsonObject& main_stat : flower_main_stats) {
    result.flower_main_stats_.push_back(main_stat.string_value());
  }
  for (Json::JsonObject& main_stat : feather_main_stats) {
    result.feather_main_stats_.push_back(main_stat.string_value());
  }
  for (Json::JsonObject& main_stat : sands_main_stats) {
    result.sands_main_stats_.push_back(main_stat.string_value());
  }
  for (Json::JsonObject& main_stat : goblet_main_stats) {
    result.goblet_main_stats_.push_back(main_stat.string_value());
  }
  for (Json::JsonObject& main_stat : circlet_main_stats) {
    result.circlet_main_stats_.push_back(main_stat.string_value());
  }

  return result;
}
}  // namespace Parser