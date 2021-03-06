// SPDX-License-Identifier: GPL-2.0-or-later
/** @file
 * TODO: insert short description here
 *//*
 * Authors: see git history
 *
 * Copyright (C) 2017 Authors
 * Released under GNU GPL v2+, read the file 'COPYING' for more information.
 */
#ifndef SEEN_COLOR_PROFILE_FNS_H
#define SEEN_COLOR_PROFILE_FNS_H

/** \file 
 * Macros and fn declarations related to linear gradients.
 */

#include <vector>
#include <glibmm/ustring.h>
#include "cms-color-types.h"

class SPDocument;

namespace Inkscape {

class ColorProfile;

class CMSSystem {
public:
    static cmsHPROFILE getHandle( SPDocument* document, unsigned int* intent, char const* name );

    static cmsHTRANSFORM getDisplayTransform();

    static std::string getDisplayId(int monitor);

    static Glib::ustring setDisplayPer( void* buf, unsigned int bufLen, int monitor );

    static cmsHTRANSFORM getDisplayPer(std::string const &id);

    static std::vector<Glib::ustring> getDisplayNames();

    static std::vector<Glib::ustring> getSoftproofNames();

    static Glib::ustring getPathForProfile(Glib::ustring const& name);

    static void doTransform(cmsHTRANSFORM transform, void *inBuf, void *outBuf, unsigned int size);

    static bool isPrintColorSpace(ColorProfile const *profile);

    static int getChannelCount(ColorProfile const *profile);
};


} // namespace Inkscape


#endif // !SEEN_COLOR_PROFILE_FNS_H

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:fileencoding=utf-8:textwidth=99 :
