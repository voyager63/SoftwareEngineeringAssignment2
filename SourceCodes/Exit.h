#pragma once
#include "EntityObjects.h"
#include "ExitUI.h"

class ExitUI;

//���� ����� �����ϱ� ���� Control Class
class Exit {
private:
	//ExitUI Boundary object�� �����ϰ�, Boundary object�� StartInterface()�� ȣ���ϱ� ���� ����
	ExitUI* exit_ui_;

	//���Ḧ ���� ������ ���� �ٲٱ� ���� ����
	int* is_program_exit_;

public:
	//������
	Exit(ifstream* input_stream, ofstream* output_stream, int* is_program_exit);

	//���Ḧ ���� ������ ���� 1�� �ٲ�.
	void ExitSystem();
};
