#pragma once
#include "./pch.h"

#define ATK_PERCENT "ATK %"
#define HP_PERCENT "HP %"
#define DEF_PERCENT "DEF %"
#define ELEMENTAL_MASTERY "Elemental Mastery"
#define ENERGY_RECHARGE "Energy Recharge%"
#define CRIT_RATE "Crit Rate"
#define CRIT_DAMAGE "Crit Damage"
#define ANEMO_DAMAGE_BONUS "Anemo DMG Bonus%"
#define CRYO_DAMAGE_BONUS "Cryo DMG Bonus%"
#define DENDRO_DAMAGE_BONUS "Dendro DMG Bonus%"
#define ELECTRO_DAMAGE_BONUS "Electro DMG Bonus%"
#define HYDRO_DAMAGE_BONUS "Hydro DMG Bonus%"
#define PYRO_DAMAGE_BONUS "Pyro DMG Bonus%"
#define PHYSICAL_DAMAGE_BONUS "Physical DMG Bonus%"
#define OTHER_DAMAGE_BONUS "Other DMG Bonus%"

#define BASE_ATK "Base Attack"
#define BASE_HP "Base HP"
#define BASE_DEFENSE "Base Defense"
#define FLAT_ATK "Flat Attack"
#define FLAT_HP "Flat HP"
#define FLAT_DEF "Flat Defense"

#define MAX_ATK_ROLL 19.45
#define MAX_ATK_PERCENT_ROLL 0.0583
#define MAX_HP_ROLL 298.75
#define MAX_HP_PERCENT_ROLL 0.0583
#define MAX_DEF_ROLL 23.15
#define MAX_DEF_PERCENT_ROLL 0.0729
#define MAX_EM_ROLL 23.31
#define MAX_ER_PERCENT_ROLL 0.0648
#define MAX_CRIT_RATE_ROLL 0.0387
#define MAX_CRIT_DAMAGE_ROLL 0.0777

#define MAX_ATK_MAIN 311
#define MAX_ATK_PERCENT_MAIN 0.466
#define MAX_HP_MAIN 4780
#define MAX_HP_PERCENT_MAIN 0.466
#define MAX_DEF_MAIN 0
#define MAX_DEF_PERCENT_MAIN 0.583
#define MAX_EM_MAIN 187
#define MAX_ER_PERCENT_MAIN 0.518
#define MAX_CRIT_RATE_MAIN 0.359
#define MAX_CRIT_DAMAGE_MAIN 0.622
#define MAX_ELEMENTAL_DAMAGE_BONUS_MAIN 0.466
#define MAX_PHYSICAL_DAMAGE_BONUS_MAIN 0.583

#define FLOWER "Flower"
#define FEATHER "Feather"
#define SANDS "Sands"
#define GOBLET "Goblet"
#define CIRCLET "Circlet"

#define FLOWER_MAIN_STATS \
  { FLAT_HP }
#define FEATHER_MAIN_STATS \
  { FLAT_ATK }
#define SANDS_MAIN_STATS \
  { ATK_PERCENT, HP_PERCENT, DEF_PERCENT, ELEMENTAL_MASTERY, ENERGY_RECHARGE }
#define GOBLET_MAIN_STATS      \
  {                            \
    ATK_PERCENT,               \
        HP_PERCENT,            \
        DEF_PERCENT,           \
        ELEMENTAL_MASTERY,     \
        ANEMO_DAMAGE_BONUS,    \
        CRYO_DAMAGE_BONUS,     \
        DENDRO_DAMAGE_BONUS,   \
        ELECTRO_DAMAGE_BONUS,  \
        HYDRO_DAMAGE_BONUS,    \
        PYRO_DAMAGE_BONUS,     \
        PHYSICAL_DAMAGE_BONUS, \
  }
#define CIRCLET_MAIN_STATS \
  { ATK_PERCENT, HP_PERCENT, DEF_PERCENT, ELEMENTAL_MASTERY, CRIT_RATE, CRIT_DAMAGE }

#define ANEMO "Anemo"
#define CRYO "Cryo"
#define DENDRO "Dendro"
#define ELECTRO "Electro"
#define HYDRO "Hydro"
#define PYRO "Pyro"
#define PHYSICAL "Physical"
#define ALL "All"

namespace Constants {

std::vector<std::string> possible_substats_ = {
    FLAT_ATK,
    ATK_PERCENT,
    FLAT_HP,
    HP_PERCENT,
    FLAT_DEF,
    DEF_PERCENT,
    ELEMENTAL_MASTERY,
    ENERGY_RECHARGE,
    CRIT_RATE,
    CRIT_DAMAGE,
};

// retrieve max roll for a single substat
std::unordered_map<std::string, double> substat_max_roll_mapping_ = {
    {FLAT_ATK, MAX_ATK_ROLL},
    {ATK_PERCENT, MAX_ATK_PERCENT_ROLL},
    {FLAT_HP, MAX_HP_ROLL},
    {HP_PERCENT, MAX_HP_PERCENT_ROLL},
    {FLAT_DEF, MAX_DEF_ROLL},
    {DEF_PERCENT, MAX_DEF_PERCENT_ROLL},
    {ELEMENTAL_MASTERY, MAX_EM_ROLL},
    {ENERGY_RECHARGE, MAX_ER_PERCENT_ROLL},
    {CRIT_RATE, MAX_CRIT_RATE_ROLL},
    {CRIT_DAMAGE, MAX_CRIT_DAMAGE_ROLL},
};

// retrieve lv. 20 values for a single main stat
std::unordered_map<std::string, double> main_stat_max_roll_mapping_ = {
    {FLAT_ATK, MAX_ATK_MAIN},
    {ATK_PERCENT, MAX_ATK_PERCENT_MAIN},
    {FLAT_HP, MAX_HP_MAIN},
    {HP_PERCENT, MAX_HP_PERCENT_MAIN},
    {FLAT_DEF, MAX_DEF_MAIN},
    {DEF_PERCENT, MAX_DEF_PERCENT_MAIN},
    {ELEMENTAL_MASTERY, MAX_EM_MAIN},
    {ENERGY_RECHARGE, MAX_ER_PERCENT_MAIN},
    {CRIT_RATE, MAX_CRIT_RATE_MAIN},
    {CRIT_DAMAGE, MAX_CRIT_DAMAGE_MAIN},
    {ANEMO_DAMAGE_BONUS, MAX_ELEMENTAL_DAMAGE_BONUS_MAIN},
    {CRYO_DAMAGE_BONUS, MAX_ELEMENTAL_DAMAGE_BONUS_MAIN},
    {DENDRO_DAMAGE_BONUS, MAX_ELEMENTAL_DAMAGE_BONUS_MAIN},
    {ELECTRO_DAMAGE_BONUS, MAX_ELEMENTAL_DAMAGE_BONUS_MAIN},
    {HYDRO_DAMAGE_BONUS, MAX_ELEMENTAL_DAMAGE_BONUS_MAIN},
    {PYRO_DAMAGE_BONUS, MAX_ELEMENTAL_DAMAGE_BONUS_MAIN},
    {PHYSICAL_DAMAGE_BONUS, MAX_PHYSICAL_DAMAGE_BONUS_MAIN},
};

// possible main stats for artifact pieces
std::unordered_map<std::string, std::vector<std::string>> artifact_main_stats_ = {
    {FLOWER, FLOWER_MAIN_STATS},
    {FEATHER, FEATHER_MAIN_STATS},
    {SANDS, SANDS_MAIN_STATS},
    {GOBLET, GOBLET_MAIN_STATS},
    {CIRCLET, CIRCLET_MAIN_STATS},
};

std::vector<std::string> valid_elements_ = {
    ANEMO,
    CRYO,
    DENDRO,
    ELECTRO,
    HYDRO,
    PYRO,
    PHYSICAL,
};

bool validateElement(std::string label) {
  for (const std::string& element : valid_elements_) {
    if (label == element) return true;
  }

  return false;
}

std::vector<double> character_quicken_base = {
    1.0,  // lvl 0
    17.165606,
    18.535048,
    19.904854,
    21.274902,
    22.6454,
    24.649612,
    26.640642,
    28.868587,
    31.36768,
    34.143345,
    37.201,
    40.66,
    44.446667,
    48.56352,
    53.74848,
    59.081898,
    64.420044,
    69.72446,
    75.12314,
    80.58478,
    86.11203,
    91.70374,
    97.24463,
    102.812645,
    108.40956,
    113.20169,
    118.102905,
    122.97932,
    129.72733,
    136.29291,
    142.67085,
    149.02902,
    155.41699,
    161.8255,
    169.10631,
    176.51808,
    184.07274,
    191.70952,
    199.55692,
    207.38205,
    215.3989,
    224.16566,
    233.50217,
    243.35057,
    256.06308,
    268.5435,
    281.52606,
    295.01364,
    309.0672,
    323.6016,
    336.75754,
    350.5303,
    364.4827,
    378.61917,
    398.6004,
    416.39825,
    434.387,
    452.95105,
    472.60623,
    492.8849,
    513.56854,
    539.1032,
    565.51056,
    592.53876,
    624.4434,
    651.47015,
    679.4968,
    707.79407,
    736.67145,
    765.64026,
    794.7734,
    824.67737,
    851.1578,
    877.74207,
    914.2291,
    946.74677,
    979.4114,
    1011.223,
    1044.7917,
    1077.4437,
    1109.9976,
    1142.9766,
    1176.3695,
    1210.1844,
    1253.8357,
    1288.9528,
    1325.4841,
    1363.4569,
    1405.0974,
    1446.853458,
};
};  // namespace Constants
