#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

namespace {
    constexpr char const* kPrefix = "ollfx.gdtoolkit.";

    float getSpeed() {
        return Mod::get()->getSavedValue<float>(std::string(kPrefix) + "speed", 1.0f);
    }

    class ToolkitPanel final : public FLAlertLayer {
    public:
        static ToolkitPanel* create() {
            auto ret = new ToolkitPanel();
            if (ret->init(150.f)) {
                ret->autorelease();
                return ret;
            }
            delete ret;
            return nullptr;
        }

        bool init(float) {
            if (!FLAlertLayer::init(nullptr, "oll.fx // GD TOOLKIT",
                "close", nullptr, 300.f, true, 190.f)) return false;

            auto win = CCDirector::sharedDirector()->getWinSize();
            auto panel = CCScale9Sprite::create("square02_001.png",
                CCRect(0, 0, 80, 80), CCRect(20, 20, 40, 40));
            panel->setContentSize({280.f, 250.f});
            panel->setColor({20, 24, 36});
            panel->setOpacity(245);
            panel->setPosition({win.width / 2, win.height / 2});
            this->addChild(panel, -1);

            auto heading = CCLabelBMFont::create("PRACTICE TOOLKIT", "bigFont.fnt");
            heading->setScale(.48f);
            heading->setPosition({win.width / 2, win.height / 2 + 96.f});
            this->addChild(heading);

            auto hint = CCLabelBMFont::create("offline / practice use", "goldFont.fnt");
            hint->setScale(.38f);
            hint->setPosition({win.width / 2, win.height / 2 + 76.f});
            this->addChild(hint);

            auto status = CCLabelBMFont::create(
                "Use Geode mod settings to configure available features.", "chatFont.fnt");
            status->setScale(.42f);
            status->setWidth(245.f);
            status->setAlignment(kCCTextAlignmentCenter);
            status->setPosition({win.width / 2, win.height / 2 + 20.f});
            this->addChild(status);

            auto note = CCLabelBMFont::create(
                "Noclip / hitboxes / completion / icon unlocks\\nneed version-specific hooks and are not active in this build.",
                "chatFont.fnt");
            note->setScale(.38f);
            note->setWidth(245.f);
            note->setAlignment(kCCTextAlignmentCenter);
            note->setPosition({win.width / 2, win.height / 2 - 28.f});
            this->addChild(note);

            auto speed = CCLabelBMFont::create(
                fmt::format("speed multiplier: {:.2f}x", getSpeed()).c_str(), "bigFont.fnt");
            speed->setScale(.42f);
            speed->setPosition({win.width / 2, win.height / 2 - 82.f});
            this->addChild(speed);
            return true;
        }
    };
}

class $modify(ToolkitMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        auto menu = this->getChildByID("bottom-menu");
        if (!menu) menu = this->getChildByID("main-menu");
        if (!menu) return true;

        auto spr = CCLabelBMFont::create("oll.fx", "bigFont.fnt");
        spr->setScale(.5f);
        auto item = CCMenuItemSpriteExtra::create(
            spr, this, menu_selector(ToolkitMenuLayer::onToolkit));
        item->setID("ollfx-toolkit-button");
        menu->addChild(item);
        menu->updateLayout();
        return true;
    }

    void onToolkit(CCObject*) {
        if (auto panel = ToolkitPanel::create()) panel->show();
    }
};

class $modify(ToolkitPlayLayer, PlayLayer) {
    void update(float dt) {
        float multiplier = std::clamp(getSpeed(), 0.25f, 2.0f);
        PlayLayer::update(dt * multiplier);
    }
};
