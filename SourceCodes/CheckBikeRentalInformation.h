#pragma once
#include "EntityObjects.h"
#include "CheckBikeRentalInformationUI.h"

class CheckBikeRentalInformationUI;

//�뿩 ���� ������ ��ȸ ����� �����ϱ� ���� Control Class
class CheckBikeRentalInformation {
private:
	//CheckBikeRentalInformation Boundary object�� �����ϰ�, Boundary object�� StartInterface()�� ȣ���ϱ� ���� ����
	CheckBikeRentalInformationUI* check_bike_rental_information_ui_;

	//AccessManager Entity Class�� �Լ��� ȣ���ϱ� ���� ����
	AccessManager* access_manager_;

public:
	//������
	CheckBikeRentalInformation(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager);

	//Entity object�κ��� ���� ���, Boundary object���� ��ȯ���� ��ȯ��.
	pair<BikeInput*, int> ShowBikeRentalInformation();
};
