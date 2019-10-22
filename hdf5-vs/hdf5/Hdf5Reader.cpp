#include "Hdf5Reader.h"

#include <hdf5.h>
#include <string>
#include <H5Cpp.h>
//ǿ�����С��λ���coutʹ�ã�����cout << setprecision(8) << value << endl; // �ĳ�8���ȣ��������Ϊ12.345679
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
	//��ȡhdf5�ļ�
	H5File file(filename, H5F_ACC_RDONLY);
	//��ȡ����������Ϣ
	DataSet dataset = file.openDataSet(TBData1);
	DataSpace filespace = dataset.getSpace();
	//��ȡ���ݵ�ά�ȣ������ά�����2
	int rank = filespace.getSimpleExtentNdims();
	// dataset dimensions��dims[0]�����һά�ȵĴ�С
	hsize_t dims[2];        
	//��ȡ����ӡ�ļ����ݿռ��ά�ȴ�С
	rank = filespace.getSimpleExtentDims(dims);
	/*
	//���dataset��ά�ȼ�ά�ȵĴ�С
	cout << "dataset rank = " << rank << ", dimensions "
		<< (unsigned long)(dims[0]) << " x "
		<< (unsigned long)(dims[1]) << endl;*/
	//����Ҫ��ȡ���ݼ����ڴ�ռ䣬������Ҫ����ʵ��ֵ���и��£����������AttitudeData���ں�TBData����ռ䲻һ������Ҫ�������¶��壻
	
	DataSpace mspace1(2, dims);
	dataset.read(TBDataTmp, PredType::NATIVE_FLOAT, mspace1, filespace);
	Hdf.TBData = TBDataTmp[row][col];


	//��ȡ������Ϣ
	dataset = file.openDataSet(Longitude1);
	filespace = dataset.getSpace();
	dataset.read(LongitudeTmp, PredType::NATIVE_FLOAT, mspace1, filespace);
	Hdf.Longitude = LongitudeTmp[row][col];



	//��ȡγ����Ϣ
	dataset = file.openDataSet(Latitude1);
	filespace = dataset.getSpace();
	dataset.read(LatitudeTmp, PredType::NATIVE_FLOAT, mspace1, filespace);
	Hdf.Latitude = LatitudeTmp[row][col];

	//��ȡ���Ƿ�λ����Ϣ
	dataset = file.openDataSet(SensorAzimuth1);
	filespace = dataset.getSpace();
	dataset.read(SensorAzimuthTmp, PredType::NATIVE_FLOAT, mspace1, filespace);
	Hdf.SensorAzimuth = SensorAzimuthTmp[row][col];

	//��ȡ�����춥����Ϣ
	dataset = file.openDataSet(SensorZenith1);
	filespace = dataset.getSpace();
	dataset.read(SensorZenithTmp, PredType::NATIVE_FLOAT, mspace1, filespace);
	Hdf.SensorZenith = SensorZenithTmp[row][col];

	//��ȡ��·�߽���Ϣ
	dataset = file.openDataSet(LandSeaMask1);
	filespace = dataset.getSpace();
	dataset.read(LandSeaMaskTmp, PredType::NATIVE_UINT, mspace1, filespace);
	Hdf.LandSeaMask = LandSeaMaskTmp[row][col];

	//��ȡ�۲�ʱ�����̬����
	dataset = file.openDataSet(AttituteData1);
	filespace = dataset.getSpace();
	rank = filespace.getSimpleExtentNdims();
	rank = filespace.getSimpleExtentDims(dims);
	DataSpace mspace2(2, dims);
	dataset.read(Hdf.AttituteData, PredType::NATIVE_DOUBLE, mspace2, filespace);



	//��ȡ�������
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
	
	cout << "���꣺" << "(" << row << "," << col << ")" << endl;
	cout << "Latitude:"<<std::setprecision(20) << hdf5.get_Latitude() << endl;
	cout << "Longitude:"<<std::setprecision(20) << hdf5.get_Longitude() << endl;
	cout << "TBData:"<<std::setprecision(20) << hdf5.get_TBData() << endl;
	cout << "LandSeaMask:" << std::setprecision(20) << hdf5.get_LandSeaMask() << endl;
	cout << "AttituteData-RLR:"<<std::setprecision(20) << hdf5.get_AttituteData() << endl;
	cout << "GPSData[0]:" << std::setprecision(20) << hdf5.Hdf.GPSData[0][0] << endl;
	system("pause");
	return 0;
}
