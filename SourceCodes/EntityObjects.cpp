#include "EntityObjects.h"

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