///
/// HybridUnistylesRuntimeSpec.cpp
/// Fri Aug 16 2024
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/react-native-nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#include "HybridUnistylesRuntimeSpec.hpp"

namespace margelo::nitro::unistyles {

  void HybridUnistylesRuntimeSpec::loadHybridMethods() {
    // load base methods/properties
    HybridObject::loadHybridMethods();
    // load custom methods/properties
    registerHybrids(this, [](Prototype& prototype) {
      prototype.registerHybridGetter("colorScheme", &HybridUnistylesRuntimeSpec::getColorScheme);
      prototype.registerHybridGetter("hasAdaptiveThemes", &HybridUnistylesRuntimeSpec::getHasAdaptiveThemes);
      prototype.registerHybridGetter("screen", &HybridUnistylesRuntimeSpec::getScreen);
      prototype.registerHybridGetter("themeName", &HybridUnistylesRuntimeSpec::getThemeName);
      prototype.registerHybridGetter("contentSizeCategory", &HybridUnistylesRuntimeSpec::getContentSizeCategory);
      prototype.registerHybridGetter("breakpoint", &HybridUnistylesRuntimeSpec::getBreakpoint);
      prototype.registerHybridGetter("insets", &HybridUnistylesRuntimeSpec::getInsets);
      prototype.registerHybridGetter("orientation", &HybridUnistylesRuntimeSpec::getOrientation);
      prototype.registerHybridGetter("pixelRatio", &HybridUnistylesRuntimeSpec::getPixelRatio);
      prototype.registerHybridGetter("fontScale", &HybridUnistylesRuntimeSpec::getFontScale);
      prototype.registerHybridMethod("setTheme", &HybridUnistylesRuntimeSpec::setTheme);
      prototype.registerHybridMethod("setAdaptiveThemes", &HybridUnistylesRuntimeSpec::setAdaptiveThemes);
      prototype.registerHybridMethod("setImmersiveMode", &HybridUnistylesRuntimeSpec::setImmersiveMode);
      prototype.registerHybridMethod("setRootViewBackgroundColor", &HybridUnistylesRuntimeSpec::setRootViewBackgroundColor);
    });
  }

} // namespace margelo::nitro::unistyles
