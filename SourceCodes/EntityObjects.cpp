#include "EntityObjects.h"

//이용자의 생성자. 이용자의 ID, 비밀번호, 전화번호, 유형, 대여한 자전거 컬렉션을 초기화함.
User::User(string id, string password, string phone_number, char user_type) {
	id_ = id;
	password_ = password;
	phone_number_ = phone_number;
	user_type_ = user_type;
	owned_rented_bike_collection_ = new RentedBikeCollection();
}

//이용자의 ID를 반환함.
string User::GetId() {
	return id_;
}

//이용자의 비밀번호를 반환함.
string User::GetPassword() {
	return password_;
}

//이용자의 대여한 자전거 컬렉션을 반환함.
RentedBikeCollection* User::GetUserBikes() {
	return owned_rented_bike_collection_;
}

//이용자가 관리자라면 true를 반환, 아니라면 false를 반환함.
bool User::IsAdmin() {
	if (user_type_ = 'A') return true;
	else return false;
}

//이용자가 회원이라면 true를 반환, 아니라면 false를 반환함.
bool User::IsMember() {
	if (user_type_ = 'M') return true;
	else return false;
}


//이용자 컬렉션의 생성자. 현재 시스템에 등록된 이용자의 수를 초기화함.
UserCollection::UserCollection(string admin_id, string admin_password) {
	num_users_ = 0;

	//생성될 때 관리자를 생성함.
	user_list_[num_users_++] = new User(admin_id, admin_password, "", 'A');
}


//이용자 ID, 비밀번호, 전화번호, 이용자 유형을 입력받아 이용자를 생성함.
void UserCollection::AddNewUser(UserInput user_input) {
	user_list_[num_users_++] = new User(user_input.id, user_input.password, user_input.phone_number, user_input.user_type);
}


//입력받은 ID와 같은 ID를 가진 이용자를 반환함.
User* UserCollection::GetUserById(string id) {
	for (int i = 0; i < num_users_; i++) {
		if (user_list_[i]->GetId() == id) return user_list_[i];
	}
}



//자전거의 생성자. 자전거의 ID, 제품명을 초기화함.
Bike::Bike(string bike_id, string bike_product_name) {
	bike_id_ = bike_id;
	bike_product_name_ = bike_product_name;
}

//자전거의 ID, 제품명을 반환함.
BikeInput Bike::GetBikeDetails() {
	BikeInput bike_input;
	bike_input.bike_id = bike_id_;
	bike_input.bike_product_name = bike_product_name_;
	return bike_input;
}

//자전거 컬렉션의 생성자. 현재 시스템에 등록된 자전거의 수를 초기화함.
BikeCollection::BikeCollection() {
	num_bikes_ = 0;
}


//자전거 ID, 제품명을 입력받아 자전거를 생성함.
void BikeCollection::AddNewBike(BikeInput bike_input) {
	bike_list_[num_bikes_++] = new Bike(bike_input.bike_id, bike_input.bike_product_name);
}


//입력한 자전거 ID와 같은 ID를 가진 자전거를 반환함.
Bike* BikeCollection::GetBikeById(string bike_id) {
	for (int i = 0; i < num_bikes_; i++) {
		if (bike_list_[i]->GetBikeDetails().bike_id == bike_id) return bike_list_[i];
	}
}



//이용자의 대여한 자전거 컬렉션의 생성자. 대여한 자전거의 수를 초기화함.
RentedBikeCollection::RentedBikeCollection() {
	num_rented_bikes_ = 0;
}

//자전거를 입력받아 대여한 자전거 배열에 추가함.
void RentedBikeCollection::AddNewBike(Bike* bike) {
	owned_rented_bike_[num_rented_bikes_++] = bike;
}


//이용자의 대여한 자전거의 수를 반환함.
int RentedBikeCollection::GetNumRentedBikes() {
	return num_rented_bikes_;
}

//이용자의 대여한 자전거들을 반환함.
Bike** RentedBikeCollection::GetRentedBikes() {
	return owned_rented_bike_;
}


//대여한 자전거들을 선택 정렬을 통해 자전거 ID의 오름차순으로 정렬함.
void RentedBikeCollection::SortBikeById() {
	for (int i = 0; i < num_rented_bikes_ - 1; i++) {

		//가장 작은 자전거 ID를 가진 자전거의 인덱스
		int min = i;

		//가장 작은 자전거 ID를 가진 자전거의 인덱스를 찾음.
		for (int j = i + 1; j < num_rented_bikes_; j++) {
			if (owned_rented_bike_[min]->GetBikeDetails().bike_id > owned_rented_bike_[j]->GetBikeDetails().bike_id) {
				min = j;
			}
		}

		//가장 작은 자전거 ID를 가진 자전거와 i 번째 자전거의 위치를 서로 바꿈.
		Bike* temp = owned_rented_bike_[i];
		owned_rented_bike_[i] = owned_rented_bike_[min];
		owned_rented_bike_[min] = temp;
	}
}


//로그인, 로그아웃 기능과 현재 로그인된 이용자를 표시해주는 Class의 생성자.
AccessManager::AccessManager() {
	current_user_ = NULL;
}

//현재 로그인된 이용자를 가리키는 변수에 입력받은 이용자를 저장함으로써 입력받은 이용자를 로그인시킴.
void AccessManager::Connect(User* user) {
	current_user_ = user;
}

//현재 로그인된 이용자를 가리키는 변수의 값을 NULL로 바꿈으로써 현재 로그인된 이용자를 로그아웃시킴.
void AccessManager::Disconnect() {
	current_user_ = NULL;
}

//현재 로그인된 이용자를 반환함.
User* AccessManager::GetCurrentUser() {
	return current_user_;
}