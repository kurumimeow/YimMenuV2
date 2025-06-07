#pragma once
#include "types/script/Timer.hpp"
#include "types/script/types.hpp"

namespace YimMenu
{
	enum class RainbowColorStyle
	{
		Fade,
		Spasm
	};

	inline void RainbowColor(Vector3& color, int speed = 1, RainbowColorStyle type = RainbowColorStyle::Fade)
	{
		static TIMER spasmTimer;
		static bool firstInit = true;

		if (type == RainbowColorStyle::Spasm)
		{
			int delay = std::max(10, 1010 - (speed * 100));

			if (spasmTimer.HasTimePassed(delay))
			{
				color.x = rand() % 256;
				color.y = rand() % 256;
				color.z = rand() % 256;

				spasmTimer.Reset();
				firstInit = true;
			}
		}

		if (type == RainbowColorStyle::Fade)
		{
			if (firstInit)
			{
				color.x   = 255;
				color.y   = 0;
				color.z   = 0;
				firstInit = false;
			}

			if (color.x > 0 && color.z == 0)
			{
				color.y += speed;
				color.x -= speed;
			}
			if (color.y > 0 && color.x == 0)
			{
				color.z += speed;
				color.y -= speed;
			}
			if (color.z > 0 && color.y == 0)
			{
				color.x += speed;
				color.z -= speed;
			}
			color.x = std::clamp(color.x, 0.f, 255.f);
			color.y = std::clamp(color.y, 0.f, 255.f);
			color.z = std::clamp(color.z, 0.f, 255.f);
		}
	}
}