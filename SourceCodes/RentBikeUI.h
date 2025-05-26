#pragma once
#include "EntityObjects.h"
#include "RentBike.h"

class RentBike;

//자전거 대여 기능을 구현하기 위한 Boundary Class
class RentBikeUI {
private:
	//RentBike Control object의 함수를 호출하기 위한 변수
	RentBike* rent_bike_;

	//파일로부터 입력을 받기 위한 변수
	ifstream* input_stream_;

	//Control object로부터 반환받은 값을 파일에 출력하기 위한 변수
	ofstream* output_stream_;

public:
	//생성자
	RentBikeUI(ifstream* input_stream, ofstream* output_stream, RentBike* rent_bike);

	//회원으로부터 입력을 받음.
	void StartInterface();

	//회원의 입력을 Control object에게 전달함.
	void HireBike(string bike_id);
};