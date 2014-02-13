/***************************************************************
 * Name:      Tetro2App.cpp
 * Purpose:   Code for Application Class
 * Author:    CHEN Junshi (cjshappy@163.com)
 * Created:   2014-02-12
 * Copyright: CHEN Junshi ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "glapp.h"

//(*AppHeaders
#include "glmainwindow.h"
#include <wx/image.h>
#include <wx/log.h>
#include <stdio.h>
//*)

IMPLEMENT_APP(GLApp);

bool GLApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	GLMainWindow* Frame = new GLMainWindow(0);
    	Frame->Show();
    	SetTopWindow(Frame);

        m_pLogFile = fopen("log.txt", "w+");
        delete wxLog::SetActiveTarget(new wxLogStderr(m_pLogFile));
        wxLog::SetTimestamp(wxT("%Y-%m-%d %H:%M:%S"));
        wxLog::SetLogLevel(wxLOG_Info);

        wxLogMessage("Launch Application.");
    }
    //*)
    return wxsOK;
}

int GLApp::OnExit()
{
    fclose(m_pLogFile);
    return 0;
}
