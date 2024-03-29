/*
 * Copyright multiple authors, see README for licence details
 */
#include <stdio.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include "link.h"
#include "menu.h"
#include "dat.h"
#include "fns.h"

typedef struct {
	int width;
	int hot[2];
	unsigned char mask[64];
	unsigned char fore[64];
} Cursordata;

Cursordata sweep0data = {
	16,
	{7, 7},
	{0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03,
	 0xC0, 0x03, 0xC0, 0x03, 0xFF, 0xFF, 0xFF, 0xFF,
	 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x03, 0xC0, 0x03,
	 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03},
	{0x00, 0x00, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01,
	 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0xFE, 0x7F,
	 0xFE, 0x7F, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01,
	 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x00, 0x00}
};

Cursordata boxcursdata = {
	16,
	{7, 7},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	 0xFF, 0xFF, 0x1F, 0xF8, 0x1F, 0xF8, 0x1F, 0xF8,
	 0x1F, 0xF8, 0x1F, 0xF8, 0x1F, 0xF8, 0xFF, 0xFF,
	 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0x00, 0x00, 0xFE, 0x7F, 0xFE, 0x7F, 0xFE, 0x7F,
	 0x0E, 0x70, 0x0E, 0x70, 0x0E, 0x70, 0x0E, 0x70,
	 0x0E, 0x70, 0x0E, 0x70, 0x0E, 0x70, 0x0E, 0x70,
	 0xFE, 0x7F, 0xFE, 0x7F, 0xFE, 0x7F, 0x00, 0x00}
};

Cursordata sightdata = {
	16,
	{7, 7},
	{0xF8, 0x1F, 0xFC, 0x3F, 0xFE, 0x7F, 0xDF, 0xFB,
	 0xCF, 0xF3, 0xC7, 0xE3, 0xFF, 0xFF, 0xFF, 0xFF,
	 0xFF, 0xFF, 0xFF, 0xFF, 0xC7, 0xE3, 0xCF, 0xF3,
	 0xDF, 0x7B, 0xFE, 0x7F, 0xFC, 0x3F, 0xF8, 0x1F,},
	{0x00, 0x00, 0xF0, 0x0F, 0x8C, 0x31, 0x84, 0x21,
	 0x82, 0x41, 0x82, 0x41, 0x82, 0x41, 0xFE, 0x7F,
	 0xFE, 0x7F, 0x82, 0x41, 0x82, 0x41, 0x82, 0x41,
	 0x84, 0x21, 0x8C, 0x31, 0xF0, 0x0F, 0x00, 0x00,}
};

Cursordata arrowdata = {
	16,
	{1, 1},
	{0xFF, 0x07, 0xFF, 0x07, 0xFF, 0x03, 0xFF, 0x00,
	 0xFF, 0x00, 0xFF, 0x01, 0xFF, 0x03, 0xFF, 0x07,
	 0xE7, 0x0F, 0xC7, 0x1F, 0x83, 0x3F, 0x00, 0x7F,
	 0x00, 0xFE, 0x00, 0x7C, 0x00, 0x38, 0x00, 0x10,},
	{0x00, 0x00, 0xFE, 0x03, 0xFE, 0x00, 0x3E, 0x00,
	 0x7E, 0x00, 0xFE, 0x00, 0xF6, 0x01, 0xE6, 0x03,
	 0xC2, 0x07, 0x82, 0x0F, 0x00, 0x1F, 0x00, 0x3E,
	 0x00, 0x7C, 0x00, 0x38, 0x00, 0x10, 0x00, 0x00,}
};

Cursordata whitearrow = {
	16,
	{0, 0},
	{0xFF, 0x07, 0xFF, 0x07, 0xFF, 0x03, 0xFF, 0x00,
	 0xFF, 0x00, 0xFF, 0x01, 0xFF, 0x03, 0xFF, 0x07,
	 0xE7, 0x0F, 0xC7, 0x1F, 0x83, 0x3F, 0x00, 0x7F,
	 0x00, 0xFE, 0x00, 0x7C, 0x00, 0x38, 0x00, 0x10,},
	{0xFF, 0x07, 0xFF, 0x07, 0x83, 0x03, 0xC3, 0x00,
	 0xC3, 0x00, 0x83, 0x01, 0x1B, 0x03, 0x3F, 0x06,
	 0x67, 0x0C, 0xC7, 0x18, 0x83, 0x31, 0x00, 0x63,
	 0x00, 0xC6, 0x00, 0x6C, 0x00, 0x38, 0x00, 0x10,}
};

Cursordata blittarget = {
	18,
	{8, 8},
	{0xe0, 0x1f, 0x00, 0xf0, 0x3f, 0x00, 0xf8, 0x7f, 0x00,
	 0xfc, 0xff, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xff, 0x03,
	 0xff, 0xff, 0x03, 0xff, 0xff, 0x03, 0xff, 0xff, 0x03,
	 0xff, 0xff, 0x03, 0xff, 0xff, 0x03, 0xff, 0xff, 0x03,
	 0xff, 0xff, 0x03, 0xfe, 0xff, 0x01, 0xfc, 0xff, 0x00,
	 0xf8, 0x7f, 0x00, 0xf0, 0x3f, 0x00, 0xe0, 0x1f, 0x00},
	{0x00, 0x00, 0x00, 0xc0, 0x0f, 0x00, 0xf0, 0x3f, 0x00,
	 0x38, 0x73, 0x00, 0x8c, 0xc7, 0x00, 0xec, 0xdf, 0x00,
	 0x66, 0x9b, 0x01, 0x36, 0xb3, 0x01, 0xfe, 0xff, 0x01,
	 0xfe, 0xff, 0x01, 0x36, 0xb3, 0x01, 0x66, 0x9b, 0x01,
	 0xec, 0xdf, 0x00, 0x8c, 0xc7, 0x00, 0x38, 0x73, 0x00,
	 0xf0, 0x3f, 0x00, 0xc0, 0x0f, 0x00, 0x00, 0x00, 0x00}
};

Cursordata blitarrow = {
	18,
	{1, 1},
	{0xff, 0x0f, 0x00, 0xff, 0x07, 0x00, 0xff, 0x03, 0x00,
	 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x01, 0x00,
	 0xff, 0x03, 0x00, 0xff, 0x07, 0x00, 0xe7, 0x0f, 0x00,
	 0xc7, 0x1f, 0x00, 0x87, 0x3f, 0x00, 0x03, 0x7f, 0x00,
	 0x01, 0xfe, 0x00, 0x00, 0xfc, 0x01, 0x00, 0xf8, 0x03,
	 0x00, 0xf0, 0x01, 0x00, 0xe0, 0x00, 0x00, 0x40, 0x00},
	{0x00, 0x00, 0x00, 0xfe, 0x03, 0x00, 0xfe, 0x00, 0x00,
	 0x3e, 0x00, 0x00, 0x7e, 0x00, 0x00, 0xfe, 0x00, 0x00,
	 0xf6, 0x01, 0x00, 0xe6, 0x03, 0x00, 0xc2, 0x07, 0x00,
	 0x82, 0x0f, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x3e, 0x00,
	 0x00, 0x7c, 0x00, 0x00, 0xf8, 0x00, 0x00, 0xf0, 0x01,
	 0x00, 0xe0, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00}
};

Cursordata blitsweep = {
	18,
	{8, 8},
	{0xc4, 0xff, 0x03, 0xce, 0xff, 0x03, 0xdf, 0xff, 0x03,
	 0x3e, 0x80, 0x03, 0x7c, 0x83, 0x03, 0xf8, 0x83, 0x03,
	 0xf7, 0x83, 0x03, 0xe7, 0x83, 0x03, 0xf7, 0x83, 0x03,
	 0xf7, 0x83, 0x03, 0x07, 0x80, 0x03, 0x07, 0x80, 0x03,
	 0x07, 0x80, 0x03, 0x07, 0x80, 0x03, 0x07, 0x80, 0x03,
	 0xff, 0xff, 0x03, 0xff, 0xff, 0x03, 0xff, 0xff, 0x03},
	{0x00, 0x00, 0x00, 0x84, 0xff, 0x01, 0x0e, 0x00, 0x01,
	 0x1c, 0x00, 0x01, 0x38, 0x00, 0x01, 0x70, 0x01, 0x01,
	 0xe0, 0x01, 0x01, 0xc2, 0x01, 0x01, 0xe2, 0x01, 0x01,
	 0x02, 0x00, 0x01, 0x02, 0x00, 0x01, 0x02, 0x00, 0x01,
	 0x02, 0x00, 0x01, 0x02, 0x00, 0x01, 0x02, 0x00, 0x01,
	 0x02, 0x00, 0x01, 0xfe, 0xff, 0x01, 0x00, 0x00, 0x00}
};

static XColor bl, wh;

Cursor
getcursor(Cursordata * c, ScreenInfo * s)
{
	Pixmap f, m;

	f = XCreatePixmapFromBitmapData(dpy, s->root, (char *) c->fore, c->width, c->width, 1, 0, 1);
	m = XCreatePixmapFromBitmapData(dpy, s->root, (char *) c->mask, c->width, c->width, 1, 0, 1);
	return XCreatePixmapCursor(dpy, f, m, &bl, &wh, c->hot[0], c->hot[1]);
}

void
initcurs(ScreenInfo * s)
{
	XColor dummy;

	XAllocNamedColor(dpy, DefaultColormap(dpy, s->num), "black", &bl, &dummy);
	XAllocNamedColor(dpy, DefaultColormap(dpy, s->num), "white", &wh, &dummy);

	switch (curs) {
	case 2:
		s->arrow = getcursor(&blitarrow, s);
		s->target = getcursor(&blittarget, s);
		s->sweep0 = getcursor(&blitsweep, s);
		s->boxcurs = getcursor(&blitsweep, s);
		break;
	case 1:
		s->arrow = getcursor(&arrowdata, s);
		s->target = getcursor(&sightdata, s);
		s->sweep0 = getcursor(&sweep0data, s);
		s->boxcurs = getcursor(&boxcursdata, s);
		break;
	default:
		s->arrow = XCreateFontCursor(dpy, XC_left_ptr);
		s->target = XCreateFontCursor(dpy, XC_crosshair);
		s->sweep0 = XCreateFontCursor(dpy, XC_sizing);
		s->boxcurs = XCreateFontCursor(dpy, XC_dotbox);
		break;
	}
}
