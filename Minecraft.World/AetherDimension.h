#pragma once
#include "Dimension.h"

class AetherDimension : public Dimension
{
public:
	virtual void init();
	virtual Vec3 *getFogColor(float td, float a) const;
	virtual bool mayRespawn() const;
	virtual bool isNaturalDimension();
};
