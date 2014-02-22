#ifndef _GL_MAIN_CANVAS_H_
#define _GL_MAIN_CANVAS_H_

#include <string>

#include <wx/glcanvas.h>
#include <wx/timer.h>

#include "Image.h"
#include "AnimatedSprite.h"

/**
 * The rendering context used by all GL canvas.
 */
class GLMainContext : public wxGLContext
{
public:
    GLMainContext(wxGLCanvas *canvas);
    virtual ~GLMainContext() { }

    bool InitGL();
    void ResizeGL(int, int);
    // void CleanGL();
    void DrawScene();
    void UpdateAnimation();
    void UpdateLogic();

private:
    // The image for the grass.
    TImagePtr m_pGrassImg;

    // Images for the trees
    TImagePtr m_pTreesImg[16];

    // The animated sprite of the knight
    CAnimatedSprite* m_pKnightSprite;

    // The last direction of the knight
    std::string m_strLastDir;

public:
    bool m_KeysDown[256];
};

class GLMainCanvas : public wxGLCanvas
{
public:
    GLMainCanvas(wxWindow *parent, wxWindowID id = wxID_ANY,
                 const int *attribList = NULL,
                 const wxPoint &pos = wxDefaultPosition,
                 const wxSize &size = wxDefaultSize,
                 long style = 0,
                 const wxString &name = "GLMainCanvas",
                 const wxPalette &palette = wxNullPalette);
    virtual ~GLMainCanvas();
    GLMainContext& GetGLContext();
    void Pause();
    void Start();

private:
    void OnSize(wxSizeEvent &);
    void OnPaint(wxPaintEvent &);
    void OnMouseEvent(wxMouseEvent &);
    void OnKeyUp(wxKeyEvent &);
    void OnKeyDown(wxKeyEvent &);
    void OnTimer(wxTimerEvent &);
    DECLARE_EVENT_TABLE();

    static const long ID_TIMER1;

    wxTimer m_timer;
    GLMainContext *m_glContext;

    bool m_pause;

    bool m_active;
    bool m_fullscreen;
};

#endif // _GL_MAIN_CANVAS_H_
