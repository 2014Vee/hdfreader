#pragma once
#ifdef HDFREADER_EXPORTS
#define HDFREADER_API __declspec(dllexport)
#else
#define HDFREADER_API __declspec(dllimport)
#endif//这里注意#endif位置，刚开始放在头文件的尾部造成了无法生成对应lib文件的恶果
#include <string>
#include <iostream>

using std::string;

extern "C" HDFREADER_API float get_TBData(const std::string filename, const int &row, const int &col);
extern "C" HDFREADER_API float get_Latitude(const std::string filename, const int &row, const int &col);
extern "C" HDFREADER_API float get_Longitude(const std::string filename, const int &row, const int &col);
extern "C" HDFREADER_API unsigned int get_LandSeaMask(const std::string filename, const int &row, const int &col);
extern "C" HDFREADER_API float get_SensorAzimuth(const std::string filename, const int &row, const int &col);
extern "C" HDFREADER_API float get_SensorZenith(const std::string filename, const int &row, const int &col);
//extern "C" HDFREADER_API double get_GPSData(const std::string filename, const int &col);
extern "C" HDFREADER_API double get_AttituteData(const std::string filename);

