#include "../Game/Character/Character.h"
#include "../Game/Enemy.h"
#include "./generate.h"

namespace Initial {

vector<string> subStatPreference = {
    FLAT_ATK,
    ATK_PERCENT,
    ELEMENTAL_MASTERY,
    ENERGY_RECHARGE,
    CRIT_DAMAGE,
};

vector<string> mainStatPreference = {
    FLAT_HP,   // Flower
    FLAT_ATK,  // Feather
    ATK_PERCENT,
    ENERGY_RECHARGE,
    ELECTRO_DAMAGE_BONUS,
    CRIT_DAMAGE,
};

vector<string> mainStatGobletPref = {
    ELECTRO_DAMAGE_BONUS,
};
vector<string> mainStatCircletPref = {
    CRIT_DAMAGE,
};

vector<string> FlowerMainStats = {FLAT_HP};
vector<string> FeatherMainStats = {FLAT_ATK};
vector<string> SandsMainStats = {ATK_PERCENT, ELEMENTAL_MASTERY};
vector<string> GobletMainStats = {PYRO_DAMAGE_BONUS};
vector<string> CircletMainStats = {CRIT_DAMAGE, ELEMENTAL_MASTERY};

// unordered_map<string, vector<string>> mainStatPreference = {
//     {FLOWER, FlowerMainStats},
//     {FEATHER, FeatherMainStats},
//     {SANDS, SandsMainStats},
//     {GOBLET, GobletMainStats},
//     {CIRCLET, CircletMainStats},
// };

vector<string> FlowerMainPref = Utils::intersection(Constants::artifact_main_stats_[FLOWER], mainStatPreference);
vector<string> FeatherMainPref = Utils::intersection(Constants::artifact_main_stats_[FEATHER], mainStatPreference);
vector<string> SandsMainPref = Utils::intersection(Constants::artifact_main_stats_[SANDS], mainStatPreference);
vector<string> GobletMainPref = Utils::intersection(Constants::artifact_main_stats_[GOBLET], mainStatGobletPref);
vector<string> CircletMainPref = Utils::intersection(Constants::artifact_main_stats_[CIRCLET], mainStatCircletPref);

vector<Artifact> FlowerArtifacts = Generate::generateArtifacts(FlowerMainPref, subStatPreference);
vector<Artifact> FeatherArtifacts = Generate::generateArtifacts(FeatherMainPref, subStatPreference);
vector<Artifact> SandsArtifacts = Generate::generateArtifacts(SandsMainPref, subStatPreference);
vector<Artifact> GobletArtifacts = Generate::generateArtifacts(GobletMainPref, subStatPreference);
vector<Artifact> CircletArtifacts = Generate::generateArtifacts(CircletMainPref, subStatPreference);

}  // namespace Initial