import Element from "../constants/Elements";
import { FinalStat, BonusStat } from "../constants/Stats";

export interface CharacterStats {
  element: Element;
  base_attack: number;
  base_hp: number;
  base_def: number;
  flat_attack: number;
  attack_percent: number;
  flat_hp: number;
  hp_percent: number;
  flat_def: number;
  def_percent: number;
  elemental_mastery: number;
  energy_recharge: number;
  crit_rate: number;
  crit_damage: number;
  damage_bonus_elemental: number;
  damage_bonus_all: number;
  melt_bonus: number;
  base_damage_bonus: number;
  defense_shred: number;
  quicken_bonus: number;
}

export interface TalentScaling {
  talent_stat: FinalStat;
  talent_percent: number;
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
  feather_main_stats: BonusStat[]; // only 1
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
}
