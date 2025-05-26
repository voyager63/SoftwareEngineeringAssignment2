#include "RegisterBike.h"

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