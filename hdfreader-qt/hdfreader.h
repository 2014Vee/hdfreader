#pragma once
#ifndef HDF5READER_H
#define HDF5READER_H
#include <iostream>
//#include <hdf5.h>






struct Hdf5Data
{
    float Latitude, Longitude, SensorAzimuth, SensorZenith, TBData;
    double GPSData[1][6], AttituteData[1][4];
    unsigned int LandSeaMask;

};


class Hdf5Reader
{
private:
    std::string filename;

    //Hdf5Data Hdf5;
public:
    Hdf5Data Hdf;
    Hdf5Reader(const char *filename, const int row, const int col);
    ~Hdf5Reader();
    float get_Latitude();
    float get_Longitude();
    float get_TBData();
    float get_SensorAzimuth();
    float get_SensorZenith();
    //这里需要注意一下，LandSeaMask是unsigned int型并非数据编目上写的unsigned char
    unsigned int get_LandSeaMask();
    double get_AttituteData();

};
/*
读取hdf5中的物理量信息类
函数get_Latitude()输入参数无，输出为对应坐标纬度；
函数get_Longitude()输入参数无，输出为对应坐标经度；
函数get_TBData()输入参数无，输出为对应坐标辐射亮度；
函数get_SensorAzimuth()输入参数无，输出为卫星方位角；
函数get_SensorZenith()输入参数无，输出为卫星天顶角；
函数get_LandSeaMask()输入参数无，输出为海路边界信息；
函数get_AttituteData()输入参数无，输出为观测是时间和姿态数据，这里默认输出第一列的时间。

也可以通过访问Hdf5Reader类中的Hdf5Data结构体进行数据获取。
*/


#endif
