#include "AqiActivity.h"
#include <ArduinoJson.h>
#include <HalStorage.h>
#include "components/UITheme.h"
#include "network/HttpDownloader.h"
#include "WifiCredentialStore.h"
#include "CrossPointSettings.h"
#include "I18n.h"
#include <WiFi.h>

constexpr const char* AQI_CONFIG_PATH = "/.crosspoint/aqi.json";
constexpr const char* AQI_CACHE_PATH = "/.crosspoint/aqi_cache.json";

AqiActivity::AqiActivity(GfxRenderer& renderer, MappedInputManager& mappedInput)
    : Activity("AqiActivity", renderer, mappedInput) {}

void AqiActivity::onEnter() {
  Activity::onEnter();
  loadAqiCache();

  // Update view
  requestUpdate();
}

void AqiActivity::loadAqiCache() {
  if (Storage.exists(AQI_CACHE_PATH)) {
    HalFile file;
    if (Storage.openFileForRead("AQI", AQI_CACHE_PATH, file)) {
      JsonDocument doc;
      if (!deserializeJson(doc, file)) {
        aqiValue = doc["aqi"] | "--";
        lastUpdated = doc["time"] | "";

        int aqiNum = doc["aqi"] | -1;
        if (aqiNum >= 0 && aqiNum <= 50) description = "Good";
        else if (aqiNum > 50 && aqiNum <= 100) description = "Moderate";
        else if (aqiNum > 100 && aqiNum <= 150) description = "Unhealthy for Sensitive Groups";
        else if (aqiNum > 150 && aqiNum <= 200) description = "Unhealthy";
        else if (aqiNum > 200 && aqiNum <= 300) description = "Very Unhealthy";
        else if (aqiNum > 300) description = "Hazardous";
      }
    }
  }
}

void AqiActivity::fetchAqi(bool manual) {
  isFetching = true;
  requestUpdateAndWait();

  std::string url;
  if (Storage.exists(AQI_CONFIG_PATH)) {
    HalFile file;
    if (Storage.openFileForRead("AQI", AQI_CONFIG_PATH, file)) {
      JsonDocument doc;
      if (!deserializeJson(doc, file)) {
        url = doc["url"] | "";
      }
    }
  }

  if (url.empty()) {
    aqiValue = "Config Err";
    isFetching = false;
    requestUpdate();
    return;
  }

  const wifi_mode_t originalMode = WiFi.getMode();
  bool connectedHere = false;

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);

    // Try saved credentials
    size_t count = WIFI_STORE.getCredentialCount();
    for (size_t i = 0; i < count; i++) {
      auto credOpt = WIFI_STORE.getCredentialAt(i);
      if (!credOpt) continue;

      WiFi.begin(credOpt->ssid.c_str(), credOpt->password.c_str());
      unsigned long start = millis();
      while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
        vTaskDelay(pdMS_TO_TICKS(100));
      }
      if (WiFi.status() == WL_CONNECTED) {
        connectedHere = true;
        break;
      }
      WiFi.disconnect();
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    std::string response;
    if (HttpDownloader::fetchUrl(url, response)) {
      JsonDocument doc;
      if (!deserializeJson(doc, response)) {
        if (doc["status"] == "ok") {
          int aqi = doc["data"]["aqi"] | -1;
          if (aqi >= 0) {
            aqiValue = std::to_string(aqi);

            // Save cache
            JsonDocument cacheDoc;
            cacheDoc["aqi"] = aqi;
            cacheDoc["time"] = doc["data"]["time"]["s"] | "";
            cacheDoc["last_fetch_ms"] = millis();

            HalFile out;
            if (Storage.openFileForWrite("AQI", AQI_CACHE_PATH, out)) {
              serializeJson(cacheDoc, out);
            }
            loadAqiCache();
          }
        } else {
           aqiValue = "API Err";
        }
      } else {
         aqiValue = "JSON Err";
      }
    } else {
      aqiValue = "HTTP Err";
    }
  } else {
    aqiValue = "No WiFi";
  }

  if (connectedHere) {
    WiFi.disconnect(true);
    WiFi.mode(originalMode);
  }

  isFetching = false;
  requestUpdate();
}

void AqiActivity::loop() {
  if (mappedInput.wasReleased(MappedInputManager::Button::Back)) {
    activityManager.goHome();
    return;
  }
  if (mappedInput.wasReleased(MappedInputManager::Button::Confirm)) {
    if (!isFetching) {
      fetchAqi(true);
    }
  }
}

void AqiActivity::render(RenderLock&&) {
  const auto& metrics = UITheme::getInstance().getMetrics();
  renderer.clearScreen();

  const int screenW = renderer.getScreenWidth();
  const int screenH = renderer.getScreenHeight();

  GUI.drawHeader(renderer, Rect{0, 0, screenW, metrics.headerHeight}, "Air Quality");

  if (isFetching) {
    UITheme::drawCenteredText(renderer, Rect{0, 0, screenW, screenH},
                              SETTINGS.getReaderFontId(), screenH / 2, "Fetching...", true);
  } else {
    int startY = screenH / 2 - 40;

    // Main AQI Value
    std::string dispAqi = "AQI: " + aqiValue;
    UITheme::drawCenteredText(renderer, Rect{0, 0, screenW, screenH},
                              SETTINGS.getReaderFontId(), startY, dispAqi.c_str(), true);

    if (!description.empty()) {
        UITheme::drawCenteredText(renderer, Rect{0, 0, screenW, screenH},
                                  SETTINGS.getReaderFontId(), startY + 40, description.c_str(), true);
    }

    if (!lastUpdated.empty()) {
        std::string updateStr = "Updated: " + lastUpdated;
        UITheme::drawCenteredText(renderer, Rect{0, 0, screenW, screenH},
                                  SETTINGS.getReaderFontId(), startY + 80, updateStr.c_str(), true);
    }
  }

  const auto labels = mappedInput.mapLabels(tr(STR_BACK), isFetching ? "" : tr(STR_REFRESH), "", "");
  GUI.drawButtonHints(renderer, labels.btn1, labels.btn2, labels.btn3, labels.btn4);

  renderer.displayBuffer();
}
