#include "Bioms.h"

namespace syrenmap::bioms
{

	namespace Colors
	{
		namespace temperature
		{
			const ofColor s_coldest = ofColor(0, 255, 255);
			const ofColor s_colder = ofColor(170, 255, 255);
			const ofColor s_cold = ofColor(0, 229, 133);
			const ofColor s_warm = ofColor(255, 255, 100);
			const ofColor s_warmer = ofColor(255, 100, 0);
			const ofColor s_warmest = ofColor(241, 12, 0);
		}


		namespace wet
		{
			const ofColor s_dryest = ofColor(255, 139, 17);
			const ofColor s_dryer = ofColor(245, 245, 23);
			const ofColor s_dry = ofColor(80, 255, 0);
			const ofColor s_wett = ofColor(85, 255, 255);
			const ofColor s_wetter = ofColor(20, 70, 255);
			const ofColor s_wettest = ofColor(0, 0, 100);
		}

		HeightColorMap::HeightColorMap() //customize your height presets
		{
			//[min height in zone]  = zone color
			_defaultColor = ofColor(0,0,128);//lower then lowest user-define value
			_colorMap[0] = ofColor(218, 165, 32);//sand
			_colorMap[10] = ofColor(34, 177, 34);//forest or smth like
			_colorMap[50] = ofColor(44, 133, 84);// black forest
			_colorMap[80] = ofColor(86, 103, 117);//mount
			_colorMap[110] = ofColor(118, 123, 120);
			_colorMap[170] = ofColor::white;//show peak
		}

		TempColorMap::TempColorMap()//customize your temp presets
		{
			//[min temperature in zone]  = zone color
			_colorMap[40] = temperature::s_warmest;
			_colorMap[20] = temperature::s_warmer;
			_colorMap[10] = temperature::s_warm;
			_colorMap[-20] = temperature::s_cold;
			_colorMap[-30] = temperature::s_colder;

			_defaultColor = temperature::s_coldest;//in case temp lower then lowest user-defined zone
		}

		WetColorMap::WetColorMap()//customize your wet presets
		{
			_colorMap[0] = wet::s_dryest;
			_colorMap[1] = wet::s_dryer;
			_colorMap[2] = wet::s_dry;
			_colorMap[3] = wet::s_wett;
			_colorMap[4] = wet::s_wetter;
			_colorMap[5] = wet::s_wettest;
		}

		BiomsColorMap::BiomsColorMap()// customize your bioms presets
		{
			set(Biom::DeepOcean,						ofColor(0, 0, 100));
			set(Biom::Ocean,							ofColor(85, 255, 255));
			set(Biom::Desert,							ofColor(239, 243, 184));
			set(Biom::SubtropicalDesert,				ofColor(193, 154, 107));
			set(Biom::Savanna,							ofColor(220, 160, 112));
			set(Biom::RainForest,						ofColor(103, 162, 61));
			set(Biom::TemperateRainForest,				ofColor(197, 214, 207));
			set(Biom::SeasonForest,						ofColor(34, 139, 34));
			set(Biom::GrassLand,						ofColor(76, 153, 0));
			set(Biom::Woodland,							ofColor(58, 144, 99));
			set(Biom::BorealForest,						ofColor(84, 96, 79));
			set(Biom::Tundra,							ofColor(77, 98, 69));
			set(Biom::Ice,								ofColor(239, 255, 250));
		}

		const ofColor& HeightColorMap::find(const int& height) const noexcept
		{
			auto it = _colorMap.upper_bound(height);
			if (it == _colorMap.begin())
			{
				return _defaultColor;
			}

			--it;
			return it->second;
		}

		const ofColor& TempColorMap::find(const int& temp) const noexcept
		{
			auto it = _colorMap.upper_bound(temp);
			if (it == _colorMap.begin())
			{
				return _defaultColor;
			}

			--it;
			return it->second;
		}



		const ofColor& WetColorMap::operator[](const int& stage) const noexcept
		{
			return _colorMap[stage];
		}
		void BiomsColorMap::set(const Biom& biom, ofColor color) noexcept
		{
			_colorMap[int(biom)] = color;
 		}
		const ofColor& BiomsColorMap::operator[](const Biom& biom) const noexcept
		{
			return _colorMap[int(biom)];
		}
	}

	Biom defBiom(int _temps, int _wet, int _heights)
	{
		if (_heights <= 0)
		{
			if (_heights <= -13)
				return Biom::DeepOcean;

			return Biom::Ocean;
		}

		if (_temps > 40)//hottest
		{
			switch (_wet)
			{

			case 0://Dryest
				return Biom::Desert;
				break;
			case 1://Dryer
				return Biom::Desert;
				break;
			case 2://Dry
				return Biom::SubtropicalDesert;
				break;
			case 3://wet
				return Biom::Savanna;
				break;
			case 4://wetter
				return Biom::SeasonForest;
				break;
			case 5://wettest
				return Biom::RainForest;
				break;
			default:
				break;
			}

			return Biom::Unknown;
		}
		if (_temps > 20)//hotter
		{
			switch (_wet)
			{

			case 0://Dryest
				return Biom::Desert;
				break;
			case 1://Dryer
				return Biom::Desert;
				break;
			case 2://Dry
				return Biom::Savanna;
				break;
			case 3://wet
				return Biom::Savanna;
				break;
			case 4://wetter
				return Biom::RainForest;
				break;
			case 5://wettest
				return Biom::RainForest;
				break;
			default:
				break;
			}

			return Biom::Unknown;
		}
		if (_temps > 10)//hot
		{
			switch (_wet)
			{

			case 0://Dryest
				return Biom::GrassLand;
				break;
			case 1://Dryer
				return Biom::GrassLand;
				break;
			case 2://Dry
				return Biom::Woodland;
				break;
			case 3://wet
				return Biom::Woodland;
				break;
			case 4://wetter
				return Biom::SeasonForest;
				break;
			case 5://wettest
				return Biom::TemperateRainForest;
				break;
			default:
				break;
			}
			return Biom::Unknown;
		}
		if (_temps > -20)//cold
		{
			switch (_wet)
			{

			case 0://Dryest
				return Biom::GrassLand;
				break;
			case 1://Dryer
				return Biom::GrassLand;
				break;
			case 2://Dry
				return Biom::Woodland;
				break;
			case 3://wet
				return Biom::BorealForest;
				break;
			case 4://wetter
				return Biom::BorealForest;
				break;
			case 5://wettest
				return Biom::BorealForest;
				break;
			default:
				break;
			}

			return Biom::Unknown;
		}
		if (_temps > -30)//s_colder
		{
			switch (_wet)
			{
			default:
				return Biom::Tundra;
				break;
			}
			return Biom::Unknown;
		}

		//s_coldest
		switch (_wet)
		{
		default:
			return Biom::Ice;
			break;
		}

		return Biom::Unknown;
	}

}

