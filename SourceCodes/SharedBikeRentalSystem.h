#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

//전방 선언
class User;
class UserCollection;
class Bike;
class BikeCollection;
class RentedBikeCollection;
class AccessManager;
class SignUpUI;
class SignUp;
class LoginUI;
class Login;
class LogoutUI;
class Logout;
class RegisterBikeUI;
class RegisterBike;
class RentBikeUI;
class RentBike;
class CheckBikeRentalInformationUI;
class CheckBikeRentalInformation;
class ExitUI;
class Exit;


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


//이용자 목록을 표현하는 Entity Class
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


//등록된 자전거 목록을 표현하는 Entity Class
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


//회원이 대여한 자전거 목록을 표현하는 Entity Class
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


//회원가입 기능을 구현하기 위한 Boundary Class
class SignUpUI {
private:
	//SignUp Control object의 함수를 호출하기 위한 변수
	SignUp* sign_up_;

	//파일로부터 입력을 받기 위한 변수
	ifstream* input_stream_;

	//Control object로부터 반환받은 값을 파일에 출력하기 위한 변수
	ofstream* output_stream_;

public:
	//생성자
	SignUpUI(ifstream* input_stream, ofstream* output_stream, SignUp* sign_up);

	//사용자로부터 입력을 받음.
	void StartInterface();

	//사용자의 입력을 Control object에게 전달함.
	void CreateNewUser(UserInput user_input);
};


//회원가입 기능을 구현하기 위한 Control Class
class SignUp {
private:
	//SignUpUI Boundary object를 생성하고, Boundary object의 StartInterface()를 호출하기 위한 변수
	SignUpUI* sign_up_ui_;

	//UserCollection Entity Class의 함수를 호출하기 위한 변수
	UserCollection* user_collection_;

public:
	//생성자
	SignUp(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection);

	//Boundary object로부터 받은 값을 Entity object에게 전달함.
	UserInput AddNewUser(UserInput user_input);
};


//로그인 기능을 구현하기 위한 Boundary Class 
class LoginUI{
private:
	//Login Control object의 함수를 호출하기 위한 변수
	Login* login_;

	//파일로부터 입력을 받기 위한 변수
	ifstream* input_stream_;

	//Control object로부터 반환받은 값을 파일에 출력하기 위한 변수
	ofstream* output_stream_;

public:
	//생성자
	LoginUI(ifstream* input_stream, ofstream* output_stream, Login* login);

	//이용자로부터 입력을 받음.
	void StartInterface();

	//이용자의 입력을 Control object에게 전달함.
	void ClickLogin(string user_id, string user_password);
};

//로그인 기능을 구현하기 위한 Control Class
class Login {
private:
	//LoginUI Boundary object를 생성하고, Boundary object의 StartInterface()를 호출하기 위한 변수
	LoginUI* login_ui_;

	//UserCollection Entity Class의 함수를 호출하기 위한 변수
	UserCollection* user_collection_;

	//AccessManager Entity Class의 함수를 호출하기 위한 변수
	AccessManager* access_manager_;

public:
	//생성자
	Login(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection, AccessManager* access_manager);

	//이용자의 ID, 비밀번호를 입력받아 로그인이 성공했는지를 반환함.
	bool IsValid(string input_id, string input_password);

	//이용자가 입력한 비밀번호와 저장된 비밀번호가 일치하는지를 반환함.
	bool IsEqual(string input_password, string user_password);
};


//로그아웃 기능을 구현하기 위한 Boundary Class
class LogoutUI {
private:
	//Logout Control object의 함수를 호출하기 위한 변수
	Logout* logout_;

	//파일로부터 입력을 받기 위한 변수
	ifstream* input_stream_;

	//Control object로부터 반환받은 값을 파일에 출력하기 위한 변수
	ofstream* output_stream_;

public:
	//생성자
	LogoutUI(ifstream* input_stream, ofstream* output_stream, Logout* logout);

	//이용자로부터 입력을 받음.
	void StartInterface();

	//이용자의 입력을 Control object에게 전달함.
	void ClickLogout();
};


//로그아웃 기능을 구현하기 위한 Control Class
class Logout {
private:
	//LogoutUI Boundary object를 생성하고, Boundary object의 StartInterface()를 호출하기 위한 변수
	LogoutUI* logout_ui_;

	//AccessManager Entity Class의 함수를 호출하기 위한 변수
	AccessManager* access_manager_;

public:
	//생성자
	Logout(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager);

	//Entity object의 함수를 호출하여 로그아웃시킴.
	string ExitSystemAccess();
};


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


//대여 중인 자전거 정보 조회 기능을 구현하기 위한 Boundary Class
class CheckBikeRentalInformationUI {
private:
	//CheckBikeRentalInformation Control object의 함수를 호출하기 위한 변수
	CheckBikeRentalInformation* check_bike_rental_information_;

	//파일로부터 입력을 받기 위한 변수
	ifstream* input_stream_;

	//Control object로부터 반환받은 값을 파일에 출력하기 위한 변수
	ofstream* output_stream_;

public:
	//생성자
	CheckBikeRentalInformationUI(ifstream* input_stream, ofstream* output_stream, CheckBikeRentalInformation* check_bike_rental_information);

	//회원으로부터 입력을 받음.
	void StartInterface();

	//회원의 입력을 Control object에게 전달함.
	void ViewBikeRentalInformation();
};


//대여 중인 자전거 정보 조회 기능을 구현하기 위한 Control Class
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


//종료 기능을 구현하기 위한 Boundary Class
class ExitUI {
private:
	//Exit Control object의 함수를 호출하기 위한 변수
	Exit* exit_;

	//파일로부터 입력을 받기 위한 변수
	ifstream* input_stream_;

	//Control object로부터 반환받은 값을 파일에 출력하기 위한 변수
	ofstream* output_stream_;

public:
	//생성자
	ExitUI(ifstream* input_stream, ofstream* output_stream, Exit* exit);

	//사용자, 이용자로부터 입력을 받음.
	void StartInterface();

	//사용자, 이용자의 입력을 Control object에게 전달함.
	void ExitSystem();
};


//종료 기능을 구현하기 위한 Control Class
class Exit {
private:
	//ExitUI Boundary object를 생성하고, Boundary object의 StartInterface()를 호출하기 위한 변수
	ExitUI* exit_ui_;

	//종료를 위한 변수의 값을 바꾸기 위한 변수
	int* is_program_exit_;

public:
	//생성자
	Exit(ifstream* input_stream, ofstream* output_stream, int* is_program_exit);

	//종료를 위한 변수의 값을 1로 바꿈.
	void ExitSystem();
};