#pragma once

#define WLR_USE_UNSTABLE

#include <hyprland/src/render/decorations/IHyprWindowDecoration.hpp>
#include <hyprland/src/render/OpenGL.hpp>
#include <hyprland/src/devices/IPointer.hpp>
#include "globals.hpp"

class CHyprBar : public IHyprWindowDecoration {
  public:
    CHyprBar(PHLWINDOW);
    virtual ~CHyprBar();

    virtual SDecorationPositioningInfo getPositioningInfo();

    virtual void                       onPositioningReply(const SDecorationPositioningReply& reply);

    virtual void                       draw(PHLMONITOR, float const& a);

    virtual eDecorationType            getDecorationType();

    virtual void                       updateWindow(PHLWINDOW);

    virtual void                       damageEntire();

    virtual eDecorationLayer           getDecorationLayer();

    virtual uint64_t                   getDecorationFlags();

    bool                               m_bButtonsDirty = true;

    virtual std::string                getDisplayName();

    PHLWINDOW                          getOwner();

    void                               updateRules();
    void                               applyRule(const SP<CWindowRule>&);

  private:
    SBoxExtents               m_seExtents;

    PHLWINDOWREF              m_pWindow;

    CBox                      m_bAssignedBox;

    SP<CTexture>              m_pTextTex;
    SP<CTexture>              m_pButtonsTex;

    bool                      m_bWindowSizeChanged = false;
    bool                      m_bHidden            = false;
    bool                      m_bTitleColorChanged = false;
    std::optional<CHyprColor> m_bForcedBarColor;
    std::optional<CHyprColor> m_bForcedTitleColor;

    Vector2D                  cursorRelativeToBar();

    void                      renderPass(PHLMONITOR, float const& a);
    void                      renderBarTitle(const Vector2D& bufferSize, const float scale);
    void                      renderText(SP<CTexture> out, const std::string& text, const CHyprColor& color, const Vector2D& bufferSize, const float scale, const int fontSize);
    void                      renderBarButtons(const Vector2D& bufferSize, const float scale);
    void                      renderBarButtonsText(CBox* barBox, const float scale, const float a);
    void                      onMouseDown(SCallbackInfo& info, IPointer::SButtonEvent e);
    void                      onMouseMove(Vector2D coords);
    CBox                      assignedBoxGlobal();

    SP<HOOK_CALLBACK_FN>      m_pMouseButtonCallback;
    SP<HOOK_CALLBACK_FN>      m_pMouseMoveCallback;

    std::string               m_szLastTitle;

    bool                      m_bDraggingThis  = false;
    bool                      m_bDragPending   = false;
    bool                      m_bCancelledDown = false;

    // for dynamic updates
    int m_iLastHeight = 0;

    friend class CBarPassElement;
};
