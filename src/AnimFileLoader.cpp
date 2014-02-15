#include "AnimFileLoader.h"

#include <string>
using namespace std;

CAnimFileLoader::CAnimFileLoader(const string& strFile,
                                 unsigned imgsPerRow,
                                 unsigned imgWidth,
                                 unsigned imgHeight)
:	m_strFileName(strFile), m_uImgsPerRow(imgsPerRow),
    m_uImgWidth(imgWidth), m_uImgHeight(imgHeight)
{
}

CAnimFileLoader::~CAnimFileLoader()
{
}

CImageList CAnimFileLoader::GetAnimation(unsigned startIndex,
                                         unsigned stopIndex)
{
    CImageList newImgList;

    for (unsigned i=startIndex; i<=stopIndex; i++)
    {
        unsigned row = i/m_uImgsPerRow;
        unsigned col = i%m_uImgsPerRow;

        TRectanglei imgRect(row*m_uImgHeight,(row+1)*m_uImgHeight,
                            col*m_uImgWidth, (col+1)*m_uImgWidth);
        newImgList.AppendImage(
            CImage::CreateImage(m_strFileName,imgRect));
    }

    return newImgList;
}

