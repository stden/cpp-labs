// minimapclass.h - класс реализующий миникарту

class minimap {
 public:
  bool initm;
  int xsize, ysize; // размеры окна миникарты
  int xstart, ystart; // стартовая позиция
  int c_xsize, c_ysize; // размеры клиентской области создаваемого окна
  HWND hwnd; // хендл окна
 public:
  minimap();
  void init(HWND w_hwnd, HINSTANCE hinst, WNDPROC msg, int ixstart, int iystart, int ixsize, int iysize);
};

minimap::minimap() {
  initm = false;
}
void minimap::init(HWND w_hwnd, HINSTANCE hinst, WNDPROC msg, int ixstart, int iystart, int ixsize, int iysize) {
  WNDCLASSEX  wc;
  RECT    rc;
  wc.cbSize   = sizeof(wc);
  wc.style    = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc  = msg;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance  = hinst;
  wc.hIcon    = LoadIcon(NULL, IDI_APPLICATION );
  wc.hCursor    = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_BACKGROUND);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "Minimap";
  wc.hIconSm    = LoadIcon(NULL, IDI_APPLICATION);
  RegisterClassEx(&wc);
  GetWindowRect(w_hwnd, &rc);
  xsize = ixsize;
  ysize = iysize;
  xstart = rc.left + ixstart + 10;
  ystart = rc.top + iystart + 35;
  hwnd = CreateWindowEx(
           WS_EX_LEFT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
           "Minimap", "Minimap",
           WS_BORDER | WS_VISIBLE | WS_MINIMIZEBOX,
           xstart, ystart,
           xsize, ysize, w_hwnd, NULL, wc.hInstance, NULL);
  GetClientRect(hwnd, &rc);
  c_xsize = rc.right;
  c_ysize = rc.bottom;

  SetActiveWindow(w_hwnd);
  initm = true;
}
