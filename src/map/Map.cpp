#include "Map.h"
#include "ofGraphics.h"

namespace syrenmap
{
	Map::Map(int psnt) noexcept :
		_heights(_width, _width),
		_temps(_width, _width),
		_wet(_width, _width),
		_bioms(_width, _width),
		color(_width, _width),
		_persent(psnt),
		_rState(renderStatus::BiomMap),
		_waterLvl(0)
	{
	}

	void Map::draw()
	{
		for (int i = 0; i < getWidth(); i++)
		{
			for (int j = 0; j < getWidth(); j++)
			{
				ofSetColor(color(i, j));
				ofRect(i, j, 1, 1);
			}
		}
	}

	void Map::generate()
	{
		_heights.fill(0);
		_temps.fill(0);
		_wet.fill(0);

		_heights.generate();
		_temps.setRoudness(2);
		_temps.setMin_bound(-40);
		_temps.generate();
		_temps.Scaling(50);
		_wet.setRoudness(10);
		_wet.generate();
		for (int i = 0; i < _width; i++)//make linear temperature distribution
			for (int j = 0; j < _width; j++)
			{
				if (j < _width / 2)
					_temps(i, j) += 160 * j / _width - 50;
				else
					_temps(i, j) += -(160 * j / int(_width)) + 110;
			}
		_wet.Scaling(5);
		_heights.Scaling(255);
		_heights.WaterLvl_setting(24, _width);
		for (int i = 0; i < _width; i++)
			for (int j = 0; j < _width; j++)//decrease temperature with height
			{
				if (_heights(i, j) > 0)
					_temps(i, j) = -float(_heights(i, j)) / 200.0f + _temps(i, j);
			}
		const int DeepWater = -float(_waterLvl / 4) * 3;
		const double wetDropToHighest = 4.0;
		const double factor = 1 / log(wetDropToHighest);//how wet is dropped over height
		for (int i = 0; i < _width; i++)
			for (int j = 0; j < _width; j++)//decrease wet with height
			{

				if (_heights(i, j) <= DeepWater)
				{
					_wet(i, j) = 5;
					continue;
				}

				if (_heights(i, j) < 0)
				{
					_wet(i, j) = std::min<int>(_wet(i, j) + 3, bioms::s_wetMax - 1);
					continue;
				}
				_wet(i, j) = _wet(i, j) * exp(-double(_heights(i, j) / 255)/factor);
				_wet(i, j) = std::min<int>(_wet(i, j), bioms::s_wetMax - 1);

			}
		for (int i = 0; i < _width; i++)
			for (int j = 0; j < _width; j++)
			{
				_bioms(i, j) = bioms::defBiom(_temps(i, j), _wet(i, j), _heights(i, j));
			}
	}


	void Map::heatColoring()
	{
		auto& colors = bioms::Colors::TempColorMap::instance();
		for (int i = 0; i < _width; i++)
			for (int j = 0; j < _width; j++)
			{
				color(i, j) = colors.find(_temps(i, j));
				if (_heights(i, j) > 0 && _heights(i, j) <= 10)
					color(i, j) = ofColor::black;
			}
	}

	void Map::heightColoring()
	{
		auto& colors = bioms::Colors::HeightColorMap::instance();
		for (int i = 0; i < _width; i++)
			for (int j = 0; j < _width; j++)
			{

				const auto& h = _heights(i, j);
				const auto& customColor = colors.find(h);
				if (h <= 0)
				{
					color(i, j) = customColor + ofColor(rand() % 13, rand() % 13, rand() % 13);
					continue;
				}
				else if (h > 170)
				{
					auto rnd = std::clamp(random(-8, 8) + h, 0, 255);
					color(i, j) = ofColor(rnd, rnd, rnd);
					continue;
				}

				color(i, j) = customColor;
			}
	}

	void Map::wetColoring()
	{
		auto& colors = bioms::Colors::WetColorMap::instance();
		for (int i = 0; i < _width; i++)
			for (int j = 0; j < _width; j++)
			{
				color(i, j) = colors[_wet(i, j)];
			}
	}

	void Map::biomColoring()
	{
		auto& colors = bioms::Colors::BiomsColorMap::instance();
		for (int i = 0; i < _width; i++)
			for (int j = 0; j < _width; j++)
			{
				color(i, j) = colors[_bioms(i, j)];
			}
	}

}

