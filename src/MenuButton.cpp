#include "include.h"

MenuButton::MenuButton(
	int width, int height, int posx, int posy, int windowwidth, int windowheight,
	int text_aling, int text_justify, _In_opt_ int icon_align, _In_opt_ int icon_justify,
	int font_width, int font_height, LPCWSTR font_family,
	COLORREF border_color, COLORREF text_color, COLORREF background_color,
	HDC hdc, LPCWSTR text
) {

	MenuButton::width = width;
	MenuButton::height = height;
	MenuButton::posx = posx;
	MenuButton::posy = posy;
	MenuButton::windowwidth = windowwidth;
	MenuButton::windowheight = windowheight;
	MenuButton::text_align = text_aling;
	MenuButton::text_justify = text_justify;
	if (icon_align != NULL) MenuButton::icon_align = icon_align;
	if (icon_justify != NULL) MenuButton::icon_justify = icon_justify;
	MenuButton::border_color = border_color;
	MenuButton::text_color = text_color;
	MenuButton::background_color = background_color;
	MenuButton::hdc = hdc;
	MenuButton::text = text;
	
	MenuButton::font = CreateFontW(font_width, font_height, 0, 0,
		FW_EXTRALIGHT, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, font_family);

}

void MenuButton::drawBox() {

	SelectObject(MenuButton::hdc, MenuButton::font);

	if (MenuButton::posx == NULL) posx = MenuButton::windowwidth / 2;
	if (MenuButton::posy == NULL) posy = MenuButton::windowheight / 2;

	//box 1 = new file
	for (int i = 0; i < (width / 2); i++) SetPixel(hdc, posx - i, posy, MenuButton::border_color);
	for (int i = 0; i < (width / 2); i++) SetPixel(hdc, posx + i, posy, MenuButton::border_color);
	for (int i = 0; i < height + 1; i++) SetPixel(hdc, posx - (MenuButton::width / 2), posy + i, MenuButton::border_color);
	for (int i = 0; i < height + 1; i++) SetPixel(hdc, posx + (MenuButton::width / 2), posy + i, MenuButton::border_color);
	for (int i = 0; i < (width / 2); i++) SetPixel(hdc, posx - i, posy + height, MenuButton::border_color);
	for (int i = 0; i < (width / 2); i++) SetPixel(hdc, posx + i, posy + height, MenuButton::border_color);

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);
	RECT rect = { posx - (width / 2), posy,  posx + (width / 2), posy + height };
	DrawText(hdc, MenuButton::text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}

int MenuButton::getPosX() {

	if (MenuButton::posx != NULL) return MenuButton::posx;
	else return (MenuButton::windowwidth / 2) - (MenuButton::width / 2);

}

int MenuButton::getPosY() {

	if (MenuButton::posy != NULL) return MenuButton::posy;
	else return (MenuButton::windowheight / 2);
	return MenuButton::posy;

}

int MenuButton::getWidth() {

	return MenuButton::width;

}

int MenuButton::getHeight() {

	return MenuButton::height;

}