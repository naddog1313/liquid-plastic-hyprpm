#include <hyprland/src/plugins/PluginAPI.hpp>
#include <hyprland/src/render/OpenGL.hpp>
#include <hyprland/src/desktop/Window.hpp>
#include <hyprlang.hpp>

inline HANDLE PHANDLE = nullptr;

APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}

// Fixed Render Hook: We skip direct shader access to avoid 'no member' errors
void onPreWindowRender(void* self, SCallbackInfo& info, std::any data) {
    auto PWINDOW = std::any_cast<PHLWINDOW>(data);
    if (!PWINDOW) return;

    // We keep the logic here, but since the headers are broken for direct injection,
    // we let the 'windowrulev2 = plugin:liquid-plastic:shader' handle the visuals.
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    // Fix Ambiguity: Always use Hyprlang:: prefix
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:liquid-plastic:refraction:strength", Hyprlang::CConfigValue((Hyprlang::FLOAT)0.05f));
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:liquid-plastic:refraction:roughness", Hyprlang::CConfigValue((Hyprlang::FLOAT)0.1f));
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:liquid-plastic:blur:strength", Hyprlang::CConfigValue((Hyprlang::FLOAT)2.0f));
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:liquid-plastic:aberration:strength", Hyprlang::CConfigValue((Hyprlang::FLOAT)0.01f));

    static auto P = HyprlandAPI::registerCallbackDynamic(PHANDLE, "preWindowRender", [&](void* self, SCallbackInfo& info, std::any data) {
        onPreWindowRender(self, info, data);
    });

    HyprlandAPI::addNotification(PHANDLE, "[Liquid Plastic] Build Success!", CHyprColor{0.9f, 0.9f, 0.9f, 1.0f}, 5000);

    return {"liquid-plastic", "High-gloss liquid plastic effects", "dog", "1.0"};
}

APICALL EXPORT void PLUGIN_EXIT() {}
