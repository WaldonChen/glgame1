#include "glmainwindow.h"
#include "glmaincanvas.h"

#include <iostream>

//(*InternalHeaders(GLMainWindow)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(GLMainWindow)
//*)

BEGIN_EVENT_TABLE(GLMainWindow,wxFrame)
	//(*EventTable(GLMainWindow)
	//*)
END_EVENT_TABLE()

GLMainWindow::GLMainWindow(wxWindow* parent,wxWindowID id,const wxPoint& pos,
                           const wxSize& size)
{
	//(*Initialize(GLMainWindow)
	Create(parent, id, _("GLMainWindow"), wxDefaultPosition, wxDefaultSize,
           wxDEFAULT_FRAME_STYLE, _T("id"));
	// SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	//*)

    int attriblist[] = {
        WX_GL_RGBA, WX_GL_MIN_RED, 1, WX_GL_MIN_GREEN, 1,
        WX_GL_MIN_BLUE, 1, WX_GL_DEPTH_SIZE, 1, WX_GL_DOUBLEBUFFER, None
    };
	m_GLMainCanvas = new GLMainCanvas(this, wxID_ANY, attriblist, wxDefaultPosition,
                                      GetClientSize(), wxSUNKEN_BORDER);
    SetClientSize(800, 600);
    m_GLMainCanvas->Start();
}

GLMainWindow::~GLMainWindow()
{
	//(*Destroy(GLMainWindow)
	//*)
	delete m_GLMainCanvas;
}
