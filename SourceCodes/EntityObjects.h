#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

class User;
class UserCollection;
class Bike;
class BikeCollection;
class RentedBikeCollection;
class AccessManager;

//이용자의 정보를 입력하거나 반환하기 위한 구조체
struct UserInput {
	string id;
	string password;
	string phone_number;
	char user_type;
};

//자전거의 정보를 입력하거나 반환하기 위한 구조체
struct BikeInput {
	string bike_id;
	string bike_product_name;
};


//이용자를 표현하는 Entity Class
class User {
private:
	//이용자의 ID
	string id_;

	//이용자의 비밀번호
	string password_;

	//이용자의 전화번호
	string phone_number_;

	//이용자의 유형. 회원 또는 관리자임.
	char user_type_;

	//회원이 대여한 자전거의 배열
	RentedBikeCollection* owned_rented_bike_collection_;

public:
	//생성자
	User(string id, string password, string phone_number, char user_type);

	//이용자의 ID를 반환함.
	string GetId();

	//이용자의 비밀번호를 반환함.
	string GetPassword();

	//이용자의 자신이 대여한 자전거 목록을 반환함.
	RentedBikeCollection* GetUserBikes();

	//이용자의 유형이 '회원'이면 true를 반환함. 그렇지 않으면 false를 반환함.
	bool IsAdmin();

	//이용자의 유형이 '관리자'이면 true를 반환함. 그렇지 않으면 false를 반환함.
	bool IsMember();
};


//현재 시스템에 등록된 이용자 컬렉션을 표현하는 Entity Class
class UserCollection {
private:
	//현재 시스템에 등록된 이용자의 배열
	User* user_list_[50];

	//현재 시스템에 등록된 이용자의 수
	int num_users_;

public:
	//생성자. 생성됨과 동시에 관리자를 생성함.
	UserCollection(string admin_id, string admin_password);

	//시스템에 이용자를 등록함.
	void AddNewUser(UserInput user_input);

	//이용자의 ID를 이용하여 해당 ID를 가진 이용자를 반환함.
	User* GetUserById(string id);
};


//자전거를 표현하는 Entity Class
class Bike {
private:
	//자전거의 ID
	string bike_id_;

	//자전거의 자전거 제품명
	string bike_product_name_;

public:
	//생성자
	Bike(string bike_id, string bike_product_name);

	//자전거의 자전거 ID, 자전거 제품명을 반환함.
	BikeInput GetBikeDetails();
};


//현재 시스템에 등록된 자전거 컬렉션을 표현하는 Entity Class
class BikeCollection {
private:
	//현재 시스템에 등록된 자전거의 배열
	Bike* bike_list_[50];

	//현재 시스템에 등록된 자전거의 수
	int num_bikes_;

public:
	//생성자
	BikeCollection();

	//시스템에 자전거를 등록함.
	void AddNewBike(BikeInput bike_input);

	//자전거의 ID를 이용하여 해당 ID를 가진 자전거를 반환함.
	Bike* GetBikeById(string bike_id);
};


//회원이 대여한 자전거 컬렉션을 표현하는 Entity Class
class RentedBikeCollection {
private:
	//회원이 현재 대여한 자전거의 배열
	Bike* owned_rented_bike_[50];

	//회원이 현재 대여한 자전거의 수
	int num_rented_bikes_;

public:
	//생성자
	RentedBikeCollection();

	//자전거를 입력받아 그것을 회원이 현재 대여한 자전거의 배열에 추가함.
	void AddNewBike(Bike* bike);

	//회원이 현재 대여한 자전거의 수를 반환함.
	int GetNumRentedBikes();

	//회원이 현재 대여한 자전거의 배열을 반환함.
	Bike** GetRentedBikes();

	//회원이 현재 대여한 자전거들을 자전거 ID의 오름차순으로 정렬함.
	void SortBikeById();
};


//이용자의 로그인, 로그아웃과 현재 로그인된 이용자를 표현하기 위한 Entity Class
class AccessManager {
private:
	//현재 시스템에 로그인한 이용자
	User* current_user_;

public:
	//생성자
	AccessManager();

	//입력받은 이용자가 로그인되게 함.
	void Connect(User* user);

	//이용자가 로그아웃되게 함.
	void Disconnect();

	//현재 시스템에 로그인한 이용자를 반환함.
	User* GetCurrentUser();
};