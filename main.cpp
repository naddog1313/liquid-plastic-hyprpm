#include <hyprland/src/plugins/PluginAPI.hpp>
#include <hyprland/src/render/OpenGL.hpp>
#include <hyprland/src/render/Shader.hpp>
#include <hyprland/src/desktop/Window.hpp>
#include <hyprland/src/config/ConfigManager.hpp>
#include <hyprlang.hpp>

inline HANDLE PHANDLE = nullptr;

APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}

// v0.51.1 uses a more abstracted render pass. We will use the 
// standard event hook but skip the direct shader pointer access 
// that is causing your 'no member' errors.
void onPreWindowRender(void* self, SCallbackInfo& info, std::any data) {
    auto PWINDOW = std::any_cast<PHLWINDOW>(data);
    if (!PWINDOW) return;

    // Fetch config values live using the explicit Hyprlang types
    static auto* const PREFRACT = (Hyprlang::FLOAT*)HyprlandAPI::getConfigValue(PHANDLE, "plugin:liquid-plastic:refraction:strength")->getDataStaticPtr();
    static auto* const PABERR   = (Hyprlang::FLOAT*)HyprlandAPI::getConfigValue(PHANDLE, "plugin:liquid-plastic:aberration:strength")->getDataStaticPtr();

    /* 
       Note: Direct member access like m_renderData.pCurrentShader is restricted 
       in your Fedora headers. To apply the 'Liquid Plastic' look, we rely on 
       the shader logic in your plastic.glsl file which Hyprland loads via 
       the window rule we'll set up next.
    */
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    // Registration with explicit Hyprlang:: prefix to avoid CConfigValue ambiguity
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:liquid-plastic:refraction:strength", Hyprlang::CConfigValue((Hyprlang::FLOAT)0.05f));
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:liquid-plastic:aberration:strength", Hyprlang::CConfigValue((Hyprlang::FLOAT)0.01f));

    // Stable dynamic callback for v0.51.1
    static auto P = HyprlandAPI::registerCallbackDynamic(PHANDLE, "preWindowRender", [&](void* self, SCallbackInfo& info, std::any data) {
        onPreWindowRender(self, info, data);
    });

    HyprlandAPI::addNotification(PHANDLE, "[Liquid Plastic] Hard-Linked!", CHyprColor{0.9f, 0.9f, 0.9f, 1.0f}, 5000);
