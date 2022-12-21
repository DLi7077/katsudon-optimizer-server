#include "./Constants/pch.h"
#include "./JSON/JSONObject.cpp"
#include "./Utils/optimize.cpp"

using namespace std;

int main(int argc, char** argv) {
  if (argc == 1) {
    cout << "{ Usage: " << argv[0] << " json input ";
    return 0;
  }

  std::string arg1 = argv[1];

  Json::JsonObject input(arg1);

  std::string characterElement = input["element"].string_value();
  double base_attack = input["base_attack"].double_value();
  double base_hp = input["base_hp"].double_value();
  double base_def = input["base_def"].double_value();

  double flat_attack = input["flat_attack"].double_value();
  double attack_percent = input["attack_percent"].double_value();

  double flat_hp = input["flat_hp"].double_value();
  double hp_percent = input["hp_percent"].double_value();

  double flat_def = input["flat_def"].double_value();
  double def_percent = input["def_percent"].double_value();
  double elemental_mastery = input["elemental_mastery"].double_value();
  double energy_recharge = input["energy_recharge"].double_value();
  double crit_rate = input["crit_rate"].double_value();
  double crit_damage = input["crit_damage"].double_value();
  double damage_bonus_elemental = input["damage_bonus_elemental"].double_value();
  double damage_bonus_all = input["damage_bonus_all"].double_value();
  double melt_bonus = input["melt_bonus"].double_value();

  Character character(characterElement);
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

  character.setStat(MELT_BONUS, melt_bonus);

  character.setTalentDetails(BURST, "total_attack", 9.86);

  Enemy enemy;
  enemy.setAffectedElement(PYRO);
  enemy.setLevel(90);
  enemy.setResistance(PYRO, -1.8);

  Optimize::optimize(character, enemy);

  /**
   * TODO:
   * Parse input to unordered_map representing JSON
   * Pass unordered_map into optimizer
   * Optimizer returns a JSON representation of the result
   * Print out JSON result
   */

  return 0;
}