// SPDX-License-Identifier: GPL-2.0-or-later
/** @file
 * @brief SVG diffuse lighting filter effect
 *//*
 * Authors:
 *   Hugo Rodrigues <haa.rodrigues@gmail.com>
 *   Jean-Rene Reinhard <jr@komite.net>
 *
 * Copyright (C) 2006-2007 Authors
 * Released under GNU GPL v2+, read the file 'COPYING' for more information.
 */

#ifndef SP_FEDIFFUSELIGHTING_H_SEEN
#define SP_FEDIFFUSELIGHTING_H_SEEN

#include "sp-filter-primitive.h"
#include "number-opt-number.h"

#define SP_FEDIFFUSELIGHTING(obj) (dynamic_cast<SPFeDiffuseLighting*>((SPObject*)obj))
#define SP_IS_FEDIFFUSELIGHTING(obj) (dynamic_cast<const SPFeDiffuseLighting*>((SPObject*)obj) != NULL)

struct SVGICCColor;

namespace Inkscape {
namespace Filters {
class FilterDiffuseLighting;
} }

class SPFeDiffuseLighting : public SPFilterPrimitive {
public:
	SPFeDiffuseLighting();
	~SPFeDiffuseLighting() override;

    gfloat surfaceScale;
    guint surfaceScale_set : 1;
    gfloat diffuseConstant;
    guint diffuseConstant_set : 1;
    NumberOptNumber kernelUnitLength;
    guint32 lighting_color;
    guint lighting_color_set : 1;
    Inkscape::Filters::FilterDiffuseLighting *renderer;
    SVGICCColor *icc;

protected:
	void build(SPDocument* doc, Inkscape::XML::Node* repr) override;
	void release() override;

	void child_added(Inkscape::XML::Node* child, Inkscape::XML::Node* ref) override;
	void remove_child(Inkscape::XML::Node* child) override;

	void order_changed(Inkscape::XML::Node* child, Inkscape::XML::Node* old_repr, Inkscape::XML::Node* new_repr) override;

	void set(SPAttr key, const gchar* value) override;

	void update(SPCtx* ctx, unsigned int flags) override;

	Inkscape::XML::Node* write(Inkscape::XML::Document* doc, Inkscape::XML::Node* repr, guint flags) override;

	void build_renderer(Inkscape::Filters::Filter* filter) override;
};

#endif /* !SP_FEDIFFUSELIGHTING_H_SEEN */

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
