#ifndef _ANIMATEDSPRITE_H_
#define _ANIMATEDSPRITE_H_

#include "Image.h"
#include "ImageList.h"
#include <string>
#include <map>
#include <list>

// This class represent an animated sprite: it is able to play
// different animations that were previously loaded.
class CAnimatedSprite
{
public:
	// Default constructor and destructor.
	CAnimatedSprite();
	~CAnimatedSprite();

	// Adds a new animation for the sprite. The strAnimName 
	// is a string that identifies the animation and should 
	// be unique for this sprite.
	void AddAnimation(const std::string& strAnimName, 
					  const CImageList& lstAnimation);
	// Plays a previously loaded animation. The strAnimName
	// is the name that was passed when calling AddAnimation.
	void PlayAnimation(const std::string& strAnimName);

	// Draw the current frame of the animation at the sprite
	// current position.
	void DrawSprite();
	// Go to the next animation frame.
	void NextFrame();

	// Set the position of the sprite
	void SetPosition(int XPos, int YPos) 
	{
		m_iXPos = XPos;
		m_iYPos = YPos;
	}
	// Move the sprite from its current position
	void OffsetPosition(int XOffset, int YOffset) 
	{
		m_iXPos += XOffset;
		m_iYPos += YOffset;
	}

private:
	typedef std::map<std::string, CImageList> TAnimMap;
	typedef TAnimMap::iterator TAnimMapIter;

	// Map containing all the animations that can be 
	// played.
	TAnimMap m_mapAnimations;
	// Iterator to the current animation being played
	TAnimMapIter  m_iterCurrentAnim;

	// Position of the sprite
	int m_iXPos;
	int m_iYPos;
};

#endif  // _ANIMATEDSPRITE_H_