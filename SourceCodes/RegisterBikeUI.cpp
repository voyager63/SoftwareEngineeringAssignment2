#include "RegisterBikeUI.h"

RegisterBikeUI::RegisterBikeUI(ifstream* input_stream, ofstream* output_stream, RegisterBike* register_bike) {
	//���Ϸκ��� �Է¹ޱ� ���� ���� ������ �ʱ�ȭ��.
	input_stream_ = input_stream;

	//���Ͽ� ����ϱ� ���� ���� ������ �ʱ�ȭ��.
	output_stream_ = output_stream;

	//RegisterBike Control object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	register_bike_ = register_bike;
}

void RegisterBikeUI::StartInterface() {
	//������ ��Ͽ� �ʿ��� �Է°��� �Է¹���.
	BikeInput bike_input;
	*input_stream_ >> bike_input.bike_id >> bike_input.bike_product_name;

	//�Է¹��� ���� ���η� �����ϱ� ���� �Լ��� ȣ����.
	RegisterNewBike(bike_input);
}

void RegisterBikeUI::RegisterNewBike(BikeInput bike_input) {
	//Control object�� �Լ��� ȣ���ϰ�, Control object�κ��� ��ȯ���� ���� �����.
	BikeInput registered_bike = register_bike_->CreateNewBike(bike_input);
	*output_stream_ << "3.1. ������ ���" << endl << "> " << registered_bike.bike_id << ' ' << registered_bike.bike_product_name << endl << endl;
}