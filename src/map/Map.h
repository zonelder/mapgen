#ifndef  __MAP_H__
#define __MAP_H__

#include "Matrix.h"
#include "Bioms.h"

namespace syrenmap
{

	enum class  renderStatus 
	{
		HeightMap,
		HeatMap,
		WetMap,
		BiomMap,
		MAX,//always set in end of enum
	};
	class Map {
	public:

		explicit Map(int psnt) noexcept;
		renderStatus getRenderStatus() const noexcept
		{
			return _rState;
		}
		void setRenderstatus(renderStatus NewStatus) noexcept
		{
			_rState = NewStatus;
			updateColoring();
		}
		int getWidth() const noexcept
		{
			return _width;
		}

		void draw();
		void generate();
		void heatColoring();

		void heightColoring();
		void wetColoring();

		void biomColoring();
		void updateColoring()
		{

			switch (_rState) {
			case renderStatus::HeatMap:
				this->heatColoring();
				break;
			case renderStatus::HeightMap:
				this->heightColoring();
				break;
			case renderStatus::WetMap:
				this->wetColoring();
				break;
			case renderStatus::BiomMap:	
				this->biomColoring();
				break;
			default:
				this->biomColoring();
				break;
			}
		}

	public:
		Matrix<ofColor>color;

	private:
		static const int _width = 1024;
		Matrix<int> _heights;

		Matrix<int>_temps;
		Matrix<int>_wet;
		Matrix<bioms::Biom>_bioms;
		int _waterLvl;
		int _persent;

		renderStatus _rState;
	};

}


#endif //  __MAP_H__