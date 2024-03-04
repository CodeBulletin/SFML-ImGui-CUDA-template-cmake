#ifndef SFH_COLOR_HPP
#define SFH_COLOR_HPP

#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics/Color.hpp>

namespace sfh
{
	struct HColor
	{
		float h, s, l, a = 255.0f;

		HColor(float h, float s, float l, float a = 255.0f) : h(h), s(s), l(l), a(a) {}
		HColor() = default;
		HColor(const HColor &col) : h(col.h), s(col.s), l(col.l), a(col.a) {}
		HColor &operator=(const HColor &col)
		{
			h = col.h;
			s = col.s;
			l = col.l;
			a = col.a;
			return *this;
		}
	};

	struct CMYK
	{
		float c, m, y, k;
		CMYK(float c, float m, float y, float k) : c(c), m(m), y(y), k(k) {}
		CMYK() = default;
		CMYK(const CMYK &col) : c(col.c), m(col.m), y(col.y), k(col.k) {}
		CMYK &operator=(const CMYK &col)
		{
			c = col.c;
			m = col.m;
			y = col.y;
			k = col.k;
			return *this;
		}
	};

	namespace color
	{

		// RGB_CMYK
		CMYK RGBtoCMYK(const sf::Color &rgba)
		{
			float c = 1 - (rgba.r / 255.0);
			float m = 1 - (rgba.g / 255.0);
			float y = 1 - (rgba.b / 255.0);
			float k = std::min(c, std::min(m, y));

			// Adjust CMY values based on K
			c = (c - k) / (1 - k);
			m = (m - k) / (1 - k);
			y = (y - k) / (1 - k);

			return {c, m, y, k};
		}

		sf::Color CMYKtoRGBA(const CMYK &cmyk, uint8_t alpha)
		{
			uint8_t r = 255 * (1 - cmyk.c) * (1 - cmyk.k);
			uint8_t g = 255 * (1 - cmyk.m) * (1 - cmyk.k);
			uint8_t b = 255 * (1 - cmyk.y) * (1 - cmyk.k);
			return {r, g, b, alpha};
		}

		// HSL_RGB
		HColor RGB_to_HSL(sf::Color col)
		{
			const float R1 = col.r / 255.0f;
			const float G1 = col.g / 255.0f;
			const float B1 = col.b / 255.0f;

			float cmax = std::max(R1, std::max(G1, B1));
			float cmin = std::min(R1, std::min(G1, B1));

			float delta = cmax - cmin;
			float l = (cmax + cmin) / 2.0f;
			float h = 0;
			if (delta == 0.0f)
			{
				return {h, 0.0f, l, float(col.a)};
			}
			float s = delta / (1 - std::fabs(2.0f * l - 1.0f));
			if (R1 == cmax)
				(h = 60 * std::fmod((G1 - B1) / delta, 6.0f)) < 0.0f ? h = 360 + h : h = h;
			else if (G1 == cmax)
				h = 60 * ((B1 - R1) / delta + 2);
			else if (B1 == cmax)
				h = 60 * ((R1 - G1) / delta + 4);

			return {h, s, l, (float)col.a};
		}

		sf::Color HSL_to_RGB(HColor col)
		{
			float C = (1 - std::fabs(2 * col.l - 1)) * col.s;
			float h = col.h / 60.0f;
			float X = C * (1 - std::fabs(std::fmod(h, 2) - 1));
			float m = col.l - C / 2.0f;
			switch (int(h))
			{
			case 0:
				return {(uint8_t)std::round((C + m) * 255.0f), (uint8_t)std::round((X + m) * 255.0f), (uint8_t)std::round((m) * 255.0f), (uint8_t)col.a};
			case 1:
				return {(uint8_t)std::round((X + m) * 255.0f), (uint8_t)std::round((C + m) * 255.0f), (uint8_t)std::round((m) * 255.0f), (uint8_t)col.a};
			case 2:
				return {(uint8_t)std::round((m) * 255.0f), (uint8_t)std::round((C + m) * 255.0f), (uint8_t)std::round((X + m) * 255.0f), (uint8_t)col.a};
			case 3:
				return {(uint8_t)std::round((m) * 255.0f), (uint8_t)std::round((X + m) * 255.0f), (uint8_t)std::round((C + m) * 255.0f), (uint8_t)col.a};
			case 4:
				return {(uint8_t)std::round((X + m) * 255.0f), (uint8_t)std::round((m) * 255.0f), (uint8_t)std::round((C + m) * 255.0f), (uint8_t)col.a};
			case 5:
				return {(uint8_t)std::round((C + m) * 255.0f), (uint8_t)std::round((m) * 255.0f), (uint8_t)std::round((X + m) * 255.0f), (uint8_t)col.a};
			default:
				return {(uint8_t)std::round((C + m) * 255.0f), (uint8_t)std::round((X + m) * 255.0f), (uint8_t)std::round((m) * 255.0f), (uint8_t)col.a};
			}
		}

		// HSV_RGB
		HColor RGB_to_HSV(sf::Color col)
		{
			const float R1 = col.r / 255.0f;
			const float G1 = col.g / 255.0f;
			const float B1 = col.b / 255.0f;

			float cmax = std::max(R1, std::max(G1, B1));
			float cmin = std::min(R1, std::min(G1, B1));

			float delta = cmax - cmin;
			float h = 0;
			float v = cmax;
			float s = cmax == 0.0f ? 0.0f : delta / cmax;
			if (delta == 0.0f)
				return {h, s, v, float(col.a)};
			else if (R1 == cmax)
				(h = 60 * std::fmod((G1 - B1) / delta, 6.0f)) < 0.0f ? h = 360 + h : h = h;
			else if (G1 == cmax)
				h = 60 * ((B1 - R1) / delta + 2);
			else if (B1 == cmax)
				h = 60 * ((R1 - G1) / delta + 4);

			return {h, s, v, float(col.a)};
		}

		sf::Color HSV_to_RGB(HColor col)
		{
			float C = col.l * col.s;
			float h = col.h / 60.0f;
			float X = C * (1 - std::fabs(std::fmod(h, 2) - 1));
			float m = col.l - C;
			switch (int(h))
			{
			case 0:
				return {(uint8_t)std::round((C + m) * 255.0f), (uint8_t)std::round((X + m) * 255.0f), (uint8_t)std::round((m) * 255.0f), (uint8_t)col.a};
			case 1:
				return {(uint8_t)std::round((X + m) * 255.0f), (uint8_t)std::round((C + m) * 255.0f), (uint8_t)std::round((m) * 255.0f), (uint8_t)col.a};
			case 2:
				return {(uint8_t)std::round((m) * 255.0f), (uint8_t)std::round((C + m) * 255.0f), (uint8_t)std::round((X + m) * 255.0f), (uint8_t)col.a};
			case 3:
				return {(uint8_t)std::round((m) * 255.0f), (uint8_t)std::round((X + m) * 255.0f), (uint8_t)std::round((C + m) * 255.0f), (uint8_t)col.a};
			case 4:
				return {(uint8_t)std::round((X + m) * 255.0f), (uint8_t)std::round((m) * 255.0f), (uint8_t)std::round((C + m) * 255.0f), (uint8_t)col.a};
			case 5:
				return {(uint8_t)std::round((C + m) * 255.0f), (uint8_t)std::round((m) * 255.0f), (uint8_t)std::round((X + m) * 255.0f), (uint8_t)col.a};
			default:
				return {(uint8_t)std::round((C + m) * 255.0f), (uint8_t)std::round((X + m) * 255.0f), (uint8_t)std::round((m) * 255.0f), (uint8_t)col.a};
			}
		}

		// HSL_HSV
		HColor HSV_to_HSL(HColor HSV)
		{
			float h = HSV.h;
			float l = (HSV.l - (HSV.l * HSV.s) / 2.0f);
			float s = (l == 0.0f || l == 1.0f) ? 0.0f : (HSV.l - l) / (std::min(l, 1.0f - l));
			return {h, s, l, HSV.a};
		}

		HColor HSL_to_HSV(HColor HSL)
		{
			float h = HSL.h;
			float v = (HSL.s + (HSL.s * std::min(HSL.l, 1.0f - HSL.l)));
			float s = (v == 0.0f) ? 0.0f : 2.0f - (2.0f * HSL.l / v);
			return {h, s, v, HSL.a};
		}

		// RGB_Hex
		sf::Color hexToRGBA(uint32_t hex)
		{
			uint8_t r = hex >> 24;
			uint32_t x = hex << 8;
			uint8_t g = x >> 24;
			x = hex << 16;
			uint8_t b = x >> 24;
			x = hex << 24;
			uint8_t a = x >> 24;
			return {r, g, b, a};
		}

		uint32_t RGBA_toHex(const sf::Color &color)
		{
			uint32_t hex = color.r;
			hex <<= 8;
			hex += color.g;
			hex <<= 8;
			hex += color.b;
			hex <<= 8;
			hex += color.a;
			return hex;
		}

		// lerp
		HColor lerpHue(const HColor &L1, const HColor &L2, float x)
		{
			return {
				L1.h + (L2.h - L1.h) * x,
				L1.s,
				L1.l,
				L1.a};
		}

		sf::Color lerp(const sf::Color &L1, const sf::Color &L2, float x1, float x2, float x3, float x4)
		{
			return {
				(uint8_t)(L1.r + (L2.r - L1.r) * x1),
				(uint8_t)(L1.g + (L2.g - L1.g) * x2),
				(uint8_t)(L1.b + (L2.b - L1.b) * x3),
				(uint8_t)(L1.a + (L2.a - L1.a) * x4)};
		}

		sf::Color lerp(const sf::Color &L1, const sf::Color &L2, float x)
		{
			return lerp(L1, L2, x, x, x, x);
		}

		// Additive Mixing
		sf::Color additive_mixing(const sf::Color &L1, const sf::Color &L2)
		{
			return {
				(uint8_t)((L2.r + L1.r) * 0.5f),
				(uint8_t)((L2.g + L1.g) * 0.5f),
				(uint8_t)((L2.b + L1.b) * 0.5f),
				(uint8_t)((L2.a + L1.a) * 0.5f)};
		}

		// Subtractive Mixing
		CMYK subtractive_mixing(const CMYK &L1, const CMYK &L2)
		{
			return {
				(L2.c + L1.c) / 2.0f,
				(L2.m + L1.m) / 2.0f,
				(L2.y + L1.y) / 2.0f,
				(L2.k + L1.k) / 2.0f};
		}

		sf::Color subtractive_mixing(const sf::Color &L1, const sf::Color &L2)
		{
			return CMYKtoRGBA(subtractive_mixing(RGBtoCMYK(L1), RGBtoCMYK(L2)), 255);
		}

		// Gradient
		std::vector<sf::Color> gradient(const sf::Color &L1, const sf::Color &L2, int steps)
		{
			std::vector<sf::Color> colors;
			for (int i = 0; i < steps; i++)
			{
				colors.push_back(lerp(L1, L2, (float)i / (float)steps));
			}
			return colors;
		}

		std::vector<HColor> gradient(const HColor &L1, const HColor &L2, int steps)
		{
			std::vector<HColor> colors;
			for (int i = 0; i < steps; i++)
			{
				colors.push_back(lerpHue(L1, L2, (float)i / (float)steps));
			}
			return colors;
		}
	}
}

#endif // SFH_COLOR_HPP