///
/// HybridUnistylesStatusBarSpec.hpp
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#pragma once

#if __has_include(<NitroModules/HybridObject.hpp>)
#include <NitroModules/HybridObject.hpp>
#else
#error NitroModules cannot be found! Are you sure you installed NitroModules properly?
#endif





namespace margelo::nitro::unistyles {

  using namespace margelo::nitro;

  /**
   * An abstract base class for `UnistylesStatusBar`
   * Inherit this class to create instances of `HybridUnistylesStatusBarSpec` in C++.
   * @example
   * ```cpp
   * class HybridUnistylesStatusBar: public HybridUnistylesStatusBarSpec {
   *   // ...
   * };
   * ```
   */
  class HybridUnistylesStatusBarSpec: public virtual HybridObject {
    public:
      // Constructor
      explicit HybridUnistylesStatusBarSpec(): HybridObject(TAG) { }

      // Destructor
      virtual ~HybridUnistylesStatusBarSpec() { }

    public:
      // Properties
      virtual double getWidth() = 0;
      virtual double getHeight() = 0;

    public:
      // Methods
      virtual void setBackgroundColor(double color) = 0;

    protected:
      // Hybrid Setup
      void loadHybridMethods() override;

    protected:
      // Tag for logging
      static constexpr auto TAG = "UnistylesStatusBar";
  };

} // namespace margelo::nitro::unistyles
