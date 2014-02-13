#ifndef _ANIMFILELOADER_H_
#define _ANIMFILELOADER_H_

#include "ImageList.h"

// Simple class to help in the loading of the animations
// of a sprite.
class CAnimFileLoader
{
public:
	CAnimFileLoader(const std::string& strFile, unsigned imgsPerRow, 
			unsigned imgWidth, unsigned imgHeight);
	~CAnimFileLoader();

	CImageList GetAnimation(unsigned startIndex, unsigned stopIndex);

private:
	std::string m_strFileName;

	unsigned m_uImgWidth;
	unsigned m_uImgHeight;
	unsigned m_uImgsPerRow;
};

#endif  // _ANIMFILELOADER_H_
