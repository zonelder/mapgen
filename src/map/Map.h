#pragma once
#include "Matrix.h"
static ofColor Coldest = ofColor(0, 255, 255);
static ofColor Colder = ofColor(170, 255, 255);
static ofColor Cold = ofColor(0, 229, 133);
static ofColor Warm = ofColor(255, 255, 100);
static ofColor Warmer = ofColor(255, 100, 0);
static ofColor Warmest = ofColor(241, 12, 0);
//влажность
static ofColor Dryest = ofColor(255, 139, 17);
static ofColor Dryer = ofColor(245, 245, 23);
static ofColor Dry = ofColor(80, 255, 0);
static ofColor Wett = ofColor(85, 255, 255);
static ofColor Wetter = ofColor(20, 70, 255);
static ofColor Wettest = ofColor(0, 0, 100);

enum class  renderStatus {
	HeightMap, HeatMap, WetMap, BiomMap
};
 class Map {
 public:
	 Matrix<ofColor>color;
 private:
	 const int Width = 1024;
	 Matrix<int> Height;
	
	 Matrix<int>Temp;
	 Matrix<int>Wet;
	 Matrix<biom>Biom;
	 int waterLvl = 0;
	 int persent = 24;

	 renderStatus RStat = renderStatus::BiomMap;
 public:
	
	 Map(int psnt)
	 {
		 Height = Matrix<int>(Width, Width);
		 Temp = Matrix<int>(Width, Width);
		 Wet = Matrix<int>(Width, Width);
		 Biom = Matrix<biom>(Width, Width);
		 color= Matrix<ofColor>(Width, Width);
		 persent = psnt;
	 };
	 renderStatus GetRenderStatus()
	 {
		 return RStat;
	  }
	 void SetRenderstatus(renderStatus NewStatus)
	 {
		 RStat = NewStatus;
	 }
	 int GetWidth()
	 {
		 return Width;
	}
	 void Generate()
	 {
		 Height.fill(0);
		 Temp.fill(0);
		 Wet.fill(0);

		 Height.Generate();
		 Temp.setRoudness(2);
		 Temp.setMin_bound(-40);
		 Temp.Generate();
		 Temp.Scaling(50);
		 Wet.setRoudness(10);
		 Wet.Generate();
		 for (int i = 0; i < Width; i++)
			 for (int j = 0; j < Width; j++)
			 {
				 if (j < Width / 2)
					 Temp(i, j) += 160 * j / Width - 50;
				 else
					 Temp(i, j) += -(160 * j / int(Width)) + 110;
			 }
		 Wet.Scaling(5);
		 Height.Scaling(255);
		 //cout << "height in range: " << 0 << " - " << Map.Max() << endl;
		 /// <settings>
		Height.WaterLvl_setting(24,Width);
		 for (int i = 0; i < Width; i++)
			 for (int j = 0; j < Width; j++)
			 {
				 if (Height(i, j) > 0)
					 Temp(i, j) = -float(Height(i, j)) / 200.0f + Temp(i, j);//2- за сколько понижается тмпература с единицей высоты, можно настраивать и генерировать более мягкие или жесткие условия
			 }
		 for (int i = 0; i < Width; i++)
			 for (int j = 0; j < Width; j++)
			 {
				 int DeepWater = -float(waterLvl / 4) * 3;
				 if (Height(i, j) <= DeepWater)
					 Wet(i, j) = 5;
				 if (Height(i, j) < 0 && Height(i, j) > DeepWater)
					 Wet(i, j) = (Wet(i, j) > 2) ? (5) : (Wet(i, j) + 3);
				 if (Height(i, j) <= 100 && Height(i, j) >= 0)
				 {
					 Wet(i, j) = ((3 - round(1.1f * 8 * Height(i, j) / 255)) + Wet(i, j));
					 if (Wet(i, j) > 5)
						 Wet(i, j) = 5;
				 }

				 if (Height(i, j) > 100 && Height(i, j) <= 230)
				 {
					 Wet(i, j) = (round(8 * Height(i, j) / 255) * 0.25f + Wet(i, j));
					 if (Wet(i, j) > 5)
						 Wet(i, j) = 5;
				 }

			 }
		 /// </settings>
		 for (int i = 0; i < Width; i++)
			 for (int j = 0; j < Width; j++)
			 {
				 Biom(i, j) = defBiom(Temp(i, j), Wet(i, j), Height(i, j));
			 }
	 }
	 void HeatColoring()
	 {
		 for (int i = 0; i < Width; i++)
			 for (int j = 0; j < Width; j++)
			 {
				 if (Temp(i, j) > 40)
					 color(i, j) = Warmest;
				 else
					 if (Temp(i, j) > 20 && Temp(i, j) <= 40)
						 color(i, j) = Warmer;
					 else
						 if (Temp(i, j) > 10 && Temp(i, j) <= 20)
							 color(i, j) = Warm;
						 else
							 if (Temp(i, j) > -20 && Temp(i, j) <= 10)
								 color(i, j) = Cold;
							 else
								 if (Temp(i, j) > -30 && Temp(i, j) <= -20)
									 color(i, j) = Colder;
								 else
									 if (Temp(i, j) <= -30)
										 color(i, j) = Coldest;
				 if (Height(i, j) > 0 && Height(i, j) <= 10)
					 color(i, j) = ofColor::black;
			 }
	 }

	 void HeightColoring()
	 {
		 for (int i = 0; i < Width; i++)
			 for (int j = 0; j < Width; j++)
			 {
				 if ((Height(i, j) <= 0))
					 color(i, j) = ofColor(rand() % 13, rand() % 13, 128 + rand() % 13);
				 //if (Map(i,j)==0)
					 //color(i,j) = ofColor(204+rand()%13, 204 + rand() % 13, 217+rand()%13);
				 else
					 if ((Height(i, j) >= 0) && (Height(i, j) <= 10))
						 color(i, j) = ofColor(218, 165, 32);//песок

					 else
						 if (Height(i, j) > 170)
						 {
							 int rnd = random(-8, 8);
							 if (Height(i, j) + rnd > 255)
								 rnd = Height(i, j);
							 else
								 rnd += Height(i, j);
							 //color(i, j) = ofColor(255, 250, 250);//снежная вершина
							 color(i, j) = ofColor(rnd, rnd, rnd);
						 }
						 else
							 if ((Height(i, j) < 50) && (Height(i, j) > 10))//типа лесочек

							 {

								 color(i, j) = ofColor(34, 177, 34);
							 }
							 else
								 if (Height(i, j) >= 50 && Height(i, j) < 80)//темный лес
									 color(i, j) = ofColor(44, 133, 84);
								 else
									 if (Height(i, j) >= 80 && Height(i, j) <= 110)//горный массив
										 color(i, j) = ofColor(86, 103, 117);
									 else
										 if (Height(i, j) > 110 && Height(i, j) < 170)//серые скалы
											 color(i, j) = ofColor(118, 123, 120);
										 else

											 color(i, j) = ofColor(Height(i, j), Height(i, j), Height(i, j));

			 }
	 }
	 void WetColoring()
	 {
		 for (int i = 0; i < Width; i++)
			 for (int j = 0; j < Width; j++)
			 {
				 if (Wet(i, j) == 0)
					 color(i, j) = Dryest;
				 else
					 if (Wet(i, j) == 1)
						 color(i, j) = Dryer;
					 else if (Wet(i, j) == 2)
						 color(i, j) = Dry;
					 else
						 if (Wet(i, j) == 3)
							 color(i, j) = Wett;
						 else if (Wet(i, j) == 4)
							 color(i, j) = Wetter;
						 else if (Wet(i, j) == 5)
							 color(i, j) = Wettest;
				 if (Height(i, j) > 0 && Height(i, j) <= 10)
					 color(i, j) = ofColor::black;
			 }
	 }

	 void BiomColoring()
	 {
		 for (int i = 0; i < Width; i++)
			 for (int j = 0; j < Width; j++)
			 {
				 switch (Biom(i, j))
				 {
				 case biom::DeepOcean:
					 color(i, j) = ofColor(0, 0, 100);
					 break;
				 case biom::Ocean:
					 color(i, j) = ofColor(85, 255, 255);
					 break;
				 case biom::Desert:
					 color(i, j) = ofColor(239, 243, 184);
					 break;
				 case biom::SubtropicalDesert:
					 color(i, j) = ofColor(193, 154, 107);
					 break;
				 case biom::Savanna:
					 color(i, j) = ofColor(220, 160, 112);
					 break;
				 case biom::RainForest:
					 color(i, j) = ofColor(103, 162, 61);
					 break;
				 case biom::TemperateRainForest:
					 color(i, j) = ofColor(197, 214, 207);
					 break;
				 case biom::SeasonForest:
					 color(i, j) = ofColor(34, 139, 34);
					 break;
				 case biom::GrassLand:
					 color(i, j) = ofColor(76, 153, 0);
					 break;
				 case biom::Woodland:
					 color(i, j) = ofColor(58, 144, 99);
					 break;
				 case biom::BorealForest:
					 color(i, j) = ofColor(84, 96, 79);
					 break;
				 case biom::Tundra:
					 color(i, j) = ofColor(77, 98, 69);
					 break;
				 case biom::Ice:
					 color(i, j) = ofColor(239, 255, 250);
					 break;
				 default:
					 color(i, j) = ofColor(0, 0, 0);
					 break;
				 }
			 }
	 }
	 void coloring()
	 {
		 
		 switch (RStat) {
		 case renderStatus::HeatMap:
		 {
			 this->HeatColoring();
		 }
		 break;
		 case renderStatus::HeightMap:
		 {
			 
			this-> HeightColoring();
		 }
		 break;
		 case renderStatus::WetMap:
		 {
			 this->WetColoring();
		 }
		 break;
		 case renderStatus::BiomMap:
		 {
			 this->BiomColoring();
		 }
		 break;
		 defaulf:
		 this->BiomColoring();
		 break;
		 }
	 }
 };