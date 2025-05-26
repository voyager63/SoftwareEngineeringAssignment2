#pragma once
#include "EntityObjects.h"
#include "CheckBikeRentalInformationUI.h"

class CheckBikeRentalInformationUI;

//대여 중인 자전거 조회 기능을 구현하기 위한 Control Class
class CheckBikeRentalInformation {
private:
	//CheckBikeRentalInformation Boundary object를 생성하고, Boundary object의 StartInterface()를 호출하기 위한 변수
	CheckBikeRentalInformationUI* check_bike_rental_information_ui_;

	//AccessManager Entity Class의 함수를 호출하기 위한 변수
	AccessManager* access_manager_;

public:
	//생성자
	CheckBikeRentalInformation(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager);

	//Entity object로부터 값을 얻고, Boundary object에게 반환값을 반환함.
	pair<BikeInput*, int> ShowBikeRentalInformation();
};
