#include "config.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace config {
    std::string GetConfigDir() {
        return "configs";
    }

    static std::string ConfigPath(const std::string& name) {
        return GetConfigDir() + "/" + name + ".json";
    }

    static void ToJson(nlohmann::json& j) {
        j = nlohmann::json{
            {"aimbot", settings::aimbot},
            {"fov", settings::fov},
            {"smoothing", settings::smoothing},
            {"showfov", settings::showfov},
            {"dynamic_aim", settings::dynamic_aim},
            {"vischeck", settings::vischeck},
            {"box", settings::box},
            {"distance", settings::distance},
            {"health", settings::health},
            {"headdot", settings::headdot},
            {"name", settings::name},
            {"normal_box", settings::normal_box},
            {"playerDistance", settings::playerDistance},
            {"skeleton", settings::skeleton},
            {"streamproof", settings::streamproof},
            {"weapon", settings::weapon},
            {"weapon_icon", settings::weapon_icon},
            {"health_shield", settings::health_shield},
            {"sheild", settings::sheild},
            {"op", settings::op},
            {"lootDistance", settings::lootDistance},
            {"key", settings::key},
            {"BackPack", settings::BackPack},
            {"Energy", settings::Energy},
            {"EnergyAmmo", settings::EnergyAmmo},
            {"Heavy", settings::Heavy},
            {"HeavyAmmo", settings::HeavyAmmo},
            {"Helmet", settings::Helmet},
            {"Icon", settings::Icon},
            {"Knocked", settings::Knocked},
            {"Legendary", settings::Legendary},
            {"LightAmmo", settings::LightAmmo},
            {"LightWeapon", settings::LightWeapon},
            {"Medic", settings::Medic},
            {"Shield", settings::Shield},
            {"Shotgun", settings::Shotgun},
            {"ShotgunAmmo", settings::ShotgunAmmo},
            {"Sniper", settings::Sniper},
            {"SniperAmmo", settings::SniperAmmo},
            {"Text", settings::Text},
            {"rgb", {settings::rgb[0], settings::rgb[1], settings::rgb[2]}},
            {"fov_color", {settings::fov_color[0], settings::fov_color[1], settings::fov_color[2]}},
            {"target_color", {settings::target_color[0], settings::target_color[1], settings::target_color[2]}},
            {"box_color", {settings::box_color[0], settings::box_color[1], settings::box_color[2]}},
            {"skel_color", {settings::skel_color[0], settings::skel_color[1], settings::skel_color[2]}},
            {"name_color", {settings::name_color[0], settings::name_color[1], settings::name_color[2]}},
            {"headdot_color", {settings::headdot_color[0], settings::headdot_color[1], settings::headdot_color[2]}},
            {"distance_color", {settings::distance_color[0], settings::distance_color[1], settings::distance_color[2]}},
            {"operator_color", {settings::operator_color[0], settings::operator_color[1], settings::operator_color[2]}},
            {"weapon_color", {settings::weapon_color[0], settings::weapon_color[1], settings::weapon_color[2]}},
            {"weapon_icon_color", {settings::weapon_icon_color[0], settings::weapon_icon_color[1], settings::weapon_icon_color[2]}},
            {"box_color_visible", {settings::box_color_visible[0], settings::box_color_visible[1], settings::box_color_visible[2]}},
            {"box_color_not_visible", {settings::box_color_not_visible[0], settings::box_color_not_visible[1], settings::box_color_not_visible[2]}},
            {"normal_box_color_visible", {settings::normal_box_color_visible[0], settings::normal_box_color_visible[1], settings::normal_box_color_visible[2]}},
            {"normal_box_color_not_visible", {settings::normal_box_color_not_visible[0], settings::normal_box_color_not_visible[1], settings::normal_box_color_not_visible[2]}},
            {"skel_color_visible", {settings::skel_color_visible[0], settings::skel_color_visible[1], settings::skel_color_visible[2]}},
            {"skel_color_not_visible", {settings::skel_color_not_visible[0], settings::skel_color_not_visible[1], settings::skel_color_not_visible[2]}},
            {"name_color_visible", {settings::name_color_visible[0], settings::name_color_visible[1], settings::name_color_visible[2]}},
            {"name_color_not_visible", {settings::name_color_not_visible[0], settings::name_color_not_visible[1], settings::name_color_not_visible[2]}},
            {"distance_color_visible", {settings::distance_color_visible[0], settings::distance_color_visible[1], settings::distance_color_visible[2]}},
            {"distance_color_not_visible", {settings::distance_color_not_visible[0], settings::distance_color_not_visible[1], settings::distance_color_not_visible[2]}},
            {"operator_color_visible", {settings::operator_color_visible[0], settings::operator_color_visible[1], settings::operator_color_visible[2]}},
            {"operator_color_not_visible", {settings::operator_color_not_visible[0], settings::operator_color_not_visible[1], settings::operator_color_not_visible[2]}},
            {"weapon_color_visible", {settings::weapon_color_visible[0], settings::weapon_color_visible[1], settings::weapon_color_visible[2]}},
            {"weapon_color_not_visible", {settings::weapon_color_not_visible[0], settings::weapon_color_not_visible[1], settings::weapon_color_not_visible[2]}},
            {"weapon_icon_color_visible", {settings::weapon_icon_color_visible[0], settings::weapon_icon_color_visible[1], settings::weapon_icon_color_visible[2]}},
            {"weapon_icon_color_not_visible", {settings::weapon_icon_color_not_visible[0], settings::weapon_icon_color_not_visible[1], settings::weapon_icon_color_not_visible[2]}},
        };
    }

    static void FromJson(const nlohmann::json& j) {
        if (j.contains("aimbot")) settings::aimbot = j["aimbot"].get<bool>();
        if (j.contains("fov")) settings::fov = j["fov"].get<int>();
        if (j.contains("smoothing")) settings::smoothing = j["smoothing"].get<float>();
        if (j.contains("showfov")) settings::showfov = j["showfov"].get<bool>();
        if (j.contains("dynamic_aim")) settings::dynamic_aim = j["dynamic_aim"].get<bool>();
        if (j.contains("vischeck")) settings::vischeck = j["vischeck"].get<bool>();
        if (j.contains("box")) settings::box = j["box"].get<bool>();
        if (j.contains("distance")) settings::distance = j["distance"].get<bool>();
        if (j.contains("health")) settings::health = j["health"].get<bool>();
        if (j.contains("headdot")) settings::headdot = j["headdot"].get<bool>();
        if (j.contains("name")) settings::name = j["name"].get<bool>();
        if (j.contains("normal_box")) settings::normal_box = j["normal_box"].get<bool>();
        if (j.contains("playerDistance")) settings::playerDistance = j["playerDistance"].get<int>();
        if (j.contains("skeleton")) settings::skeleton = j["skeleton"].get<bool>();
        if (j.contains("streamproof")) settings::streamproof = j["streamproof"].get<bool>();
        if (j.contains("weapon")) settings::weapon = j["weapon"].get<bool>();
        if (j.contains("weapon_icon")) settings::weapon_icon = j["weapon_icon"].get<bool>();
        if (j.contains("health_shield")) settings::health_shield = j["health_shield"].get<bool>();
        if (j.contains("sheild")) settings::sheild = j["sheild"].get<bool>();
        if (j.contains("op")) settings::op = j["op"].get<bool>();
        if (j.contains("lootDistance")) settings::lootDistance = j["lootDistance"].get<int>();
        if (j.contains("key")) settings::key = j["key"].get<int>();
        if (j.contains("BackPack")) settings::BackPack = j["BackPack"].get<bool>();
        if (j.contains("Energy")) settings::Energy = j["Energy"].get<bool>();
        if (j.contains("EnergyAmmo")) settings::EnergyAmmo = j["EnergyAmmo"].get<bool>();
        if (j.contains("Heavy")) settings::Heavy = j["Heavy"].get<bool>();
        if (j.contains("HeavyAmmo")) settings::HeavyAmmo = j["HeavyAmmo"].get<bool>();
        if (j.contains("Helmet")) settings::Helmet = j["Helmet"].get<bool>();
        if (j.contains("Icon")) settings::Icon = j["Icon"].get<bool>();
        if (j.contains("Knocked")) settings::Knocked = j["Knocked"].get<bool>();
        if (j.contains("Legendary")) settings::Legendary = j["Legendary"].get<bool>();
        if (j.contains("LightAmmo")) settings::LightAmmo = j["LightAmmo"].get<bool>();
        if (j.contains("LightWeapon")) settings::LightWeapon = j["LightWeapon"].get<bool>();
        if (j.contains("Medic")) settings::Medic = j["Medic"].get<bool>();
        if (j.contains("Shield")) settings::Shield = j["Shield"].get<bool>();
        if (j.contains("Shotgun")) settings::Shotgun = j["Shotgun"].get<bool>();
        if (j.contains("ShotgunAmmo")) settings::ShotgunAmmo = j["ShotgunAmmo"].get<bool>();
        if (j.contains("Sniper")) settings::Sniper = j["Sniper"].get<bool>();
        if (j.contains("SniperAmmo")) settings::SniperAmmo = j["SniperAmmo"].get<bool>();
        if (j.contains("Text")) settings::Text = j["Text"].get<bool>();
        if (j.contains("rgb")) for (int i = 0; i < 3; ++i) settings::rgb[i] = j["rgb"][i].get<float>();
        if (j.contains("fov_color")) for (int i = 0; i < 3; ++i) settings::fov_color[i] = j["fov_color"][i].get<float>();
        if (j.contains("target_color")) for (int i = 0; i < 3; ++i) settings::target_color[i] = j["target_color"][i].get<float>();
        if (j.contains("box_color")) for (int i = 0; i < 3; ++i) settings::box_color[i] = j["box_color"][i].get<float>();
        if (j.contains("skel_color")) for (int i = 0; i < 3; ++i) settings::skel_color[i] = j["skel_color"][i].get<float>();
        if (j.contains("name_color")) for (int i = 0; i < 3; ++i) settings::name_color[i] = j["name_color"][i].get<float>();
        if (j.contains("headdot_color")) for (int i = 0; i < 3; ++i) settings::headdot_color[i] = j["headdot_color"][i].get<float>();
        if (j.contains("distance_color")) for (int i = 0; i < 3; ++i) settings::distance_color[i] = j["distance_color"][i].get<float>();
        if (j.contains("operator_color")) for (int i = 0; i < 3; ++i) settings::operator_color[i] = j["operator_color"][i].get<float>();
        if (j.contains("weapon_color")) for (int i = 0; i < 3; ++i) settings::weapon_color[i] = j["weapon_color"][i].get<float>();
        if (j.contains("weapon_icon_color")) for (int i = 0; i < 3; ++i) settings::weapon_icon_color[i] = j["weapon_icon_color"][i].get<float>();
        if (j.contains("box_color_visible")) for (int i = 0; i < 3; ++i) settings::box_color_visible[i] = j["box_color_visible"][i].get<float>();
        if (j.contains("box_color_not_visible")) for (int i = 0; i < 3; ++i) settings::box_color_not_visible[i] = j["box_color_not_visible"][i].get<float>();
        if (j.contains("normal_box_color_visible")) for (int i = 0; i < 3; ++i) settings::normal_box_color_visible[i] = j["normal_box_color_visible"][i].get<float>();
        if (j.contains("normal_box_color_not_visible")) for (int i = 0; i < 3; ++i) settings::normal_box_color_not_visible[i] = j["normal_box_color_not_visible"][i].get<float>();
        if (j.contains("skel_color_visible")) for (int i = 0; i < 3; ++i) settings::skel_color_visible[i] = j["skel_color_visible"][i].get<float>();
        if (j.contains("skel_color_not_visible")) for (int i = 0; i < 3; ++i) settings::skel_color_not_visible[i] = j["skel_color_not_visible"][i].get<float>();
        if (j.contains("name_color_visible")) for (int i = 0; i < 3; ++i) settings::name_color_visible[i] = j["name_color_visible"][i].get<float>();
        if (j.contains("name_color_not_visible")) for (int i = 0; i < 3; ++i) settings::name_color_not_visible[i] = j["name_color_not_visible"][i].get<float>();
        if (j.contains("distance_color_visible")) for (int i = 0; i < 3; ++i) settings::distance_color_visible[i] = j["distance_color_visible"][i].get<float>();
        if (j.contains("distance_color_not_visible")) for (int i = 0; i < 3; ++i) settings::distance_color_not_visible[i] = j["distance_color_not_visible"][i].get<float>();
        if (j.contains("operator_color_visible")) for (int i = 0; i < 3; ++i) settings::operator_color_visible[i] = j["operator_color_visible"][i].get<float>();
        if (j.contains("operator_color_not_visible")) for (int i = 0; i < 3; ++i) settings::operator_color_not_visible[i] = j["operator_color_not_visible"][i].get<float>();
        if (j.contains("weapon_color_visible")) for (int i = 0; i < 3; ++i) settings::weapon_color_visible[i] = j["weapon_color_visible"][i].get<float>();
        if (j.contains("weapon_color_not_visible")) for (int i = 0; i < 3; ++i) settings::weapon_color_not_visible[i] = j["weapon_color_not_visible"][i].get<float>();
        if (j.contains("weapon_icon_color_visible")) for (int i = 0; i < 3; ++i) settings::weapon_icon_color_visible[i] = j["weapon_icon_color_visible"][i].get<float>();
        if (j.contains("weapon_icon_color_not_visible")) for (int i = 0; i < 3; ++i) settings::weapon_icon_color_not_visible[i] = j["weapon_icon_color_not_visible"][i].get<float>();
    }

    bool Save(const std::string& name) {
        try {
            fs::create_directories(GetConfigDir());
            nlohmann::json j;
            ToJson(j);
            std::ofstream out(ConfigPath(name));
            out << j.dump(4);
            return true;
        } catch (...) {
            return false;
        }
    }

    bool Load(const std::string& name) {
        try {
            std::ifstream in(ConfigPath(name));
            if (!in.is_open()) return false;
            nlohmann::json j;
            in >> j;
            FromJson(j);
            return true;
        } catch (...) {
            return false;
        }
    }

    std::vector<std::string> List() {
        std::vector<std::string> configs;
        try {
            fs::create_directories(GetConfigDir());
            for (const auto& entry : fs::directory_iterator(GetConfigDir())) {
                if (entry.is_regular_file()) {
                    auto path = entry.path();
                    if (path.extension() == ".json") {
                        configs.push_back(path.stem().string());
                    }
                }
            }
        } catch (...) {}
        return configs;
    }

    bool Delete(const std::string& name) {
        try {
            return fs::remove(ConfigPath(name));
        } catch (...) {
            return false;
        }
    }
} 