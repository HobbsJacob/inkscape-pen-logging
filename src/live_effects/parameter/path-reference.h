// SPDX-License-Identifier: GPL-2.0-or-later
#ifndef SEEN_LPE_PATH_REFERENCE_H
#define SEEN_LPE_PATH_REFERENCE_H

/*
 * Copyright (C) 2008-2012 Authors
 * Authors: Johan Engelen
 *          Abhishek Sharma
 *
 * Released under GNU GPL v2+, read the file 'COPYING' for more information.
 */

#include "object/uri-references.h"

class SPItem;
namespace Inkscape {
namespace XML { class Node; }

namespace LivePathEffect {

/**
 * The reference corresponding to href of LPE PathParam.
 */
class PathReference : public Inkscape::URIReference {
public:
    PathReference(SPObject *owner) : URIReference(owner) {}

    SPItem *getObject() const {
        return (SPItem *)URIReference::getObject();
    }

protected:
    bool _acceptObject(SPObject * const obj) const override;

private:
    PathReference(const PathReference&) = delete;
    PathReference& operator=(const PathReference&) = delete;
};

} // namespace LivePathEffect

} // namespace Inkscape



#endif /* !SEEN_LPE_PATH_REFERENCE_H */

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :
