#include <Geode/Geode.hpp>
#include <Geode/modify/EndLevelLayer.hpp>

using namespace geode::prelude;

static std::string formatWithCommas(int value) {
    auto str = std::to_string(value);
    std::string result;
    int count = 0;
    for (int i = str.size() - 1; i >= 0; i--) {
        if (count > 0 && count % 3 == 0) result = ',' + result;
        result = str[i] + result;
        count++;
    }
    return result;
}

static CCNode* findChildRecursive(CCNode* parent, std::string_view id) {
    if (!parent) return nullptr;
    
    auto* children = parent->getChildren();
    if (!children) return nullptr;

    for (int i = 0; i < children->count(); i++) {
        auto* child = static_cast<CCNode*>(children->objectAtIndex(i));
        if (!child) continue;

        if (child->getID() == id) return child;

        auto* found = findChildRecursive(child, id);
        if (found) return found;
    }
    return nullptr;
}

class $modify(TotalAttemptsEndLevel, EndLevelLayer) {
    void customSetup() {
        EndLevelLayer::customSetup();

        auto* level = m_playLayer->m_level;
        if (!level) return;

        if (Mod::get()->getSettingValue<bool>("total-attempts")) {
            if (auto* label = findChildRecursive(this, "attempts-label")) {
                if (auto* bmfont = typeinfo_cast<CCLabelBMFont*>(label)) {
                    bmfont->setString(
                        ("Total Attempts: " + formatWithCommas(level->m_attempts)).c_str()
                    );
                }
            }
        }

        if (Mod::get()->getSettingValue<bool>("total-jumps")) {
            if (auto* label = findChildRecursive(this, "jumps-label")) {
                if (auto* bmfont = typeinfo_cast<CCLabelBMFont*>(label)) {
                    bmfont->setString(
                        ("Total Jumps: " + formatWithCommas(level->m_jumps)).c_str()
                    );
                }
            }
        }
    }
};
