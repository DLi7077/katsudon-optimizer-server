#include "../Game/Character/Character.h"
#include "../Game/Enemy.h"
#include "./generate.h"

namespace Initial {
    
struct StatPreference {
  std::vector<std::string> substat_preferences_;
  std::vector<std::string> flower_main_stats_;
  std::vector<std::string> feather_main_stats_;
  std::vector<std::string> sands_main_stats_;
  std::vector<std::string> goblet_main_stats_;
  std::vector<std::string> circlet_main_stats_;
};

std::vector<Artifact> generateArtifacts(
    std::vector<std::string>& mainStatPref,
    std::vector<std::string>& mainStatPossible,
    std::vector<std::string>& substatPreference) {
  std::vector<std::string> artifactMainStats = Utils::intersection(mainStatPref, mainStatPossible);
  std::vector<Artifact> createdArtifacts = Generate::generateArtifacts(artifactMainStats, substatPreference);

  return createdArtifacts;
}

std::vector<std::vector<Artifact>> generateArtifactPool(StatPreference& preference) {
  std::vector<Artifact> flowerArtifacts = generateArtifacts(
      preference.flower_main_stats_,
      Constants::artifact_main_stats_[FLOWER],
      preference.substat_preferences_);

  std::vector<Artifact> featherArtifacts = generateArtifacts(
      preference.feather_main_stats_,
      Constants::artifact_main_stats_[FEATHER],
      preference.substat_preferences_);

  std::vector<Artifact> sandsArtifacts = generateArtifacts(
      preference.sands_main_stats_,
      Constants::artifact_main_stats_[SANDS],
      preference.substat_preferences_);

  std::vector<Artifact> gobletArtifacts = generateArtifacts(
      preference.goblet_main_stats_,
      Constants::artifact_main_stats_[GOBLET],
      preference.substat_preferences_);

  std::vector<Artifact> circletArtifacts = generateArtifacts(
      preference.circlet_main_stats_,
      Constants::artifact_main_stats_[CIRCLET],
      preference.substat_preferences_);

  return {
      std::move(flowerArtifacts),
      std::move(featherArtifacts),
      std::move(sandsArtifacts),
      std::move(gobletArtifacts),
      std::move(circletArtifacts),
  };
}

}  // namespace Initial