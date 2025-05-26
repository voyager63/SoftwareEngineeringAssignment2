#include "CheckBikeRentalInformation.h"

CheckBikeRentalInformation::CheckBikeRentalInformation(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager) {
	//AccessManager Entity object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	access_manager_ = access_manager;

	//CheckBikeRentalInformationUI object�� ������.
	check_bike_rental_information_ui_ = new CheckBikeRentalInformationUI(input_stream, output_stream, this);

	//Boundary object�� StartInterface() �Լ��� ȣ����.
	check_bike_rental_information_ui_->StartInterface();
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