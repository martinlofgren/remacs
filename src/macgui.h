/* Definitions and headers for communication on the Mac OS.
   Copyright (C) 2000, 2001 Free Software Foundation, Inc.

This file is part of GNU Emacs.

GNU Emacs is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Emacs is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Emacs; see the file COPYING.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* Contributed by Andrew Choi (akochoi@mac.com).  */

#ifndef EMACS_MACGUI_H
#define EMACS_MACGUI_H

typedef int Display;  /* fix later */

typedef char * XrmDatabase;  /* fix later */

typedef unsigned long Time;

#if MAC_OSX
#undef mktime
#undef DEBUG
#undef Z
#undef free
#undef malloc
#undef realloc
/* Macros max and min defined in lisp.h conflict with those in
   precompiled header Carbon.h.  */
#undef max
#undef min
#undef init_process
#include <Carbon/Carbon.h>
#undef Z
#define Z (current_buffer->text->z)
#undef free
#define free unexec_free
#undef malloc
#define malloc unexec_malloc
#undef realloc
#define realloc unexec_realloc
#undef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#undef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#undef init_process
#define init_process emacs_init_process
#undef INFINITY
#else
#include <QuickDraw.h>		/* for WindowPtr */
#include <QDOffscreen.h>	/* for GWorldPtr */
#include <Controls.h>		/* for ControlHandle in xdisp.c */
#include <Gestalt.h>
#endif

typedef GWorldPtr Pixmap;

#if TARGET_API_MAC_CARBON
typedef struct OpaqueWindowPtr *Window;
#define Cursor ThemeCursor
#define No_Cursor (-1)
#else
typedef WindowPtr Window;
#define SetPortWindowPort(w) SetPort(w)
#define Cursor CursHandle
#define No_Cursor (0)
extern CursPtr arrow_cursor;
#endif

#define FACE_DEFAULT (~0)


/* Emulate XCharStruct.  */
typedef struct _XCharStruct
{
  int rbearing;
  int lbearing;
  int width;
  int ascent;
  int descent;
} XCharStruct;

struct MacFontStruct {
  char *fontname;

  short mac_fontnum;  /* font number of font used in this window */
  int mac_fontsize;  /* size of font */
  short mac_fontface;  /* plain, bold, italics, etc. */
  short mac_scriptcode;  /* Mac OS script code for font used */

#if 0
  SInt16 mFontNum;  /* font number of font used in this window */
  short mScriptCode;  /* Mac OS script code for font used */
  int mFontSize;  /* size of font */
  Style mFontFace;  /* plain, bold, italics, etc. */
  int mHeight;  /* height of one line of text in pixels */
  int mWidth;  /* width of one character in pixels */
  int mAscent;
  int mDescent;
  int mLeading;
  char mTwoByte;  /* true for two-byte font */
#endif /* 0 */

/* from Xlib.h */
#if 0
  XExtData *ext_data;      /* hook for extension to hang data */
  Font fid;                /* Font id for this font */
  unsigned direction;      /* hint about the direction font is painted */
#endif /* 0 */
  unsigned min_char_or_byte2;/* first character */
  unsigned max_char_or_byte2;/* last character */
  unsigned min_byte1;      /* first row that exists */
  unsigned max_byte1;      /* last row that exists */
#if 0
  Bool all_chars_exist;    /* flag if all characters have nonzero size */
  unsigned default_char;   /* char to print for undefined character */
  int n_properties;        /* how many properties there are */
  XFontProp *properties;   /* pointer to array of additional properties */
#endif /* 0 */
  XCharStruct min_bounds;  /* minimum bounds over all existing char */
  XCharStruct max_bounds;  /* maximum bounds over all existing char */
  XCharStruct *per_char;   /* first_char to last_char information */
  int ascent;              /* logical extent above baseline for spacing */
  int descent;             /* logical decent below baseline for spacing */
};

typedef struct MacFontStruct MacFontStruct;
typedef struct MacFontStruct XFontStruct;

/* Structure borrowed from Xlib.h to represent two-byte characters.  */

typedef struct {
  unsigned char byte1;
  unsigned char byte2;
} XChar2b;

#define STORE_XCHAR2B(chp, b1, b2) \
  ((chp)->byte1 = (b1), (chp)->byte2 = (b2))

#define XCHAR2B_BYTE1(chp) \
  ((chp)->byte1)

#define XCHAR2B_BYTE2(chp) \
  ((chp)->byte2)


/* Emulate X GC's by keeping color and font info in a structure.  */
typedef struct _XGCValues
{
  unsigned long foreground;
  unsigned long background;
  XFontStruct *font;
} XGCValues;

typedef XGCValues *GC;

extern XGCValues *
XCreateGC (void *, Window, unsigned long, XGCValues *);

#define GCForeground 0x01
#define GCBackground 0x02
#define GCFont 0x03
#define GCGraphicsExposures 0

/* Bit Gravity */

#define ForgetGravity		0
#define NorthWestGravity	1
#define NorthGravity		2
#define NorthEastGravity	3
#define WestGravity		4
#define CenterGravity		5
#define EastGravity		6
#define SouthWestGravity	7
#define SouthGravity		8
#define SouthEastGravity	9
#define StaticGravity		10

#define NoValue		0x0000
#define XValue  	0x0001
#define YValue		0x0002
#define WidthValue  	0x0004
#define HeightValue  	0x0008
#define AllValues 	0x000F
#define XNegative 	0x0010
#define YNegative 	0x0020

#define USPosition	(1L << 0) /* user specified x, y */
#define USSize		(1L << 1) /* user specified width, height */

#define PPosition	(1L << 2) /* program specified position */
#define PSize		(1L << 3) /* program specified size */
#define PMinSize	(1L << 4) /* program specified minimum size */
#define PMaxSize	(1L << 5) /* program specified maximum size */
#define PResizeInc	(1L << 6) /* program specified resize increments */
#define PAspect		(1L << 7) /* program specified min and max aspect ratios */
#define PBaseSize	(1L << 8) /* program specified base for incrementing */
#define PWinGravity	(1L << 9) /* program specified window gravity */

extern int XParseGeometry ();

typedef struct {
    int x, y;
    unsigned width, height;
} XRectangle;

#define NativeRectangle Rect

#define CONVERT_TO_XRECT(xr,nr)			\
  ((xr).x = (nr).left,				\
   (xr).y = (nr).top,				\
   (xr).width = ((nr).right - (nr).left),	\
   (xr).height = ((nr).bottom - (nr).top))

#define CONVERT_FROM_XRECT(xr,nr)		\
  ((nr).left = (xr).x,				\
   (nr).top = (xr).y,				\
   (nr).right = ((xr).x + (xr).width),		\
   (nr).bottom = ((xr).y + (xr).height))

#define STORE_NATIVE_RECT(nr,x,y,width,height)	\
  ((nr).left = (x),				\
   (nr).top = (y),				\
   (nr).right = ((nr).left + (width)),		\
   (nr).bottom = ((nr).top + (height)))

#endif /* EMACS_MACGUI_H */

/* arch-tag: 5a0da49a-35e2-418b-a58c-8a55778ae849
   (do not change this comment) */
