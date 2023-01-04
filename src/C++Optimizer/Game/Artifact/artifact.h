#pragma once
#include "../../Constants/pch.h"
#include "./stat.h"

class Artifact {
 public:
  Artifact() {}
  // two-param constructor
  Artifact(const std::array<std::string, SUBSTAT_COUNT>& substats, std::string mainStat) {
    main_stat_ = Stat(mainStat);
    main_stat_.setMainStat();

    for (size_t i = 0; i < SUBSTAT_COUNT; i++) {
      substats_[i] = Stat(substats[i]);
    }
  }

  Artifact(const std::array<std::string, SUBSTAT_COUNT>& substats, std::array<int, SUBSTAT_COUNT> rolls, std::string mainStat) {
    main_stat_ = Stat(mainStat);
    main_stat_.setMainStat();

    for (size_t i = 0; i < SUBSTAT_COUNT; i++) {
      substats_[i] = Stat(substats[i]);
      substats_[i].addRolls(rolls[i]);
    }
  }

  // copy constructor
  Artifact(const Artifact& rhs) {
    main_stat_ = Stat(rhs.main_stat_);

    for (size_t i = 0; i < SUBSTAT_COUNT; i++) {
      substats_[i] = Stat(rhs.substats_[i]);  // only possible due to copy assignment
    }
  }

  // copy assignment
  Artifact& operator=(const Artifact& rhs) {
    main_stat_ = Stat(rhs.main_stat_);

    for (size_t i = 0; i < SUBSTAT_COUNT; i++) {
      substats_[i] = Stat(rhs.substats_[i]);  // only possible due to copy assignment
    }

    return *this;
  }

  // move constructor
  Artifact(Artifact&& rhs) {
    main_stat_ = Stat(rhs.main_stat_);

    for (size_t i = 0; i < SUBSTAT_COUNT; i++) {
      substats_[i] = rhs.substats_[i];
    }
  }

  // move assignment
  Artifact& operator=(Artifact&& rhs) {
    std::swap(main_stat_, rhs.main_stat_);
    std::swap(substats_, rhs.substats_);

    return *this;
  }

  ~Artifact() = default;

  int size() const {
    return SUBSTAT_COUNT;
  }

  Stat& operator[](size_t location) {
    if (location < 0 || location > SUBSTAT_COUNT) {
      std::cout << "index " << location << " Out of Bounds";
      abort();
    }

    return substats_[location];
  }

  const Stat& mainStat() const {
    return main_stat_;
  }

  friend std::ostream& operator<<(std::ostream& out, const Artifact& rhs) {
    out << "main:\t" << rhs.main_stat_;
    for (int i = 0; i < SUBSTAT_COUNT; i++) {
      out << rhs.substats_[i];
    }
    out << "\n";
    return out;
  }

  Json::JsonObject toJSON() {
    Json::JsonObject result;
    result["main_stat"] = main_stat_.toJSON();
    result["substats"] = Json::JsonObject(Json::TYPE::ARRAY);
    for (Stat& substat : substats_) {
      result["substats"].push_back(substat.toJSON());
    }

    return result;
  }

 private:
  std::array<Stat, SUBSTAT_COUNT> substats_;
  Stat main_stat_;
};
