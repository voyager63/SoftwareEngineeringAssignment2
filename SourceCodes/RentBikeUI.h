#pragma once
#include "EntityObjects.h"
#include "RentBike.h"

class RentBike;

//������ �뿩 ����� �����ϱ� ���� Boundary Class
class RentBikeUI {
private:
	//RentBike Control object�� �Լ��� ȣ���ϱ� ���� ����
	RentBike* rent_bike_;

	//���Ϸκ��� �Է��� �ޱ� ���� ����
	ifstream* input_stream_;

	//Control object�κ��� ��ȯ���� ���� ���Ͽ� ����ϱ� ���� ����
	ofstream* output_stream_;

public:
	//������
	RentBikeUI(ifstream* input_stream, ofstream* output_stream, RentBike* rent_bike);

	//ȸ�����κ��� �Է��� ����.
	void StartInterface();

	//ȸ���� �Է��� Control object���� ������.
	void HireBike(string bike_id);
};