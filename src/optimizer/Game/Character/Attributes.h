#pragma once
#include "../../Constants/pch.h"

namespace Attributes {
struct TalentScaling {
  std::string source_stat_;  // stat to scale on (total_attack)
  double stat_scaling_;      // scaling percent (3.29x , or 329%)
  TalentScaling() {}
  TalentScaling(std::string&& source, double scaling)
      : source_stat_(std::move(source)), stat_scaling_(scaling) {}
  TalentScaling(const std::string& source, double scaling)
      : source_stat_(source), stat_scaling_(scaling) {}
};

// support for stats like Hu Tao E and 4pc emblem of severed fate
struct BonusStatGain {
  std::string source_stat_;  // stat that bonus is proportional to
  std::string target_stat_;  // target stat to buff
  double source_offset_;     // threshold to gain bonus (4pc emblem = min(0.75, (ER-100) * .25))
  double percent_gain_;      // percentage gain
  double max_gain_;          // maximum gain

  BonusStatGain() {}
  // constructor
  BonusStatGain(
      std::string sourceStat,
      std::string targetStat,
      double sourceOffset,
      double percentGain,
      double maxGain) {
    source_stat_ = sourceStat;
    target_stat_ = targetStat;
    source_offset_ = sourceOffset;
    percent_gain_ = percentGain;
    max_gain_ = maxGain;
  }

  // JSON Stringify
  friend std::ostream& operator<<(std::ostream& out, BonusStatGain& rhs) {
    out << "{\n"
        << "\t\"source_stat_\": "
        << "\"" << rhs.source_stat_ << "\""
        << ",\n"
        << "\t\"target_stat_\": "
        << "\"" << rhs.target_stat_ << "\""
        << ",\n"
        << "\t\"source_offset_\": " << rhs.source_offset_ << ",\n"
        << "\t\"percent_gain_\": " << rhs.percent_gain_ << ",\n"
        << "\t\"max_gain_\": " << rhs.max_gain_ << "\n"
        << "}";

    return out;
  }
};

}  // namespace Attributes