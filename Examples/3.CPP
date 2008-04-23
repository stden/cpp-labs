#include <stdio.h>
#include <conio.h>
#include <dos.h>

typedef void interrupt (*intrHandler)(...);

class CAlarm
{
	unsigned int AlarmCounter;
	public:
		CAlarm(){AlarmCounter=0;}
		void Alarm();
		void Enable();
		void Disable();
};

class CClock
{
	unsigned long sec;
	unsigned long AlarmTimeBeg;
	unsigned long AlarmTimeEnd;
	CAlarm*  Alarm;
	public:
		CClock();
		CClock(CAlarm*);
		void timeEvent();
		unsigned long getTime();
		void SetAlarmTime(unsigned long L,unsigned long H)
		{ AlarmTimeBeg=L; AlarmTimeEnd=H;}
};


void CAlarm::Alarm()
{
	if(AlarmCounter)
		sound(200);//1000
	else
		nosound();
}

void CAlarm::Enable()
{
	AlarmCounter++;
	Alarm();
}

void CAlarm::Disable()
{
	AlarmCounter--;
	Alarm();
}

CClock::CClock()
{
	sec = 0L;
}


CClock::CClock(CAlarm* B)
{
	Alarm=B;
	sec = 0L;
}

void CClock::timeEvent()
{
	sec++;
	if(sec==AlarmTimeBeg)
		Alarm->Enable();
	if(sec==AlarmTimeEnd)
		Alarm->Disable();
}

unsigned long CClock::getTime()
{
	return(sec);
}



class CTimer
{
	static unsigned long  sec;
	static intrHandler    oldHandler;
	static void interrupt newHandler(...);
	static int            intrno;
	static CClock**       clockList;
	static int            clockCount;
	static void           timeEvent();
	public:
		CTimer(int);
		~CTimer();
		unsigned long getTime();
		void addClock(CClock*);
};

unsigned long CTimer::sec = 0L;
intrHandler   CTimer::oldHandler = NULL;
int           CTimer::intrno = 0;
CClock**      CTimer::clockList = NULL;
int           CTimer::clockCount = 0;


CTimer::CTimer(int no)
{
	if (intrno == 0)
	{
		intrno = no;
		oldHandler = getvect(no);
		setvect(no,newHandler);
	}
}

CTimer::~CTimer()
{
	if (intrno != 0)
		setvect(intrno,oldHandler);
	if (clockCount > 0)
		delete [] clockList;
}

void CTimer::timeEvent()
{
	sec++;
	for (int i=0;i<clockCount;i++)
		clockList[i]->timeEvent();
}

void interrupt CTimer::newHandler(...)
{
	timeEvent();
	oldHandler();
}
unsigned long CTimer::getTime()
{
	return(sec);
}

void CTimer::addClock(CClock* clock)
{
	if (clockCount == 0)
		clockList = new CClock*;
	else
	{
		CClock** temp;
		temp = new CClock* [clockCount + 1];
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
	clrscr();
	CAlarm b1;
	CClock  c1(&b1), c2(&b1);
	c1.SetAlarmTime(100,120);
	c2.SetAlarmTime(140,150);
	CTimer* timer = new CTimer(8);
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

