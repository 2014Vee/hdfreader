#include "HdfReader.h"
#include <hdf5.h>
#include <string>
#include <H5Cpp.h>
//强制输出小数位配合cout使用，比如cout << setprecision(8) << value << endl; // 改成8精度，所以输出为12.345679
#include <iomanip>
//#include <fstream>
using namespace H5;
using std::cout;
using std::endl;


float TBDataTmp[512][512], LatitudeTmp[512][512], SensorAzimuthTmp[512][512], LongitudeTmp[512][512], SensorZenithTmp[512][512];
unsigned int LandSeaMaskTmp[512][512];

Hdf5Reader::Hdf5Reader(const char *filename, const int row, const int col)
{
    hid_t file_id;
    herr_t status;
    hid_t dataset_id;
    status = H5Fclose(file_id);
    file_id = H5Fopen(filename, H5F_ACC_RDWR, H5P_DEFAULT);
    //读取辐射亮度信息
    dataset_id = H5Dopen(file_id, "/TBData", H5P_DEFAULT);
    status = H5Dread(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, TBDataTmp);
    Hdf.TBData = TBDataTmp[row][col];


    //读取经度信息
    dataset_id = H5Dopen(file_id, "/Longitude", H5P_DEFAULT);
    status = H5Dread(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, LongitudeTmp);
    Hdf.Longitude = LongitudeTmp[row][col];



    //读取纬度信息
    dataset_id = H5Dopen(file_id, "/Latitude", H5P_DEFAULT);
    status = H5Dread(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, LatitudeTmp);
    Hdf.Latitude = LatitudeTmp[row][col];

    //读取卫星方位角信息
    dataset_id = H5Dopen(file_id, "/SensorAzimuth", H5P_DEFAULT);
    status = H5Dread(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, SensorAzimuthTmp);
    Hdf.SensorAzimuth = SensorAzimuthTmp[row][col];

    //读取卫星天顶角信息
    dataset_id = H5Dopen(file_id, "/SensorZenith", H5P_DEFAULT);
    status = H5Dread(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, SensorZenithTmp);
    Hdf.SensorZenith = SensorZenithTmp[row][col];

    //读取海路边界信息
    dataset_id = H5Dopen(file_id, "/LandSeaMask", H5P_DEFAULT);
    status = H5Dread(dataset_id, H5T_NATIVE_UINT, H5S_ALL, H5S_ALL, H5P_DEFAULT, LandSeaMaskTmp);
    Hdf.LandSeaMask = LandSeaMaskTmp[row][col];

    //读取观测时间和姿态数据
    dataset_id = H5Dopen(file_id, "/AttituteData", H5P_DEFAULT);
    status = H5Dread(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, Hdf.AttituteData);

    //读取轨道数据
    dataset_id = H5Dopen(file_id, "/GPSData", H5P_DEFAULT);
    status = H5Dread(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, Hdf.GPSData);


    status = H5Dclose(dataset_id);
    status = H5Fclose(file_id);



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





int main()
{
    int row = 1;
    int col = 1;
    const char* FILENAME =  "NSXJ.HDF5";
    Hdf5Reader hdf5(FILENAME, row, col);
    cout << "Location:("<< row << "," << col << ")" << endl;
    cout << "Latitude:"<<std::setprecision(20) << hdf5.get_Latitude() << endl;
    cout << "Longitude:"<<std::setprecision(20) << hdf5.get_Longitude() << endl;
    cout << "TBData:"<<std::setprecision(20) << hdf5.get_TBData() << endl;
    cout << "LandSeaMask:" << std::setprecision(20) << hdf5.get_LandSeaMask() << endl;
    cout << "AttituteData-RLR:"<<std::setprecision(20) << hdf5.get_AttituteData() << endl;
    cout << "GPSData[0]:" << std::setprecision(20) << hdf5.Hdf.GPSData[0][0] << endl;
    system("pause");
    return 0;
}
