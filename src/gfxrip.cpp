/*
 * gfxrip.cc - GxfRip
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

#include "src/gfxrip.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <list>

gr_ripper_t::gr_ripper_t() {
  source = NULL;
  source_size = 0;

  palette = NULL;
  palette_size = 0;
  generate_random_palette(256);

  offset = 0;

  blXSize = 320/8;
  blYSize = 200;

  bits = 1;

  skip = 0;
  skipmode = skip_after_picture;

  reverse = false;
  mode = 0;
  palsearchmode = 2;
}

gr_ripper_t::~gr_ripper_t() {
}

void
gr_ripper_t::add_handler(gr_ripper_handler *handler) {
  handlers.push_back(handler);
}

void
gr_ripper_t::set_source(const void *data, size_t size) {
  if (source != NULL) {
    source = NULL;
    source_size = 0;
  }

  source = reinterpret_cast<const unsigned char*>(data);
  source_size = size;

  data_changed();
}

size_t
gr_ripper_t::get_image_count() {
  return (size_t)((static_cast<float>(source_size - offset) /
                   static_cast<float>(get_image_size())) + 1.f);
}

gr_bitmap_t *
gr_ripper_t::get_image(size_t index) {
  gr_bitmap_t *bitmap = new gr_bitmap_t(blXSize*8, blYSize);
  drawbitmap(bitmap, get_image_offset(index), 0, 0);
  return bitmap;
}

size_t
gr_ripper_t::getpixelcol(size_t pos, size_t x, size_t y) {
  bool bit[8];
  size_t p;
  size_t byte1;
  int bit1;
  int nn;
  int bitn;
  size_t i;

  for (i=0; i < 8; i++) {
    bit[i] = false;
  }

  for (i=0; i < bits; i++) {
    switch (mode) {
    case 0:
      // Amiga type bitplanes
      p = pos+(blXSize*blYSize)*(i);
      nn = x+(y*(blXSize*8));
      break;
    case 1:
      // ST Type bitplanes
      p = pos+blXSize*(i);
      nn = x+(bits*y*(blXSize*8));
      break;
    case 2:
      // mode == 2  // Amiga Sprite !!!
      if (i < 2) {
        p = pos+blXSize*(i);
        nn = x+((2*y)*(blXSize*8));
      } else {
        p = pos+blXSize*(i-2)+(blYSize*blXSize)*2;
        nn = x+((2*y)*(blXSize*8));
      }
      break;
    case 3:
      // mode == 3 // CPC gfx for Bat-Man / HoH
      p = pos+(x/8)+i;
      nn = x+((2*y)*(blXSize*8));
      break;
    case 4:
      //  mode ==4 // CPC gfx for Ultimate games
      p = pos+(x/4)+(blXSize*y*2);
      nn = (i*4)+x%4;
      break;
    }
    if (skipmode == 1) {
      p+=skip*i;
    }
    byte1 = nn/8;
    bit1 = 7-(nn%8);
    if (reverse) {
      bitn = (bits-i)-1;
    } else {
      bitn = i;
    }
    if (p+byte1 < source_size) {
      if (source[p+byte1] & (1 << bit1)) {
        bit[bitn] = true;
      } else {
        bit[bitn] = false;
      }
    } else {
      bit[bitn] = false;
    }
  }

  int col = 0;
  for (i=0; i < bits; i++) {
    if (bit[bplorder[i]]) {
      col += 1 << i;
    }
  }
  return col;
}

void
gr_ripper_t::drawbitmap(gr_bitmap_t *bmp, size_t pos, size_t xx, size_t yy) {
  for (size_t x = 0; x < blXSize*8; x ++) {
    for (size_t y = 0; y < blYSize; y++) {
      size_t color = getpixelcol(pos, x, y);
      bmp->putpixel(xx+x, yy+y, palette[color]);
    }
  }
}

size_t
gr_ripper_t::get_image_size() {
  if (skipmode == 0) {
    return ((blXSize * blYSize) * bits) + skip;
  } else {
    return (blXSize * blYSize + skip) * bits;
  }
}

size_t
gr_ripper_t::get_image_offset(size_t index) {
  return offset + (get_image_size() * index);
}

gr_size_t
gr_ripper_t::get_image_size(size_t /*index*/) {
  gr_size_t size;

  size.width = blXSize*8;
  size.height = blYSize;

  return size;
}

char *
gr_ripper_t::get_status() {
  char pmoder[4] = { 'S', 'X', 'E', 'A' };

  char rev;
  if (reverse) {
    rev = 'R';
  } else {
    rev = 'N';
  }

  const char *moder = "";
  switch (mode) {
    case 0:
      moder = "AM";
      break;
    case 1:
      moder = "ST";
      break;
    case 2:
      moder = "SP";
      break;
    case 3:
      moder = "C+";
      break;
    case 4:
      moder = "C-";
      break;
  }

  if (skipmode == 0) {
    skipmoder = 'P';
  } else {
    skipmoder = 'B';
  }

  char str[1024];
  snprintf(str, sizeof(str), "Off:%7lu Siz: X:%4lu Y:%4lu Bit:%lu Pal%c:%7i "
                             "Mode:%s Skip-%c:%4i Order:%c %i%i%i%i%i%i%i%i",
          offset, blXSize*8, blYSize, bits, pmoder[palsearchmode],
          palfound, moder, skipmoder, skip, rev,
          bplorder[7], bplorder[6], bplorder[5], bplorder[4], bplorder[3],
          bplorder[2], bplorder[1], bplorder[0]);

  return strdup(str);
}

void
gr_ripper_t::generate_random_palette(size_t size) {
  if (palette != NULL) {
    delete[] palette;
    palette = NULL;
    palette_size = 0;
  }

  palette = new gr_color_t[size];

  srand(1);
  for (size_t i = 0; i < size; i++) {
    palette[i].r = std::rand() % size;
    palette[i].g = std::rand() % size;
    palette[i].b = std::rand() % size;
    palette[i].a = 0xFF;
  }
  palette[1].r = palette[1].g = palette[1].b = 0xFF;
  palette[0].r = palette[0].g = palette[0].b = 0x00;
  palette[size-1].r = palette[size-1].g = palette[size-1].b = 0x00;
  palette[size-2].r = palette[size-2].g = palette[size-2].b = 0xFF/2;
  palette[size-2].b = 0xFF/2 + 2;
}

void
gr_ripper_t::data_changed() {
  std::list<gr_ripper_handler*>::iterator it = handlers.begin();
  for (; it != handlers.end(); ++it) {
    (*it)->image_updated();
  }
}

void
gr_ripper_t::set_width(size_t width) {
  if (width < 1) {
    return;
  }

  blXSize = width;
  data_changed();
}

void
gr_ripper_t::set_height(size_t height) {
  if (height < 1) {
    return;
  }

  blYSize = height;
  data_changed();
}

void
gr_ripper_t::set_bits(size_t bits) {
  if ((bits < 1) || (bits > 8)) {
    return;
  }

  this->bits = bits;
  data_changed();
}

void
gr_ripper_t::set_offset(size_t offset) {
  if (offset > (source_size - 1)) {
    return;
  }

  this->offset = offset;
  data_changed();
}

gr_bitmap_t::gr_bitmap_t(size_t width, size_t height) {
  this->width = width;
  this->height = height;

  if ((width * height) > 0) {
    bitmap = new gr_color_t[width * height];
    memset(bitmap, 0xFF, width * height * sizeof(gr_color_t));
  } else {
    bitmap = NULL;
  }
}

gr_bitmap_t::~gr_bitmap_t() {
  if (bitmap != NULL) {
    delete[] bitmap;
  }
}

void
gr_bitmap_t::putpixel(size_t x, size_t y, gr_color_t color) {
  if (bitmap == NULL) {
    return;
  }

  bitmap[y * width + x] = color;
}

void
gr_bitmap_t::fill(gr_color_t color) {
  if (bitmap == NULL) {
    return;
  }

  for (size_t i = 0; i < width * height; i++) {
    bitmap[i] = color;
  }
}

void
gr_ripper_client::set_ripper(gr_ripper_t *ripper) {
  if (ripper == this->ripper) {
    return;
  }

  if (this->ripper != NULL) {
//    this->ripper->del_handler(this);
    this->ripper = NULL;
  }

  this->ripper = ripper;
  if (ripper != NULL) {
    ripper->add_handler(this);
  }
}
