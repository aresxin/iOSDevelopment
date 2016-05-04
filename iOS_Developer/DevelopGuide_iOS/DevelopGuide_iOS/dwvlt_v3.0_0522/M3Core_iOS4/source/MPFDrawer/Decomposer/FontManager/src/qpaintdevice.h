#ifndef QPAINTDEVICE_H_
#define QPAINTDEVICE_H_

class QPaintDevice
{
protected:
	QPaintDevice()
	{
		return;
	};

public:

	virtual ~QPaintDevice ()
	{
		return;
	};

	/*
	bool isExtDev () const
	{
		return false;
	};

	bool paintingActive () const
	{
		return false;
	};

	virtual HDC handle () const

	virtual Qt::HANDLE handle () const

	Display * x11Display () const

	int x11Screen () const

	int x11Depth () const

	int x11Cells () const

	Qt::HANDLE x11Colormap () const

	bool x11DefaultColormap () const

	void * x11Visual () const

	bool x11DefaultVisual () const
	*/

public:
	/*
	static Display * x11AppDisplay ()

	static int x11AppScreen ()

	static int x11AppDepth ()

	static int x11AppCells ()

	static int x11AppDpiX ()

	static int x11AppDpiY ()

	static Qt::HANDLE x11AppColormap ()

	static bool x11AppDefaultColormap ()

	static void * x11AppVisual ()

	static bool x11AppDefaultVisual ()

	static void x11SetAppDpiX ( int dpi )

	static void x11SetAppDpiY ( int dpi )
	*/

};
#endif /*QPAINTDEVICE_H_*/
