#include "AnimatedSprite.h"
#include "Exception.h"

using namespace std;

CAnimatedSprite::CAnimatedSprite() : m_iXPos(0), m_iYPos(0)
{
}

CAnimatedSprite::~CAnimatedSprite()
{
}

void CAnimatedSprite::AddAnimation(const string &strAnimName,
                                   const CImageList& lstAnimation)
{
    m_mapAnimations[strAnimName] = lstAnimation;
}

void CAnimatedSprite::PlayAnimation(const string &strAnimName)
{
    m_iterCurrentAnim = m_mapAnimations.find(strAnimName);
    if (m_iterCurrentAnim == m_mapAnimations.end())
    {
        string strError = "Unable to play: " + strAnimName;
        strError += ". Animation not found.";
        throw CException(strError);
    }
}

void CAnimatedSprite::DrawSprite()
{
    if (m_iterCurrentAnim == m_mapAnimations.end())
        return;
    m_iterCurrentAnim->second.GetCurrentImage()
        ->BlitImage(m_iXPos,m_iYPos);
}

void CAnimatedSprite::NextFrame()
{
    if (m_iterCurrentAnim == m_mapAnimations.end())
        return;

    m_iterCurrentAnim->second.GoToNextImage();
}
