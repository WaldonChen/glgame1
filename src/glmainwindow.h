#ifndef _GL_MAIN_WINDOW_H_
#define _GL_MAIN_WINDOW_H_

//(*Headers(GLMainWindow)
#include <wx/frame.h>
//*)

class GLMainCanvas;

class GLMainWindow: public wxFrame
{
	public:

		GLMainWindow(wxWindow* parent, wxWindowID id=wxID_ANY,
                     const wxPoint& pos=wxDefaultPosition,
                     const wxSize& size=wxDefaultSize);
		virtual ~GLMainWindow();

		//(*Declarations(GLMainWindow)
		//*)

	protected:

		//(*Identifiers(GLMainWindow)
		//*)

	private:

		//(*Handlers(GLMainWindow)
        /* void OnKeyDown(wxKeyEvent &);
        void OnKeyUp(wxKeyEvent &); */
		//*)

		DECLARE_EVENT_TABLE()

		GLMainCanvas *m_GLMainCanvas;
};

#endif
