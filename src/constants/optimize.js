export const DEFAULT_CHARACTER_STATS = {
  element: "Pyro",
  base_attack: 0.34,
  base_hp: 0,
  base_def: 0,
  flat_attack: 100000,
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
  damage_bonus_all: 0,
  melt_bonus: 0,
  base_damage_bonus: 0,
  defense_shred: 0,
  quicken_bonus: 0,

  talent_stat: "total_attack",
  talent_percent: 0,
  bonus_stat_gain: [
    {
      source_stat: "ex: total_hp",
      target_stat: "ex: Flat Attack",
      source_offset: 0,
      percent_gain: 0,
      max_gain: 0,
    },
    {
      source_stat: "ex: total_hp",
      target_stat: "ex: Flat Attack",
      source_offset: 0,
      percent_gain: 0,
      max_gain: 0,
    },
  ],
};

export const DEFAULT_ENEMY_STATS = {
  enemy_level: 0,
  affected_element: "ex: Cryo",
  resistance_to_damage_element: 0,
  defense_percent_dropped: 0,
};
