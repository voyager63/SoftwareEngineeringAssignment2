#include "RentBike.h"

RentBike::RentBike(ifstream* input_stream, ofstream* output_stream, BikeCollection* bike_collection, AccessManager* access_manager) {
	//BikeCollection Entity object의 함수를 호출하기 위한 변수를 초기화함.
	bike_collection_ = bike_collection;

	//AccessManager Entity object의 함수를 호출하기 위한 변수를 초기화함.
	access_manager_ = access_manager;

	//RentBikeUI Boundary object를 생성함.
	rent_bike_ui_ = new RentBikeUI(input_stream, output_stream, this);

	//Boundary object의 StartInterface() 함수를 호출함.
	rent_bike_ui_->StartInterface();
}

BikeInput RentBike::AddNewBike(string bike_id) {
	//AccessManager Entity Class로부터 현재 로그인된 이용자를 받음.
	User* current_user = access_manager_->GetCurrentUser();

	//현재 로그인된 이용자가 회원이라면 자전거를 대여함.
	if (current_user->IsMember()) {
		//입력한 자전거 ID를 가진 자전거를 받음.
		Bike* selected_bike = bike_collection_->GetBikeById(bike_id);

		//그 자전거를 현재 로그인된 이용자의 대여한 자전거 컬렉션에 추가함.
		RentedBikeCollection* user_rented_bike_collection = current_user->GetUserBikes();
		user_rented_bike_collection->AddNewBike(selected_bike);

		//대여한 자전거의 자전거 ID, 자전거 제품명을 Boundary object에게 반환함.
		return selected_bike->GetBikeDetails();
	}
}