#include "stdafx.h"
#include "AetherDimension.h"

void AetherDimension::init()
{
	Dimension::init();
	id = AETHER_ID;
}

Vec3 *AetherDimension::getFogColor(float td, float a) const
{
	float br = Mth::cos(td * PI * 2) * 2 + 0.5f;
	if (br < 0.0f) br = 0.0f;
	if (br > 1.0f) br = 1.0f;

	const unsigned int baseFogColour = 0x9fd6ff;
	float r = ((baseFogColour >> 16) & 0xff) / 255.0f;
	float g = ((baseFogColour >> 8) & 0xff) / 255.0f;
	float b = ((baseFogColour) & 0xff) / 255.0f;
	r *= br * 0.90f + 0.10f;
	g *= br * 0.92f + 0.08f;
	b *= br * 0.95f + 0.05f;

	return Vec3::newTemp(r, g, b);
}

bool AetherDimension::mayRespawn() const
{
	return true;
}

bool AetherDimension::isNaturalDimension()
{
	return true;
}
