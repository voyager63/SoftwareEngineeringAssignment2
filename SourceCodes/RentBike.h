#pragma once
#include "EntityObjects.h"
#include "RentBikeUI.h"

class RentBikeUI;

//������ �뿩 ����� �����ϱ� ���� Control Class
class RentBike {
private:
	//RentBike Boundary object�� �����ϰ�, Boundary object�� StartInterface()�� ȣ���ϱ� ���� ����
	RentBikeUI* rent_bike_ui_;

	//BikeCollection Entity Class�� �Լ��� ȣ���ϱ� ���� ����
	BikeCollection* bike_collection_;

	//AccessManager Entity Class�� �Լ��� ȣ���ϱ� ���� ����
	AccessManager* access_manager_;

public:

	//������
	RentBike(ifstream* input_stream, ofstream* output_stream, BikeCollection* bike_collection, AccessManager* access_manager);

	//Boundary object�κ��� ���� �Է��� Entity object���� �����ϰ�, Boundary object���� ��ȯ���� ��ȯ��.
	BikeInput AddNewBike(string bike_id);
};