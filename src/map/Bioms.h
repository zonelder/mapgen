#pragma once

enum class biom {
	DeepOcean, Ocean, RainForest, TemperateRainForest, Woodland, Desert, Savanna, SeasonForest, BorealForest, GrassLand, SubtropicalDesert, Tundra, Ice, River

};

biom defBiom(int Temp, int Wet, int Height);