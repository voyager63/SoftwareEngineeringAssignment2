#include "SharedBikeRentalSystem.h"

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



//회원 가입 기능을 구현하기 위한 Class의 구현부
SignUp::SignUp(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection) {
	//UserCollection Entity object의 함수를 호출하기 위한 변수를 초기화함.
	user_collection_ = user_collection;

	//SignUpUI Boundary object를 생성함.
	sign_up_ui_ = new SignUpUI(input_stream, output_stream, this);

	//Boundary object의 StartInterface() 함수를 호출함.
	sign_up_ui_->StartInterface();
}

SignUpUI::SignUpUI(ifstream* input_stream, ofstream* output_stream, SignUp* sign_up) {
	//파일로부터 입력받기 위해 사용될 변수를 초기화함.
	input_stream_ = input_stream;

	//파일에 출력하기 위해 사용될 변수를 초기화함.
	output_stream_ = output_stream;

	//SignUp Control object의 함수를 호출하기 위한 변수를 초기화함.
	sign_up_ = sign_up;
}


void SignUpUI::StartInterface()
{
	//회원 가입에 필요한 필수 입력 정보를 입력받음.
	UserInput user_input;
	user_input.user_type = 'M';
	*input_stream_ >> user_input.id >> user_input.password >> user_input.phone_number;

	//입력받은 값을 내부로 전달하기 위해 함수를 호출함.
	CreateNewUser(user_input);
}

void SignUpUI::CreateNewUser(UserInput user_input)
{
	//Control object의 함수를 호출하고, Control object로부터 반환받은 값을 출력함.
	UserInput registered_user = sign_up_->AddNewUser(user_input);
	*output_stream_ << "1.1. 회원가입" << endl << "> " << registered_user.id << ' ' << registered_user.password << ' ' << registered_user.phone_number << endl << endl;
}

UserInput SignUp::AddNewUser(UserInput user_input) {
	//함수를 호출함으로써 Entity object에게 값을 전달함.
	user_collection_->AddNewUser(user_input);

	//Boundary object에게 값을 반환함.
	return user_input;
}



//로그인 기능을 구현하기 위한 Class의 구현부
LoginUI::LoginUI(ifstream* input_stream, ofstream* output_stream, Login* login) {
	//파일로부터 입력받기 위해 사용될 변수를 초기화함.
	input_stream_ = input_stream;

	//파일에 출력하기 위해 사용될 변수를 초기화함.
	output_stream_ = output_stream;

	//Login Control object의 함수를 호출하기 위한 변수를 초기화함.
	login_ = login;
}

Login::Login(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection, AccessManager* access_manager) {
	//UserCollection Entity object의 함수를 호출하기 위한 변수를 초기화함.
	user_collection_ = user_collection;

	//AccessManager Entity object의 함수를 호출하기 위한 변수를 초기화함.
	access_manager_ = access_manager;

	//LoginUI Boundary object를 생성함.
	login_ui_ = new LoginUI(input_stream, output_stream, this);

	//Boundary object의 StartInterface() 함수를 호출함.
	login_ui_->StartInterface();
}

void LoginUI::StartInterface() {
	//로그인에 필요한 입력값을 입력받음.
	string user_id, user_password;
	*input_stream_ >> user_id >> user_password;

	//입력받은 값을 내부로 전달하기 위해 함수를 호출함.
	ClickLogin(user_id, user_password);
}

void LoginUI::ClickLogin(string user_id, string user_password) {
	//로그인에 성공했다면 로그인된 이용자의 ID를 출력함.
	if (login_->IsValid(user_id, user_password)) {
		*output_stream_ << "2.1. 로그인" << endl << "> " << user_id << ' ' << user_password << endl << endl;
	}
}

bool Login::IsValid(string input_id, string input_password) {
	//입력받은 ID를 가진 이용자를 받음.
	User* user = user_collection_->GetUserById(input_id);

	//입력받은 ID를 가진 이용자의 비밀번호를 받음.
	string user_password = user->GetPassword();

	//입력한 비밀번호와 저장된 비밀번호가 일치하면 로그인시킴.
	if (IsEqual(input_password, user_password)) {
		//함수를 호출함으로써 Entity object에게 값을 전달함.
		access_manager_->Connect(user);

		//로그인에 성공했다는 것을 Boundary object에게 전달함.
		return true;
	}
	return false;
}

//입력받은 비밀번호와 이용자의 저장된 비밀번호를 비교하여, 같으면 true, 그렇지 않으면 false를 반환함.
bool Login::IsEqual(string input_password, string user_password) {
	if (input_password == user_password) return true;
	else return false;
}



//로그아웃 기능을 구현하기 위한 Class의 구현부
LogoutUI::LogoutUI(ifstream* input_stream, ofstream* output_stream, Logout* logout) {
	//파일로부터 입력받기 위해 사용될 변수를 초기화함.
	input_stream_ = input_stream;

	//파일에 출력하기 위해 사용될 변수를 초기화함.
	output_stream_ = output_stream;

	//Logout Control object의 함수를 호출하기 위한 변수를 초기화함.
	logout_ = logout;
}

Logout::Logout(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager) {
	//AccessManager Entity object의 함수를 호출하기 위한 변수를 초기화함.
	access_manager_ = access_manager;

	//LogoutUI Boundary object를 생성함.
	logout_ui_ = new LogoutUI(input_stream, output_stream, this);

	//Boundary object의 StartInterface() 함수를 호출함.
	logout_ui_->StartInterface();
}


void LogoutUI::StartInterface() {
	//입력받은 값을 내부로 전달하기 위해 함수를 호출함.
	ClickLogout();
}

void LogoutUI::ClickLogout() {
	//Control object의 함수를 호출하고, Control object로부터 반환받은 로그아웃된 이용자의 ID를 출력함.
	string current_user_id = logout_->ExitSystemAccess();
	*output_stream_ << "2.2. 로그아웃" << endl << "> " << current_user_id << endl << endl;
}
string Logout::ExitSystemAccess() {
	//AccessManager Entity Class로부터 현재 로그인된 이용자를 받음.
	User* current_user = access_manager_->GetCurrentUser();

	//현재 로그인된 이용자의 ID를 받음.
	string current_user_id = current_user->GetId();

	//현재 로그인된 이용자를 로그아웃시킴.
	access_manager_->Disconnect();

	//로그아웃된 이용자의 ID를 반환함.
	return current_user_id;
}



//자전거 등록 기능을 구현하기 위한 Class의 구현부
RegisterBikeUI::RegisterBikeUI(ifstream* input_stream, ofstream* output_stream, RegisterBike* register_bike) {
	//파일로부터 입력받기 위해 사용될 변수를 초기화함.
	input_stream_ = input_stream;

	//파일에 출력하기 위해 사용될 변수를 초기화함.
	output_stream_ = output_stream;

	//RegisterBike Control object의 함수를 호출하기 위한 변수를 초기화함.
	register_bike_ = register_bike;
}

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

void RegisterBikeUI::StartInterface() {
	//자전거 등록에 필요한 입력값을 입력받음.
	BikeInput bike_input;
	*input_stream_ >> bike_input.bike_id >> bike_input.bike_product_name;

	//입력받은 값을 내부로 전달하기 위해 함수를 호출함.
	RegisterNewBike(bike_input);
}

void RegisterBikeUI::RegisterNewBike(BikeInput bike_input) {
	//Control object의 함수를 호출하고, Control object로부터 반환받은 값을 출력함.
	BikeInput registered_bike = register_bike_->CreateNewBike(bike_input);
	*output_stream_ << "3.1. 자전거 등록" << endl << "> " << registered_bike.bike_id << ' ' << registered_bike.bike_product_name << endl << endl;
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



//자전거 대여 기능을 구현하기 위한 Class의 구현부
RentBikeUI::RentBikeUI(ifstream* input_stream, ofstream* output_stream, RentBike* rent_bike) {
	//파일로부터 입력받기 위해 사용될 변수를 초기화함.
	input_stream_ = input_stream;

	//파일에 출력하기 위해 사용될 변수를 초기화함.
	output_stream_ = output_stream;

	//RentBike Control object의 함수를 호출하기 위한 변수를 초기화함.
	rent_bike_ = rent_bike;
}

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


void RentBikeUI::StartInterface() {
	//자전거 대여에 필요한 입력값을 입력받음.
	string bike_id;
	*input_stream_ >> bike_id;

	//입력받은 값을 내부로 전달하기 위해 함수를 호출함.
	HireBike(bike_id);
}

void RentBikeUI::HireBike(string bike_id) {
	//Control object의 함수를 호출하고, Control object로부터 반환받은 값을 출력함.
	BikeInput rented_bike = rent_bike_->AddNewBike(bike_id);
	*output_stream_ << "4.1. 자전거 대여" << endl << "> " << rented_bike.bike_id << ' ' << rented_bike.bike_product_name << endl << endl;
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



//대여 중인 자전거 정보 조회 기능을 구현하기 위한 Class의 구현부
CheckBikeRentalInformationUI::CheckBikeRentalInformationUI(ifstream* input_stream, ofstream* output_stream, CheckBikeRentalInformation* check_bike_rental_information) {
	//파일로부터 입력받기 위해 사용될 변수를 초기화함.
	input_stream_ = input_stream;

	//파일에 출력하기 위해 사용될 변수를 초기화함.
	output_stream_ = output_stream;

	//CheckBikeRentalInformation Control object의 함수를 호출하기 위한 변수를 초기화함.
	check_bike_rental_information_ = check_bike_rental_information;
}

CheckBikeRentalInformation::CheckBikeRentalInformation(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager){
	//AccessManager Entity object의 함수를 호출하기 위한 변수를 초기화함.
	access_manager_ = access_manager;

	//CheckBikeRentalInformationUI object를 생성함.
	check_bike_rental_information_ui_ = new CheckBikeRentalInformationUI(input_stream, output_stream, this);

	//Boundary object의 StartInterface() 함수를 호출함.
	check_bike_rental_information_ui_->StartInterface();
}


void CheckBikeRentalInformationUI::StartInterface() {
	//입력받은 값을 내부로 전달하기 위해 함수를 호출함.
	ViewBikeRentalInformation();
}

void CheckBikeRentalInformationUI::ViewBikeRentalInformation() {
	//Control object의 함수를 호출하고, Control object로부터 반환받은 값을 출력함.
	pair<BikeInput*, int> rented_bike_details_list = check_bike_rental_information_->ShowBikeRentalInformation();
	*output_stream_ << "5.1. 자전거 대여 리스트" << endl;
	for (int i = 0; i < rented_bike_details_list.second; i++) {
		*output_stream_ << "> " << rented_bike_details_list.first[i].bike_id << ' ' << rented_bike_details_list.first[i].bike_product_name << endl;
	}
	*output_stream_ << endl;
	delete[] rented_bike_details_list.first;
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



//종료 기능을 구현하기 위한 Class의 구현부
ExitUI::ExitUI(ifstream* input_stream, ofstream* output_stream, Exit* exit) {
	//파일로부터 입력받기 위해 사용될 변수를 초기화함.
	input_stream_ = input_stream;

	//파일에 출력하기 위해 사용될 변수를 초기화함.
	output_stream_ = output_stream;

	//Exit Control object의 함수를 호출하기 위한 변수를 초기화함.
	exit_ = exit;
}

Exit::Exit(ifstream* input_stream, ofstream* output_stream, int* is_program_exit) {
	//종료를 위한 변수의 값을 바꾸기 위한 변수를 초기화함.
	is_program_exit_ = is_program_exit;

	//ExitUI Boundary object를 생성함.
	exit_ui_ = new ExitUI(input_stream, output_stream, this);

	//Boundary object의 StartInterface() 함수를 호출함.
	exit_ui_->StartInterface();
}


void ExitUI::StartInterface() {
	//입력받은 값을 내부로 전달하기 위해 함수를 호출함.
	ExitSystem();
}

void ExitUI::ExitSystem() {
	//Control object의 함수를 호출함.
	exit_->ExitSystem();

	//시스템이 종료되었음을 화면에 출력함.
	*output_stream_ << "6.1. 종료";
}

void Exit::ExitSystem() {
	//종료를 위한 변수의 값을 1로 바꿈.
	*is_program_exit_ = 1;
}


