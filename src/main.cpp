#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/loader/SettingV3.hpp>
#include <chrono>
#include <ctime>

using namespace geode::prelude;

auto timeHours = Mod::get()->getSettingValue<int64_t>("time_hours");
auto timeMins  = Mod::get()->getSettingValue<int64_t>("time_mins");

using namespace geode::prelude;

$execute {
    listenForSettingChanges("time_hours", [](int64_t value) {
        timeHours = Mod::get()->getSettingValue<int64_t>("time_hours");
    });

    listenForSettingChanges("time_mins", [](int64_t value) {
        timeMins = Mod::get()->getSettingValue<int64_t>("time_mins");
    });
}

class $modify(PlayerObject) {
    void playDeathEffect() {
        PlayerObject::playDeathEffect();

        auto now = std::time(nullptr);
        auto* timeinfo = std::localtime(&now);
        
        int currentMins = timeinfo->tm_hour * 60 + timeinfo->tm_min;
        int settingMins = timeHours * 60 + timeMins;

        if (currentMins >= settingMins) {
            GameManager::get()->setGameVariable("0026", false);
        } 
        else {
            GameManager::get()->setGameVariable("0026", true);
        }
    }
};