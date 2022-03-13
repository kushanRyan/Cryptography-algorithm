//�л���------------------------------------------------------------------------------------------------------
//�л�ϱ任��ͨ�����������ʵ�ֵģ�������λ���״̬������̶��ľ�����ˣ��õ��������״̬����
//�ٸ�����
//ʹ�����ϵĳ˷�����00000010�ȼ�������1λ(��λ��0)���ٸ������ͬ0x00011011�����������
//����(00000100)���Բ�ֳ����γ���(00000010)������
//����(0000 0011)���Բ�ֳ��ȷֱ����(0000 0001)��(0000 0010)���ٽ������˻����
//ֻ��Ҫʵ�ֳ���2�ĺ�����������ֵ�ĳ˷�������ͨ�������ʵ��
int aMatrix[4][4] = {
	{2,3,1,1},
	{1,2,3,1},
	{1,1,2,3},
	{3,1,1,2}
};
int GFNo2(int s) {
	int result = s << 1;
	//��λ֮��ͨ����0x00000100�;��ܽ�a7Ū����
	int a7 = result & 0x00000100;
	//���a7Ϊ1�������������㣬���򲻽���
	if (a7 != 0) {
		result = result & 0x000000ff;
		result = result ^ 0x1b;
	}

	return result;
}
//��������������˵����������gfno2�Ļ�������s���
int GFNo3(int s) {
	return GFNo2(s) ^ s;
}
int GFNo4(int s) {
	return GFNo2(GFNo2(s));
}
int GFNo5(int s) {
	return GFNo4(s) ^ s;
}
int GFNo6(int s) {
	return GFNo3(s) ^ GFNo3(s);
}
int GFNo7(int s) {
	return GFNo3(s) ^ GFNo4(s);
}
int GFNo8(int s) {
	return GFNo2(GFNo4(s));
}
int GFNo9(int s) {
	return GFNo8(s) ^ s;
}
int GFNo10(int s) {
	return GFNo5(s) ^ GFNo5(s);
}
int GFNo11(int s) {
	return GFNo9(s) ^ GFNo2(s);
}
int GFNo12(int s) {
	return GFNo8(s) ^ GFNo4(s);
}
int GFNo13(int s) {
	return GFNo12(s) ^ s;
}
int GFNo14(int s) {
	return GFNo12(s) ^ GFNo2(s);
}
int GFNo15(int s) {
	return GFNo14(s) ^ s;
}
int GFMain(int n, int s) {
	int result = 0;
	//ͨ��aMartix��ֵ������"��"������
	if (n == 1) {
		result = s;
	}
	else if (n == 2) {
		result = GFNo2(s);
	}
	else if (n == 3) {
		result = GFNo3(s);
	}
	else if (n == 4) {
		result = GFNo4(s);
	}
	else if (n == 5) {
		result = GFNo5(s);
	}
	else if (n == 6) {
		result = GFNo6(s);
	}
	else if (n == 7) {
		result = GFNo7(s);
	}
	else if (n == 8) {
		result = GFNo8(s);
	}
	else if (n == 0x9) {
		result = GFNo9(s);
	}
	else if (n == 0xa) {
		result = GFNo10(s);
	}
	else if (n == 0xb) {
		result = GFNo11(s);
	}
	else if (n == 0xc) {
		result = GFNo12(s);
	}
	else if (n == 0xd) {
		result = GFNo13(s);
	}
	else if (n == 0xe) {
		result = GFNo14(s);
	}
	else if (n == 0xf) {
		result = GFNo15(s);
	}
	return result;
}
void mixColumn(int textContainer[4][4]) {
	int plainContainer[4][4];
	//����ʱ�������г�ʼ��
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			plainContainer[i][j] = textContainer[i][j];
		}
	}
	//�л������Ҫ�Ĳ��֣�Ҳ���Ǿ���ĳ˷�
	//GFMain�ǳ˷�,����GF(2^8)
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			textContainer[i][j] =
				GFMain(aMatrix[i][0], plainContainer[0][j]) ^
				GFMain(aMatrix[i][1], plainContainer[1][j]) ^
				GFMain(aMatrix[i][2], plainContainer[2][j]) ^
				GFMain(aMatrix[i][3], plainContainer[3][j]);
		}
	}
}