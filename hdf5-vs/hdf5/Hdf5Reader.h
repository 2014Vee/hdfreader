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
	Hdf5Reader(std::string filename, const int row, const int col);
	~Hdf5Reader();
	float get_Latitude();
	float get_Longitude();
	float get_TBData();
	float get_SensorAzimuth();
	float get_SensorZenith();
	//������Ҫע��һ�£�LandSeaMask��unsigned int�Ͳ������ݱ�Ŀ��д��unsigned char
	unsigned int get_LandSeaMask();
	double get_AttituteData();

};
/*
��ȡhdf5�е���������Ϣ��
����get_Latitude()��������ޣ����Ϊ��Ӧ����γ�ȣ�
����get_Longitude()��������ޣ����Ϊ��Ӧ���꾭�ȣ�
����get_TBData()��������ޣ����Ϊ��Ӧ����������ȣ�
����get_SensorAzimuth()��������ޣ����Ϊ���Ƿ�λ�ǣ�
����get_SensorZenith()��������ޣ����Ϊ�����춥�ǣ�
����get_LandSeaMask()��������ޣ����Ϊ��·�߽���Ϣ��
����get_AttituteData()��������ޣ����Ϊ�۲���ʱ�����̬���ݣ�����Ĭ�������һ�е�ʱ�䡣

Ҳ����ͨ������Hdf5Reader���е�Hdf5Data�ṹ��������ݻ�ȡ��
*/


#endif