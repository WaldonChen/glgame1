/***************************************************************
 * Name:      glapp.h
 * Purpose:   Defines Application Class
 * Author:    CHEN Junshi (cjshappy@163.com)
 * Created:   2014-02-12
 * Copyright: CHEN Junshi (2014-2024)
 * License:
 **************************************************************/
#ifndef _GL_APP_H_
#define _GL_APP_H_

#include <wx/app.h>
#include <stdio.h>

class GLApp : public wxApp
{
public:
    virtual bool OnInit();
    virtual int OnExit();

private:
    FILE *m_pLogFile;
};

DECLARE_APP(GLApp);

#endif	// _GL_APP_H_


