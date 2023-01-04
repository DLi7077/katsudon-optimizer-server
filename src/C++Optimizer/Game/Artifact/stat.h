#pragma once
#include "../../Constants/constants.h"
#include "../../Constants/pch.h"

class Stat {
 public:
  // default
  Stat() {
    label_ = "";
    value_ = 0;
    rolls_ = 0;
  }

  // one-param
  Stat(std::string label) {
    label_ = label;
    value_ = Constants::substat_max_roll_mapping_[label];
  }

  // copy constructor
  Stat(const Stat& rhs) {
    label_ = rhs.label_;
    value_ = rhs.value_;
    rolls_ = rhs.rolls_;
  }

  // copy assignment
  Stat& operator=(const Stat& rhs) {
    Stat tempCopy = rhs;
    std::swap(*this, tempCopy);

    return *this;
  }

  // move constructor
  Stat(Stat&& rhs) {
    label_ = rhs.label_;
    rolls_ = rhs.rolls_;
    value_ = rhs.value_;

    rhs.label_ = "";
    rhs.value_ = 0;
    rhs.rolls_ = 0;
  }

  // move assignment
  Stat& operator=(Stat&& rhs) {
    std::swap(label_, rhs.label_);
    std::swap(value_, rhs.value_);
    std::swap(rolls_, rhs.rolls_);

    return *this;
  }

  ~Stat() = default;

  // simulate roll
  void addRolls(int rolls) {
    double value = Constants::substat_max_roll_mapping_[this->label_];
    value_ += rolls * value;
    rolls_ += rolls;
    return;
  }

  void setMainStat() {
    int mainStatMaxRolls = 20;
    value_ = Constants::main_stat_max_roll_mapping_[label_];
    rolls_ = mainStatMaxRolls;
  }

  std::string& label() {
    return label_;
  }

  double value() {
    return value_;
  }

  friend std::ostream& operator<<(std::ostream& out, const Stat& rhs) {
    std::cout << rhs.label_ << " " << rhs.value_ << "\n";
    return out;
  }

  Json::JsonObject toJSON() {
    Json::JsonObject result;
    // std::string roll_label = JSONUtils::wrap(label_ + " (" + std::to_string(rolls_) + ")", "\"");
    result["label"] = Json::JsonObject(Json::TYPE::STRING, label_);
    result["rolls"] = Json::JsonObject(double(rolls_));
    result["value"] = Json::JsonObject(value_);

    return result;
  }

 private:
  std::string label_;
  double value_;
  size_t rolls_ = 0;
};
