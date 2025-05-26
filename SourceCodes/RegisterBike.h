#pragma once
#include "EntityObjects.h"
#include "RegisterBikeUI.h"

class RegisterBikeUI;

//자전거 등록 기능을 구현하기 위한 Control Class
class RegisterBike {
private:
	//RegisterBike Boundary object를 생성하고, Boundary object의 StartInterface()를 호출하기 위한 변수
	RegisterBikeUI* register_bike_ui_;

	//BikeCollection Entity Class의 함수를 호출하기 위한 변수
	BikeCollection* bike_collection_;

	//AccessManager Entity Class의 함수를 호출하기 위한 변수
	AccessManager* access_manager_;

public:
	//생성자
	RegisterBike(ifstream* input_stream, ofstream* output_stream, BikeCollection* bike_collection, AccessManager* access_manager);

	//Boundary object로부터 받은 입력을 Entity object에게 전달하고, Boundary object에게 반환값을 반환함.
	BikeInput CreateNewBike(BikeInput bike_input);
};
