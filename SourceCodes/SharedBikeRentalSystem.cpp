#include "SharedBikeRentalSystem.h"

//entity

//User
User::User(string id, string password, string phone_number, char user_type) {
	id_ = id;
	password_ = password;
	phone_number_ = phone_number;
	user_type_ = user_type;
	owned_rented_bike_collection_ = new RentedBikeCollection();
}

string User::GetId() {
	return id_;
}

string User::GetPassword() {
	return password_;
}

RentedBikeCollection* User::GetUserBikes() {
	return owned_rented_bike_collection_;
}

bool User::IsAdmin() {
	if (user_type_ = 'A') return true;
	else return false;
}

bool User::IsMember() {
	if (user_type_ = 'M') return true;
	else return false;
}



//UserCollection
UserCollection::UserCollection(string admin_id, string admin_password) {
	num_users_ = 0;
	user_list_[num_users_++] = new User(admin_id, admin_password, "", 'A');
}

void UserCollection::AddNewUser(UserInput user_input) {
	user_list_[num_users_++] = new User(user_input.id, user_input.password, user_input.phone_number, user_input.user_type);
}

User* UserCollection::GetUserById(string id) {
	for (int i = 0; i < num_users_; i++) {
		if (user_list_[i]->GetId() == id) return user_list_[i];
	}
}



//Bike
Bike::Bike(string bike_id, string bike_product_name) {
	bike_id_ = bike_id;
	bike_product_name_ = bike_product_name;
}

BikeInput Bike::GetBikeDetails() {
	BikeInput bike_input;
	bike_input.bike_id = bike_id_;
	bike_input.bike_product_name = bike_product_name_;
	return bike_input;
}



//BikeCollection
BikeCollection::BikeCollection() {
	num_bikes_ = 0;
}

void BikeCollection::AddNewBike(BikeInput bike_input) {
	bike_list_[num_bikes_++] = new Bike(bike_input.bike_id, bike_input.bike_product_name);
}

Bike* BikeCollection::GetBikeById(string bike_id) {
	for (int i = 0; i < num_bikes_; i++) {
		if (bike_list_[i]->GetBikeDetails().bike_id == bike_id) return bike_list_[i];
	}
}



//RentedBikeCollection
RentedBikeCollection::RentedBikeCollection() {
	num_rented_bikes_ = 0;
}

void RentedBikeCollection::AddNewBike(Bike* bike) {
	owned_rented_bike_[num_rented_bikes_++] = bike;
}

int RentedBikeCollection::GetNumRentedBikes() {
	return num_rented_bikes_;
}

Bike** RentedBikeCollection::GetRentedBikes() {
	return owned_rented_bike_;
}

void RentedBikeCollection::SortBikeById() {
	for (int i = 0; i < num_rented_bikes_ - 1; i++) {
		int min = i;
		for (int j = i + 1; j < num_rented_bikes_; j++) {
			if (owned_rented_bike_[min]->GetBikeDetails().bike_id > owned_rented_bike_[j]->GetBikeDetails().bike_id) {
				min = j;
			}
		}
		Bike* temp = owned_rented_bike_[i];
		owned_rented_bike_[i] = owned_rented_bike_[min];
		owned_rented_bike_[min] = temp;
	}
}



//AccessManager
AccessManager::AccessManager() {
	current_user_ = NULL;
}

void AccessManager::Connect(User* user) {
	current_user_ = user;
}

void AccessManager::Disconnect() {
	current_user_ = NULL;
}

User* AccessManager::GetCurrentUser() {
	return current_user_;
}



//boundary and control

//Sign up

SignUp::SignUp(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection) { //SignUp 객체를 만들며 SignUpUI 생성. 그후 SignUpUI의 interface 호출.
	user_collection_ = user_collection;
	sign_up_ui_ = new SignUpUI(input_stream, output_stream,this);
	sign_up_ui_->StartInterface();
}

SignUpUI::SignUpUI(ifstream* input_stream, ofstream* output_stream, SignUp* sign_up) {
	input_stream_ = input_stream;
	output_stream_ = output_stream;
	sign_up_ = sign_up;
}


void SignUpUI::StartInterface() //사용자로 부터 입력을 받음.
{
	UserInput user_input;
	user_input.user_type = 'M';
	*input_stream_ >> user_input.id >> user_input.password >> user_input.phone_number;
	CreateNewUser(user_input);
}

void SignUpUI::CreateNewUser(UserInput user_input)
{
	UserInput registered_user = sign_up_->AddNewUser(user_input); //control을 호출하고, control로 부터 값을 받아옴.
	*output_stream_ << "1.1. 회원가입" << endl << "> " << registered_user.id << ' ' << registered_user.password << ' ' << registered_user.phone_number << endl << endl;
	// control로부터 받아온 결과를 출력.
}

UserInput SignUp::AddNewUser(UserInput user_input) {
	user_collection_->AddNewUser(user_input);
	return user_input; // boundary에게 값을 넘겨줌.
}



//Login

Login::Login(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection, AccessManager* access_manager) {
	user_collection_ = user_collection;
	access_manager_ = access_manager;
	login_ui_ = new LoginUI(input_stream, output_stream, this);
	login_ui_->StartInterface();
}


bool Login::IsValid(string input_id, string input_password) {
	User* user = user_collection_->GetUserById(input_id);
	string user_password = user->GetPassword();
	if (IsEqual(input_password, user_password)) {
		access_manager_->Connect(user);
		return true;
	}
	return false;
}

bool Login::IsEqual(string input_password, string user_password) {
	if (input_password == user_password) return true;
	else return false;
}

LoginUI::LoginUI(ifstream* input_stream, ofstream* output_stream, Login* login) {
	input_stream_ = input_stream;
	output_stream_ = output_stream;
	login_ = login;
}

void LoginUI::StartInterface() {
	string user_id, user_password;
	*input_stream_ >> user_id >> user_password;
	ClickLogin(user_id, user_password);
}

void LoginUI::ClickLogin(string user_id, string user_password) {
	if (login_->IsValid(user_id, user_password)) {
		*output_stream_ << "2.1. 로그인" << endl << "> " << user_id << ' ' << user_password << endl << endl;
	}
}

//Logout

Logout::Logout(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager) {
	access_manager_ = access_manager;
	logout_ui_ = new LogoutUI(input_stream, output_stream, this);
	logout_ui_->StartInterface();
}

LogoutUI::LogoutUI(ifstream* input_stream, ofstream* output_stream, Logout* logout) {
	input_stream_ = input_stream;
	output_stream_ = output_stream;
	logout_ = logout;
}

void LogoutUI::StartInterface() {
	ClickLogout();
}

void LogoutUI::ClickLogout() {
	string current_user_id = logout_->ExitSystemAccess();
	*output_stream_ << "2.2. 로그아웃" << endl << "> " << current_user_id << endl << endl;
}
string Logout::ExitSystemAccess() {
	User* current_user = access_manager_->GetCurrentUser();
	string current_user_id = current_user->GetId();
	access_manager_->Disconnect();
	return current_user_id;
}

//Register a new bike

RegisterBike::RegisterBike(ifstream* input_stream, ofstream* output_stream, BikeCollection* bike_collection, AccessManager* access_manager) {
	bike_collection_ = bike_collection;
	access_manager_ = access_manager;
	register_bike_ui_ = new RegisterBikeUI(input_stream, output_stream, this);
	register_bike_ui_->StartInterface();
}

RegisterBikeUI::RegisterBikeUI(ifstream* input_stream, ofstream* output_stream, RegisterBike* register_bike) {
	input_stream_ = input_stream;
	output_stream_ = output_stream;
	register_bike_ = register_bike;
}

void RegisterBikeUI::StartInterface() {
	BikeInput bike_input;
	*input_stream_ >> bike_input.bike_id >> bike_input.bike_product_name;
	RegisterNewBike(bike_input);
}

void RegisterBikeUI::RegisterNewBike(BikeInput bike_input) {
	BikeInput registered_bike = register_bike_->CreateNewBike(bike_input);
	*output_stream_ << "3.1. 자전거 등록" << endl << "> " << registered_bike.bike_id << ' ' << registered_bike.bike_product_name << endl << endl;
}

BikeInput RegisterBike::CreateNewBike(BikeInput bike_input) {
	User* current_user = access_manager_->GetCurrentUser();
	if (current_user->IsAdmin()) {
		bike_collection_->AddNewBike(bike_input);
		return bike_input;
	}
}

//Rent a bike

RentBike::RentBike(ifstream* input_stream, ofstream* output_stream, BikeCollection* bike_collection, AccessManager* access_manager) {
	bike_collection_ = bike_collection;
	access_manager_ = access_manager;
	rent_bike_ui_ = new RentBikeUI(input_stream, output_stream, this);
	rent_bike_ui_->StartInterface();
}

RentBikeUI::RentBikeUI(ifstream* input_stream, ofstream* output_stream, RentBike* rent_bike) {
	input_stream_ = input_stream;
	output_stream_ = output_stream;
	rent_bike_ = rent_bike;
}

void RentBikeUI::StartInterface() {
	string bike_id;
	*input_stream_ >> bike_id;
	HireBike(bike_id);
}

void RentBikeUI::HireBike(string bike_id) {
	BikeInput rented_bike = rent_bike_->AddNewBike(bike_id);
	*output_stream_ << "4.1. 자전거 대여" << endl << "> " << rented_bike.bike_id << ' ' << rented_bike.bike_product_name << endl << endl;
}

BikeInput RentBike::AddNewBike(string bike_id) {
	User* current_user = access_manager_->GetCurrentUser();
	if (current_user->IsMember()) {
		Bike* selected_bike = bike_collection_->GetBikeById(bike_id);
		current_user->GetUserBikes()->AddNewBike(selected_bike);
		return selected_bike->GetBikeDetails();
	}
}

//Check bike rental information

CheckBikeRentalInformation::CheckBikeRentalInformation(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager){
	access_manager_ = access_manager;
	check_bike_rental_information_ui_ = new CheckBikeRentalInformationUI(input_stream, output_stream, this);
	check_bike_rental_information_ui_->StartInterface();
}

CheckBikeRentalInformationUI::CheckBikeRentalInformationUI(ifstream* input_stream, ofstream* output_stream, CheckBikeRentalInformation* check_bike_rental_information) {
	input_stream_ = input_stream;
	output_stream_ = output_stream;
	check_bike_rental_information_ = check_bike_rental_information;
}

void CheckBikeRentalInformationUI::StartInterface() {
	ViewBikeRentalInformation();
}

void CheckBikeRentalInformationUI::ViewBikeRentalInformation() {
	pair<BikeInput*, int> rented_bike_details = check_bike_rental_information_->ShowBikeRentalInformation();
	*output_stream_ << "5.1. 자전거 대여 리스트" << endl;
	for (int i = 0; i < rented_bike_details.second; i++) {
		*output_stream_ << "> " << rented_bike_details.first[i].bike_id << ' ' << rented_bike_details.first[i].bike_product_name << endl;
	}
	*output_stream_ << endl;
	delete[] rented_bike_details.first;
}

pair<BikeInput*, int> CheckBikeRentalInformation::ShowBikeRentalInformation() {
	User* current_user = access_manager_->GetCurrentUser();
	if (current_user->IsMember()) {
		current_user->GetUserBikes()->SortBikeById(); // 대여한 자전거를 ID순으로 정렬함.
		RentedBikeCollection* rented_bikes = current_user->GetUserBikes();
		int num_rented_bike = rented_bikes->GetNumRentedBikes();
		BikeInput* rented_bike_details = new BikeInput[num_rented_bike];
		for (int i = 0; i < num_rented_bike; i++) {
			BikeInput rented_bike = rented_bikes->GetRentedBikes()[i]->GetBikeDetails();
			rented_bike_details[i] = rented_bike;
		}
		return pair<BikeInput*, int>(rented_bike_details, num_rented_bike);
	}
}


Exit::Exit(ifstream* input_stream, ofstream* output_stream, int* is_program_exit) {
	is_program_exit_ = is_program_exit;
	exit_ui_ = new ExitUI(input_stream, output_stream, this);
	exit_ui_->StartInterface();
}

ExitUI::ExitUI(ifstream* input_stream, ofstream* output_stream, Exit* exit) {
	input_stream_ = input_stream;
	output_stream_ = output_stream;
	exit_ = exit;
}

void ExitUI::StartInterface() {
	ExitSystem();
}

void ExitUI::ExitSystem() {
	exit_->ExitSystem();
	*output_stream_ << "6.1. 종료";
}

void Exit::ExitSystem() {
	*is_program_exit_ = 1;
}


