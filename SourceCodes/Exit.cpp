#include "Exit.h"

Exit::Exit(ifstream* input_stream, ofstream* output_stream, int* is_program_exit) {
	//���Ḧ ���� ������ ���� �ٲٱ� ���� ������ �ʱ�ȭ��.
	is_program_exit_ = is_program_exit;

	//ExitUI Boundary object�� ������.
	exit_ui_ = new ExitUI(input_stream, output_stream, this);

	//Boundary object�� StartInterface() �Լ��� ȣ����.
	exit_ui_->StartInterface();
}

void Exit::ExitSystem() {
	//���Ḧ ���� ������ ���� 1�� �ٲ�.
	*is_program_exit_ = 1;
}