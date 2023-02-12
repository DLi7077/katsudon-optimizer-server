import {
  BonusStatGain,
  CharacterStats,
  StatPreference,
  TalentScaling,
} from "interface";
import Element from "./Elements";
import { FinalStat, BonusStat } from "./Stats";

export const DEFAULT_CHARACTER_STATS: CharacterStats = {
  element: "Pyro" as Element,
  base_attack: 0,
  base_hp: 0,
  base_def: 0,
  flat_attack: 0,
  attack_percent: 0,
  flat_hp: 0,
  hp_percent: 0,
  flat_def: 0,
  def_percent: 0,
  elemental_mastery: 0,
  energy_recharge: 0,
  crit_rate: 0,
  crit_damage: 0,
  damage_bonus_elemental: 0,
  damage_bonus_talent: 0,
  damage_bonus_all: 0,
  melt_bonus: 0,
  base_damage_bonus: 0,
  defense_shred: 0,
  quicken_bonus: 0,
};
export const DEFAULT_TALENT_SCALING: TalentScaling[] = [
  {
    talent_stat: "total_attack" as FinalStat,
    talent_percent: 13.473,
    talent_stat_offset: 0,
  },
];
export const DEFAULT_BONUS_STAT_GAINS: BonusStatGain[] = [
  {
    source_stat: "total_hp" as FinalStat,
    target_stat: "Flat Attack" as BonusStat,
    source_offset: 0,
    percent_gain: 0,
    max_gain: 0,
  },
  {
    source_stat: "total_hp" as FinalStat,
    target_stat: "Flat Attack" as BonusStat,
    source_offset: 0,
    percent_gain: 0,
    max_gain: 0,
  },
];
export const DEFAULT_ENEMY_STATS = {
  enemy_level: 0,
  affected_element: "Cryo" as Element,
  resistance_to_damage_element: 0,
  defense_percent_dropped: 0,
};
export const DEFAULT_STAT_PREF: StatPreference = {
  substats: [
    // at least 5 stats
    "Flat Attack" as BonusStat,
    "ATK %" as BonusStat,
    "Elemental Mastery" as BonusStat,
    "Energy Recharge%" as BonusStat,
    "Crit Damage" as BonusStat,
  ],
  flower_main_stats: [
    // only flat hp
    "Flat HP" as BonusStat,
  ],
  feather_main_stats: [
    // only flat atk
    "Flat Attack" as BonusStat,
  ],
  sands_main_stats: [
    // at least 1 stat
    "ATK %" as BonusStat,
    "Energy Recharge%" as BonusStat,
  ],
  goblet_main_stats: [
    // at least 1 stat
    "Electro DMG Bonus%" as BonusStat,
    "ATK %" as BonusStat,
  ],
  circlet_main_stats: [
    // at least 1 stat
    "ATK %" as BonusStat,
    "Crit Damage" as BonusStat,
  ],
};
export const DEFAULT_OPTIMIZE_FILTER = 30;
/*
{
  "character": {
    "level": 90,
    "element": "Electro",
    "base_attack": 945.24,
    "base_hp": 12907,
    "crit_damage": 0.6,
    "flat_attack": 925.28,
    "attack_percent": 1.28,
    "hp_percent": 0,
    "energy_recharge": 237.13,
    "elemental_mastery": 650,
    "damage_bonus_elemental": 0.918,
    "defense_shred": 0.6,
    "talent_scalings": [
      {
        "talent_stat": "total_attack",
        "talent_percent": 13.473
      }
    ],
    "bonus_stat_gain": [
      {
        "source_stat": "energy_recharge",
        "target_stat": "Electro DMG Bonus%",
        "source_offset": 100,
        "percent_gain": 0.004,
        "max_gain": 0
      },
      {
        "source_stat": "energy_recharge",
        "target_stat": "ATK %",
        "source_offset": 100,
        "percent_gain": 0.56,
        "max_gain": 1.20
      },
      {
        "source_stat": "energy_recharge",
        "target_stat": "Other DMG Bonus%",
        "source_offset": 0,
        "percent_gain": 0.25,
        "max_gain": 0.75
      }
    ]
  },
  "enemy": {
    "level": 90,
    "affected_element": "Dendro",
    "incoming_damage_element": "Electro",
    "resistance_to_damage_element": -1.2,
    "defense_percent_dropped": 0.3
  }
}
*/
