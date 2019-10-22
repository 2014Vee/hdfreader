#include "Hdf5Reader.h"

#include <hdf5.h>
#include <string>
#include <H5Cpp.h>
//强制输出小数位配合cout使用，比如cout << setprecision(8) << value << endl; // 改成8精度，所以输出为12.345679
#include <iomanip>
//#include <fstream>
using namespace H5;
using std::cout;
using std::endl;


const H5std_string Latitude1("Latitude");
const H5std_string Longitude1("Longitude");
const H5std_string SensorAzimuth1("SensorAzimuth");
const H5std_string SensorZenith1("SensorZenith");
const H5std_string TBData1("TBData");
const H5std_string GPSData1("GPSData");
const H5std_string AttituteData1("AttituteData");
const H5std_string LandSeaMask1("LandSeaMask");


float TBDataTmp[512][512], LatitudeTmp[512][512], SensorAzimuthTmp[512][512], LongitudeTmp[512][512], SensorZenithTmp[512][512];
unsigned int LandSeaMaskTmp[512][512];
Hdf5Reader::Hdf5Reader(std::string filename, const int row, const int col)
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
	/*
	//输出dataset的维度及维度的大小
	cout << "dataset rank = " << rank << ", dimensions "
		<< (unsigned long)(dims[0]) << " x "
		<< (unsigned long)(dims[1]) << endl;*/
	//定义要读取数据集的内存空间，这里需要根据实际值进行更新，比如下面的AttitudeData由于和TBData所需空间不一样则需要进行重新定义；
	
	DataSpace mspace1(2, dims);
	dataset.read(TBDataTmp, PredType::NATIVE_FLOAT, mspace1, filespace);
	Hdf.TBData = TBDataTmp[row][col];


	//读取经度信息
	dataset = file.openDataSet(Longitude1);
	filespace = dataset.getSpace();
	dataset.read(LongitudeTmp, PredType::NATIVE_FLOAT, mspace1, filespace);
	Hdf.Longitude = LongitudeTmp[row][col];



	//读取纬度信息
	dataset = file.openDataSet(Latitude1);
	filespace = dataset.getSpace();
	dataset.read(LatitudeTmp, PredType::NATIVE_FLOAT, mspace1, filespace);
	Hdf.Latitude = LatitudeTmp[row][col];

	//读取卫星方位角信息
	dataset = file.openDataSet(SensorAzimuth1);
	filespace = dataset.getSpace();
	dataset.read(SensorAzimuthTmp, PredType::NATIVE_FLOAT, mspace1, filespace);
	Hdf.SensorAzimuth = SensorAzimuthTmp[row][col];

	//读取卫星天顶角信息
	dataset = file.openDataSet(SensorZenith1);
	filespace = dataset.getSpace();
	dataset.read(SensorZenithTmp, PredType::NATIVE_FLOAT, mspace1, filespace);
	Hdf.SensorZenith = SensorZenithTmp[row][col];

	//读取海路边界信息
	dataset = file.openDataSet(LandSeaMask1);
	filespace = dataset.getSpace();
	dataset.read(LandSeaMaskTmp, PredType::NATIVE_UINT, mspace1, filespace);
	Hdf.LandSeaMask = LandSeaMaskTmp[row][col];

	//读取观测时间和姿态数据
	dataset = file.openDataSet(AttituteData1);
	filespace = dataset.getSpace();
	rank = filespace.getSimpleExtentNdims();
	rank = filespace.getSimpleExtentDims(dims);
	DataSpace mspace2(2, dims);
	dataset.read(Hdf.AttituteData, PredType::NATIVE_DOUBLE, mspace2, filespace);



	//读取轨道数据
	dataset = file.openDataSet(GPSData1);
	filespace = dataset.getSpace();
	rank = filespace.getSimpleExtentNdims();
	rank = filespace.getSimpleExtentDims(dims);
	DataSpace mspace3(2, dims);
	dataset.read(Hdf.GPSData, PredType::NATIVE_DOUBLE, mspace3, filespace);

	
}
Hdf5Reader::~Hdf5Reader()
{
	
}



float Hdf5Reader::get_TBData()
{
	return this->Hdf.TBData;
}

float Hdf5Reader::get_Latitude()
{
	return this->Hdf.Latitude;
}

float Hdf5Reader::get_Longitude()
{
	return this->Hdf.Longitude;
}

unsigned int Hdf5Reader::get_LandSeaMask()
{
	return this->Hdf.LandSeaMask;
}

double Hdf5Reader::get_AttituteData()
{
	return this->Hdf.AttituteData[0][0];
}

int main() {
	int i = 1;
	int j = 1;
	int &row = i;
	int &col = j;
	Hdf5Reader hdf5("NSXJ.HDF5", row, col);
	
	cout << "坐标：" << "(" << row << "," << col << ")" << endl;
	cout << "Latitude:"<<std::setprecision(20) << hdf5.get_Latitude() << endl;
	cout << "Longitude:"<<std::setprecision(20) << hdf5.get_Longitude() << endl;
	cout << "TBData:"<<std::setprecision(20) << hdf5.get_TBData() << endl;
	cout << "LandSeaMask:" << std::setprecision(20) << hdf5.get_LandSeaMask() << endl;
	cout << "AttituteData-RLR:"<<std::setprecision(20) << hdf5.get_AttituteData() << endl;
	cout << "GPSData[0]:" << std::setprecision(20) << hdf5.Hdf.GPSData[0][0] << endl;
	system("pause");
	return 0;
}
