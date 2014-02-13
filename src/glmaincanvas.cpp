#include "glmaincanvas.h"
#include "glapp.h"

#include <iostream>

#include <wx/dcclient.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "TextureManager.h"
#include "AnimFileLoader.h"

static int attriblist[] = {
    WX_GL_RGBA, WX_GL_MIN_RED, 1, WX_GL_MIN_GREEN, 1,
    WX_GL_MIN_BLUE, 1, WX_GL_DEPTH_SIZE, 1, WX_GL_DOUBLEBUFFER, None
};

static void CheckGLError()
{
    GLenum errLast = GL_NO_ERROR;

    while (true) {
        GLenum err = glGetError();
        if (err == GL_NO_ERROR) {
            return;
        }
        if (err == errLast) {
            wxLogError(wxT("OpenGL error state could not be reset."));
            return;
        }
        errLast = err;
        wxLogError(wxT("OpenGL error %d"), err);
    }
}

GLMainContext::GLMainContext(wxGLCanvas *canvas)
    : wxGLContext(canvas)
{
    SetCurrent(*canvas);

    InitGL();
    CheckGLError();

    // Load the grass image and set the color key
    m_pGrassImg = CImage::CreateImage("res/GrassIso.bmp");
    m_pGrassImg->GetTexture()->SetColorKey(0, 128, 128);

    // Load the tree images
    for (int i=0; i<16; i++)
    {
        TRectanglei imgRect(i/4*128,(i/4+1)*128,(i%4)*128,(i%4+1)*128);
        m_pTreesImg[i] = CImage::CreateImage("res/Trees.bmp",imgRect);
    }
    CTextureManager::GetInstance()->GetTexture("res/Trees.bmp")
        ->SetColorKey(191, 123, 199);

    // Load all the 'walk' animations for the knight.
    m_pKnightSprite = new CAnimatedSprite;
    CAnimFileLoader fileLoader1("res/KnightWalk.bmp", 8, 96, 96);
    CTextureManager::GetInstance()->GetTexture("res/KnightWalk.bmp")
        ->SetColorKey(111, 79, 51);
    m_pKnightSprite->AddAnimation("WalkE",
                                  fileLoader1.GetAnimation(0,7));
    m_pKnightSprite->AddAnimation("WalkSE",
                                  fileLoader1.GetAnimation(8,15));
    m_pKnightSprite->AddAnimation("WalkS",
                                  fileLoader1.GetAnimation(16,23));
    m_pKnightSprite->AddAnimation("WalkSW",
                                  fileLoader1.GetAnimation(24,31));
    m_pKnightSprite->AddAnimation("WalkW",
                                  fileLoader1.GetAnimation(32,39));
    m_pKnightSprite->AddAnimation("WalkNW",
                                  fileLoader1.GetAnimation(40,47));
    m_pKnightSprite->AddAnimation("WalkN",
                                  fileLoader1.GetAnimation(48,55));
    m_pKnightSprite->AddAnimation("WalkNE",
                                  fileLoader1.GetAnimation(56,63));

    // Load all the 'pause' animations for the knight.
    CAnimFileLoader fileLoader2("res/KnightPause.bmp", 8, 96, 96);
    CTextureManager::GetInstance()->GetTexture("res/KnightPause.bmp")
        ->SetColorKey(111, 79, 51);
    m_pKnightSprite->AddAnimation("PauseE",
                                  fileLoader2.GetAnimation(0,7));
    m_pKnightSprite->AddAnimation("PauseSE",
                                  fileLoader2.GetAnimation(8,15));
    m_pKnightSprite->AddAnimation("PauseS",
                                  fileLoader2.GetAnimation(16,23));
    m_pKnightSprite->AddAnimation("PauseSW",
                                  fileLoader2.GetAnimation(24,31));
    m_pKnightSprite->AddAnimation("PauseW",
                                  fileLoader2.GetAnimation(32,39));
    m_pKnightSprite->AddAnimation("PauseNW",
                                  fileLoader2.GetAnimation(40,47));
    m_pKnightSprite->AddAnimation("PauseN",
                                  fileLoader2.GetAnimation(48,55));
    m_pKnightSprite->AddAnimation("PauseNE",
                                  fileLoader2.GetAnimation(56,63));
    m_pKnightSprite->PlayAnimation("PauseE");

    /* for (int i = 0; i < 256; ++i) {
        m_KeysDown[i] = false;
    } */
    m_KeysDown[WXK_LEFT] = false;
    m_KeysDown[WXK_RIGHT] = false;
    m_KeysDown[WXK_UP] = false;
    m_KeysDown[WXK_DOWN] = false;

    m_strLastDir = "E";
    m_pKnightSprite->SetPosition(350, 250);
}

bool GLMainContext::InitGL()
{
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);

    return true;
}

void GLMainContext::ResizeGL(int width, int height)
{
    if (height == 0) {
        height = 1;
    }
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLMainContext::DrawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the grass
    int xPos=0, yPos=0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            xPos = i * 256/2 - 128;
            if (i%2)
                yPos = (j * 128) - 128/2;
            else
                yPos = (j * 128);

            m_pGrassImg->BlitImage(xPos, yPos);
        }
    }

    // Draw some trees
    m_pTreesImg[0]->BlitImage(15,25);
    m_pTreesImg[1]->BlitImage(695,55);
    m_pTreesImg[2]->BlitImage(15,25);
    m_pTreesImg[3]->BlitImage(300,400);
    m_pTreesImg[4]->BlitImage(125,75);
    m_pTreesImg[5]->BlitImage(350,250);
    m_pTreesImg[6]->BlitImage(400,350);
    m_pTreesImg[7]->BlitImage(350,105);
    m_pTreesImg[8]->BlitImage(530,76);
    m_pTreesImg[9]->BlitImage(125,450);
    m_pTreesImg[10]->BlitImage(425,390);
    m_pTreesImg[11]->BlitImage(25,125);
    m_pTreesImg[12]->BlitImage(550,365);
    m_pTreesImg[13]->BlitImage(680,250);
    m_pTreesImg[14]->BlitImage(245,325);
    m_pTreesImg[15]->BlitImage(300,245);

    // Draw the knight
    m_pKnightSprite->DrawSprite();
    // Move to the next frame of the animation
    m_pKnightSprite->NextFrame();

    glFlush();
    CheckGLError();
}

void GLMainContext::UpdateAnimation()
{
    // First check if at least one key is pressed
    bool keyPressed = false;
    if (m_KeysDown[WXK_LEFT] || m_KeysDown[WXK_RIGHT]
        || m_KeysDown[WXK_UP] || m_KeysDown[WXK_DOWN]) {
            keyPressed = true;
    }

    std::string strAnim;
    if (!keyPressed) {
        strAnim = "Pause" + m_strLastDir;
    }
    if (keyPressed) {
        std::string vertDir;
        std::string horizDir;

        if (m_KeysDown[WXK_UP]) {
            vertDir = "N";
        } else if (m_KeysDown[WXK_DOWN]) {
            vertDir = "S";
        }

        if (m_KeysDown[WXK_LEFT]) {
            horizDir = "W";
        } else if (m_KeysDown[WXK_RIGHT]) {
            horizDir = "E";
        }

        m_strLastDir = vertDir + horizDir;
        strAnim = "Walk" + m_strLastDir;
    }

    m_pKnightSprite->PlayAnimation(strAnim);
    // wxLogMessage("Sprite %s", strAnim);
}

void GLMainContext::UpdateLogic()
{
    int xOffset = 0;
    int yOffset = 0;

    if (m_KeysDown[WXK_UP]) {
        yOffset -= 5;
    }
    if (m_KeysDown[WXK_DOWN]) {
        yOffset += 5;
    }
    if (m_KeysDown[WXK_LEFT]) {
        xOffset -= 5;
    }
    if (m_KeysDown[WXK_RIGHT]) {
        xOffset += 5;
    }
    m_pKnightSprite->OffsetPosition(xOffset, yOffset);
    // wxLogMessage("Sprite offset position: %d, %d", xOffset, yOffset);
}

const long GLMainCanvas::ID_TIMER1 = wxNewId();

BEGIN_EVENT_TABLE(GLMainCanvas, wxGLCanvas)
    EVT_SIZE(GLMainCanvas::OnSize)
    EVT_PAINT(GLMainCanvas::OnPaint)
    EVT_MOUSE_EVENTS(GLMainCanvas::OnMouseEvent)
    EVT_KEY_DOWN(GLMainCanvas::OnKeyDown)
    EVT_KEY_UP(GLMainCanvas::OnKeyUp)
    EVT_TIMER(ID_TIMER1, GLMainCanvas::OnTimer)
END_EVENT_TABLE()

GLMainCanvas::GLMainCanvas(wxWindow *parent, wxWindowID id,
                 const int *attribList,
                 const wxPoint &pos,
                 const wxSize &size,
                 long style,
                 const wxString &name,
                 const wxPalette &palette)
    : wxGLCanvas(parent, id, attribList, pos, size, style, name, palette),
      m_glContext(NULL), m_pause(true)
{
    m_timer.SetOwner(this, ID_TIMER1);
}

GLMainContext& GLMainCanvas::GetGLContext()
{
    if (!m_glContext) {
        m_glContext = new GLMainContext(this);
    }
    m_glContext->SetCurrent(*this);

    return *m_glContext;
}

GLMainCanvas::~GLMainCanvas()
{
    m_timer.Stop();
    delete m_glContext;
}

void GLMainCanvas::Pause()
{
    m_timer.Stop();
}

void GLMainCanvas::Start()
{
    if (!m_timer.IsRunning()) {
        m_timer.Start(80);
    }
}

void GLMainCanvas::OnSize(wxSizeEvent &event)
{
    if (!IsShownOnScreen()) {
        return;
    }
    wxSize size = GetClientSize();
    GLMainContext &canvas = GetGLContext();
    canvas.ResizeGL(size.x, size.y);
}

void GLMainCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    const wxSize client_size = GetClientSize();

    GLMainContext& canvas = GetGLContext();
    glViewport(0, 0, client_size.x, client_size.y);

    canvas.DrawScene();

    SwapBuffers();
}

void GLMainCanvas::OnMouseEvent(wxMouseEvent &event)
{
}

void GLMainCanvas::OnKeyUp(wxKeyEvent &event)
{
    GLMainContext& canvas = GetGLContext();
    canvas.m_KeysDown[event.GetKeyCode()] = false;
    canvas.UpdateAnimation();
}

void GLMainCanvas::OnKeyDown(wxKeyEvent &event)
{
    GLMainContext& canvas = GetGLContext();
    canvas.m_KeysDown[event.GetKeyCode()] = true;
    canvas.UpdateAnimation();
    wxLogMessage("key %d down", event.GetKeyCode());
}

void GLMainCanvas::OnTimer(wxTimerEvent &event)
{
    GLMainContext& canvas = GetGLContext();
    canvas.UpdateLogic();
    Refresh();
}
