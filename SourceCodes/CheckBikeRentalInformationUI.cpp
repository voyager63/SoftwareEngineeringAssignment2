#include "CheckBikeRentalInformationUI.h"

CheckBikeRentalInformationUI::CheckBikeRentalInformationUI(ifstream* input_stream, ofstream* output_stream, CheckBikeRentalInformation* check_bike_rental_information) {
	//���Ϸκ��� �Է¹ޱ� ���� ���� ������ �ʱ�ȭ��.
	input_stream_ = input_stream;

	//���Ͽ� ����ϱ� ���� ���� ������ �ʱ�ȭ��.
	output_stream_ = output_stream;

	//CheckBikeRentalInformation Control object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	check_bike_rental_information_ = check_bike_rental_information;
}

void CheckBikeRentalInformationUI::StartInterface() {
	//�Է¹��� ���� ���η� �����ϱ� ���� �Լ��� ȣ����.
	ViewBikeRentalInformation();
}

void CheckBikeRentalInformationUI::ViewBikeRentalInformation() {
	//Control object�� �Լ��� ȣ���ϰ�, Control object�κ��� ��ȯ���� ���� �����.
	pair<BikeInput*, int> rented_bike_details_list = check_bike_rental_information_->ShowBikeRentalInformation();
	*output_stream_ << "5.1. ������ �뿩 ����Ʈ" << endl;
	for (int i = 0; i < rented_bike_details_list.second; i++) {
		*output_stream_ << "> " << rented_bike_details_list.first[i].bike_id << ' ' << rented_bike_details_list.first[i].bike_product_name << endl;
	}
	*output_stream_ << endl;
	delete[] rented_bike_details_list.first;
}