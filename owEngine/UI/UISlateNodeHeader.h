#pragma once

// Common UI
#include "UIBaseNode.h"
#include "UIColor.h"
#include "UIText.h"
#include "UITexture.h"

// Slate
#include "UISlateEditorInterfaces.h"

// FORWARD BEGIN
class CUISlateEditor;
class CUISlateNode;
// FORWARD END

class CUISlateNodeHeader : public CUIBaseNode
{
    typedef CUIBaseNode base;
public:
    CUISlateNodeHeader(std::weak_ptr<CUISlateEditor> Editor);
    virtual ~CUISlateNodeHeader();

    // CUISlateNodeHeader
    void CreateDefault();

    // CUIBaseNode
    virtual std::vector<std::shared_ptr<CUIBaseNode>> GetChilds() const override;

    // Input events
    bool OnMouseButtonPressed(MouseButtonEventArgs& e) override;
    void OnMouseButtonReleased(MouseButtonEventArgs& e) override;

private:
    std::shared_ptr<CUIColorNode>       m_Background;
    std::shared_ptr<CUITextureNode>     m_IconNode;
    std::shared_ptr<CUITextNode>        m_Text;

    // Weak refs
    std::weak_ptr<CUISlateEditor>       m_Editor;
};