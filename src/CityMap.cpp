#include "CityMap.h"
#include <random>


// const int CityMap::m_width = 24;
// const int CityMap::m_height = 24;

int CityMap::dice()
{
  static std::default_random_engine generator;
  static std::uniform_int_distribution<int> distribution(1, 1000);
  static auto dice2 = std::bind ( distribution, generator );
  return dice2();
}


CityMap::CityMap()
{
  defaultTile.road = 1;
  defaultTile.isDefault = true;



}


CityMap::~CityMap()
{


}


void CityMap::generate()
{

  // tiles[0][0].object_type = 1;
  // tiles[1][2].object_type = 2;
   // tiles[3][5].object_type = 3;



  for (int i = 0; i < m_width; ++i)
  {
    for (int j = 0; j < m_height; ++j)
    {
      if (dice() > 420)
      {
        tiles[i][j].object_type = 1;
        while (tiles[i][j].treeAng1 + tiles[i][j].treeAng2 +
               tiles[i][j].treeAng3 + tiles[i][j].treeAng4 == 0)
        {
          if (dice() > 300) tiles[i][j].treeAng1 = dice();
          if (dice() > 300) tiles[i][j].treeAng2 = dice();
          if (dice() > 300) tiles[i][j].treeAng3 = dice();
          if (dice() > 300) tiles[i][j].treeAng4 = dice();
        }
      }
    }
  }

  //
  // tiles[5][5].object_type = 3;
  //
  // tiles[8][11].object_type = 2;
  // tiles[8][11].treeAng1 = 1;
  //
  // tiles[8][12].object_type = 2;
  // tiles[8][12].treeAng1 = 2;
  //
  // tiles[8][13].object_type = 2;
  // tiles[8][13].treeAng1 = 3;
  //
  // tiles[8][14].object_type = 2;
  // tiles[8][14].treeAng1 = 4;
  //
  // tiles[8][15].object_type = 2;
  // tiles[8][15].treeAng1 = 5;


}


CityTile& CityMap::getTile(unsigned int i, unsigned int j)
{
  if (i < m_width && j < m_height)
  {
    return tiles[i][j];
  }

  return defaultTile;

}


void CityMap::update()
{
  int powerCount = 0;


  for (int i = 0; i < m_width; ++i)
  {
    for (int j = 0; j < m_height; ++j)
    {
      // Residence
      if (tiles[i][j].object_type == 2 && m_grow && dice() < 100)
      {
        // Check road
        CityTile& t_n = getTile(i, j - 1);
        CityTile& t_s = getTile(i, j + 1);
        CityTile& t_e = getTile(i + 1, j);
        CityTile& t_w = getTile(i - 1, j);

        int num = 0;
        if (t_n.road) num += 1;
        if (t_s.road) num += 1;
        if (t_e.road) num += 1;
        if (t_w.road) num += 1;

        if (num) {
          // Grow
          tiles[i][j].treeAng2 += 1;
          if (tiles[i][j].treeAng2 > 49) tiles[i][j].treeAng2 = 49;
          tiles[i][j].treeAng1 = 1 + tiles[i][j].treeAng2 / 10;
        }
      }

      // Power counting
      if (tiles[i][j].object_type == 2) powerCount -= tiles[i][j].treeAng2;
      if (tiles[i][j].object_type == 3) powerCount += 500000;
    }
  }

  m_grow = (powerCount > 0);
}