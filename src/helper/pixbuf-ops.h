// SPDX-License-Identifier: GPL-2.0-or-later
#ifndef __SP_PIXBUF_OPS_H__
#define __SP_PIXBUF_OPS_H__

/*
 * Helpers for SPItem -> gdk_pixbuf related stuff
 *
 * Authors:
 *   John Cliff <simarilius@yahoo.com>
 *
 * Copyright (C) 2008 John Cliff
 *
 * Released under GNU GPL v2+, read the file 'COPYING' for more information.
 */

#include <glib.h>

class SPDocument;
class SPItem;
namespace Inkscape { class Pixbuf; }

Inkscape::Pixbuf *sp_generate_internal_bitmap(SPDocument *doc, gchar const *filename,
                   double x0, double y0, double x1, double y1,
                   unsigned width, unsigned height, double xdpi, double ydpi,
                   unsigned long bgcolor, SPItem *item_only = nullptr);

#endif
