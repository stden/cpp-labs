#include <stdio.h>
#include <conio.h>
#include <dos.h>
//таймер, звуковой сигнал, секундомер-сигнализатор
typedef void interrupt (*intrHandler)(...);

class TBeeper
{
	unsigned int Counter;
	public:
		TBeeper(){Counter=0;}
		void Beep();
		void Enable();
		void Disable();
};

class TClock
{
	unsigned long tick;
	unsigned long BeepTimeLow;
	unsigned long BeepTimeHigh;
	TBeeper *Beeper;
	public:
		TClock();
		TClock(TBeeper*);
		void timeEvent();
		unsigned long getTime();
		void SetBeepTime(unsigned long L,unsigned long H)
		{ BeepTimeLow=L; BeepTimeHigh=H;}
		unsigned long GetBeepTime();
};

TClock::TClock()
{
	tick = 0L;
}

void TBeeper::Beep()
{
	if(Counter)
		sound(200);//1000
	else
		nosound();
}

void TBeeper::Enable()
{
	Counter++;
	Beep();
}

void TBeeper::Disable()
{
	Counter--;
	Beep();
}


TClock::TClock(TBeeper *B)
{
	Beeper=B;
	tick = 0L;
}

void TClock::timeEvent()
{
	tick++;
	if(tick==BeepTimeLow)
		Beeper->Enable();
	if(tick==BeepTimeHigh)
		Beeper->Disable();
}

unsigned long TClock::getTime()
{
	return(tick);
}



class TTimer
{
	static unsigned long  tick;
	static intrHandler    oldHandler;
	static void interrupt newHandler(...);
	static int            intrno;
	static TClock**       clockList;
	static int            clockCount;
	static void           timeEvent();
	public:
		TTimer(int);
		~TTimer();
		unsigned long getTime();
		void addClock(TClock*);
};

unsigned long TTimer::tick = 0L;
intrHandler   TTimer::oldHandler = NULL;
int           TTimer::intrno = 0;
TClock**      TTimer::clockList = NULL;
int           TTimer::clockCount = 0;

void TTimer::timeEvent()
{
	tick++;
	for (int i=0;i<clockCount;i++)
		clockList[i]->timeEvent();
}

TTimer::TTimer(int no)
{
	if (intrno == 0)
	{
		intrno = no;
		oldHandler = getvect(no);
		setvect(no,newHandler);
	}
}

TTimer::~TTimer()
{
	if (intrno != 0)
		setvect(intrno,oldHandler);
	if (clockCount > 0)
		delete [] clockList;
}
void interrupt TTimer::newHandler(...)
{
	timeEvent();
	oldHandler();
}
unsigned long TTimer::getTime()
{
	return(tick);
}

void TTimer::addClock(TClock* clock)
{
	if (clockCount == 0)
		clockList = new TClock*;
	else
	{
		TClock** temp;
		temp = new TClock* [clockCount + 1];
		for (int i=0;i<clockCount;i++)
			temp[i] = clockList[i];
		delete [] clockList;
		clockList = temp;
	}
	clockList[clockCount++] = clock;
}

void main()
{
	unsigned long t;
	int f[2] = {0,0};
	clrscr();
	TBeeper b1;
	TClock  c1(&b1), c2(&b1);
	c1.SetBeepTime(100,120);
	c2.SetBeepTime(140,150);
	TTimer* timer = new TTimer(8);
	timer->addClock(&c1);
	timer->addClock(&c2);
	while (1)
	{
		t = timer->getTime();
		gotoxy(1,1);
		printf("%lu",t);
		gotoxy(1,2);
		printf("%lu",c1.getTime());
		gotoxy(1,3);
		printf("%lu",c2.getTime());
		if (kbhit())
			break;
	}
	delete timer;
}

