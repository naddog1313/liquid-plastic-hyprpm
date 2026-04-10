#include <hyprland/src/plugins/PluginAPI.hpp>
#include <hyprland/src/render/OpenGL.hpp>
#include <hyprland/src/render/Shader.hpp>
#include <hyprland/src/desktop/Window.hpp>
#include <hyprlang.hpp>

inline HANDLE PHANDLE = nullptr;

APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}

void onPreWindowRender(void* self, SCallbackInfo& info, std::any data) {
    auto PWINDOW = std::any_cast<PHLWINDOW>(data);
    if (!PWINDOW) return;

    static auto* const PREFRACT = (Hyprlang::FLOAT*)HyprlandAPI::getConfigValue(PHANDLE, "plugin:liquid-plastic:refraction:strength")->getDataStaticPtr();
    static auto* const PABERR   = (Hyprlang::FLOAT*)HyprlandAPI::getConfigValue(PHANDLE, "plugin:liquid-plastic:aberration:strength")->getDataStaticPtr();
    static auto* const PROUGH   = (Hyprlang::FLOAT*)HyprlandAPI::getConfigValue(PHANDLE, "plugin:liquid-plastic:refraction:roughness")->getDataStaticPtr();
    static auto* const PBLUR    = (Hyprlang::FLOAT*)HyprlandAPI::getConfigValue(PHANDLE, "plugin:liquid-plastic:blur:strength")->getDataStaticPtr();

    if (g_pHyprOpenGL->m_renderData.pCurrentShader) {
        const auto PSHADER = g_pHyprOpenGL->m_renderData.pCurrentShader;
        glUniform1f(glGetUniformLocation(PSHADER->program, "refraction"), (float)*PREFRACT);
        glUniform1f(glGetUniformLocation(PSHADER->program, "aberration"), (float)*PABERR);
        glUniform1f(glGetUniformLocation(PSHADER->program, "roughness"), (float)*PROUGH);
        glUniform1f(glGetUniformLocation(PSHADER->program, "blur"), (float)*PBLUR);
    }
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    using namespace Hyprlang;
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:liquid-plastic:refraction:strength", CConfigValue((FLOAT)0.05f));
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:liquid-plastic:refraction:roughness", CConfigValue((FLOAT)0.1f));
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:liquid-plastic:blur:strength", CConfigValue((FLOAT)2.0f));
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:liquid-plastic:aberration:strength", CConfigValue((FLOAT)0.01f));

    static auto P = HyprlandAPI::registerCallbackDynamic(PHANDLE, "preWindowRender", [&](void* self, SCallbackInfo& info, std::any data) {
        onPreWindowRender(self, info, data);
    });

    HyprlandAPI::addNotification(PHANDLE, "[Liquid Plastic] Hard-Linked!", CHyprColor{0.9f, 0.9f, 0.9f, 1.0f}, 5000);

    return {"liquid-plastic", "High-gloss liquid plastic effects", "dog", "1.0"};
}

APICALL EXPORT void PLUGIN_EXIT() {}
