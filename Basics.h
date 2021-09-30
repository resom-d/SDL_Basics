#ifndef BASICS_H
#define BASICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <string>
#include <iostream>
#include <filesystem>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include "EngineBase.h"

#define GlobalFrameRate (50)
#define MUSIC
#define SINTABSIZE (720)

namespace trans = boost::geometry::strategy::transform;
using boost::geometry::dsv;
using namespace boost::geometry;
using namespace std;

typedef boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian> Point2D;

typedef unordered_map<char, SDL_Texture*> CharacterTextureMap;
typedef list<SDL_Color> ColorPalette;



#endif