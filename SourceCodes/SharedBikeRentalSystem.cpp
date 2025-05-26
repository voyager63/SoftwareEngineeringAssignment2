#include "SharedBikeRentalSystem.h"

//�̿����� ������. �̿����� ID, ��й�ȣ, ��ȭ��ȣ, ����, �뿩�� ������ �÷����� �ʱ�ȭ��.
User::User(string id, string password, string phone_number, char user_type) {
	id_ = id;
	password_ = password;
	phone_number_ = phone_number;
	user_type_ = user_type;
	owned_rented_bike_collection_ = new RentedBikeCollection();
}

//�̿����� ID�� ��ȯ��.
string User::GetId() {
	return id_;
}

//�̿����� ��й�ȣ�� ��ȯ��.
string User::GetPassword() {
	return password_;
}

//�̿����� �뿩�� ������ �÷����� ��ȯ��.
RentedBikeCollection* User::GetUserBikes() {
	return owned_rented_bike_collection_;
}

//�̿��ڰ� �����ڶ�� true�� ��ȯ, �ƴ϶�� false�� ��ȯ��.
bool User::IsAdmin() {
	if (user_type_ = 'A') return true;
	else return false;
}

//�̿��ڰ� ȸ���̶�� true�� ��ȯ, �ƴ϶�� false�� ��ȯ��.
bool User::IsMember() {
	if (user_type_ = 'M') return true;
	else return false;
}


//�̿��� �÷����� ������. ���� �ý��ۿ� ��ϵ� �̿����� ���� �ʱ�ȭ��.
UserCollection::UserCollection(string admin_id, string admin_password) {
	num_users_ = 0;

	//������ �� �����ڸ� ������.
	user_list_[num_users_++] = new User(admin_id, admin_password, "", 'A');
}


//�̿��� ID, ��й�ȣ, ��ȭ��ȣ, �̿��� ������ �Է¹޾� �̿��ڸ� ������.
void UserCollection::AddNewUser(UserInput user_input) {
	user_list_[num_users_++] = new User(user_input.id, user_input.password, user_input.phone_number, user_input.user_type);
}


//�Է¹��� ID�� ���� ID�� ���� �̿��ڸ� ��ȯ��.
User* UserCollection::GetUserById(string id) {
	for (int i = 0; i < num_users_; i++) {
		if (user_list_[i]->GetId() == id) return user_list_[i];
	}
}



//�������� ������. �������� ID, ��ǰ���� �ʱ�ȭ��.
Bike::Bike(string bike_id, string bike_product_name) {
	bike_id_ = bike_id;
	bike_product_name_ = bike_product_name;
}

//�������� ID, ��ǰ���� ��ȯ��.
BikeInput Bike::GetBikeDetails() {
	BikeInput bike_input;
	bike_input.bike_id = bike_id_;
	bike_input.bike_product_name = bike_product_name_;
	return bike_input;
}

//������ �÷����� ������. ���� �ý��ۿ� ��ϵ� �������� ���� �ʱ�ȭ��.
BikeCollection::BikeCollection() {
	num_bikes_ = 0;
}


//������ ID, ��ǰ���� �Է¹޾� �����Ÿ� ������.
void BikeCollection::AddNewBike(BikeInput bike_input) {
	bike_list_[num_bikes_++] = new Bike(bike_input.bike_id, bike_input.bike_product_name);
}


//�Է��� ������ ID�� ���� ID�� ���� �����Ÿ� ��ȯ��.
Bike* BikeCollection::GetBikeById(string bike_id) {
	for (int i = 0; i < num_bikes_; i++) {
		if (bike_list_[i]->GetBikeDetails().bike_id == bike_id) return bike_list_[i];
	}
}



//�̿����� �뿩�� ������ �÷����� ������. �뿩�� �������� ���� �ʱ�ȭ��.
RentedBikeCollection::RentedBikeCollection() {
	num_rented_bikes_ = 0;
}

//�����Ÿ� �Է¹޾� �뿩�� ������ �迭�� �߰���.
void RentedBikeCollection::AddNewBike(Bike* bike) {
	owned_rented_bike_[num_rented_bikes_++] = bike;
}


//�̿����� �뿩�� �������� ���� ��ȯ��.
int RentedBikeCollection::GetNumRentedBikes() {
	return num_rented_bikes_;
}

//�̿����� �뿩�� �����ŵ��� ��ȯ��.
Bike** RentedBikeCollection::GetRentedBikes() {
	return owned_rented_bike_;
}


//�뿩�� �����ŵ��� ���� ������ ���� ������ ID�� ������������ ������.
void RentedBikeCollection::SortBikeById() {
	for (int i = 0; i < num_rented_bikes_ - 1; i++) {

		//���� ���� ������ ID�� ���� �������� �ε���
		int min = i;

		//���� ���� ������ ID�� ���� �������� �ε����� ã��.
		for (int j = i + 1; j < num_rented_bikes_; j++) {
			if (owned_rented_bike_[min]->GetBikeDetails().bike_id > owned_rented_bike_[j]->GetBikeDetails().bike_id) {
				min = j;
			}
		}

		//���� ���� ������ ID�� ���� �����ſ� i ��° �������� ��ġ�� ���� �ٲ�.
		Bike* temp = owned_rented_bike_[i];
		owned_rented_bike_[i] = owned_rented_bike_[min];
		owned_rented_bike_[min] = temp;
	}
}


//�α���, �α׾ƿ� ��ɰ� ���� �α��ε� �̿��ڸ� ǥ�����ִ� Class�� ������.
AccessManager::AccessManager() {
	current_user_ = NULL;
}

//���� �α��ε� �̿��ڸ� ����Ű�� ������ �Է¹��� �̿��ڸ� ���������ν� �Է¹��� �̿��ڸ� �α��ν�Ŵ.
void AccessManager::Connect(User* user) {
	current_user_ = user;
}

//���� �α��ε� �̿��ڸ� ����Ű�� ������ ���� NULL�� �ٲ����ν� ���� �α��ε� �̿��ڸ� �α׾ƿ���Ŵ.
void AccessManager::Disconnect() {
	current_user_ = NULL;
}

//���� �α��ε� �̿��ڸ� ��ȯ��.
User* AccessManager::GetCurrentUser() {
	return current_user_;
}



//ȸ�� ���� ����� �����ϱ� ���� Class�� ������
SignUp::SignUp(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection) {
	//UserCollection Entity object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	user_collection_ = user_collection;

	//SignUpUI Boundary object�� ������.
	sign_up_ui_ = new SignUpUI(input_stream, output_stream, this);

	//Boundary object�� StartInterface() �Լ��� ȣ����.
	sign_up_ui_->StartInterface();
}

SignUpUI::SignUpUI(ifstream* input_stream, ofstream* output_stream, SignUp* sign_up) {
	//���Ϸκ��� �Է¹ޱ� ���� ���� ������ �ʱ�ȭ��.
	input_stream_ = input_stream;

	//���Ͽ� ����ϱ� ���� ���� ������ �ʱ�ȭ��.
	output_stream_ = output_stream;

	//SignUp Control object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	sign_up_ = sign_up;
}


void SignUpUI::StartInterface()
{
	//ȸ�� ���Կ� �ʿ��� �ʼ� �Է� ������ �Է¹���.
	UserInput user_input;
	user_input.user_type = 'M';
	*input_stream_ >> user_input.id >> user_input.password >> user_input.phone_number;

	//�Է¹��� ���� ���η� �����ϱ� ���� �Լ��� ȣ����.
	CreateNewUser(user_input);
}

void SignUpUI::CreateNewUser(UserInput user_input)
{
	//Control object�� �Լ��� ȣ���ϰ�, Control object�κ��� ��ȯ���� ���� �����.
	UserInput registered_user = sign_up_->AddNewUser(user_input);
	*output_stream_ << "1.1. ȸ������" << endl << "> " << registered_user.id << ' ' << registered_user.password << ' ' << registered_user.phone_number << endl << endl;
}

UserInput SignUp::AddNewUser(UserInput user_input) {
	//�Լ��� ȣ�������ν� Entity object���� ���� ������.
	user_collection_->AddNewUser(user_input);

	//Boundary object���� ���� ��ȯ��.
	return user_input;
}



//�α��� ����� �����ϱ� ���� Class�� ������
LoginUI::LoginUI(ifstream* input_stream, ofstream* output_stream, Login* login) {
	//���Ϸκ��� �Է¹ޱ� ���� ���� ������ �ʱ�ȭ��.
	input_stream_ = input_stream;

	//���Ͽ� ����ϱ� ���� ���� ������ �ʱ�ȭ��.
	output_stream_ = output_stream;

	//Login Control object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	login_ = login;
}

Login::Login(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection, AccessManager* access_manager) {
	//UserCollection Entity object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	user_collection_ = user_collection;

	//AccessManager Entity object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	access_manager_ = access_manager;

	//LoginUI Boundary object�� ������.
	login_ui_ = new LoginUI(input_stream, output_stream, this);

	//Boundary object�� StartInterface() �Լ��� ȣ����.
	login_ui_->StartInterface();
}

void LoginUI::StartInterface() {
	//�α��ο� �ʿ��� �Է°��� �Է¹���.
	string user_id, user_password;
	*input_stream_ >> user_id >> user_password;

	//�Է¹��� ���� ���η� �����ϱ� ���� �Լ��� ȣ����.
	ClickLogin(user_id, user_password);
}

void LoginUI::ClickLogin(string user_id, string user_password) {
	//�α��ο� �����ߴٸ� �α��ε� �̿����� ID�� �����.
	if (login_->IsValid(user_id, user_password)) {
		*output_stream_ << "2.1. �α���" << endl << "> " << user_id << ' ' << user_password << endl << endl;
	}
}

bool Login::IsValid(string input_id, string input_password) {
	//�Է¹��� ID�� ���� �̿��ڸ� ����.
	User* user = user_collection_->GetUserById(input_id);

	//�Է¹��� ID�� ���� �̿����� ��й�ȣ�� ����.
	string user_password = user->GetPassword();

	//�Է��� ��й�ȣ�� ����� ��й�ȣ�� ��ġ�ϸ� �α��ν�Ŵ.
	if (IsEqual(input_password, user_password)) {
		//�Լ��� ȣ�������ν� Entity object���� ���� ������.
		access_manager_->Connect(user);

		//�α��ο� �����ߴٴ� ���� Boundary object���� ������.
		return true;
	}
	return false;
}

//�Է¹��� ��й�ȣ�� �̿����� ����� ��й�ȣ�� ���Ͽ�, ������ true, �׷��� ������ false�� ��ȯ��.
bool Login::IsEqual(string input_password, string user_password) {
	if (input_password == user_password) return true;
	else return false;
}



//�α׾ƿ� ����� �����ϱ� ���� Class�� ������
LogoutUI::LogoutUI(ifstream* input_stream, ofstream* output_stream, Logout* logout) {
	//���Ϸκ��� �Է¹ޱ� ���� ���� ������ �ʱ�ȭ��.
	input_stream_ = input_stream;

	//���Ͽ� ����ϱ� ���� ���� ������ �ʱ�ȭ��.
	output_stream_ = output_stream;

	//Logout Control object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	logout_ = logout;
}

Logout::Logout(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager) {
	//AccessManager Entity object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	access_manager_ = access_manager;

	//LogoutUI Boundary object�� ������.
	logout_ui_ = new LogoutUI(input_stream, output_stream, this);

	//Boundary object�� StartInterface() �Լ��� ȣ����.
	logout_ui_->StartInterface();
}


void LogoutUI::StartInterface() {
	//�Է¹��� ���� ���η� �����ϱ� ���� �Լ��� ȣ����.
	ClickLogout();
}

void LogoutUI::ClickLogout() {
	//Control object�� �Լ��� ȣ���ϰ�, Control object�κ��� ��ȯ���� �α׾ƿ��� �̿����� ID�� �����.
	string current_user_id = logout_->ExitSystemAccess();
	*output_stream_ << "2.2. �α׾ƿ�" << endl << "> " << current_user_id << endl << endl;
}
string Logout::ExitSystemAccess() {
	//AccessManager Entity Class�κ��� ���� �α��ε� �̿��ڸ� ����.
	User* current_user = access_manager_->GetCurrentUser();

	//���� �α��ε� �̿����� ID�� ����.
	string current_user_id = current_user->GetId();

	//���� �α��ε� �̿��ڸ� �α׾ƿ���Ŵ.
	access_manager_->Disconnect();

	//�α׾ƿ��� �̿����� ID�� ��ȯ��.
	return current_user_id;
}



//������ ��� ����� �����ϱ� ���� Class�� ������
RegisterBikeUI::RegisterBikeUI(ifstream* input_stream, ofstream* output_stream, RegisterBike* register_bike) {
	//���Ϸκ��� �Է¹ޱ� ���� ���� ������ �ʱ�ȭ��.
	input_stream_ = input_stream;

	//���Ͽ� ����ϱ� ���� ���� ������ �ʱ�ȭ��.
	output_stream_ = output_stream;

	//RegisterBike Control object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	register_bike_ = register_bike;
}

RegisterBike::RegisterBike(ifstream* input_stream, ofstream* output_stream, BikeCollection* bike_collection, AccessManager* access_manager) {
	//BikeCollection Entity object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	bike_collection_ = bike_collection;

	//AccessManager Entity object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	access_manager_ = access_manager;

	//RegisterBikeUI Boundary object�� ������.
	register_bike_ui_ = new RegisterBikeUI(input_stream, output_stream, this);

	//Boundary object�� StartInterface() �Լ��� ȣ����.
	register_bike_ui_->StartInterface();
}

void RegisterBikeUI::StartInterface() {
	//������ ��Ͽ� �ʿ��� �Է°��� �Է¹���.
	BikeInput bike_input;
	*input_stream_ >> bike_input.bike_id >> bike_input.bike_product_name;

	//�Է¹��� ���� ���η� �����ϱ� ���� �Լ��� ȣ����.
	RegisterNewBike(bike_input);
}

void RegisterBikeUI::RegisterNewBike(BikeInput bike_input) {
	//Control object�� �Լ��� ȣ���ϰ�, Control object�κ��� ��ȯ���� ���� �����.
	BikeInput registered_bike = register_bike_->CreateNewBike(bike_input);
	*output_stream_ << "3.1. ������ ���" << endl << "> " << registered_bike.bike_id << ' ' << registered_bike.bike_product_name << endl << endl;
}

BikeInput RegisterBike::CreateNewBike(BikeInput bike_input) {
	//AccessManager Entity Class�κ��� ���� �α��ε� �̿��ڸ� ����. 
	User* current_user = access_manager_->GetCurrentUser();

	//���� �α��ε� �̿��ڰ� �����ڶ�� �����Ÿ� �����.
	if (current_user->IsAdmin()) {
		//�Լ��� ȣ�������ν� Entity object���� ���� ������.
		bike_collection_->AddNewBike(bike_input);

		//Boundary object���� ���� ��ȯ��.
		return bike_input;
	}
}



//������ �뿩 ����� �����ϱ� ���� Class�� ������
RentBikeUI::RentBikeUI(ifstream* input_stream, ofstream* output_stream, RentBike* rent_bike) {
	//���Ϸκ��� �Է¹ޱ� ���� ���� ������ �ʱ�ȭ��.
	input_stream_ = input_stream;

	//���Ͽ� ����ϱ� ���� ���� ������ �ʱ�ȭ��.
	output_stream_ = output_stream;

	//RentBike Control object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	rent_bike_ = rent_bike;
}

RentBike::RentBike(ifstream* input_stream, ofstream* output_stream, BikeCollection* bike_collection, AccessManager* access_manager) {
	//BikeCollection Entity object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	bike_collection_ = bike_collection;

	//AccessManager Entity object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	access_manager_ = access_manager;

	//RentBikeUI Boundary object�� ������.
	rent_bike_ui_ = new RentBikeUI(input_stream, output_stream, this);

	//Boundary object�� StartInterface() �Լ��� ȣ����.
	rent_bike_ui_->StartInterface();
}


void RentBikeUI::StartInterface() {
	//������ �뿩�� �ʿ��� �Է°��� �Է¹���.
	string bike_id;
	*input_stream_ >> bike_id;

	//�Է¹��� ���� ���η� �����ϱ� ���� �Լ��� ȣ����.
	HireBike(bike_id);
}

void RentBikeUI::HireBike(string bike_id) {
	//Control object�� �Լ��� ȣ���ϰ�, Control object�κ��� ��ȯ���� ���� �����.
	BikeInput rented_bike = rent_bike_->AddNewBike(bike_id);
	*output_stream_ << "4.1. ������ �뿩" << endl << "> " << rented_bike.bike_id << ' ' << rented_bike.bike_product_name << endl << endl;
}

BikeInput RentBike::AddNewBike(string bike_id) {
	//AccessManager Entity Class�κ��� ���� �α��ε� �̿��ڸ� ����.
	User* current_user = access_manager_->GetCurrentUser();

	//���� �α��ε� �̿��ڰ� ȸ���̶�� �����Ÿ� �뿩��.
	if (current_user->IsMember()) {
		//�Է��� ������ ID�� ���� �����Ÿ� ����.
		Bike* selected_bike = bike_collection_->GetBikeById(bike_id);

		//�� �����Ÿ� ���� �α��ε� �̿����� �뿩�� ������ �÷��ǿ� �߰���.
		RentedBikeCollection* user_rented_bike_collection = current_user->GetUserBikes();
		user_rented_bike_collection->AddNewBike(selected_bike);

		//�뿩�� �������� ������ ID, ������ ��ǰ���� Boundary object���� ��ȯ��.
		return selected_bike->GetBikeDetails();
	}
}



//�뿩 ���� ������ ���� ��ȸ ����� �����ϱ� ���� Class�� ������
CheckBikeRentalInformationUI::CheckBikeRentalInformationUI(ifstream* input_stream, ofstream* output_stream, CheckBikeRentalInformation* check_bike_rental_information) {
	//���Ϸκ��� �Է¹ޱ� ���� ���� ������ �ʱ�ȭ��.
	input_stream_ = input_stream;

	//���Ͽ� ����ϱ� ���� ���� ������ �ʱ�ȭ��.
	output_stream_ = output_stream;

	//CheckBikeRentalInformation Control object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	check_bike_rental_information_ = check_bike_rental_information;
}

CheckBikeRentalInformation::CheckBikeRentalInformation(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager){
	//AccessManager Entity object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	access_manager_ = access_manager;

	//CheckBikeRentalInformationUI object�� ������.
	check_bike_rental_information_ui_ = new CheckBikeRentalInformationUI(input_stream, output_stream, this);

	//Boundary object�� StartInterface() �Լ��� ȣ����.
	check_bike_rental_information_ui_->StartInterface();
}


void CheckBikeRentalInformationUI::StartInterface() {
	//�Է¹��� ���� ���η� �����ϱ� ���� �Լ��� ȣ����.
	ViewBikeRentalInformation();
}

void CheckBikeRentalInformationUI::ViewBikeRentalInformation() {
	//Control object�� �Լ��� ȣ���ϰ�, Control object�κ��� ��ȯ���� ���� �����.
	pair<BikeInput*, int> rented_bike_details_list = check_bike_rental_information_->ShowBikeRentalInformation();
	*output_stream_ << "5.1. ������ �뿩 ����Ʈ" << endl;
	for (int i = 0; i < rented_bike_details_list.second; i++) {
		*output_stream_ << "> " << rented_bike_details_list.first[i].bike_id << ' ' << rented_bike_details_list.first[i].bike_product_name << endl;
	}
	*output_stream_ << endl;
	delete[] rented_bike_details_list.first;
}

pair<BikeInput*, int> CheckBikeRentalInformation::ShowBikeRentalInformation() {
	//AccessManager Entity Class�κ��� ���� �α��ε� �̿��ڸ� ����.
	User* current_user = access_manager_->GetCurrentUser();

	//���� �α��ε� �̿��ڰ� ȸ���̶�� �뿩 ���� ������ ������ ��ȸ��.
	if (current_user->IsMember()) {
		//���� �α��ε� �̿����� �뿩�� ������ �÷����� ����.
		RentedBikeCollection* user_rented_bike_collection = current_user->GetUserBikes();

		//���� �α��ε� �̿����� �뿩�� �����ŵ��� ������.
		user_rented_bike_collection->SortBikeById();

		//���� �α��ε� �̿����� �뿩�� �������� ���� ����.
		int num_rented_bike = user_rented_bike_collection->GetNumRentedBikes();

		//���� �α��ε� �̿����� �뿩�� �����ŵ��� ����.
		Bike** user_rented_bikes = user_rented_bike_collection->GetRentedBikes();

		//Boundary object���� ��ȯ�� ���� ������ �迭�� ������.
		BikeInput* rented_bike_details_list = new BikeInput[num_rented_bike];

		//���� �α��ε� �̿����� �뿩�� �����ŵ��� ������ ID, ������ ��ǰ���� �迭�� ������.
		for (int i = 0; i < num_rented_bike; i++) {
			BikeInput rented_bike_details = user_rented_bikes[i]->GetBikeDetails();
			rented_bike_details_list[i] = rented_bike_details;
		}

		//�迭�� �������� ���� Boundary object���� ��ȯ��.
		return pair<BikeInput*, int>(rented_bike_details_list, num_rented_bike);
	}
}



//���� ����� �����ϱ� ���� Class�� ������
ExitUI::ExitUI(ifstream* input_stream, ofstream* output_stream, Exit* exit) {
	//���Ϸκ��� �Է¹ޱ� ���� ���� ������ �ʱ�ȭ��.
	input_stream_ = input_stream;

	//���Ͽ� ����ϱ� ���� ���� ������ �ʱ�ȭ��.
	output_stream_ = output_stream;

	//Exit Control object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	exit_ = exit;
}

Exit::Exit(ifstream* input_stream, ofstream* output_stream, int* is_program_exit) {
	//���Ḧ ���� ������ ���� �ٲٱ� ���� ������ �ʱ�ȭ��.
	is_program_exit_ = is_program_exit;

	//ExitUI Boundary object�� ������.
	exit_ui_ = new ExitUI(input_stream, output_stream, this);

	//Boundary object�� StartInterface() �Լ��� ȣ����.
	exit_ui_->StartInterface();
}


void ExitUI::StartInterface() {
	//�Է¹��� ���� ���η� �����ϱ� ���� �Լ��� ȣ����.
	ExitSystem();
}

void ExitUI::ExitSystem() {
	//Control object�� �Լ��� ȣ����.
	exit_->ExitSystem();

	//�ý����� ����Ǿ����� ȭ�鿡 �����.
	*output_stream_ << "6.1. ����";
}

void Exit::ExitSystem() {
	//���Ḧ ���� ������ ���� 1�� �ٲ�.
	*is_program_exit_ = 1;
}


