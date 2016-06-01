/*
 * gfxrip.h - GxfRip
 *
 * Copyright (C) 2007  TC <tomcat@sgn.net>
 *
 * This file is part of gfxrip.
 *
 * gfxrip is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * gfxrip is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gfxrip.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SRC_GFXRIP_H_
#define SRC_GFXRIP_H_

#include <cstddef>
#include <list>

typedef struct {
  unsigned char a;
  unsigned char r;
  unsigned char g;
  unsigned char b;
} gr_color_t;

class gr_palette_t {
};

class gr_bitmap_t {
 protected:
  size_t width;
  size_t height;
  gr_color_t *bitmap;
  gr_color_t *palette;

 public:
  gr_bitmap_t(size_t width, size_t height);
  virtual ~gr_bitmap_t();

  void set_palette(gr_color_t *palette) { this->palette = palette; }

  void putpixel(size_t x, size_t y, gr_color_t color);
  void putpixel(size_t x, size_t y, size_t color);

  unsigned char *get_data() { return (unsigned char*)bitmap; }
  size_t get_width() { return width; }
  size_t get_height() { return height; }

  void clear_to_color(size_t color);
};

class gr_ripper_handler {
 public:
  virtual void image_updated() = 0;
};

class gr_ripper_t;

class gr_ripper_client : public gr_ripper_handler {
 protected:
  gr_ripper_t *ripper;

 public:
  gr_ripper_client() : ripper(NULL) {}

  void set_ripper(gr_ripper_t *ripper);
  gr_ripper_t *get_ripper() { return ripper; }

  virtual void image_updated() {}
};


typedef struct {
  size_t width;
  size_t height;
} gr_size_t;

class gr_ripper_t {
 public:
  typedef enum {
    skip_after_picture,
    skip_after_bitplane
  } skip_mode_t;

 protected:
  std::list<gr_ripper_handler*> handlers;

  size_t source_size;
  const unsigned char *source;

  gr_color_t *palette;
  size_t palette_size;

  int offset;
  size_t blXSize;
  size_t blYSize;

  size_t bits;

  int skip;
  skip_mode_t skipmode;
  char skipmoder;

  bool reverse;
  int mode;
  int palsearchmode;
  int palfound;

  int bplorder[8] = {0,1,2,3,4,5,6,7};

 public:
  gr_ripper_t();
  virtual ~gr_ripper_t();

  void add_handler(gr_ripper_handler *handler);
  void set_source(const void *data, size_t size);

  size_t get_image_count();
  gr_bitmap_t *get_image(size_t index);
  char *get_status();
  gr_size_t get_image_size(size_t index);

  size_t get_width() { return blXSize; }
  size_t get_height() { return blYSize; }
  size_t get_bits() { return bits; }

  void set_width(size_t width);
  void set_height(size_t height);
  void set_bits(size_t bits);

 protected:
  size_t getpixelcol(size_t pos, size_t x, size_t y);
  void drawbitmap(gr_bitmap_t *bmp, size_t pos, size_t xx, size_t yy);
  size_t get_image_size();
  size_t get_image_offset(size_t index);
  void generate_random_palette(size_t size);

  void data_changed();
};

#endif  // SRC_GFXRIP_H_
