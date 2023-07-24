#include "Font.h" 
#include <SDL2-2.28.0/include/SDL_ttf.h> 

namespace kiko 
{ 
	Font::Font(const std::string& filename, int fontSize) 
	{ 
		Load(filename, fontSize);
	} 
	Font::~Font() 
	{ 
		if (m_ttfFont != nullptr)
		{
			TTF_CloseFont(m_ttfFont);
		}
	} 
	void Font::Load(const std::string& filename, int fontSize) 
	{ 
		const char* fstr = filename.c_str();
		m_ttfFont = TTF_OpenFont(fstr, fontSize);
	} 
}