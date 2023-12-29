#define MENUBUTTON_H
#include "include.h"

class MenuButton {

public:

	MenuButton(	// if align or justify > rect limit > align / justify = centered
		int width, int height, int posx, int posy, int windowwidth, int windowheight,
		int text_aling, int text_justify, _In_opt_ int icon_align, _In_opt_ int icon_justify,
		int font_width, int font_height, LPCWSTR font_family,
		COLORREF border_color, COLORREF text_color, COLORREF background_color,
		HDC hdc, LPCWSTR text
	);
	void drawBox();

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();

private:

	int width, height, posx, posy, windowwidth, windowheight, text_align, text_justify, icon_align, icon_justify;
	COLORREF border_color, text_color, background_color;
	HFONT font;
	LPCWSTR text;
	HDC hdc;
	//	for the icon custom class where it will be drawn

};