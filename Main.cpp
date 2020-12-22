#include<graphics.h>
#include<time.h>
#include<Vector>

#define Width 1920
#define Height 1080
#define Num 128
#define Span 32

using namespace std;

class Rain {
private:
	int x;
	int y;
	int len;
	int size;
public:
	Rain(int x, int y, int len, int size) {
		this->x = x * Span;
		this->y = y;
		this->len = len;
		this->size = size;
	}
	void move() {
		y += size;
	}
	void getpos(int& x, int& y) {
		x = this->x;
		y = this->y;
	}
	int getlen() {
		return len;
	}
	int getsize() {
		return size;
	}
	bool test() {
		if (y > Height + len * size) {
			return true;
		}
		return false;
	}
};

void Show(Rain rain) {
	int x, y;
	char num[2];
	rain.getpos(x, y);
	settextstyle(rain.getsize(), rain.getsize() / 2, "宋体");
	for (int i = 0; i < rain.getlen(); i++) {
		setcolor(RGB(0, 255 - i * 255 / rain.getlen(), 0));
		sprintf_s(num, "%d", rand() % 10);
		outtextxy(x, y - i * rain.getsize(), num);
	}
}

Rain Create() {
	return Rain(rand() % (Width / Span), rand() % Height - Height, rand() % 8 + 8, rand() % 16 + 16);
}

int main() {
	initgraph(Width, Height);
	time_t t;
	srand((unsigned)time(&t));

	vector<Rain>rains;
	for (int i = 0; i < Num; i++) {
		rains.push_back(Create());
	}

	while (true) {
		BeginBatchDraw();
		cleardevice();
		for (int i = 0; i < Num; i++) {
			Show(rains[i]);
			rains[i].move();
			if (rains[i].test()) {
				rains[i] = Create();
			}
		}
		EndBatchDraw();
		Sleep(64);
	}

	closegraph();
	return 0;
}