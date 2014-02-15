#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <string>

class CException : public std::exception
{
public:
    const char* what() const throw() { return m_strMessage.c_str(); }

    CException(const std::string& strMessage="") : m_strMessage(strMessage)  { }
    virtual ~CException() throw() { }

    std::string m_strMessage;
};

#endif  // _EXCEPTION_H_
