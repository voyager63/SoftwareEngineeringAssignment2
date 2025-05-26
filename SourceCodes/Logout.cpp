#include "Logout.h"

Logout::Logout(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager) {
	//AccessManager Entity object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	access_manager_ = access_manager;

	//LogoutUI Boundary object�� ������.
	logout_ui_ = new LogoutUI(input_stream, output_stream, this);

	//Boundary object�� StartInterface() �Լ��� ȣ����.
	logout_ui_->StartInterface();
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