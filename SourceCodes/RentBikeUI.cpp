#include "RentBikeUI.h"

RentBikeUI::RentBikeUI(ifstream* input_stream, ofstream* output_stream, RentBike* rent_bike) {
	//파일로부터 입력받기 위해 사용될 변수를 초기화함.
	input_stream_ = input_stream;

	//파일에 출력하기 위해 사용될 변수를 초기화함.
	output_stream_ = output_stream;

	//RentBike Control object의 함수를 호출하기 위한 변수를 초기화함.
	rent_bike_ = rent_bike;
}

void RentBikeUI::StartInterface() {
	//자전거 대여에 필요한 입력값을 입력받음.
	string bike_id;
	*input_stream_ >> bike_id;

	//입력받은 값을 내부로 전달하기 위해 함수를 호출함.
	HireBike(bike_id);
}

void RentBikeUI::HireBike(string bike_id) {
	//Control object의 함수를 호출하고, Control object로부터 반환받은 값을 출력함.
	BikeInput rented_bike = rent_bike_->AddNewBike(bike_id);
	*output_stream_ << "4.1. 자전거 대여" << endl << "> " << rented_bike.bike_id << ' ' << rented_bike.bike_product_name << endl << endl;
}