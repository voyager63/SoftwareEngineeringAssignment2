#include "CheckBikeRentalInformation.h"

CheckBikeRentalInformation::CheckBikeRentalInformation(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager) {
	//AccessManager Entity object의 함수를 호출하기 위한 변수를 초기화함.
	access_manager_ = access_manager;

	//CheckBikeRentalInformationUI object를 생성함.
	check_bike_rental_information_ui_ = new CheckBikeRentalInformationUI(input_stream, output_stream, this);

	//Boundary object의 StartInterface() 함수를 호출함.
	check_bike_rental_information_ui_->StartInterface();
}

pair<BikeInput*, int> CheckBikeRentalInformation::ShowBikeRentalInformation() {
	//AccessManager Entity Class로부터 현재 로그인된 이용자를 받음.
	User* current_user = access_manager_->GetCurrentUser();

	//현재 로그인된 이용자가 회원이라면 대여 중인 자전거 정보를 조회함.
	if (current_user->IsMember()) {
		//현재 로그인된 이용자의 대여한 자전거 컬렉션을 받음.
		RentedBikeCollection* user_rented_bike_collection = current_user->GetUserBikes();

		//현재 로그인된 이용자의 대여한 자전거들을 정렬함.
		user_rented_bike_collection->SortBikeById();

		//현재 로그인된 이용자의 대여한 자전거의 수를 받음.
		int num_rented_bike = user_rented_bike_collection->GetNumRentedBikes();

		//현재 로그인된 이용자의 대여한 자전거들을 받음.
		Bike** user_rented_bikes = user_rented_bike_collection->GetRentedBikes();

		//Boundary object에게 반환할 값을 저장할 배열을 생성함.
		BikeInput* rented_bike_details_list = new BikeInput[num_rented_bike];

		//현재 로그인된 이용자의 대여한 자전거들의 자전거 ID, 자전거 제품명을 배열에 저장함.
		for (int i = 0; i < num_rented_bike; i++) {
			BikeInput rented_bike_details = user_rented_bikes[i]->GetBikeDetails();
			rented_bike_details_list[i] = rented_bike_details;
		}

		//배열과 자전거의 수를 Boundary object에게 반환함.
		return pair<BikeInput*, int>(rented_bike_details_list, num_rented_bike);
	}
}