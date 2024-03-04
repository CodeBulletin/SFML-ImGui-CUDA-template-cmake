#ifndef SFH_RANDOM_HPP
#define SFH_RANDOM_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Color.hpp>
#include <random>
#include <cmath>
#include <vector>

#include "SFH/color.hpp"

#define PI 3.14159265
#define PI_D 3.141592653589793238462643383279502884197169399375105820974944

namespace sfh
{
	template <typename T>
	struct Vector4
	{
		T x, y, z, w;
		Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		Vector4() = default;
		Vector4(const Vector4 &vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
		Vector4 &operator=(const Vector4 &vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = vec.w;
			return *this;
		}
	};

	namespace random
	{
		static std::random_device randomDevice;
		static std::mt19937 mt_engine(randomDevice());

		template <class type>
		using uniform_distribution =
			typename std::conditional<std::is_floating_point<type>::value, std::uniform_real_distribution<type>,
									  typename std::conditional<std::is_integral<type>::value, std::uniform_int_distribution<type>, void>::type>::type;

		// Random Scalar
		template <typename T>
		T rScaler(T min = -1, T max = 1)
		{
			uniform_distribution<T> rand(min, max);
			return {rand(mt_engine)};
		}

		// Random2d
		template <typename T>
		sf::Vector2<T> r2d(T min1, T max1, T min2, T max2)
		{
			uniform_distribution<T> rand1(min1, max1);
			uniform_distribution<T> rand2(min2, max2);
			return {rand1(mt_engine), rand2(mt_engine)};
		}

		template <typename T>
		sf::Vector2<T> r2d(T min, T max)
		{
			return random2d<T>(min, max, min, max);
		}

		template <typename T>
		sf::Vector2<T> rVec2d()
		{
			uniform_distribution<T> rand((T)0, (T)(2 * PI_D));
			T angle = rand(mt_engine);
			return {std::cos<T>(angle), std::sin<T>(angle)};
		}

		// Random3d
		template <typename T>
		sf::Vector3<T> r3d(T min1, T max1, T min2, T max2, T min3, T max3)
		{
			uniform_distribution<T> rand1(min1, max1);
			uniform_distribution<T> rand2(min2, max2);
			uniform_distribution<T> rand3(min3, max3);
			return {rand1(mt_engine), rand2(mt_engine), rand3(mt_engine)};
		}

		template <typename T>
		sf::Vector3<T> r3d(T min, T max)
		{
			return r3d<T>(min, max, min, max, min, max);
		}

		template <typename T>
		sf::Vector3<T> rVec3d()
		{
			uniform_distribution<T> rand((T)0, (T)(2 * PI_D));
			T phi = rand(mt_engine);
			T theta = rand(mt_engine);
			return {
				(T)(std::sin<T>(theta) * std::cos<T>(phi)),
				(T)(std::sin<T>(theta) * std::sin<T>(phi)),
				(T)(std::cos<T>(theta))};
		}

		// Random4d
		template <typename T>
		Vector4<T> r4d(T min1, T max1, T min2, T max2, T min3, T max3, T min4, T max4)
		{
			uniform_distribution<T> rand1(min1, max1);
			uniform_distribution<T> rand2(min2, max2);
			uniform_distribution<T> rand3(min3, max3);
			uniform_distribution<T> rand4(min4, max4);
			return {rand1(mt_engine), rand2(mt_engine), rand3(mt_engine), rand4(mt_engine)};
		}

		template <typename T>
		Vector4<T> r4d(T min, T max)
		{
			return r4d<T>(min, max, min, max, min, max, min, max);
		}

		template <typename T>
		Vector4<T> rVec4d()
		{
			uniform_distribution<T> rand((T)0, (T)(2 * PI_D));
			T alpha = rand(mt_engine);
			T beta = rand(mt_engine);
			T gamma = rand(mt_engine);
			return {
				(std::sin(alpha) * std::cos(beta) * std::cos(gamma)),
				(std::cos(alpha) * std::cos(beta) * std::cos(gamma)),
				(std::sin(beta) * std::cos(gamma)),
				(std::cos(gamma))};
		}

		// RandomNd
		template <typename T>
		std::vector<T> rNd(int n, const T &min, const T &max)
		{
			uniform_distribution<T> rand(min, max);
			std::vector<T> vec;

			for (int i = 0; i < n; i++)
			{
				vec.push_back(rand(mt_engine));
			}

			return vec;
		}

		template <typename T>
		std::vector<T> rVecNd(int n)
		{
			uniform_distribution<T> rand((T)0, (T)(2 * PI_D));
			std::vector<T> vec;

			for (int i = 0; i < n; i++)
			{
				vec.push_back(rand(mt_engine));
			}

			std::vector<T> normalized_vec;

			T sum = 0;
			for (int i = 0; i < n; i++)
			{
				sum += vec[i] * vec[i];
			}

			sum = std::sqrt(sum);

			for (int i = 0; i < n; i++)
			{
				normalized_vec.push_back(vec[i] / sum);
			}

			return normalized_vec;
		}

		//RandomBool
		bool rBool()
		{
			uniform_distribution<int> rand(0, 1);
			return rand(mt_engine);
		}

		bool rThreshold(float threshold)
		{
			uniform_distribution<float> rand(0.0f, 1.0f);
			return rand(mt_engine) < threshold;
		}

		// RandomColor
		sf::Color rRGBA()
		{
			uniform_distribution<uint8_t> rand(0, 255);
			return {rand(mt_engine), rand(mt_engine), rand(mt_engine), rand(mt_engine)};
		}

		sf::Color rRGB(int alpha = 255)
		{
			uniform_distribution<uint8_t> rand(0, 255);
			return { rand(mt_engine), rand(mt_engine), rand(mt_engine), (uint8_t)alpha };
		}

		sf::Color rSurfaceRGBA() {
			Vector4<float> vec = rVec4d<float>();
			return { (uint8_t)(vec.x * 255), (uint8_t)(vec.y * 255), (uint8_t)(vec.z * 255), (uint8_t)(vec.w * 255) };
		}

		sf::Color randomRGB_Surface(int alpha = 255)
		{
			sf::Vector3<float> vec = rVec3d<float>();
			return { (uint8_t)(vec.x * 255), (uint8_t)(vec.y * 255), (uint8_t)(vec.z * 255), (uint8_t)alpha };
		}

		HColor rHue(float s = 1.0f, float l = 0.5f, float a = 1.0f)
		{
			uniform_distribution<float> rand(0.0f, 1.0f);
			return { rand(mt_engine) * 360, s, l, a };
		}
	}
}

#endif // SFH_RANDOM_HPP