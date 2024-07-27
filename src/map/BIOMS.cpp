#pragma once
#include "Bioms.h"

biom defBiom(int Temp, int Wet, int Height)
{
	if (Height <= 0)
	{
		if (Height <= -13)
			return biom::DeepOcean;
		else
			return biom::Ocean;
	}
	else
	{
		if (Temp > 40)//hottest
		{
			switch (Wet)
			{

			case 0://Dryest
				return biom::Desert;
				break;
			case 1://Dryer
				return biom::Desert;
				break;
			case 2://Dry
				return biom::SubtropicalDesert;
				break;
			case 3://wet
				return biom::Savanna;
				break;
			case 4://wetter
				return biom::SeasonForest;
				break;
			case 5://wettest
				return biom::RainForest;
				break;
			default:
				break;
			}
		}
		if (Temp > 20 && Temp <= 40)//hotter
		{
			switch (Wet)
			{

			case 0://Dryest
				return biom::Desert;
				break;
			case 1://Dryer
				return biom::Desert;
				break;
			case 2://Dry
				return biom::Savanna;
				break;
			case 3://wet
				return biom::Savanna;
				break;
			case 4://wetter
				return biom::RainForest;
				break;
			case 5://wettest
				return biom::RainForest;
				break;
			default:
				break;
			}
		}
		if (Temp > 10 && Temp <= 20)//hot
		{
			switch (Wet)
			{

			case 0://Dryest
				return biom::GrassLand;
				break;
			case 1://Dryer
				return biom::GrassLand;
				break;
			case 2://Dry
				return biom::Woodland;
				break;
			case 3://wet
				return biom::Woodland;
				break;
			case 4://wetter
				return biom::SeasonForest;
				break;
			case 5://wettest
				return biom::TemperateRainForest;
				break;
			default:
				break;
			}
		}
		if (Temp > -20 && Temp <= 10)//cold
		{
			switch (Wet)
			{

			case 0://Dryest
				return biom::GrassLand;
				break;
			case 1://Dryer
				return biom::GrassLand;
				break;
			case 2://Dry
				return biom::Woodland;
				break;
			case 3://wet
				return biom::BorealForest;
				break;
			case 4://wetter
				return biom::BorealForest;
				break;
			case 5://wettest
				return biom::BorealForest;
				break;
			default:
				break;
			}
		}
		if (Temp > -30 && Temp <= -20)//Colder
		{
			switch (Wet)
			{
			default:
				return biom::Tundra;
				break;
			}
		}
		if (Temp <= -30)//Coldest
		{
			switch (Wet)
			{
			default:
				return biom::Ice;
				break;
			}
		}
	}
}