#pragma once
#include "EntityObjects.h"
#include "CheckBikeRentalInformation.h"

class CheckBikeRentalInformation;

//대여 중인 자전거 조회 기능을 구현하기 위한 Boundary Class
class CheckBikeRentalInformationUI {
private:
	//CheckBikeRentalInformation Control object의 함수를 호출하기 위한 변수
	CheckBikeRentalInformation* check_bike_rental_information_;

	//파일로부터 입력을 받기 위한 변수
	ifstream* input_stream_;

	//Control object로부터 반환받은 값을 파일에 출력하기 위한 변수
	ofstream* output_stream_;

public:
	//생성자
	CheckBikeRentalInformationUI(ifstream* input_stream, ofstream* output_stream, CheckBikeRentalInformation* check_bike_rental_information);

	//회원으로부터 입력을 받음.
	void StartInterface();

	//회원의 입력을 Control object에게 전달함.
	void ViewBikeRentalInformation();
};