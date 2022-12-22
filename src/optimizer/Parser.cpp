#include "./Constants/pch.h"
#include "./JSON/JSONObject.cpp"
#include "./Utils/optimize.cpp"

namespace Parser {
Character CreateCharacter(Json::JsonObject& characterJson) {
  std::string characterElement = characterJson["element"].string_value();
  double level = characterJson["level"].double_value();
  // base stats
  double base_attack = characterJson["base_attack"].double_value();
  double base_hp = characterJson["base_hp"].double_value();
  double base_def = characterJson["base_def"].double_value();

  // bonus attack
  double flat_attack = characterJson["flat_attack"].double_value();
  double attack_percent = characterJson["attack_percent"].double_value();

  // bonus hp
  double flat_hp = characterJson["flat_hp"].double_value();
  double hp_percent = characterJson["hp_percent"].double_value();

  // bonus def
  double flat_def = characterJson["flat_def"].double_value();
  double def_percent = characterJson["def_percent"].double_value();

  // dmg bonuses
  double elemental_mastery = characterJson["elemental_mastery"].double_value();
  double energy_recharge = characterJson["energy_recharge"].double_value();
  double crit_rate = characterJson["crit_rate"].double_value();
  double crit_damage = characterJson["crit_damage"].double_value();
  double damage_bonus_elemental = characterJson["damage_bonus_elemental"].double_value();
  double damage_bonus_all = characterJson["damage_bonus_all"].double_value();
  double melt_bonus = characterJson["melt_bonus"].double_value();
  double base_damage_bonus = characterJson["base_damage_bonus"].double_value();
  double defense_shred = characterJson["defense_shred"].double_value();

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
}  // namespace Parser