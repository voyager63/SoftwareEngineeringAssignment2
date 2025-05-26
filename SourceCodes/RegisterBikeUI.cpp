#include "RegisterBikeUI.h"

RegisterBikeUI::RegisterBikeUI(ifstream* input_stream, ofstream* output_stream, RegisterBike* register_bike) {
	//파일로부터 입력받기 위해 사용될 변수를 초기화함.
	input_stream_ = input_stream;

	//파일에 출력하기 위해 사용될 변수를 초기화함.
	output_stream_ = output_stream;

	//RegisterBike Control object의 함수를 호출하기 위한 변수를 초기화함.
	register_bike_ = register_bike;
}

void RegisterBikeUI::StartInterface() {
	//자전거 등록에 필요한 입력값을 입력받음.
	BikeInput bike_input;
	*input_stream_ >> bike_input.bike_id >> bike_input.bike_product_name;

	//입력받은 값을 내부로 전달하기 위해 함수를 호출함.
	RegisterNewBike(bike_input);
}

void RegisterBikeUI::RegisterNewBike(BikeInput bike_input) {
	//Control object의 함수를 호출하고, Control object로부터 반환받은 값을 출력함.
	BikeInput registered_bike = register_bike_->CreateNewBike(bike_input);
	*output_stream_ << "3.1. 자전거 등록" << endl << "> " << registered_bike.bike_id << ' ' << registered_bike.bike_product_name << endl << endl;
}