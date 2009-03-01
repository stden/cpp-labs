// scrmapclass.h - класс, обеспечивающий работу с областью простмотра карты на экране
class scrmap{
public:
	int xstart, ystart; // координаты левого верхнего угла на карте (в координатах карты)
	int xsize, ysize; // размер отображаемой карты (в блоках карты)
	int m_xsize, m_ysize; // размеры всей карты мира

	bool init(int xst, int yst, int xsz, int ysz, int m_xsz, int m_ysz);
	void dxstart(int dx); // смещение левого верхнего угла просмотра на величину dx
	void dystart(int dy); // dy
};

bool scrmap::init(int xst, int yst, int xsz, int ysz, int m_xsz, int m_ysz){
	bool flag=true;
	xstart=xst;
	ystart=yst;
	m_xsize=m_xsz;
	m_ysize=m_ysz;
    if (xsz<m_xsize) 
		xsize=xsz;
	else{
		flag=false;
		xsize=m_xsize;
	}
    if (ysz<m_ysize) 
		ysize=ysz;
	else{
		flag=false;
		ysize=m_ysize;
	}
	return flag;
}

void scrmap::dxstart(int dx){
	if ((dx+xstart>=0)&&(dx+xstart+xsize<=m_xsize))
		xstart+=dx;
}

void scrmap::dystart(int dy){
	if ((dy+ystart>=0)&&(dy+ystart+ysize<=m_ysize))
		ystart+=dy;
}