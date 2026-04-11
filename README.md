# 🧪 Liquid Plastic for Hyprland

A high-gloss, industrial-strength "liquid plastic" effect for Hyprland v0.51+. This plugin provides live-configurable refraction and chromatic aberration sliders for a synthetic, viscous look.

## ✨ Features
- **Real-time Refraction**: Warp background pixels like thick molded plastic.
- **Chromatic Aberration**: Color-fringing at window edges for an optical "lens" effect.
- **Hyprpm Compatible**: Fully managed by the official Hyprland plugin manager.

## 🚀 Installation

1. **Add the plugin**:
   bash
   hyprpm add https://github.com/naddog1313/liquid-plastic-hyprpm
   hyprpm enable liquid-plastic
2. Example config
3. plugin {
    liquid-plastic {
        refraction:strength = 0.05
        refraction:roughness = 0.5
        blur:strength = 2
        aberration:strength = 0.05
    }
}

# This is the "on" switch for the visual warping
windowrulev2 = plugin:liquid-plastic:shader, class:.*
also YOU MUST HAVE BLUR TRUE IN YOUR DECORATION AND PASSES AT 3 Then you are good :)
