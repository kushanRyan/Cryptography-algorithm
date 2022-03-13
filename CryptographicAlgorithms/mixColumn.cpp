//列混淆------------------------------------------------------------------------------------------------------
//列混合变换是通过矩阵相乘来实现的，经行移位后的状态矩阵与固定的矩阵相乘，得到混淆后的状态矩阵
//举个例子
//使用域上的乘法乘以00000010等价于左移1位(低位补0)后，再根据情况同0x00011011进行异或运算
//乘以(00000100)可以拆分成两次乘以(00000010)的运算
//乘以(0000 0011)可以拆分成先分别乘以(0000 0001)和(0000 0010)，再将两个乘积异或
//只需要实现乘以2的函数，其他数值的乘法都可以通过组合来实现
int aMatrix[4][4] = {
	{2,3,1,1},
	{1,2,3,1},
	{1,1,2,3},
	{3,1,1,2}
};
int GFNo2(int s) {
	int result = s << 1;
	//移位之后，通过和0x00000100和就能将a7弄出来
	int a7 = result & 0x00000100;
	//如果a7为1，则进行异或运算，否则不进行
	if (a7 != 0) {
		result = result & 0x000000ff;
		result = result ^ 0x1b;
	}

	return result;
}
//其他几个，比如说三，就是在gfno2的基础上与s异或
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
	//通过aMartix的值来进行"乘"法运算
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
	//对暂时变量进行初始化
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			plainContainer[i][j] = textContainer[i][j];
		}
	}
	//列混合最重要的部分，也就是矩阵的乘法
	//GFMain是乘法,基于GF(2^8)
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