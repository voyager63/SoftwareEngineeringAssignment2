#include "CheckBikeRentalInformationUI.h"

CheckBikeRentalInformationUI::CheckBikeRentalInformationUI(ifstream* input_stream, ofstream* output_stream, CheckBikeRentalInformation* check_bike_rental_information) {
	//파일로부터 입력받기 위해 사용될 변수를 초기화함.
	input_stream_ = input_stream;

	//파일에 출력하기 위해 사용될 변수를 초기화함.
	output_stream_ = output_stream;

	//CheckBikeRentalInformation Control object의 함수를 호출하기 위한 변수를 초기화함.
	check_bike_rental_information_ = check_bike_rental_information;
}

void CheckBikeRentalInformationUI::StartInterface() {
	//입력받은 값을 내부로 전달하기 위해 함수를 호출함.
	ViewBikeRentalInformation();
}

void CheckBikeRentalInformationUI::ViewBikeRentalInformation() {
	//Control object의 함수를 호출하고, Control object로부터 반환받은 값을 출력함.
	pair<BikeInput*, int> rented_bike_details_list = check_bike_rental_information_->ShowBikeRentalInformation();
	*output_stream_ << "5.1. 자전거 대여 리스트" << endl;
	for (int i = 0; i < rented_bike_details_list.second; i++) {
		*output_stream_ << "> " << rented_bike_details_list.first[i].bike_id << ' ' << rented_bike_details_list.first[i].bike_product_name << endl;
	}
	*output_stream_ << endl;
	delete[] rented_bike_details_list.first;
}