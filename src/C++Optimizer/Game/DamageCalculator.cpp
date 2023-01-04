#include "../Constants/constants.h"
#include "../Constants/pch.h"
#include "./Character/Character.h"
#include "./Enemy.h"

struct DamageOutput {
  double skill_damage;
  double burst_damage;
};

namespace Calculator {
/*
(BASE_DAMAGE + BONUS_BASE_DMG) *
(CRIT DMG) * (DMG BONUS) * MELT? * ENEMY_DMG_REDUCE * ENEMY_RESISTANCE
*/
double baseDamage(Character& character) {
  double baseDamage = 0;
  for (const Attributes::TalentScaling& talentScaling : character.getTalentScalings()) {
    double damageInstance = character.getStat(talentScaling.source_stat_) * talentScaling.stat_scaling_;
    baseDamage += damageInstance;
  }

  return baseDamage + character.getStat("base_damage_bonus");
}

double bonusMultipliers(Character& character) {
  double dmg_bonus = character.getDMGBonus(character.getDamageElement());
  double dmg_bonus_all = character.getDMGBonus(ALL);
  double dmg_bonus_talent = character.getDMGBonus(TALENT);
  double crit_dmg = character.getStat("crit_damage");

  return (1 + dmg_bonus + dmg_bonus_all + dmg_bonus_talent) * (1 + crit_dmg);
}

// TODO: add crimson witch buffs
double meltBonus(Character& character, Enemy& enemy) {
  double EM = character.getStat("elemental_mastery");
  std::string dmgElement = character.getDamageElement();
  std::string enemyElement = enemy.getAffectedElement();
  double reactionBonus = (1 + (2.78 * (EM / (EM + 1400))));
  double meltBonus = character.getStat(MELT_BONUS);

  double multiplier = 1;
  if (dmgElement == PYRO && enemyElement == CRYO)
    multiplier = 2 * (reactionBonus + meltBonus);
  else if (dmgElement == CRYO && enemyElement == PYRO)
    multiplier = 1.5 * (reactionBonus + meltBonus);
  else if (dmgElement == HYDRO && enemyElement == PYRO)
    multiplier = 2 * (reactionBonus + meltBonus);
  else if (dmgElement == PYRO && enemyElement == HYDRO)
    multiplier = 1.5 * (reactionBonus + meltBonus);

  return multiplier;
}

double quickenBonusMultiplier(int elementalMastery) {
  return 5 * elementalMastery / double(elementalMastery + 1200);
}

// https://genshin-impact.fandom.com/wiki/Damage#Catalyze_Damage_Bonus
double quickenDamageBonus(Character& character, Enemy& enemy) {
  bool DendroOnElectro = character.getDamageElement() == DENDRO && enemy.getAffectedElement() == ELECTRO;
  bool ElectroOnDendro = character.getDamageElement() == ELECTRO && enemy.getAffectedElement() == DENDRO;

  if (!DendroOnElectro && !ElectroOnDendro) return 0;

  double quicken_em_multiplier = quickenBonusMultiplier(character.getStat("elemental_mastery"));
  double quicken_bonus = character.getStat("quicken_bonus");
  double quicken_reaction_multiplier = DendroOnElectro ? 1.25 : 1.15;
  double quicken_base_damage = Constants::character_quicken_base[character.getLevel()];

  return (1 + quicken_em_multiplier + quicken_bonus) * quicken_reaction_multiplier * quicken_base_damage;
}

// https://library.keqingmains.com/combat-mechanics/damage/damage-formula#enemy-defense
double damageReductionByDefense(Character& character, Enemy& enemy) {
  int characterLevel = character.getLevel();
  int enemyLevel = enemy.getLevel();

  double defensePercentDropped = enemy.getDefensePercentDropped();
  double defensePercentIgnored = character.getStat("defense_shred");
  double reducedDefense = (enemyLevel + 100) * (1 - defensePercentDropped) * (1 - defensePercentIgnored);

  double DMGReduction = (characterLevel + 100) / (characterLevel + 100 + reducedDefense);

  return DMGReduction;
}

double enemyElementResistance(Character& character, Enemy& enemy) {
  std::string& damageElement = character.getDamageElement();
  double resistance = enemy.getResistance(damageElement);

  if (resistance < 0) {
    return 1 - (resistance / 2);
  }
  if (resistance >= 0.75) {
    return 1 / (4 * resistance + 1);
  }
  return 1 - resistance;
}

double damageOutput(Character& character, Enemy& enemy) {
  // create copy character to apply stat gains
  Character finalized = character;
  finalized.applyStatGains();

  double baseDamageBonus = quickenDamageBonus(finalized, enemy) + character.getStat("base_damage_bonus");

  double baseDMG = baseDamage(finalized) + baseDamageBonus;
  double multipliers = bonusMultipliers(finalized);
  double DMGReducedPercent = damageReductionByDefense(finalized, enemy);
  double resistanceMultiplier = enemyElementResistance(finalized, enemy);
  double meltVapMultiplier = meltBonus(finalized, enemy);

  return baseDMG *
         multipliers *
         DMGReducedPercent *
         resistanceMultiplier *
         meltVapMultiplier;
}

Json::JsonObject toJson(Character& character, Enemy& enemy) {
  Character finalized = character;
  finalized.applyStatGains();

  double baseDamageBonus = quickenDamageBonus(finalized, enemy) + finalized.getStat("base_damage_bonus");

  double baseDMG = baseDamage(finalized) + baseDamageBonus;
  double multipliers = bonusMultipliers(finalized);
  double DMGReducedPercent = damageReductionByDefense(finalized, enemy);
  double resistanceMultiplier = enemyElementResistance(finalized, enemy);
  double meltVapMultiplier = meltBonus(finalized, enemy);

  double damageOutput = baseDMG *
                        multipliers *
                        DMGReducedPercent *
                        resistanceMultiplier *
                        meltVapMultiplier;

  Json::JsonObject analysis;
  analysis["base_damage"] = Json::JsonObject(baseDamage(finalized));
  analysis["base_damage_bonus"] = Json::JsonObject(baseDamageBonus);
  analysis["multipliers"] = Json::JsonObject(multipliers);
  analysis["dmg_reduced_percent"] = Json::JsonObject(DMGReducedPercent);
  analysis["resistance_multiplier"] = Json::JsonObject(resistanceMultiplier);
  analysis["melt_vap_multiplier"] = Json::JsonObject(meltVapMultiplier);
  analysis["damage_output"] = Json::JsonObject(damageOutput);

  Json::JsonObject result;
  result["character"] = finalized.toJSON();
  result["analysis"] = analysis;
  return result;
}

}  // namespace Calculator