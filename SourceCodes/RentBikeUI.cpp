#include "RentBikeUI.h"

RentBikeUI::RentBikeUI(ifstream* input_stream, ofstream* output_stream, RentBike* rent_bike) {
	//���Ϸκ��� �Է¹ޱ� ���� ���� ������ �ʱ�ȭ��.
	input_stream_ = input_stream;

	//���Ͽ� ����ϱ� ���� ���� ������ �ʱ�ȭ��.
	output_stream_ = output_stream;

	//RentBike Control object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	rent_bike_ = rent_bike;
}

void RentBikeUI::StartInterface() {
	//������ �뿩�� �ʿ��� �Է°��� �Է¹���.
	string bike_id;
	*input_stream_ >> bike_id;

	//�Է¹��� ���� ���η� �����ϱ� ���� �Լ��� ȣ����.
	HireBike(bike_id);
}

void RentBikeUI::HireBike(string bike_id) {
	//Control object�� �Լ��� ȣ���ϰ�, Control object�κ��� ��ȯ���� ���� �����.
	BikeInput rented_bike = rent_bike_->AddNewBike(bike_id);
	*output_stream_ << "4.1. ������ �뿩" << endl << "> " << rented_bike.bike_id << ' ' << rented_bike.bike_product_name << endl << endl;
}