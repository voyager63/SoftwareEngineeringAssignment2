#include "RegisterBike.h"

RegisterBike::RegisterBike(ifstream* input_stream, ofstream* output_stream, BikeCollection* bike_collection, AccessManager* access_manager) {
	//BikeCollection Entity object의 함수를 호출하기 위한 변수를 초기화함.
	bike_collection_ = bike_collection;

	//AccessManager Entity object의 함수를 호출하기 위한 변수를 초기화함.
	access_manager_ = access_manager;

	//RegisterBikeUI Boundary object를 생성함.
	register_bike_ui_ = new RegisterBikeUI(input_stream, output_stream, this);

	//Boundary object의 StartInterface() 함수를 호출함.
	register_bike_ui_->StartInterface();
}

BikeInput RegisterBike::CreateNewBike(BikeInput bike_input) {
	//AccessManager Entity Class로부터 현재 로그인된 이용자를 받음. 
	User* current_user = access_manager_->GetCurrentUser();

	//현재 로그인된 이용자가 관리자라면 자전거를 등록함.
	if (current_user->IsAdmin()) {
		//함수를 호출함으로써 Entity object에게 값을 전달함.
		bike_collection_->AddNewBike(bike_input);

		//Boundary object에게 값을 반환함.
		return bike_input;
	}
}