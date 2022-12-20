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
  double flatATK = std::stod(argv[2]);

  Json::JsonObject input(arg1);
  LOG(input);

  Character character(PYRO);
  character.setStat(BASE_ATK, 700);
  character.setStat(CRIT_DAMAGE, DEFAULT_CRIT_DAMAGE + .1);
  character.setStat(FLAT_ATK, flatATK);
  character.setStat(ATK_PERCENT, 46.6);
  character.setStat(FLAT_HP, 311);
  character.setStat(HP_PERCENT, 46.6);
  character.setStat(FLAT_DEF, 311);
  character.setStat(DEF_PERCENT, 46.6);
  character.setStat(ELEMENTAL_MASTERY, 238);
  character.setStat(ENERGY_RECHARGE, 2.0);
  character.setStat(MELT_BONUS, .15);
  
  character.setStat(BASE_ATK, 700);
  character.setStat(CRIT_DAMAGE, DEFAULT_CRIT_DAMAGE + .1);
  character.setStat(FLAT_ATK, flatATK);
  character.setStat(ATK_PERCENT, 46.6);
  character.setStat(FLAT_HP, 311);
  character.setStat(HP_PERCENT, 46.6);
  character.setStat(FLAT_DEF, 311);
  character.setStat(DEF_PERCENT, 46.6);
  character.setStat(ELEMENTAL_MASTERY, 238);
  character.setStat(ENERGY_RECHARGE, 2.0);
  character.setStat(MELT_BONUS, .15);

  character.setTalentDetails(BURST, "total_attack", 9.86);

  character.setDamageBonus(PYRO, .466);
  character.setDamageBonus(ALL, .5);

  Enemy enemy;
  enemy.setAffectedElement(PYRO);
  enemy.setLevel(90);
  enemy.setResistance(PYRO, -1.8);

  // Optimize::optimize(character, enemy);

  /**
   * TODO:
   * Parse input to unordered_map representing JSON
   * Pass unordered_map into optimizer
   * Optimizer returns a JSON representation of the result
   * Print out JSON result
   */

  return 0;
}