#pragma once
#include "EntityObjects.h"
#include "RegisterBike.h"

class RegisterBike;

//������ ��� ����� �����ϱ� ���� Boundary Class
class RegisterBikeUI {
private:
	//RegisterBike Control object�� �Լ��� ȣ���ϱ� ���� ����
	RegisterBike* register_bike_;

	//���Ϸκ��� �Է��� �ޱ� ���� ����
	ifstream* input_stream_;

	//Control object�κ��� ��ȯ���� ���� ���Ͽ� ����ϱ� ���� ����
	ofstream* output_stream_;

public:
	//������
	RegisterBikeUI(ifstream* input_stream, ofstream* output_stream, RegisterBike* register_bike);

	//�����ڷκ��� �Է��� ����.
	void StartInterface();

	//�������� �Է��� Control object���� ������.
	void RegisterNewBike(BikeInput bike_input);
};