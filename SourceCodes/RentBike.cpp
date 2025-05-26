#include "RentBike.h"

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