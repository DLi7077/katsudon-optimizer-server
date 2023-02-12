import Element from "../constants/Elements";
import { FinalStat, BonusStat } from "../constants/Stats";

// request interfaces
export interface CharacterStats {
  element: Element;
  base_attack: number;
  base_hp: number;
  base_def: number;
  flat_attack: number;
  attack_percent: number;
  hp_percent: number;
  def_percent: number;
  flat_hp: number;
  flat_def: number;
  elemental_mastery: number;
  energy_recharge: number;
  crit_rate: number;
  crit_damage: number;
  damage_bonus_elemental: number;
  damage_bonus_talent: number;
  damage_bonus_all: number;
  melt_bonus: number;
  base_damage_bonus: number;
  defense_shred: number;
  quicken_bonus: number;
}

export interface TalentScaling {
  talent_stat: FinalStat;
  talent_percent: number;
  talent_stat_offset: number;
}

export interface BonusStatGain {
  source_stat: FinalStat;
  target_stat: BonusStat;
  source_offset: number;
  percent_gain: number;
  max_gain: number;
}

export interface StatPreference {
  substats: [
    // at least 5 stats
    BonusStat,
    BonusStat,
    BonusStat,
    BonusStat,
    BonusStat,
    ...BonusStat[]
  ];
  flower_main_stats: [BonusStat]; // only 1
  feather_main_stats: [BonusStat]; // only 1
  sands_main_stats: [BonusStat, ...BonusStat[]]; // at least 1
  goblet_main_stats: [BonusStat, ...BonusStat[]]; // at least 1
  circlet_main_stats: [BonusStat, ...BonusStat[]]; // at least 1
}

export interface CharacterAttributes {
  stats: CharacterStats;
  talent_scalings: TalentScaling[];
  bonus_stat_gain: BonusStatGain[];
  stat_preferences: StatPreference;
}

export interface EnemyAttributes {
  level: number;
  affected_element: Element;
  incoming_damage_element: Element;
  resistance_to_damage_element: number;
  defense_percent_dropped: number;
}

export interface CharacterEnemyRequest {
  character: CharacterAttributes;
  enemy: EnemyAttributes;
  optimize_filter: number;
}

// result interfaces

export interface OptimizedFinalStats {
  level: number;
  total_attack: number;
  flat_attack: number;
  total_defense: number;
  flat_defense: number;
  total_hp: number;
  flat_hp: number;
  energy_recharge: number;
  elemental_mastery: number;
  crit_damage: number;
  crit_rate: number;

  defense_shred: number;
  quicken_bonus: number;
  base_damage_bonus: number;

  damage_bonus_anemo: number;
  damage_bonus_cryo: number;
  damage_bonus_dendro: number;
  damage_bonus_hydro: number;
  damage_bonus_electro: number;
  damage_bonus_physical: number;
  damage_bonus_pyro: number;
  damage_bonus_all: number;
  damage_bonus_talent: number;
}

export interface StatRoll {
  value: number;
  label: BonusStat;
  rolls: number;
}

export interface Artifact {
  substats: StatRoll[];
  main_stat: StatRoll;
  rolls: number;
}

export interface BonusStatResult {
  source_stat: FinalStat;
  target_stat: BonusStat;
  bonus: number;
}

export interface OptimizedCharacterResult {
  artifacts: Artifact[];
  bonuses: BonusStatResult[];
  stats: OptimizedFinalStats;
}

export interface Analysis {
  base_damage_bonus: number;
  base_damage: number;
  dmg_reduced_percent: number;
  melt_vap_multiplier: number;
  resistance_multiplier: number;
  multipliers: number;
  damage_output: number;
}
