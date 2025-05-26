#pragma once
#include "EntityObjects.h"
#include "CheckBikeRentalInformation.h"

class CheckBikeRentalInformation;

//�뿩 ���� ������ ��ȸ ����� �����ϱ� ���� Boundary Class
class CheckBikeRentalInformationUI {
private:
	//CheckBikeRentalInformation Control object�� �Լ��� ȣ���ϱ� ���� ����
	CheckBikeRentalInformation* check_bike_rental_information_;

	//���Ϸκ��� �Է��� �ޱ� ���� ����
	ifstream* input_stream_;

	//Control object�κ��� ��ȯ���� ���� ���Ͽ� ����ϱ� ���� ����
	ofstream* output_stream_;

public:
	//������
	CheckBikeRentalInformationUI(ifstream* input_stream, ofstream* output_stream, CheckBikeRentalInformation* check_bike_rental_information);

	//ȸ�����κ��� �Է��� ����.
	void StartInterface();

	//ȸ���� �Է��� Control object���� ������.
	void ViewBikeRentalInformation();
};