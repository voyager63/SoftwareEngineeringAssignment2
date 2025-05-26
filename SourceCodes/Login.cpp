#include "Login.h"

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