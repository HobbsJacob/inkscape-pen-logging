// SPDX-License-Identifier: GPL-2.0-or-later
/** @file
 * @brief see lpe-recursiveskeleton.cpp.
 */
/* Authors:
 *   Johan Engelen <j.b.c.engelen@utwente.nl>
 *
 * Copyright (C) 2007-2009 Authors
 *
 * Released under GNU GPL v2+, read the file 'COPYING' for more information.
 */

#ifndef INKSCAPE_LPE_RECURSIVESKELETON_H
#define INKSCAPE_LPE_RECURSIVESKELETON_H

#include "live_effects/effect.h"
#include "live_effects/parameter/parameter.h"

namespace Inkscape {
namespace LivePathEffect {


class LPERecursiveSkeleton : public Effect {
public:
    LPERecursiveSkeleton(LivePathEffectObject *lpeobject);
    ~LPERecursiveSkeleton() override;

    Geom::Piecewise<Geom::D2<Geom::SBasis> > doEffect_pwd2 (Geom::Piecewise<Geom::D2<Geom::SBasis> > const & pwd2_in) override;

private:
    ScalarParam iterations;

    LPERecursiveSkeleton(const LPERecursiveSkeleton&) = delete;
    LPERecursiveSkeleton& operator=(const LPERecursiveSkeleton&) = delete;
};

} //namespace LivePathEffect
} //namespace Inkscape

#endif

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
