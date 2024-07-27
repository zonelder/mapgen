#ifndef __BIOMS__H__
#define __BIOMS__H__

#include "ofColor.h"
#include <array>
#include <map>

namespace syrenmap
{
	namespace bioms
	{

		enum class Biom {
			DeepOcean, Ocean, RainForest,
			TemperateRainForest, Woodland, Desert,
			Savanna, SeasonForest, BorealForest,
			GrassLand, SubtropicalDesert, Tundra,
			Ice, River,Unknown,
			MAX,//keep last
		};

		static constexpr size_t s_wetMax = 6;

		namespace Colors
		{
			template<class T>
			class const_singleton
			{
			public:
				static const T& instance() noexcept
				{
					static T m;
					return m;
				}
			};
			struct BiomsColorMap : public const_singleton< BiomsColorMap>
			{
				BiomsColorMap();
				const ofColor& operator[](const Biom&) const noexcept;

				void set(const Biom& biom, ofColor color) noexcept;
			private:

				std::array < ofColor, int(Biom::MAX)> _colorMap;
			};

			struct WetColorMap : public const_singleton< WetColorMap>
			{
				WetColorMap();
				const ofColor& operator[](const int&) const noexcept;
			private:
				std::array < ofColor, s_wetMax> _colorMap;
			};

			struct TempColorMap : public const_singleton< TempColorMap>
			{
				TempColorMap();
				const ofColor& find(const int& temp) const noexcept;

			private:
				std::map<int, ofColor> _colorMap;//pair of (min zone temp, zone color)
				ofColor _defaultColor;//color of zone if user input less then minimum defined key
			};

			struct HeightColorMap : public const_singleton< HeightColorMap>
			{
				HeightColorMap();
				const ofColor& find(const int& height) const noexcept;

			private:
				std::map<int, ofColor> _colorMap;//pair of (min zone temp, zone color)
				ofColor _defaultColor;//color of zone if user input less then minimum defined key
			};

			namespace temperature
			{
				extern const ofColor s_coldest;
				extern const ofColor s_colder;
				extern const ofColor s_cold;
				extern const ofColor s_warm;
				extern const ofColor s_warmer;
				extern const ofColor s_warmest;
			}

			namespace wet
			{
				extern const ofColor s_dryest;
				extern const ofColor s_dryer;
				extern const ofColor s_dry;
				extern const ofColor s_wett;
				extern const ofColor s_wetter;
				extern const ofColor s_wettest;
			}

		};



		Biom defBiom(int _temps, int _wet, int _heights);


	}
}

#endif // !__BIOMS__H__