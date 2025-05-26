#pragma once
#include "EntityObjects.h"
#include "RegisterBikeUI.h"

class RegisterBikeUI;

//������ ��� ����� �����ϱ� ���� Control Class
class RegisterBike {
private:
	//RegisterBike Boundary object�� �����ϰ�, Boundary object�� StartInterface()�� ȣ���ϱ� ���� ����
	RegisterBikeUI* register_bike_ui_;

	//BikeCollection Entity Class�� �Լ��� ȣ���ϱ� ���� ����
	BikeCollection* bike_collection_;

	//AccessManager Entity Class�� �Լ��� ȣ���ϱ� ���� ����
	AccessManager* access_manager_;

public:
	//������
	RegisterBike(ifstream* input_stream, ofstream* output_stream, BikeCollection* bike_collection, AccessManager* access_manager);

	//Boundary object�κ��� ���� �Է��� Entity object���� �����ϰ�, Boundary object���� ��ȯ���� ��ȯ��.
	BikeInput CreateNewBike(BikeInput bike_input);
};
