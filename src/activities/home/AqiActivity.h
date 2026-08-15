#pragma once

#include "activities/Activity.h"
#include "util/ButtonNavigator.h"
#include <string>

class AqiActivity final : public Activity {
  ButtonNavigator buttonNavigator;
  std::string aqiValue = "--";
  std::string lastUpdated = "";
  std::string description = "";
  bool isFetching = false;

  void fetchAqi(bool manual = false);
  void loadAqiCache();

 public:
  explicit AqiActivity(GfxRenderer& renderer, MappedInputManager& mappedInput);
  void onEnter() override;
  void loop() override;
  void render(RenderLock&&) override;
};
