#include "LogoutUI.h"

LogoutUI::LogoutUI(ifstream* input_stream, ofstream* output_stream, Logout* logout) {
	//���Ϸκ��� �Է¹ޱ� ���� ���� ������ �ʱ�ȭ��.
	input_stream_ = input_stream;

	//���Ͽ� ����ϱ� ���� ���� ������ �ʱ�ȭ��.
	output_stream_ = output_stream;

	//Logout Control object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	logout_ = logout;
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