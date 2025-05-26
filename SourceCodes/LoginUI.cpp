#include "LoginUI.h"

LoginUI::LoginUI(ifstream* input_stream, ofstream* output_stream, Login* login) {
	//���Ϸκ��� �Է¹ޱ� ���� ���� ������ �ʱ�ȭ��.
	input_stream_ = input_stream;

	//���Ͽ� ����ϱ� ���� ���� ������ �ʱ�ȭ��.
	output_stream_ = output_stream;

	//Login Control object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	login_ = login;
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