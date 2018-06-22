/**
*copyright lidonghai
*2018.6
*@Nanchang University( ncu.edu.cn )
* website www.eastsea.ac.cn
* license:GPL
*/
#include<iostream>
#include<Windows.h>
#include<time.h>
#include<math.h>


//壶嘴X1
int UtahMouthX1[4][4]{
	170,170,170,170,
	260,260,310,310,
	230,230,240,240,
	270,270,330,330
};

//壶嘴X2
int UtahMouthX2[4][4]{
	270,270,330,330,
	280,280,352,352,
	290,290,340,340,
	280,280,320,320
};


//壶嘴Y1
int UtahMouthY1[4][4]{
	127,127,40,40,
	127,127,67,67,
	195,195,187,187,
	225,225,220,220
};

//壶嘴Y2
int UtahMouthY2[4][4]{
	225,225,220,220,
	232, 232, 234,234,
	232,232, 236,236,
	225,225,225, 225
};

//壶嘴Z1
int UtahMouthZ1[4][4]{
	66,66,0,0,
	66,66,0,0,
	25,25,0,0,
	25,25,0,0
};

//壶嘴Z2
int UtahMouthZ2[4][4]{
	25,25,0,0,
	25,25,0,0,
	15,15,0,0,
	15,15,0,0
};

//壶把手X1
int UtahHandlerX1[4][4]{
	160,160,150,150,
	230,230,250,250,
	270,270,300,300,
	270,270,300,300
};

//X2
int UtahHandlerX2[4][4]{
	270,270,300,300,
	270,270,300,300,
	250,250,265,265,
	200,200,190,190
};

//Y1
int UtahHandlerY1[4][4]{
	187,187,210,210,
	187,187,210,210,
	187,187,210,210,
	165,165,165,165
};

//Y2
int UtahHandlerY2[4][4]{
	165,165,165,165,
	142,142,120,120,
	97,97,78,78,
	75,75,45,45
};

//Z
int UtahHandlerZ[4][4]{
	30,30,0,0,
	30,30,0,0,
	30,30,0,0,
	30,30,0,0
};




//壶体一边
int UtahBody[3][8]{
	140,225,133,238,143,238,150,225,
	150,225,175,172,200,120,200,75,
	200,75,200,30,150,7.5,150,0
};

int UtahBody1[9][8]{
	140,225,133,238,143,238,150,225,
	150,225,175,172,200,120,200,75,
	200,75,200,30,150,7.5,150,0,
	150,0,125,0,100,0,100,0,
	100,0,80,0,70,0,65,0,
	65,0,60,0,55,0,50,0,
	50,0,45,0,40,0,35,0,
	35,0,30,0,25,0,20,0,
	20,0,0,0,0,0,0,0
};

//壶盖
int UtahTop[2][8]{
	0,300,80,300,0,270,20,255,
	20,255,40,240,130,240,130,225,
};


HDC getHDC() {
	HWND cmd = GetConsoleWindow();//获取控制台窗口句柄
	HDC hdc = GetWindowDC(cmd);//获取控制台窗口
	return hdc;
}

//dorw函数参数说明：arr-数据数组；HDC代表HDC画图；arrRow-数组行大小；tIncreament-t增长大小，建议0.01； 
//scale-缩放，大于1代表缩小，小于1大于0代表放大；  offsetX-代表X偏移，y一致；turn为1 代表图反的，-1代表正的
void drow(int arr[][8], HDC hdc, int arrRow, float tIncreament, int scale, int offsetX, int offsetY, int turn) {

	for (int i = 0; i < arrRow; i++) {
		for (float t = 0.0; t <= 1; t += tIncreament) {
			int x = (1 - t) * (1 - t) * (1 - t) * arr[i][0] + 3 * t * (1 - t) * (1 - t) *arr[i][2] + 3 * t * t * (1 - t) * arr[i][4] + t * t *t *arr[i][6];
			int y = (1 - t) * (1 - t) * (1 - t) * arr[i][1] + 3 * t * (1 - t) * (1 - t) *arr[i][3] + 3 * t * t * (1 - t) * arr[i][5] + t * t *t * arr[i][7];
			SetPixel(hdc, turn*(x / scale) + offsetX, turn *(y / scale) + offsetY, RGB(0, 255, 0));
		}
	}
} 

//投影函数
void drowTouYing(HDC hdc, double sx, double sy, double sz, int bx, int by, int bz,int xOff,int yOff) {
	int x = -1 * sz * bx + sx * bz;
	int y = -1 * sz * by + sy * bz;
	SetPixel(hdc, x + xOff, y + yOff, RGB(0, 255, 0));
}



//旋转函数

void drowMain(HDC hdc,int arr[][8],int row, float tIncreament, int jIncreament) {

	for (int i = 0; i < row; i++) {
		for (float t = 0.0; t <= 1; t += tIncreament) {
			int x = (1 - t) * (1 - t) * (1 - t) * arr[i][0] + 3 * t * (1 - t) * (1 - t) *arr[i][2] + 3 * t * t * (1 - t) * arr[i][4] + t * t *t *arr[i][6];
			int y = (1 - t) * (1 - t) * (1 - t) * arr[i][1] + 3 * t * (1 - t) * (1 - t) *arr[i][3] + 3 * t * t * (1 - t) * arr[i][5] + t * t *t * arr[i][7];

			for (int j = 0; j < 360; j += jIncreament) {
				int xx = x * cos(j * 3.1415926 / 180);
				int yy = y;
				int zz = -1 * x * sin(j * 3.1415926 / 180);
				drowTouYing(hdc, 0, 0.2, 1, xx, yy, zz,400,400);
			}
		}
	}

}

//双三次berzier曲线
// int turn ：代表对X轴对称
void drowBerzier(HDC hdc, float uIncrement,float wIncrement, int arrX[][4], int arrY[][4],int arrZ[][4],int xOff, int yOff,int turn) {
	for (float u = 0; u < 1; u += uIncrement) {
		for (float w = 0; w < 1; w += wIncrement) {

			//双三次berzier曲线 算x y z的值
			int x1 = (1 - u)*(1 - u)*(1 - u) * arrX[0][0] + 3 * u*(1 - u)*(1 - u)*arrX[1][0] + 3 * u*u*(1 - u)*arrX[2][0] + u * u*u*arrX[3][0];
			int x2 = (1 - u)*(1 - u)*(1 - u) * arrX[0][1] + 3 * u*(1 - u)*(1 - u)*arrX[1][1] + 3 * u*u*(1 - u)*arrX[2][1] + u * u*u*arrX[3][1];
			int x3 = (1 - u)*(1 - u)*(1 - u) * arrX[0][2] + 3 * u*(1 - u)*(1 - u)*arrX[1][2] + 3 * u*u*(1 - u)*arrX[2][2] + u * u*u*arrX[3][2];
			int x4 = (1 - u)*(1 - u)*(1 - u) * arrX[0][3] + 3 * u*(1 - u)*(1 - u)*arrX[1][3] + 3 * u*u*(1 - u)*arrX[2][3] + u * u*u*arrX[3][3];

			int y1 = (1 - u)*(1 - u)*(1 - u) * arrY[0][0] + 3 * u*(1 - u)*(1 - u)*arrY[1][0] + 3 * u*u*(1 - u)*arrY[2][0] + u * u*u*arrY[3][0];
			int y2 = (1 - u)*(1 - u)*(1 - u) * arrY[0][1] + 3 * u*(1 - u)*(1 - u)*arrY[1][1] + 3 * u*u*(1 - u)*arrY[2][1] + u * u*u*arrY[3][1];
			int y3 = (1 - u)*(1 - u)*(1 - u) * arrY[0][2] + 3 * u*(1 - u)*(1 - u)*arrY[1][2] + 3 * u*u*(1 - u)*arrY[2][2] + u * u*u*arrY[3][2];
			int y4 = (1 - u)*(1 - u)*(1 - u) * arrY[0][3] + 3 * u*(1 - u)*(1 - u)*arrY[1][3] + 3 * u*u*(1 - u)*arrY[2][3] + u * u*u*arrY[3][3];

			int z1 = (1 - u)*(1 - u)*(1 - u) * arrZ[0][0] + 3 * u*(1 - u)*(1 - u)*arrZ[1][0] + 3 * u*u*(1 - u)*arrZ[2][0] + u * u*u*arrZ[3][0];
			int z2 = (1 - u)*(1 - u)*(1 - u) * arrZ[0][1] + 3 * u*(1 - u)*(1 - u)*arrZ[1][1] + 3 * u*u*(1 - u)*arrZ[2][1] + u * u*u*arrZ[3][1];
			int z3 = (1 - u)*(1 - u)*(1 - u) * arrZ[0][2] + 3 * u*(1 - u)*(1 - u)*arrZ[1][2] + 3 * u*u*(1 - u)*arrZ[2][2] + u * u*u*arrZ[3][2];
			int z4 = (1 - u)*(1 - u)*(1 - u) * arrZ[0][3] + 3 * u*(1 - u)*(1 - u)*arrZ[1][3] + 3 * u*u*(1 - u)*arrZ[2][3] + u * u*u*arrZ[3][3];

			int xx = x1 * (1 - w)*(1 - w)*(1 - w) + x2 * 3 * w*(1 - w)*(1 - w) + x3 * 3 * w*w*(1 - w) + x4 * w * w * w;
			int yy = y1 * (1 - w)*(1 - w)*(1 - w) + y2 * 3 * w*(1 - w)*(1 - w) + y3 * 3 * w*w*(1 - w) + y4 * w * w * w;
			int zz = z1 * (1 - w)*(1 - w)*(1 - w) + z2 * 3 * w*(1 - w)*(1 - w) + z3 * 3 * w*w*(1 - w) + z4 * w * w * w;

			drowTouYing(hdc, 0, 0.2, 1, xx * turn, yy, zz, xOff, yOff);
			//printf("%d %d",xx,yy);
		}
	}
}


int main() {
	HDC hdc = getHDC();
	
	//drow(UtahBody1, hdc, 7, 0.01, 1, 200, 200, 1);

	
	//绘制壶把手
	drowBerzier(hdc, 0.01, 0.01, UtahHandlerX1, UtahHandlerY1, UtahHandlerZ, 400, 380,-1);
	drowBerzier(hdc, 0.01, 0.01, UtahHandlerX2, UtahHandlerY2, UtahHandlerZ, 400, 380,-1);
	
	
	//绘制壶体以及壶盖
	drowMain(hdc, UtahBody1, 9, 0.01, 8);//画竖线
	drowMain(hdc, UtahBody1, 9, 0.2, 1);//画横线
	//drowMain(hdc, UtahBody, 3, 0.01, 1);
	//drowMain(hdc, UtahBody, 3, 0.01, 1);

	
	drowMain(hdc, UtahTop, 3, 0.01, 8);
	drowMain(hdc, UtahTop, 3, 0.2, 1);

	//绘制壶嘴
	drowBerzier(hdc, 0.01, 0.01, UtahMouthX1, UtahMouthY1, UtahMouthZ1, 380, 380, 1);
	drowBerzier(hdc, 0.01, 0.01, UtahMouthX2, UtahMouthY2, UtahMouthZ2, 380, 380, 1);
	

	getchar();
	return 1;
}