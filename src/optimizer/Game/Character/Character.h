#pragma once
#include "../../Constants/constants.h"
#include "../../Constants/pch.h"
#include "../Artifact/artifact.h"
#include "./Attributes.h"

#define CHARACTER_LEVEL "level"
#define MELT_BONUS "Melt Bonus"

#define DEFAULT_ELEMENT PYRO
#define DEFAULT_CHARACTER_LEVEL 90
#define DEFAULT_BASE_ATK 800
#define DEFAULT_BASE_HP 10000
#define DEFAULT_BASE_DEF 200
#define DEFAULT_CRIT_DAMAGE .5

using TalentScalingStat = std::unordered_map<std::string, std::string>;
using TalentDMGPercent = std::unordered_map<std::string, double>;

class Character {
 private:
  int character_level_ = DEFAULT_CHARACTER_LEVEL;
  std::unordered_map<std::string, double> stats_;
  std::unordered_map<std::string, double> damage_bonus_;
  std::unordered_map<std::string, double> final_stats_;
  std::vector<Artifact> artifact_set_;
  std::string damage_element_ = DEFAULT_ELEMENT;
  std::vector<Attributes::TalentScaling> talent_scalings_;
  std::vector<Attributes::BonusStatGain> bonus_stat_gains_;

  double damage_ceiling_ = 0;

  void InitCharacterStats() {
    stats_[BASE_ATK] = DEFAULT_BASE_ATK;
    stats_[BASE_HP] = DEFAULT_BASE_HP;
    stats_[BASE_DEFENSE] = DEFAULT_BASE_DEF;
    stats_[ATK_PERCENT] = 0;
    stats_[HP_PERCENT] = 0;
    stats_[DEF_PERCENT] = 0;
    stats_[FLAT_ATK] = 0;
    stats_[FLAT_HP] = 0;
    stats_[FLAT_DEF] = 0;
    stats_[ELEMENTAL_MASTERY] = 0;
    stats_[ENERGY_RECHARGE] = 1;
    stats_[CRIT_RATE] = .05;
    stats_[CRIT_DAMAGE] = DEFAULT_CRIT_DAMAGE;
    stats_[MELT_BONUS] = 0;
  }

  void InitCharacterDamageBonus() {
    damage_bonus_[ANEMO] = 0;
    damage_bonus_[CRYO] = 0;
    damage_bonus_[DENDRO] = 0;
    damage_bonus_[ELECTRO] = 0;
    damage_bonus_[HYDRO] = 0;
    damage_bonus_[PYRO] = 0;
    damage_bonus_[PHYSICAL] = 0;
    damage_bonus_[ALL] = 0;
  }

  // update final stats on stat change
  void updateStatModel() {
    final_stats_["total_attack"] = stats_[BASE_ATK] * (1 + stats_[ATK_PERCENT]) + stats_[FLAT_ATK];
    final_stats_["total_hp"] = stats_[BASE_HP] * (1 + stats_[HP_PERCENT]) + stats_[FLAT_HP];
    final_stats_["total_defense"] = stats_[BASE_DEFENSE] * (1 + stats_[DEF_PERCENT]) + stats_[FLAT_DEF];
    final_stats_["elemental_mastery"] = stats_[ELEMENTAL_MASTERY];
    final_stats_["energy_recharge"] = stats_[ENERGY_RECHARGE];
    final_stats_["crit_rate"] = stats_[CRIT_RATE];
    final_stats_[MELT_BONUS] = stats_[MELT_BONUS];
    final_stats_["crit_damage"] = stats_[CRIT_DAMAGE];
    final_stats_["damage_bonus_anemo"] = damage_bonus_[ANEMO];
    final_stats_["damage_bonus_cryo"] = damage_bonus_[CRYO];
    final_stats_["damage_bonus_dendro"] = damage_bonus_[DENDRO];
    final_stats_["damage_bonus_electro"] = damage_bonus_[ELECTRO];
    final_stats_["damage_bonus_hydro"] = damage_bonus_[HYDRO];
    final_stats_["damage_bonus_pyro"] = damage_bonus_[PYRO];
    final_stats_["damage_bonus_physical"] = damage_bonus_[PHYSICAL];
    final_stats_["damage_bonus_all"] = damage_bonus_[ALL];
  }

  bool validFinalStat(std::string statLabel) {
    static std::vector<std::string> validStats = {
        "total_attack",
        "total_hp",
        "total_defense",
        "elemental_mastery",
        "energy_recharge",
        "crit_rate",
        "crit_damage",
        "damage_bonus_anemo",
        "damage_bonus_cryo",
        "damage_bonus_dendro",
        "damage_bonus_electro",
        "damage_bonus_hydro",
        "damage_bonus_pyro",
        "damage_bonus_physical",
        "damage_bonus_all",
        "base_damage_bonus",
        "defense_shred",
        "quicken_bonus",
        MELT_BONUS,
    };
    for (const std::string& stat : validStats) {
      if (statLabel == stat) return true;
    }

    return false;
  }

  bool isDmgBonus(std::string& label) {
    if (label == ANEMO_DAMAGE_BONUS) return true;
    if (label == CRYO_DAMAGE_BONUS) return true;
    if (label == DENDRO_DAMAGE_BONUS) return true;
    if (label == ELECTRO_DAMAGE_BONUS) return true;
    if (label == HYDRO_DAMAGE_BONUS) return true;
    if (label == PYRO_DAMAGE_BONUS) return true;
    if (label == PHYSICAL_DAMAGE_BONUS) return true;
    if (label == OTHER_DAMAGE_BONUS) return true;

    return false;
  }

  // changes elemental_damage_bonus to the element
  // if not damage bonus, returns the label
  std::string labelCastToElement(std::string& label) {
    if (label == ANEMO_DAMAGE_BONUS) return ANEMO;
    if (label == CRYO_DAMAGE_BONUS) return CRYO;
    if (label == DENDRO_DAMAGE_BONUS) return DENDRO;
    if (label == ELECTRO_DAMAGE_BONUS) return ELECTRO;
    if (label == HYDRO_DAMAGE_BONUS) return HYDRO;
    if (label == PYRO_DAMAGE_BONUS) return PYRO;
    if (label == PHYSICAL_DAMAGE_BONUS) return PHYSICAL;
    if (label == OTHER_DAMAGE_BONUS) return ALL;

    return label;
  }

 public:
  // default
  Character() {
    damage_element_ = "";
    InitCharacterStats();
    InitCharacterDamageBonus();
    updateStatModel();
  }

  // one-param
  Character(std::string damage_element) {
    damage_element_ = damage_element;
    InitCharacterStats();
    InitCharacterDamageBonus();
    updateStatModel();
  }

  // copy-construct
  Character(const Character& rhs) {
    character_level_ = rhs.character_level_;
    stats_ = rhs.stats_;
    damage_bonus_ = rhs.damage_bonus_;
    final_stats_ = rhs.stats_;
    damage_element_ = rhs.damage_element_;
    artifact_set_ = rhs.artifact_set_;
    bonus_stat_gains_ = rhs.bonus_stat_gains_;
    talent_scalings_ = rhs.talent_scalings_;

    updateStatModel();
  }

  // copy assign
  Character operator=(const Character& rhs) {
    Character copy = rhs;
    std::swap(*this, copy);
    updateStatModel();

    return *this;
  }

  // move construct
  Character(Character&& rhs) {
    character_level_ = std::move(rhs.character_level_);
    stats_ = std::move(rhs.stats_);
    damage_bonus_ = std::move(rhs.damage_bonus_);
    final_stats_ = std::move(rhs.stats_);
    damage_element_ = std::move(rhs.damage_element_);
    talent_scalings_ = std::move(rhs.talent_scalings_);
    artifact_set_ = std::move(rhs.artifact_set_);
    bonus_stat_gains_ = std::move(rhs.bonus_stat_gains_);

    updateStatModel();
  }

  // move assign
  Character& operator=(Character&& rhs) {
    std::swap(character_level_, rhs.character_level_);
    std::swap(stats_, rhs.stats_);
    std::swap(damage_bonus_, rhs.damage_bonus_);
    std::swap(final_stats_, rhs.stats_);
    std::swap(damage_element_, rhs.damage_element_);
    std::swap(talent_scalings_, rhs.talent_scalings_);
    std::swap(artifact_set_, rhs.artifact_set_);
    std::swap(bonus_stat_gains_, rhs.bonus_stat_gains_);

    updateStatModel();

    return *this;
  }

  // destructor
  ~Character() = default;

  int getLevel() {
    return character_level_;
  }

  double getDamageCeiling() {
    return damage_ceiling_;
  }

  std::string& getDamageElement() {
    return damage_element_;
  }
  // retrieve info from complete built
  double getStat(std::string label) {
    if (!validFinalStat(label)) {
      std::cout << label << " is not a valid stat\n";
      abort();
    }
    return final_stats_[label];
  }

  double getDMGBonus(std::string label) {
    return damage_bonus_[label];
  }

  const std::unordered_map<std::string, double>& finalStats() {
    return final_stats_;
  }

  std::vector<Artifact> getArtifacts() {
    return artifact_set_;
  }

  const std::vector<Attributes::TalentScaling>& getTalentScalings() const {
    return talent_scalings_;
  }

  const std::vector<Attributes::BonusStatGain>& getBonusStatGains() {
    return bonus_stat_gains_;
  }

  void setLevel(int level) {
    character_level_ = level;
  }

  void setDamageCeiling(double dmg) {
    damage_ceiling_ = dmg;
  }
  // modify base stats
  void setStat(std::string label, double value) {
    stats_[label] = value;
    updateStatModel();
  }

  void setDamageBonus(std::string label, double value) {
    damage_bonus_[label] = value;
    updateStatModel();
  }

  void addArtifact(Artifact& artifact) {
    artifact_set_.push_back(artifact);

    Stat mainStat = artifact.mainStat();
    std::string mainLabel = mainStat.label();
    std::unordered_map<std::string, double>& stats = isDmgBonus(mainLabel) ? damage_bonus_ : stats_;
    mainLabel = labelCastToElement(mainStat.label());

    stats[mainLabel] += mainStat.value();

    for (size_t i = 0; i < artifact.size(); i++) {
      std::string statLabel = artifact[i].label();
      stats_[statLabel] += artifact[i].value();
    }

    updateStatModel();
  }

  void removeArtifact(Artifact& artifact) {
    Stat mainStat = artifact.mainStat();
    std::string mainLabel = mainStat.label();
    std::unordered_map<std::string, double>& stats = isDmgBonus(mainLabel) ? damage_bonus_ : stats_;
    mainLabel = labelCastToElement(mainStat.label());

    stats[mainLabel] -= mainStat.value();

    for (size_t i = 0; i < artifact.size(); i++) {
      std::string statLabel = artifact[i].label();

      stats[statLabel] -= artifact[i].value();
    }

    updateStatModel();
  }

  void addTalentScaling(Attributes::TalentScaling& talentScaling) {
    talent_scalings_.push_back(talentScaling);
  }

  // stat gain bonus like hutao e and 4pc emblem
  void addBonusStatGain(Attributes::BonusStatGain bonus) {
    bonus_stat_gains_.push_back(bonus);
  }

  void applyStatGains() {
    for (const Attributes::BonusStatGain& bonus : bonus_stat_gains_) {
      double sourceValue = getStat(bonus.source_stat_);
      double bonusValue = (sourceValue - bonus.source_offset_) * bonus.percent_gain_;
      double cappedBonus = (bonus.max_gain_ == 0) ? bonusValue : std::min(bonus.max_gain_, bonusValue);

      std::string targetStat = bonus.target_stat_;
      // LOG_LINE("cast " << targetStat << " to " << labelCastToElement(targetStat));
      if (isDmgBonus(targetStat)) {
        targetStat = labelCastToElement(targetStat);
        setDamageBonus(targetStat, damage_bonus_[targetStat] + cappedBonus);
      }

      else {
        setStat(targetStat, stats_[targetStat] + cappedBonus);
      }
    }

    updateStatModel();
  }

  friend std::ostream& operator<<(std::ostream& out, Character& rhs) {
    out << "Character Level:\t" << rhs.character_level_ << "\n";
    out << "Base FLAT_ATK:\t\t" << rhs.stats_[BASE_ATK] << "\n";
    out << "ATK\t\t\t" << rhs.final_stats_["total_attack"] << "\n";
    out << "MAX HP:\t\t\t" << rhs.final_stats_["total_hp"] << "\n";
    out << "DEF:\t\t\t" << rhs.final_stats_["total_defense"] << "\n";
    out << "Elemental Mastery:\t" << rhs.final_stats_["elemental_mastery"] << "\n";
    out << "Energy Recharge:\t" << rhs.final_stats_["energy_recharge"] * 100 << "%\n";
    out << "Crit Rate:\t\t" << rhs.final_stats_["crit_rate"] * 100 << "%\n";
    out << "Crit Damage:\t\t" << rhs.final_stats_["crit_damage"] * 100 << "%\n";
    out << "Anemo DMG Bonus:\t" << rhs.final_stats_["damage_bonus_anemo"] * 100 << "%\n";
    out << "Cryo DMG Bonus: \t" << rhs.final_stats_["damage_bonus_cryo"] * 100 << "%\n";
    out << "Dendro DMG Bonus:\t" << rhs.final_stats_["damage_bonus_dendro"] * 100 << "%\n";
    out << "Electro DMG Bonus:\t" << rhs.final_stats_["damage_bonus_electro"] * 100 << "%\n";
    out << "Hydro DMG Bonus:\t" << rhs.final_stats_["damage_bonus_hydro"] * 100 << "%\n";
    out << "Pyro DMG Bonus: \t" << rhs.final_stats_["damage_bonus_pyro"] * 100 << "%\n";
    out << "Physical DMG Bonus:\t" << rhs.final_stats_["damage_bonus_physical"] * 100 << "%\n";
    out << "Other DMG Bonus:\t" << rhs.final_stats_["damage_bonus_all"] * 100 << "%\n";
    out << std::string(30, '-') << "\n";

    return out;
  }

  Json::JsonObject toJSON() {
    Json::JsonObject character;
    Json::JsonObject stats;
    stats["level"] = Json::JsonObject(character_level_);
    stats["total_attack"] = Json::JsonObject(final_stats_["total_attack"]);
    stats["total_hp"] = Json::JsonObject(final_stats_["total_hp"]);
    stats["total_defense"] = Json::JsonObject(final_stats_["total_defense"]);

    stats["elemental_mastery"] = Json::JsonObject(final_stats_["elemental_mastery"]);
    stats["energy_recharge"] = Json::JsonObject(final_stats_["energy_recharge"]);
    stats["crit_rate"] = Json::JsonObject(final_stats_["crit_rate"]);
    stats["crit_damage"] = Json::JsonObject(final_stats_["crit_damage"]);

    stats["damage_bonus_anemo"] = Json::JsonObject(final_stats_["damage_bonus_anemo"]);
    stats["damage_bonus_cryo"] = Json::JsonObject(final_stats_["damage_bonus_cryo"]);
    stats["damage_bonus_dendro"] = Json::JsonObject(final_stats_["damage_bonus_dendro"]);
    stats["damage_bonus_electro"] = Json::JsonObject(final_stats_["damage_bonus_electro"]);
    stats["damage_bonus_hydro"] = Json::JsonObject(final_stats_["damage_bonus_hydro"]);
    stats["damage_bonus_pyro"] = Json::JsonObject(final_stats_["damage_bonus_pyro"]);
    stats["damage_bonus_physical"] = Json::JsonObject(final_stats_["damage_bonus_physical"]);
    stats["damage_bonus_all"] = Json::JsonObject(final_stats_["damage_bonus_all"]);
    stats["base_damage_bonus"] = Json::JsonObject(final_stats_["base_damage_bonus"]);
    stats["defense_shred"] = Json::JsonObject(final_stats_["defense_shred"]);

    Json::JsonObject statBonuses = Json::JsonObject(Json::TYPE::ARRAY);
    for (Attributes::BonusStatGain& bonus : bonus_stat_gains_) {
      Json::JsonObject stat_gain;
      double sourceValue = getStat(bonus.source_stat_);
      double bonusValue = (sourceValue - bonus.source_offset_) * bonus.percent_gain_;
      double cappedBonus = (bonus.max_gain_ == 0) ? bonusValue : std::min(bonus.max_gain_, bonusValue);

      stat_gain["source_stat"] = Json::JsonObject(Json::TYPE::STRING, bonus.source_stat_);
      stat_gain["target_stat"] = Json::JsonObject(Json::TYPE::STRING, bonus.target_stat_);
      stat_gain["bonus"] = Json::JsonObject(cappedBonus);
      statBonuses.push_back(stat_gain);
    }

    character["damage_ceiling"] = Json::JsonObject(damage_ceiling_);
    character["stats"] = stats;
    character["bonuses"] = statBonuses;
    character["artifacts"] = Json::JsonObject(Json::TYPE::ARRAY);
    for (Artifact& artifact : artifact_set_) {
      character["artifacts"].push_back(artifact.toJSON());
    }

    return character;
  }
};
