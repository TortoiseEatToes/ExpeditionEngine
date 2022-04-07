#ifndef	TerrainCell_h
#define	TerrainCell_h

#include "TerrainCoordinates.h"

struct TerrainCell {
	TerrainCoordinates coor;
	float MinY;
	float MaxY;
};

#endif 	TerrainCell_h
