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
  double crit_dmg = character.getStat("crit_damage");

  return (1 + dmg_bonus + dmg_bonus_all) * (1 + crit_dmg);
}

// TODO: add crimson witch buffs
double meltBonus(Character& character, Enemy& enemy) {
  double EM = character.getStat("elemental_mastery");
  std::string dmgElement = character.getDamageElement();
  std::string enemyElement = enemy.getAffectedElement();
  double reactionBonus = (1 + (2.78 * (EM / (EM + 1400))));
  double meltBonus = character.getStat(MELT_BONUS);

  // std::cout << "Reaction Bonus:\t" << reactionBonus << '\n';
  // std::cout << "melt Bonus:\t" << meltBonus << '\n';

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

// https://library.keqingmains.com/combat-mechanics/damage/damage-formula#enemy-defense
double damageReductionByDefense(Character& character, Enemy& enemy) {
  int characterLevel = character.getLevel();
  int enemyLevel = enemy.getLevel();

  // TODO: add defense shred
  double enemyDefense = enemyLevel + 100;
  double defensePercentDropped = enemy.getDefensePercentDropped();
  double defensePercentIgnored = character.getStat("defense_shred");

  double reducedDefense = enemyDefense * (1 - defensePercentDropped) * (1 - defensePercentIgnored);

  double DMGReduction = (characterLevel + 100) / ((characterLevel + 100) + reducedDefense);

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

  double baseDMG = baseDamage(finalized);
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

}  // namespace Calculator