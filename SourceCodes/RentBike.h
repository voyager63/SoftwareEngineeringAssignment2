#pragma once
#include "EntityObjects.h"
#include "RentBikeUI.h"

class RentBikeUI;

//자전거 대여 기능을 구현하기 위한 Control Class
class RentBike {
private:
	//RentBike Boundary object를 생성하고, Boundary object의 StartInterface()를 호출하기 위한 변수
	RentBikeUI* rent_bike_ui_;

	//BikeCollection Entity Class의 함수를 호출하기 위한 변수
	BikeCollection* bike_collection_;

	//AccessManager Entity Class의 함수를 호출하기 위한 변수
	AccessManager* access_manager_;

public:

	//생성자
	RentBike(ifstream* input_stream, ofstream* output_stream, BikeCollection* bike_collection, AccessManager* access_manager);

	//Boundary object로부터 받은 입력을 Entity object에게 전달하고, Boundary object에게 반환값을 반환함.
	BikeInput AddNewBike(string bike_id);
};