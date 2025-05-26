#include "ExitUI.h"


ExitUI::ExitUI(ifstream* input_stream, ofstream* output_stream, Exit* exit) {
	//���Ϸκ��� �Է¹ޱ� ���� ���� ������ �ʱ�ȭ��.
	input_stream_ = input_stream;

	//���Ͽ� ����ϱ� ���� ���� ������ �ʱ�ȭ��.
	output_stream_ = output_stream;

	//Exit Control object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	exit_ = exit;
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