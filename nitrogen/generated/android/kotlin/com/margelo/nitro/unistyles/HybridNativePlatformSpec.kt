///
/// HybridNativePlatformSpec.kt
/// Fri Aug 16 2024
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/react-native-nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

package com.margelo.nitro.unistyles

import android.util.Log
import androidx.annotation.Keep
import com.facebook.jni.HybridData
import com.facebook.proguard.annotations.DoNotStrip
import com.margelo.nitro.HybridObject

/**
 * A Kotlin class representing the NativePlatform HybridObject.
 * Implement this abstract class to create Kotlin-based instances of NativePlatform.
 */
@DoNotStrip
@Keep
abstract class HybridNativePlatformSpec: HybridObject() {
  protected val TAG = "HybridNativePlatformSpec"

  // Properties
  

  // Methods
  @DoNotStrip
  @Keep
  abstract fun getColorScheme(): String
  
  @DoNotStrip
  @Keep
  abstract fun getFontScale(): Double
  
  @DoNotStrip
  @Keep
  abstract fun getContentSizeCategory(): String
  
  @DoNotStrip
  @Keep
  abstract fun setRootViewBackgroundColor(hex: String?, alpha: Double?): Unit
  
  @DoNotStrip
  @Keep
  abstract fun setNavigationBarBackgroundColor(hex: String?, alpha: Double?): Unit
  
  @DoNotStrip
  @Keep
  abstract fun setNavigationBarHidden(isHidden: Boolean): Unit
  
  @DoNotStrip
  @Keep
  abstract fun setStatusBarStyle(style: com.margelo.nitro.unistyles.StatusBarStyle): Unit
  
  @DoNotStrip
  @Keep
  abstract fun setStatusBarHidden(isHidden: Boolean): Unit
  
  @DoNotStrip
  @Keep
  abstract fun setStatusBarBackgroundColor(hex: String?, alpha: Double?): Unit
  
  @DoNotStrip
  @Keep
  abstract fun setImmersiveMode(isEnabled: Boolean): Unit

  companion object {
    private const val TAG = "HybridNativePlatformSpec"
    init {
      try {
        Log.i(TAG, "Loading unistyles C++ library...")
        System.loadLibrary("unistyles")
        Log.i(TAG, "Successfully loaded unistyles C++ library!")
      } catch (e: Error) {
        Log.e(TAG, "Failed to load unistyles C++ library! Is it properly installed and linked? " +
                    "Is the name correct? (see `CMakeLists.txt`, at `add_library(...)`)", e)
        throw e
      }
    }
  }
}
