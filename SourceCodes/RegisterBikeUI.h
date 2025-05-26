#pragma once
#include "EntityObjects.h"
#include "RegisterBike.h"

class RegisterBike;

//자전거 등록 기능을 구현하기 위한 Boundary Class
class RegisterBikeUI {
private:
	//RegisterBike Control object의 함수를 호출하기 위한 변수
	RegisterBike* register_bike_;

	//파일로부터 입력을 받기 위한 변수
	ifstream* input_stream_;

	//Control object로부터 반환받은 값을 파일에 출력하기 위한 변수
	ofstream* output_stream_;

public:
	//생성자
	RegisterBikeUI(ifstream* input_stream, ofstream* output_stream, RegisterBike* register_bike);

	//관리자로부터 입력을 받음.
	void StartInterface();

	//관리자의 입력을 Control object에게 전달함.
	void RegisterNewBike(BikeInput bike_input);
};