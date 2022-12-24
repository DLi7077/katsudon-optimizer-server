enum FINAL_STATS {
  TOTAL_ATTACK = "total_attack",
  TOTAL_HP = "total_hp",
  TOTAL_DEFENSE = "total_defense",
  ELEMENTAL_MASTERY = "elemental_mastery",
  ENERGY_RECHARGE = "energy_recharge",
  CRIT_RATE = "crit_rate",
  CRIT_DAMAGE = "crit_damage",
  DAMAGE_BONUS_ANEMO = "damage_bonus_anemo",
  DAMAGE_BONUS_CRYO = "damage_bonus_cryo",
  DAMAGE_BONUS_DENDRO = "damage_bonus_dendro",
  DAMAGE_BONUS_ELECTRO = "damage_bonus_electro",
  DAMAGE_BONUS_GEO = "damage_bonus_geo",
  DAMAGE_BONUS_HYDRO = "damage_bonus_hydro",
  DAMAGE_BONUS_PYRO = "damage_bonus_pyro",
  DAMAGE_BONUS_PHYSICAL = "damage_bonus_physical",
  DAMAGE_BONUS_ALL = "damage_bonus_all",
  MELT_BONUS = "melt_bonus",
}

export type FinalStat =
  | FINAL_STATS.TOTAL_ATTACK
  | FINAL_STATS.TOTAL_HP
  | FINAL_STATS.TOTAL_DEFENSE
  | FINAL_STATS.ELEMENTAL_MASTERY
  | FINAL_STATS.ENERGY_RECHARGE
  | FINAL_STATS.CRIT_RATE
  | FINAL_STATS.CRIT_DAMAGE
  | FINAL_STATS.DAMAGE_BONUS_ANEMO
  | FINAL_STATS.DAMAGE_BONUS_CRYO
  | FINAL_STATS.DAMAGE_BONUS_GEO
  | FINAL_STATS.DAMAGE_BONUS_DENDRO
  | FINAL_STATS.DAMAGE_BONUS_ELECTRO
  | FINAL_STATS.DAMAGE_BONUS_HYDRO
  | FINAL_STATS.DAMAGE_BONUS_PYRO
  | FINAL_STATS.DAMAGE_BONUS_PHYSICAL
  | FINAL_STATS.DAMAGE_BONUS_ALL
  | FINAL_STATS.MELT_BONUS;

enum BONUS_STATS {
  ATK_PERCENT = "ATK %",
  HP_PERCENT = "HP %",
  DEF_PERCENT = "DEF %",
  ELEMENTAL_MASTERY = "Elemental Mastery",
  ENERGY_RECHARGE = "Energy Recharge%",
  CRIT_RATE = "Crit Rate",
  CRIT_DAMAGE = "Crit Damage",
  ANEMO_DAMAGE_BONUS = "Anemo DMG Bonus%",
  CRYO_DAMAGE_BONUS = "Cryo DMG Bonus%",
  DENDRO_DAMAGE_BONUS = "Dendro DMG Bonus%",
  ELECTRO_DAMAGE_BONUS = "Electro DMG Bonus%",
  GEO_DAMAGE_BONUS = "Geo DMG Bonus%",
  HYDRO_DAMAGE_BONUS = "Hydro DMG Bonus%",
  PYRO_DAMAGE_BONUS = "Pyro DMG Bonus%",
  PHYSICAL_DAMAGE_BONUS = "Physical DMG Bonus%",
  OTHER_DAMAGE_BONUS = "Other DMG Bonus%",
  BASE_ATK = "Base Attack",
  BASE_HP = "Base HP",
  BASE_DEFENSE = "Base Defense",
  FLAT_ATK = "Flat Attack",
  FLAT_HP = "Flat HP",
  FLAT_DEF = "Flat Defense",
}

export type BonusStat =
  | BONUS_STATS.ATK_PERCENT
  | BONUS_STATS.HP_PERCENT
  | BONUS_STATS.DEF_PERCENT
  | BONUS_STATS.ELEMENTAL_MASTERY
  | BONUS_STATS.ENERGY_RECHARGE
  | BONUS_STATS.CRIT_RATE
  | BONUS_STATS.CRIT_DAMAGE
  | BONUS_STATS.ANEMO_DAMAGE_BONUS
  | BONUS_STATS.CRYO_DAMAGE_BONUS
  | BONUS_STATS.DENDRO_DAMAGE_BONUS
  | BONUS_STATS.ELECTRO_DAMAGE_BONUS
  | BONUS_STATS.GEO_DAMAGE_BONUS
  | BONUS_STATS.HYDRO_DAMAGE_BONUS
  | BONUS_STATS.PYRO_DAMAGE_BONUS
  | BONUS_STATS.PHYSICAL_DAMAGE_BONUS
  | BONUS_STATS.OTHER_DAMAGE_BONUS
  | BONUS_STATS.BASE_ATK
  | BONUS_STATS.BASE_HP
  | BONUS_STATS.BASE_DEFENSE
  | BONUS_STATS.FLAT_ATK
  | BONUS_STATS.FLAT_HP
  | BONUS_STATS.FLAT_DEF;
