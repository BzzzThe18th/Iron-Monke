#include "config.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/document.h"

static ModInfo modInfo = {ID, VERSION};
extern Logger& getLogger();

#define INFO(value...) getLogger().info(value)
#define ERROR(value...) getLogger().error(value)

Configuration& getConfig()
{
    static Configuration config(modInfo);
    config.Load();
    return config;
}

config_t config;

void SaveConfig()
{
    INFO("Saving Configuration...");
    getConfig().config.RemoveAllMembers();
    getConfig().config.SetObject();
    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();

    getConfig().config.AddMember("power", config.power, allocator);
    getConfig().config.AddMember("hoverMode", config.hoverMode, allocator);
    getConfig().config.AddMember("enabled", config.enabled, allocator);
    getConfig().Write();
    INFO("Saved Configuration!");
}

bool LoadConfig()
{
    INFO("Loading config...");
    bool foundEverything = true;
    rapidjson::Document& doc = getConfig().config;
    if (doc.HasMember("power")) {
        config.power = doc["power"].GetInt();
    } else {
        foundEverything = false;
    }
    if(doc.HasMember("hoverMode") && doc["hoverMode"].IsBool()) {
        config.hoverMode = doc["hoverMode"].GetBool();
    } else {
        foundEverything = false;
    }
    if(doc.HasMember("enabled") && doc["enabled"].IsBool()) {
        config.enabled = doc["enabled"].GetBool();
    } else {
        foundEverything = false;
    }
    if (foundEverything) INFO("Config Loaded Succesfully!");
    return foundEverything;
}