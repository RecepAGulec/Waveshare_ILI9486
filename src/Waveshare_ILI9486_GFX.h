//
// GFX style API wrapper for Waveshare_ILI9486
// - https://github.com/ImpulseAdventure/Waveshare_ILI9486
// - Intended to work with the following displays:
//   - Waveshare 4.0" Touch Shield for Arduino
//   - Waveshare 3.5" Touch Shield for Arduino
//

//
// The Waveshare_ILI9486_GFX API is based on Adafruit-GFX.
// The associated copyright notice is reproduced below.
//
/*
This is the core graphics library for all our displays, providing a common
set of graphics primitives (points, lines, circles, etc.).  It needs to be
paired with a hardware-specific library for each display device we carry
(to handle the lower-level functions).
Adafruit invests time and resources providing this open source code, please
support Adafruit & open-source hardware by purchasing products from Adafruit!
Copyright (c) 2013 Adafruit Industries.  All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _WAVESHARE_ILI9486_GFX_
#define _WAVESHARE_ILI9486_GFX_

#if ARDUINO >= 100
#include "Arduino.h"
#include "Print.h"
#else
#include "WProgram.h"
#endif

#include "Fonts/fonts.h"

class Waveshare_ILI9486_GFX : public Print {
protected:

public:
	Waveshare_ILI9486_GFX(void);

	// General
	void      begin();

	// Display dimensions
	int16_t width(void) const { return _width; };
	int16_t height(void) const { return _height; }

	// Non-Transaction drawing
	void drawPixel(int16_t x, int16_t y, uint16_t color);
	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
	void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
	void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

	void fillScreen(uint16_t color);

	// Text configuration
	void setFont(const sFONT *f = NULL);
	void setCursor(int16_t x, int16_t y);
	void setTextColor(uint16_t c);
	void setTextColor(uint16_t c, uint16_t bg);
	void setTextSize(uint8_t s);
	void setTextSize(uint8_t sx, uint8_t sy);
	void setTextWrap(bool w);
	int16_t getCursorX(void) const { return _cursor_x; }
	int16_t getCursorY(void) const { return _cursor_y; }


	// Text drawing
	virtual size_t write(uint8_t);
	void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
		uint16_t bg, uint8_t size);
	void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
		uint16_t bg, uint8_t size_x, uint8_t size_y);
	void getTextBounds(const char *str, int16_t x, int16_t y,
		int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);

	// Placeholder stub functions
	void setRotation(uint8_t r);
	uint8_t getRotation(void) const { return _rotation; }

protected:
	void charBounds(char c, int16_t *x, int16_t *y,
		int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy);

	// UNSUPPORTED APIs:
#if 0
	// Miscellaneous
	void      setRotation(uint8_t r);
	void      invertDisplay(boolean i);
	void      scrollTo(uint16_t y);

	// Transaction API
	void      startWrite(void);
	void      endWrite(void);
	void      writePixel(int16_t x, int16_t y, uint16_t color);
	void      writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
	void      writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
	void      writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

	// Transaction API not used by GFX
	void      setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
	void      writePixel(uint16_t color);
	void      writePixels(uint16_t * colors, uint32_t len);
	void      writeColor(uint16_t color, uint32_t len);
	void      pushColor(uint16_t color);

	// Recommended Non-Transaction
	void      drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
	void      drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

	using     Adafruit_GFX::drawRGBBitmap; // Check base class first
	void      drawRGBBitmap(int16_t x, int16_t y,
		uint16_t *pcolors, int16_t w, int16_t h);

	uint8_t   readcommand8(uint8_t reg, uint8_t index = 0);

	uint16_t  color565(uint8_t r, uint8_t g, uint8_t b);
#endif


private:
	int16_t WIDTH;			// Raw display width (never changes)
	int16_t HEIGHT;			// Raw display height (never changes)
	int16_t _width;			// Display width (accounting for rotation)
	int16_t _height;		// Display height (accounting for rotation)
	uint8_t _rotation;

	const sFONT* _font;

	uint16_t _textcolor;
	uint16_t _textbgcolor;
	uint8_t _textsize_x;
	uint8_t _textsize_y;
	int16_t	_cursor_x;
	int16_t _cursor_y;
	bool _wrap;

};

  // Color definitions
  #define ILI9486_BLACK       0x0000  ///<   0,   0,   0
  #define ILI9486_NAVY        0x000F  ///<   0,   0, 123
  #define ILI9486_DARKGREEN   0x03E0  ///<   0, 125,   0
  #define ILI9486_DARKCYAN    0x03EF  ///<   0, 125, 123
  #define ILI9486_MAROON      0x7800  ///< 123,   0,   0
  #define ILI9486_PURPLE      0x780F  ///< 123,   0, 123
  #define ILI9486_OLIVE       0x7BE0  ///< 123, 125,   0
  #define ILI9486_LIGHTGREY   0xC618  ///< 198, 195, 198
  #define ILI9486_DARKGREY    0x7BEF  ///< 123, 125, 123
  #define ILI9486_BLUE        0x001F  ///<   0,   0, 255
  #define ILI9486_GREEN       0x07E0  ///<   0, 255,   0
  #define ILI9486_CYAN        0x07FF  ///<   0, 255, 255
  #define ILI9486_RED         0xF800  ///< 255,   0,   0
  #define ILI9486_MAGENTA     0xF81F  ///< 255,   0, 255
  #define ILI9486_YELLOW      0xFFE0  ///< 255, 255,   0
  #define ILI9486_WHITE       0xFFFF  ///< 255, 255, 255
  #define ILI9486_ORANGE      0xFD20  ///< 255, 165,   0
  #define ILI9486_GREENYELLOW 0xAFE5  ///< 173, 255,  41
  #define ILI9486_PINK        0xFC18  ///< 255, 130, 198


#endif // _WAVESHARE_ILI9486_GFX_
