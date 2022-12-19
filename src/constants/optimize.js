const defaultBody = {
  element: "ex: Pyro",
  base_attack: 0,
  base_hp: 0,
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
  damage_bonus_all: 0,
  melt_bonus: 0,

  talent_stat: "ex: total_attack",
  talent_percent: 0,

  enemy_level: 0,
  affected_element: "ex: Cryo",
  resistance_to_damage_element: 0,
  defense_percent_drop: 0,

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
    {
      source_stat: "ex: total_hp",
      target_stat: "ex: Flat Attack",
      source_offset: 0,
      percent_gain: 0,
      max_gain: 0,
    },
  ],
};

export default defaultBody;