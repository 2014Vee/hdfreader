// hdfreader.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include <iomanip>
#include <hdf5.h>
#include <string>
#include <H5Cpp.h>
#include "hdfreader.h"
using namespace H5;
const H5std_string TBData1("TBData");
const H5std_string Latitude1("Latitude");
const H5std_string Longitude1("Longitude");
const H5std_string SensorAzimuth1("SensorAzimuth");
const H5std_string SensorZenith1("SensorZenith");
const H5std_string GPSData1("GPSData");
const H5std_string AttituteData1("AttituteData");
const H5std_string LandSeaMask1("LandSeaMask");

float TBData[512][512], Latitude[512][512], SensorAzimuth[512][512], Longitude[512][512], SensorZenith[512][512];
unsigned int LandSeaMask[512][512];
double GPSData[1][6], AttituteData[1][4];

//const string filename = "NSXJ.HDF5";
float get_TBData(const std::string filename, const int &row, const int &col)
{

	//读取hdf5文件
	H5File file(filename, H5F_ACC_RDONLY);
	//读取辐射亮度信息
	DataSet dataset = file.openDataSet(TBData1);
	DataSpace filespace = dataset.getSpace();
	//读取数据的维度，比如二维则输出2
	int rank = filespace.getSimpleExtentNdims();
	// dataset dimensions，dims[0]代表第一维度的大小
	hsize_t dims[2];
	//获取并打印文件数据空间的维度大小
	rank = filespace.getSimpleExtentDims(dims);

	//输出dataset的维度及维度的大小
	/*std::cout << "dataset rank = " << rank << ", dimensions "
		<< (unsigned long)(dims[0]) << " x "
		<< (unsigned long)(dims[1]) << std::endl;*/
		//定义要读取数据集的内存空间，这里需要根据实际值进行更新，比如下面的AttitudeData由于和TBData所需空间不一样则需要进行重新定义；
	DataSpace mspace1(2, dims);
	dataset.read(TBData, PredType::NATIVE_FLOAT, mspace1, filespace);
	/*std::cout << TBData[row][col] << std::endl;*/
	return TBData[row][col];
}

float get_Latitude(const std::string filename, const int &row, const int &col)
{
	//读取hdf5文件
	H5File file(filename, H5F_ACC_RDONLY);
	//读取辐射亮度信息
	DataSet dataset = file.openDataSet(Latitude1);
	DataSpace filespace = dataset.getSpace();
	//读取数据的维度，比如二维则输出2
	int rank = filespace.getSimpleExtentNdims();
	// dataset dimensions，dims[0]代表第一维度的大小
	hsize_t dims[2];
	//获取并打印文件数据空间的维度大小
	rank = filespace.getSimpleExtentDims(dims);

	//输出dataset的维度及维度的大小
	/*std::cout << "dataset rank = " << rank << ", dimensions "
		<< (unsigned long)(dims[0]) << " x "
		<< (unsigned long)(dims[1]) << std::endl;*/
		//定义要读取数据集的内存空间，这里需要根据实际值进行更新，比如下面的AttitudeData由于和TBData所需空间不一样则需要进行重新定义；
	DataSpace mspace1(2, dims);
	dataset.read(TBData, PredType::NATIVE_FLOAT, mspace1, filespace);
	return Latitude[row][col];
}

float get_Longitude(const std::string filename, const int &row, const int &col)
{

	//读取hdf5文件
	H5File file(filename, H5F_ACC_RDONLY);
	//读取辐射亮度信息
	DataSet dataset = file.openDataSet(Longitude1);
	DataSpace filespace = dataset.getSpace();
	//读取数据的维度，比如二维则输出2
	int rank = filespace.getSimpleExtentNdims();
	// dataset dimensions，dims[0]代表第一维度的大小
	hsize_t dims[2];
	//获取并打印文件数据空间的维度大小
	rank = filespace.getSimpleExtentDims(dims);

	//输出dataset的维度及维度的大小
	/*std::cout << "dataset rank = " << rank << ", dimensions "
		<< (unsigned long)(dims[0]) << " x "
		<< (unsigned long)(dims[1]) << std::endl;*/
		//定义要读取数据集的内存空间，这里需要根据实际值进行更新，比如下面的AttitudeData由于和TBData所需空间不一样则需要进行重新定义；
	DataSpace mspace1(2, dims);
	dataset.read(Longitude, PredType::NATIVE_FLOAT, mspace1, filespace);
	return Longitude[row][col];
}

float get_SensorAzimuth(const std::string filename, const int &row, const int &col)
{

	//读取hdf5文件
	H5File file(filename, H5F_ACC_RDONLY);
	//读取辐射亮度信息
	DataSet dataset = file.openDataSet(SensorAzimuth1);
	DataSpace filespace = dataset.getSpace();
	//读取数据的维度，比如二维则输出2
	int rank = filespace.getSimpleExtentNdims();
	// dataset dimensions，dims[0]代表第一维度的大小
	hsize_t dims[2];
	//获取并打印文件数据空间的维度大小
	rank = filespace.getSimpleExtentDims(dims);

	//输出dataset的维度及维度的大小
	/*std::cout << "dataset rank = " << rank << ", dimensions "
		<< (unsigned long)(dims[0]) << " x "
		<< (unsigned long)(dims[1]) << std::endl;*/
		//定义要读取数据集的内存空间，这里需要根据实际值进行更新，比如下面的AttitudeData由于和TBData所需空间不一样则需要进行重新定义；
	DataSpace mspace1(2, dims);
	dataset.read(SensorAzimuth, PredType::NATIVE_FLOAT, mspace1, filespace);
	return SensorAzimuth[row][col];
}

float get_SensorZenith(const std::string filename, const int &row, const int &col)
{

	//读取hdf5文件
	H5File file(filename, H5F_ACC_RDONLY);
	//读取辐射亮度信息
	DataSet dataset = file.openDataSet(SensorZenith1);
	DataSpace filespace = dataset.getSpace();
	//读取数据的维度，比如二维则输出2
	int rank = filespace.getSimpleExtentNdims();
	// dataset dimensions，dims[0]代表第一维度的大小
	hsize_t dims[2];
	//获取并打印文件数据空间的维度大小
	rank = filespace.getSimpleExtentDims(dims);

	//输出dataset的维度及维度的大小
	/*std::cout << "dataset rank = " << rank << ", dimensions "
		<< (unsigned long)(dims[0]) << " x "
		<< (unsigned long)(dims[1]) << std::endl;*/
		//定义要读取数据集的内存空间，这里需要根据实际值进行更新，比如下面的AttitudeData由于和TBData所需空间不一样则需要进行重新定义；
	DataSpace mspace1(2, dims);
	dataset.read(SensorZenith, PredType::NATIVE_FLOAT, mspace1, filespace);
	return SensorZenith[row][col];
}

unsigned int get_LandSeaMask(const std::string filename, const int &row, const int &col)
{

	//读取hdf5文件
	H5File file(filename, H5F_ACC_RDONLY);
	//读取辐射亮度信息
	DataSet dataset = file.openDataSet(LandSeaMask1);
	DataSpace filespace = dataset.getSpace();
	//读取数据的维度，比如二维则输出2
	int rank = filespace.getSimpleExtentNdims();
	// dataset dimensions，dims[0]代表第一维度的大小
	hsize_t dims[2];
	//获取并打印文件数据空间的维度大小
	rank = filespace.getSimpleExtentDims(dims);

	//输出dataset的维度及维度的大小
	/*std::cout << "dataset rank = " << rank << ", dimensions "
		<< (unsigned long)(dims[0]) << " x "
		<< (unsigned long)(dims[1]) << std::endl;*/
		//定义要读取数据集的内存空间，这里需要根据实际值进行更新，比如下面的AttitudeData由于和TBData所需空间不一样则需要进行重新定义；
	DataSpace mspace1(2, dims);
	dataset.read(LandSeaMask, PredType::NATIVE_UINT, mspace1, filespace);
	return LandSeaMask[row][col];
}

double get_AttituteData(const std::string filename)
{
	//读取观测时间和姿态数据
	H5File file(filename, H5F_ACC_RDONLY);
	DataSet dataset = file.openDataSet(AttituteData1);
	DataSpace filespace = dataset.getSpace();
	hsize_t dims[2];
	int rank = filespace.getSimpleExtentNdims();
	rank = filespace.getSimpleExtentDims(dims);
	DataSpace mspace2(2, dims);
	dataset.read(AttituteData, PredType::NATIVE_DOUBLE, mspace2, filespace);
	return AttituteData[0][0];

}
