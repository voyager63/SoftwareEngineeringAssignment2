#pragma once
#include "EntityObjects.h"
#include "Exit.h"

class Exit;

//���� ����� �����ϱ� ���� Boundary Class
class ExitUI {
private:
	//Exit Control object�� �Լ��� ȣ���ϱ� ���� ����
	Exit* exit_;

	//���Ϸκ��� �Է��� �ޱ� ���� ����
	ifstream* input_stream_;

	//Control object�κ��� ��ȯ���� ���� ���Ͽ� ����ϱ� ���� ����
	ofstream* output_stream_;

public:
	//������
	ExitUI(ifstream* input_stream, ofstream* output_stream, Exit* exit);

	//�����, �̿��ڷκ��� �Է��� ����.
	void StartInterface();

	//�����, �̿����� �Է��� Control object���� ������.
	void ExitSystem();
};