#include "StyleSheetRegistry.h"

using namespace margelo::nitro::unistyles::core;

StyleSheet& StyleSheetRegistry::add(jsi::Runtime& rt, jsi::Object rawStyleSheet) {
    static unsigned int tag = 0;

    if (rawStyleSheet.isFunction(rt)) {
        return this->addFromFunction(rt, ++tag, rawStyleSheet.asFunction(rt));
    }

    return this->addFromObject(rt, ++tag, std::move(rawStyleSheet));
}

StyleSheet& StyleSheetRegistry::addFromObject(jsi::Runtime &rt, unsigned int tag, jsi::Object rawStyleSheet) {
    this->styleSheets.emplace_back(tag, core::StyleSheetType::Static, std::move(rawStyleSheet));

    return this->styleSheets.back();
}

StyleSheet& StyleSheetRegistry::addFromFunction(jsi::Runtime &rt, unsigned int tag, jsi::Function styleSheetFn) {
    auto numberOfArgs = styleSheetFn.getProperty(rt, "length").getNumber();

    helpers::assertThat(rt, numberOfArgs <= 2, "expected up to 2 arguments.");

    // stylesheet is still static, remove the function wrapper
    if (numberOfArgs == 0) {
        auto staticStyleSheet = styleSheetFn.call(rt).asObject(rt);

        this->styleSheets.emplace_back(tag, core::StyleSheetType::Static, std::move(staticStyleSheet));
    }

    // stylesheet depends only on theme
    if (numberOfArgs == 1) {
        this->styleSheets.emplace_back(tag, core::StyleSheetType::Themable, std::move(styleSheetFn));
    }

    // stylesheet depends on theme and mini runtime
    if (numberOfArgs == 2) {
        this->styleSheets.emplace_back(tag, core::StyleSheetType::ThemableWithMiniRuntime, std::move(styleSheetFn));
    }

    return this->styleSheets.back();
}

void StyleSheetRegistry::remove(unsigned int tag) {
    auto it = std::find_if(
        this->styleSheets.cbegin(),
        this->styleSheets.cend(),
        [tag](const StyleSheet& styleSheet){
            return styleSheet.tag == tag;
        }
    );

    if (it == this->styleSheets.cend()) {
        throw std::runtime_error("stylesheet with tag: " + std::to_string(tag) + " cannot be found.");
    }

    this->styleSheets.erase(it);
}

jsi::Object StyleSheetRegistry::parse(jsi::Runtime &rt, StyleSheet &styleSheet) {
    std::future<Dimensions> screenDimensions = std::async(std::launch::async, &HybridMiniRuntime::getScreen, miniRuntime);
    
    jsi::Object unwrappedStyleSheet = this->unwrapStyleSheet(rt, styleSheet);
    auto& unistyles = this->parseToUnistyles(rt, styleSheet, unwrappedStyleSheet);

    // configure and run parser
    auto& state = core::UnistylesRegistry::get().getState(rt);
    auto settings = std::make_unique<parser::ParserSettings>(
        styleSheet.variants,
        state.getCurrentBreakpointName(),
        state.getSortedBreakpointPairs(),
        screenDimensions.get()
    );
    
    return parser::Parser::configure(std::move(settings)).parseUnistyles(rt, unistyles);
}

jsi::Object StyleSheetRegistry::unwrapStyleSheet(jsi::Runtime &rt, StyleSheet &styleSheet) {
    // firstly we need to get object representation of user's StyleSheet
    // StyleSheet can be a function or an object

    // StyleSheet is already an object
    if (styleSheet.type == StyleSheetType::Static) {
        return jsi::Value(rt, styleSheet.rawValue).asObject(rt);
    }

    // StyleSheet is a function
    auto& state = core::UnistylesRegistry::get().getState(rt);
    auto theme = state.getJSTheme();

    if (styleSheet.type == StyleSheetType::Themable) {
        return styleSheet.rawValue
            .asFunction(rt)
            .call(rt, std::move(theme))
            .asObject(rt);
    }

    // stylesheet also has a mini runtime dependency
    // StyleSheetType::ThemableWithMiniRuntime
    auto& miniRuntime = state.getMiniRuntime();

    return styleSheet.rawValue
        .asFunction(rt)
        .call(rt, std::move(theme), miniRuntime)
        .asObject(rt);
}

std::vector<core::Unistyle>& StyleSheetRegistry::parseToUnistyles(jsi::Runtime& rt, StyleSheet& styleSheet, jsi::Object& unwrappedStyleSheet) {
    helpers::enumerateJSIObject(rt, unwrappedStyleSheet, [&](const std::string& styleKey, jsi::Value& propertyValue){
        helpers::assertThat(rt, propertyValue.isObject(), "style with name '" + styleKey + "' is not a function or object.");
        
        jsi::Object styleValue = propertyValue.asObject(rt);
        
        if (styleValue.isFunction(rt)) {
            styleSheet.unistyles.emplace_back(UnistyleType::DynamicFunction, styleKey, styleValue);
            
            return;
        }

        styleSheet.unistyles.emplace_back(UnistyleType::Object, styleKey, styleValue);
    });
    
    return styleSheet.unistyles;
}
