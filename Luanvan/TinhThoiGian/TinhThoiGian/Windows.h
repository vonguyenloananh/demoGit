// file timer4w.c
#include
#include
// khai bao cau truc va cac ham
typedef struct {
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
} stopWatch;
void startTimer(stopWatch *timer);
void stopTimer(stopWatch *timer);
double LIToSecs(LARGE_INTEGER * L);
double getElapsedTime(stopWatch *timer);
void startTimer(stopWatch *timer)
{
	QueryPerformanceCounter(&timer->start);
}
void stopTimer(stopWatch *timer)
{
	QueryPerformanceCounter(&timer->stop);
}
double LIToSecs(LARGE_INTEGER * L)
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return ((double)L->QuadPart / (double)frequency.QuadPart);
}
double getElapsedTime(stopWatch *timer) {
	LARGE_INTEGER time;
	time.QuadPart = timer->stop.QuadPart – timer->start.QuadPart;
	return LIToSecs(&time);
}
// su dung cac ham
int main()
{
	long i = 600000000L;
	stopWatch timer;
	double duration;
	// Do thoi gian cua mot su kien
	printf(“Thoi gian thuc hien %ld vong lap rong : ”, i);
	startTimer(&timer);
	while (i–)
		;
	stopTimer(&timer);
	duration = getElapsedTime(&timer);
	printf(“%2.1f giay\n”, duration);
	system(“pause”);
	return 0;
}