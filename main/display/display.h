/*
UI实现架构

1. 分层架构设计
    Application (应用层)
        ↓
    Display (抽象接口层)
        ↓
    LvglDisplay/LcdDisplay/OledDisplay (具体实现层)
        ↓
    LVGL/裸机驱动 (硬件抽象层)

2. 核心组件结构

2.1 Display抽象类 (main/display/display.h)：

    定义了统一的显示接口：SetStatus(), ShowNotification(), SetEmotion(), SetChatMessage()
    支持主题切换：SetTheme(), GetTheme()
    提供显示锁定机制：DisplayLockGuard 防止并发访问

2.2 LvglDisplay具体实现 (main/display/lvgl_display/)：

    继承Display抽象类，实现LVGL图形界面
    管理状态栏：网络状态、电池状态、时间显示
    支持通知显示、表情渲染、聊天消息展示
    实现截图功能：SnapshotToJpeg()

3. 主题系统 (main/display/lvgl_display/lvgl_theme.h)：

3.1 LvglTheme类：

    完整的主题属性：背景色、文字色、聊天气泡色、字体等
    支持背景图片和emoji集合
    提供颜色解析功能：ParseColor()

3.2 LvglThemeManager：

    单例模式管理多个主题
    支持动态主题注册和切换
    内置light/dark主题

4. 资源管理系统 (main/assets.h)：

4.1Assets类：

    支持从网络下载资源包
    自动验证资源完整性（partition验证和checksum验证）
    支持增量更新
    统一资源访问接口：GetAssetData()

*/


#ifndef DISPLAY_H
#define DISPLAY_H

#include "emoji_collection.h"

#ifndef CONFIG_USE_EMOTE_MESSAGE_STYLE
#define HAVE_LVGL 1
#include <lvgl.h>
#endif

#include <esp_timer.h>
#include <esp_log.h>
#include <esp_pm.h>

#include <string>
#include <chrono>

// 3. 主题
class Theme {
public:
    Theme(const std::string& name) : name_(name) {}
    virtual ~Theme() = default;

    inline std::string name() const { return name_; }
private:
    std::string name_;
};

// 2. 核心组件结构
// 2.1 Display抽象类 (main/display/display.h)：
class Display {
public:
    Display();
    virtual ~Display();

    virtual void SetStatus(const char* status);
    virtual void ShowNotification(const char* notification, int duration_ms = 3000);
    virtual void ShowNotification(const std::string &notification, int duration_ms = 3000);
    virtual void SetEmotion(const char* emotion);
    virtual void SetChatMessage(const char* role, const char* content);
    virtual void SetTheme(Theme* theme);
    virtual Theme* GetTheme() { return current_theme_; }
    virtual void UpdateStatusBar(bool update_all = false);
    virtual void SetPowerSaveMode(bool on);

    inline int width() const { return width_; }
    inline int height() const { return height_; }

protected:
    int width_ = 0;
    int height_ = 0;

    Theme* current_theme_ = nullptr;

    friend class DisplayLockGuard;
    virtual bool Lock(int timeout_ms = 0) = 0;
    virtual void Unlock() = 0;
};

// 2.2 显示锁定机制：DisplayLockGuard 防止并发访问
class DisplayLockGuard {
public:
    DisplayLockGuard(Display *display) : display_(display) {
        if (!display_->Lock(30000)) {
            ESP_LOGE("Display", "Failed to lock display");
        }
    }
    ~DisplayLockGuard() {
        display_->Unlock();
    }

private:
    Display *display_;
};

// 空显示实现
class NoDisplay : public Display {
private:
    virtual bool Lock(int timeout_ms = 0) override {
        return true;
    }
    virtual void Unlock() override {}
};

#endif
