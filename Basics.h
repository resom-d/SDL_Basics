#ifndef BASICS_H
#define BASICS_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <algorithm>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

using namespace boost::filesystem;
namespace trans = boost::geometry::strategy::transform;
using boost::geometry::dsv;
using namespace boost::geometry;
using namespace std;

struct  _polygon_2D {
	SDL_FPoint* Points;
	SDL_FPoint* PointsBuffer;
	unsigned short CountP;
	SDL_FPoint LocalOriginP;
	SDL_Rect BoundingBox;
};
typedef struct _polygon_2D Polygon2D;


#define MUSIC
#define GlobalFrameRate (50)
#define SINTABSIZE (720)


typedef boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian> Point2D;

typedef unordered_map<char, SDL_Texture*> CharacterTextureMap;
typedef list<SDL_Color> ColorPalette;



#endif