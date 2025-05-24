#include "SharedBikeRentalSystem.h"
#include <fstream>

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

SignUp::SignUp(ifstream* if_stream, ofstream* of_stream, UserCollection* user_collection) { //SignUp 객체를 만들며 SignUpUI 생성. 그후 SignUpUI의 interface 호출.
	user_collection_ = user_collection;
	sign_up_ui_ = new SignUpUI(if_stream, of_stream ,this);
	sign_up_ui_->StartInterface();
}

SignUpUI::SignUpUI(ifstream* if_stream, ofstream* of_stream, SignUp* sign_up) {
	if_stream_ = if_stream;
	of_stream_ = of_stream;
	sign_up_ = sign_up;
}


void SignUpUI::StartInterface() //사용자로 부터 입력을 받음.
{
	UserInput user_input;
	user_input.user_type = 'M';
	*if_stream_ >> user_input.id >> user_input.password >> user_input.phone_number;
	CreateNewUser(user_input);
}

void SignUpUI::CreateNewUser(UserInput user_input)
{
	UserInput registered_user = sign_up_->AddNewUser(user_input); //control을 호출하고, control로 부터 값을 받아옴.
	*of_stream_ << "1.1. 회원가입" << endl << "> " << registered_user.id << ' ' << registered_user.password << ' ' << registered_user.phone_number << endl;
	// control로부터 받아온 결과를 출력.
}

UserInput SignUp::AddNewUser(UserInput user_input) {
	user_collection_->AddNewUser(user_input);
	return user_input; // boundary에게 값을 넘겨줌.
}



//Login

Login::Login(ifstream* if_stream, ofstream* of_stream, UserCollection* user_collection, AccessManager* access_manager) {
	user_collection_ = user_collection;
	access_manager_ = access_manager;
	login_ui_ = new LoginUI(if_stream, of_stream, this);
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

LoginUI::LoginUI(ifstream* if_stream, ofstream* of_stream, Login* login) {
	if_stream_ = if_stream;
	of_stream_ = of_stream;
	login_ = login;
}

void LoginUI::StartInterface() {
	string user_id, user_password;
	*if_stream_ >> user_id >> user_password;
	ClickLogin(user_id, user_password);
}

void LoginUI::ClickLogin(string user_id, string user_password) {
	if (login_->IsValid(user_id, user_password)) {
		*of_stream_ << "2.1. 로그인" << endl << "> " << user_id << ' ' << user_password << endl;
	}
}

//Logout

Logout::Logout(ifstream* if_stream, ofstream* of_stream, AccessManager* access_manager) {
	access_manager_ = access_manager;
	logout_ui_ = new LogoutUI(if_stream, of_stream, this);
	logout_ui_->StartInterface();
}

LogoutUI::LogoutUI(ifstream* if_stream, ofstream* of_stream, Logout* logout) {
	if_stream_ = if_stream;
	of_stream_ = of_stream;
	logout_ = logout;
}

void LogoutUI::StartInterface() {
	ClickLogout();
}

void LogoutUI::ClickLogout() {
	string current_user_id = logout_->ExitSystemAccess();
	*of_stream_ << "2.2. 로그아웃" << endl << "> " << current_user_id << endl;
}
string Logout::ExitSystemAccess() {
	User* current_user = access_manager_->GetCurrentUser();
	string current_user_id = current_user->GetId();
	access_manager_->Disconnect();
	return current_user_id;
}

//Register a new bike

RegisterBike::RegisterBike(ifstream* if_stream, ofstream* of_stream, BikeCollection* bike_collection, AccessManager* access_manager) {
	bike_collection_ = bike_collection;
	access_manager_ = access_manager;
	register_bike_ui_ = new RegisterBikeUI(if_stream, of_stream, this);
	register_bike_ui_->StartInterface();
}

RegisterBikeUI::RegisterBikeUI(ifstream* if_stream, ofstream* of_stream, RegisterBike* register_bike) {
	if_stream_ = if_stream;
	of_stream_ = of_stream;
	register_bike_ = register_bike;
}

void RegisterBikeUI::StartInterface() {
	BikeInput bike_input;
	*if_stream_ >> bike_input.bike_id >> bike_input.bike_product_name;
	RegisterNewBike(bike_input);
}

void RegisterBikeUI::RegisterNewBike(BikeInput bike_input) {
	BikeInput registered_bike = register_bike_->CreateNewBike(bike_input);
	*of_stream_ << "3.1. 자전거 등록" << endl << "> " << registered_bike.bike_id << ' ' << registered_bike.bike_product_name << endl;
}

BikeInput RegisterBike::CreateNewBike(BikeInput bike_input) {
	User* current_user = access_manager_->GetCurrentUser();
	if (current_user->IsAdmin()) {
		bike_collection_->AddNewBike(bike_input);
		return bike_input;
	}
}

//Rent a bike

RentBike::RentBike(ifstream* if_stream, ofstream* of_stream, BikeCollection* bike_collection, AccessManager* access_manager) {
	bike_collection_ = bike_collection;
	access_manager_ = access_manager;
	rent_bike_ui_ = new RentBikeUI(if_stream, of_stream, this);
	rent_bike_ui_->StartInterface();
}

RentBikeUI::RentBikeUI(ifstream* if_stream, ofstream* of_stream, RentBike* rent_bike) {
	if_stream_ = if_stream;
	of_stream_ = of_stream;
	rent_bike_ = rent_bike;
}

void RentBikeUI::StartInterface() {
	string bike_id;
	*if_stream_ >> bike_id;
	HireBike(bike_id);
}

void RentBikeUI::HireBike(string bike_id) {
	BikeInput rented_bike = rent_bike_->AddNewBike(bike_id);
	*of_stream_ << "4.1. 자전거 대여" << endl << "> " << rented_bike.bike_id << ' ' << rented_bike.bike_product_name << endl;
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

CheckBikeRentalInformation::CheckBikeRentalInformation(ifstream* if_stream, ofstream* of_stream, AccessManager* access_manager){
	of_stream_ = of_stream;
	access_manager_ = access_manager;
	check_bike_rental_information_ui_ = new CheckBikeRentalInformationUI(if_stream, of_stream, this);
	check_bike_rental_information_ui_->StartInterface();
}

CheckBikeRentalInformationUI::CheckBikeRentalInformationUI(ifstream* if_stream, ofstream* of_stream, CheckBikeRentalInformation* check_bike_rental_information) {
	if_stream_ = if_stream;
	of_stream_ = of_stream;
	check_bike_rental_information_ = check_bike_rental_information;
}

void CheckBikeRentalInformationUI::StartInterface() {
	ViewBikeRentalInformation();
}

void CheckBikeRentalInformationUI::ViewBikeRentalInformation() {
	check_bike_rental_information_->ShowBikeRentalInformation();
}

void CheckBikeRentalInformation::ShowBikeRentalInformation() {
	User* current_user = access_manager_->GetCurrentUser();
	if (current_user->IsMember()) {
		*of_stream_ << "5.1. 자전거 대여 리스트" << endl;
		RentedBikeCollection* rented_bikes = current_user->GetUserBikes();
		for (int i = 0; i < rented_bikes->GetNumRentedBikes(); i++) {
			BikeInput rented_bike = rented_bikes->GetRentedBikes()[i]->GetBikeDetails();
			*of_stream_ << "> " << rented_bike.bike_id << ' ' << rented_bike.bike_product_name << endl;
		}
	}
}
