/*
 * The Qt class is a namespace for miscellaneous identifiers that need to be global-like.
 */
 
#ifndef QNAMESPACE_H_
#define QNAMESPACE_H_

namespace Qt
{
	enum ButtonState { NoButton = 0x0000, LeftButton = 0x0001, RightButton = 0x0002, MidButton = 0x0004, MouseButtonMask = 0x00ff, ShiftButton = 0x0100, ControlButton = 0x0200, AltButton = 0x0400, MetaButton = 0x0800, KeyButtonMask = 0x0fff, Keypad = 0x4000 };

	enum Orientation { Horizontal = 0, Vertical };

	enum AlignmentFlags { AlignAuto = 0x0000, AlignLeft = 0x0001, AlignRight = 0x0002, AlignHCenter = 0x0004, AlignJustify = 0x0008, AlignHorizontal_Mask = AlignLeft | AlignRight | AlignHCenter | AlignJustify, AlignTop = 0x0010, AlignBottom = 0x0020, AlignVCenter = 0x0040, AlignVertical_Mask = AlignTop | AlignBottom | AlignVCenter, AlignCenter = AlignVCenter | AlignHCenter };

	enum TextFlags { SingleLine = 0x0080, DontClip = 0x0100, ExpandTabs = 0x0200, ShowPrefix = 0x0400, WordBreak = 0x0800, BreakAnywhere = 0x1000, DontPrint = 0x2000, NoAccel = 0x4000 };

	enum WidgetState { WState_Created = 0x00000001, WState_Disabled = 0x00000002, WState_Visible = 0x00000004, WState_ForceHide = 0x00000008, WState_OwnCursor = 0x00000010, WState_MouseTracking = 0x00000020, WState_CompressKeys = 0x00000040, WState_BlockUpdates = 0x00000080, WState_InPaintEvent = 0x00000100, WState_Reparented = 0x00000200, WState_ConfigPending = 0x00000400, WState_Resized = 0x00000800, WState_AutoMask = 0x00001000, WState_Polished = 0x00002000, WState_DND = 0x00004000, WState_Reserved0 = 0x00008000, WState_Reserved1 = 0x00010000, WState_Reserved2 = 0x00020000, WState_Reserved3 = 0x00040000, WState_Maximized = 0x00080000, WState_Minimized = 0x00100000, WState_ForceDisabled = 0x00200000, WState_Exposed = 0x00400000, WState_HasMouse = 0x00800000 };

	enum WidgetFlags { WType_TopLevel = 0x00000001, WType_Dialog = 0x00000002, WType_Popup = 0x00000004, WType_Desktop = 0x00000008, WType_Mask = 0x0000000f, WStyle_Customize = 0x00000010, WStyle_NormalBorder = 0x00000020, WStyle_DialogBorder = 0x00000040, WStyle_NoBorder = 0x00002000, WStyle_Title = 0x00000080, WStyle_SysMenu = 0x00000100, WStyle_Minimize = 0x00000200, WStyle_Maximize = 0x00000400, WStyle_MinMax = WStyle_Minimize | WStyle_Maximize, WStyle_Tool = 0x00000800, WStyle_StaysOnTop = 0x00001000, WStyle_ContextHelp = 0x00004000, WStyle_Reserved = 0x00008000, WStyle_Mask = 0x0000fff0, WDestructiveClose = 0x00010000, WPaintDesktop = 0x00020000, WPaintUnclipped = 0x00040000, WPaintClever = 0x00080000, WResizeNoErase = 0x00100000, WMouseNoMask = 0x00200000, WStaticContents = 0x00400000, WRepaintNoErase = 0x00800000, WX11BypassWM = 0x01000000, WWinOwnDC = 0x00000000, WGroupLeader = 0x02000000, WShowModal = 0x04000000, WNoMousePropagation = 0x08000000, WSubWindow = 0x10000000, WNorthWestGravity = WStaticContents, WType_Modal = WType_Dialog | WShowModal, WStyle_Dialog = WType_Dialog, WStyle_NoBorderEx = WStyle_NoBorder };

	enum ImageConversionFlags { ColorMode_Mask = 0x00000003, AutoColor = 0x00000000, ColorOnly = 0x00000003, MonoOnly = 0x00000002, AlphaDither_Mask = 0x0000000c, ThresholdAlphaDither = 0x00000000, OrderedAlphaDither = 0x00000004, DiffuseAlphaDither = 0x00000008, NoAlpha = 0x0000000c, Dither_Mask = 0x00000030, DiffuseDither = 0x00000000, OrderedDither = 0x00000010, ThresholdDither = 0x00000020, DitherMode_Mask = 0x000000c0, AutoDither = 0x00000000, PreferDither = 0x00000040, AvoidDither = 0x00000080 };

	enum BGMode { TransparentMode, OpaqueMode };

	enum PaintUnit { PixelUnit, LoMetricUnit, HiMetricUnit, LoEnglishUnit, HiEnglishUnit, TwipsUnit };

	enum GUIStyle { MacStyle, WindowsStyle, Win3Style, PMStyle, MotifStyle }; // (obsolete)

	enum Modifier { SHIFT = 0x00200000, CTRL = 0x00400000, ALT = 0x00800000, MODIFIER_MASK = 0x00e00000, UNICODE_ACCEL = 0x10000000, ASCII_ACCEL = UNICODE_ACCEL };

	enum Key { Key_Escape = 0x1000, Key_Tab = 0x1001, Key_Backtab = 0x1002, Key_BackTab = Key_Backtab, Key_Backspace = 0x1003, Key_BackSpace = Key_Backspace, Key_Return = 0x1004, Key_Enter = 0x1005, Key_Insert = 0x1006, Key_Delete = 0x1007, Key_Pause = 0x1008, Key_Print = 0x1009, Key_SysReq = 0x100a, Key_Home = 0x1010, Key_End = 0x1011, Key_Left = 0x1012, Key_Up = 0x1013, Key_Right = 0x1014, Key_Down = 0x1015, Key_Prior = 0x1016, Key_PageUp = Key_Prior, Key_Next = 0x1017, Key_PageDown = Key_Next, Key_Shift = 0x1020, Key_Control = 0x1021, Key_Meta = 0x1022, Key_Alt = 0x1023, Key_CapsLock = 0x1024, Key_NumLock = 0x1025, Key_ScrollLock = 0x1026, Key_F1 = 0x1030, Key_F2 = 0x1031, Key_F3 = 0x1032, Key_F4 = 0x1033, Key_F5 = 0x1034, Key_F6 = 0x1035, Key_F7 = 0x1036, Key_F8 = 0x1037, Key_F9 = 0x1038, Key_F10 = 0x1039, Key_F11 = 0x103a, Key_F12 = 0x103b, Key_F13 = 0x103c, Key_F14 = 0x103d, Key_F15 = 0x103e, Key_F16 = 0x103f, Key_F17 = 0x1040, Key_F18 = 0x1041, Key_F19 = 0x1042, Key_F20 = 0x1043, Key_F21 = 0x1044, Key_F22 = 0x1045, Key_F23 = 0x1046, Key_F24 = 0x1047, Key_F25 = 0x1048, Key_F26 = 0x1049, Key_F27 = 0x104a, Key_F28 = 0x104b, Key_F29 = 0x104c, Key_F30 = 0x104d, Key_F31 = 0x104e, Key_F32 = 0x104f, Key_F33 = 0x1050, Key_F34 = 0x1051, Key_F35 = 0x1052, Key_Super_L = 0x1053, Key_Super_R = 0x1054, Key_Menu = 0x1055, Key_Hyper_L = 0x1056, Key_Hyper_R = 0x1057, Key_Help = 0x1058, Key_Direction_L = 0x1059, Key_Direction_R = 0x1060, Key_Space = 0x20, Key_Any = Key_Space, Key_Exclam = 0x21, Key_QuoteDbl = 0x22, Key_NumberSign = 0x23, Key_Dollar = 0x24, Key_Percent = 0x25, Key_Ampersand = 0x26, Key_Apostrophe = 0x27, Key_ParenLeft = 0x28, Key_ParenRight = 0x29, Key_Asterisk = 0x2a, Key_Plus = 0x2b, Key_Comma = 0x2c, Key_Minus = 0x2d, Key_Period = 0x2e, Key_Slash = 0x2f, Key_0 = 0x30, Key_1 = 0x31, Key_2 = 0x32, Key_3 = 0x33, Key_4 = 0x34, Key_5 = 0x35, Key_6 = 0x36, Key_7 = 0x37, Key_8 = 0x38, Key_9 = 0x39, Key_Colon = 0x3a, Key_Semicolon = 0x3b, Key_Less = 0x3c, Key_Equal = 0x3d, Key_Greater = 0x3e, Key_Question = 0x3f, Key_At = 0x40, Key_A = 0x41, Key_B = 0x42, Key_C = 0x43, Key_D = 0x44, Key_E = 0x45, Key_F = 0x46, Key_G = 0x47, Key_H = 0x48, Key_I = 0x49, Key_J = 0x4a, Key_K = 0x4b, Key_L = 0x4c, Key_M = 0x4d, Key_N = 0x4e, Key_O = 0x4f, Key_P = 0x50, Key_Q = 0x51, Key_R = 0x52, Key_S = 0x53, Key_T = 0x54, Key_U = 0x55, Key_V = 0x56, Key_W = 0x57, Key_X = 0x58, Key_Y = 0x59, Key_Z = 0x5a, Key_BracketLeft = 0x5b, Key_Backslash = 0x5c, Key_BracketRight = 0x5d, Key_AsciiCircum = 0x5e, Key_Underscore = 0x5f, Key_QuoteLeft = 0x60, Key_BraceLeft = 0x7b, Key_Bar = 0x7c, Key_BraceRight = 0x7d, Key_AsciiTilde = 0x7e, Key_nobreakspace = 0x0a0, Key_exclamdown = 0x0a1, Key_cent = 0x0a2, Key_sterling = 0x0a3, Key_currency = 0x0a4, Key_yen = 0x0a5, Key_brokenbar = 0x0a6, Key_section = 0x0a7, Key_diaeresis = 0x0a8, Key_copyright = 0x0a9, Key_ordfeminine = 0x0aa, Key_guillemotleft = 0x0ab, Key_notsign = 0x0ac, Key_hyphen = 0x0ad, Key_registered = 0x0ae, Key_macron = 0x0af, Key_degree = 0x0b0, Key_plusminus = 0x0b1, Key_twosuperior = 0x0b2, Key_threesuperior = 0x0b3, Key_acute = 0x0b4, Key_mu = 0x0b5, Key_paragraph = 0x0b6, Key_periodcentered = 0x0b7, Key_cedilla = 0x0b8, Key_onesuperior = 0x0b9, Key_masculine = 0x0ba, Key_guillemotright = 0x0bb, Key_onequarter = 0x0bc, Key_onehalf = 0x0bd, Key_threequarters = 0x0be, Key_questiondown = 0x0bf, Key_Agrave = 0x0c0, Key_Aacute = 0x0c1, Key_Acircumflex = 0x0c2, Key_Atilde = 0x0c3, Key_Adiaeresis = 0x0c4, Key_Aring = 0x0c5, Key_AE = 0x0c6, Key_Ccedilla = 0x0c7, Key_Egrave = 0x0c8, Key_Eacute = 0x0c9, Key_Ecircumflex = 0x0ca, Key_Ediaeresis = 0x0cb, Key_Igrave = 0x0cc, Key_Iacute = 0x0cd, Key_Icircumflex = 0x0ce, Key_Idiaeresis = 0x0cf, Key_ETH = 0x0d0, Key_Ntilde = 0x0d1, Key_Ograve = 0x0d2, Key_Oacute = 0x0d3, Key_Ocircumflex = 0x0d4, Key_Otilde = 0x0d5, Key_Odiaeresis = 0x0d6, Key_multiply = 0x0d7, Key_Ooblique = 0x0d8, Key_Ugrave = 0x0d9, Key_Uacute = 0x0da, Key_Ucircumflex = 0x0db, Key_Udiaeresis = 0x0dc, Key_Yacute = 0x0dd, Key_THORN = 0x0de, Key_ssharp = 0x0df, Key_agrave = 0x0e0, Key_aacute = 0x0e1, Key_acircumflex = 0x0e2, Key_atilde = 0x0e3, Key_adiaeresis = 0x0e4, Key_aring = 0x0e5, Key_ae = 0x0e6, Key_ccedilla = 0x0e7, Key_egrave = 0x0e8, Key_eacute = 0x0e9, Key_ecircumflex = 0x0ea, Key_ediaeresis = 0x0eb, Key_igrave = 0x0ec, Key_iacute = 0x0ed, Key_icircumflex = 0x0ee, Key_idiaeresis = 0x0ef, Key_eth = 0x0f0, Key_ntilde = 0x0f1, Key_ograve = 0x0f2, Key_oacute = 0x0f3, Key_ocircumflex = 0x0f4, Key_otilde = 0x0f5, Key_odiaeresis = 0x0f6, Key_division = 0x0f7, Key_oslash = 0x0f8, Key_ugrave = 0x0f9, Key_uacute = 0x0fa, Key_ucircumflex = 0x0fb, Key_udiaeresis = 0x0fc, Key_yacute = 0x0fd, Key_thorn = 0x0fe, Key_ydiaeresis = 0x0ff, Key_unknown = 0xffff };

	enum ArrowType { UpArrow, DownArrow, LeftArrow, RightArrow };

	enum RasterOp { CopyROP, OrROP, XorROP, NotAndROP, EraseROP = NotAndROP, NotCopyROP, NotOrROP, NotXorROP, AndROP, NotEraseROP = AndROP, NotROP, ClearROP, SetROP, NopROP, AndNotROP, OrNotROP, NandROP, NorROP, LastROP = NorROP };

	enum PenStyle { NoPen, SolidLine, DashLine, DotLine, DashDotLine, DashDotDotLine, MPenStyle = 0x0f };

	enum PenCapStyle { FlatCap = 0x00, SquareCap = 0x10, RoundCap = 0x20, MPenCapStyle = 0x30 };

	enum PenJoinStyle { MiterJoin = 0x00, BevelJoin = 0x40, RoundJoin = 0x80, MPenJoinStyle = 0xc0 };

	enum BrushStyle { NoBrush, SolidPattern, Dense1Pattern, Dense2Pattern, Dense3Pattern, Dense4Pattern, Dense5Pattern, Dense6Pattern, Dense7Pattern, HorPattern, VerPattern, CrossPattern, BDiagPattern, FDiagPattern, DiagCrossPattern, CustomPattern = 24 };

	enum WindowsVersion { WV_32s = 0x0001, WV_95 = 0x0002, WV_98 = 0x0003, WV_Me = 0x0004, WV_DOS_based = 0x000f, WV_NT = 0x0010, WV_2000 = 0x0020, WV_XP = 0x0030, WV_NT_based = 0x00f0 };

	enum UIEffect { UI_General, UI_AnimateMenu, UI_FadeMenu, UI_AnimateCombo, UI_AnimateTooltip, UI_FadeTooltip };

	enum CursorShape { ArrowCursor, UpArrowCursor, CrossCursor, WaitCursor, IbeamCursor, SizeVerCursor, SizeHorCursor, SizeBDiagCursor, SizeFDiagCursor, SizeAllCursor, BlankCursor, SplitVCursor, SplitHCursor, PointingHandCursor, ForbiddenCursor, WhatsThisCursor, LastCursor = WhatsThisCursor, BitmapCursor = 24 };

	enum TextFormat { PlainText, RichText, AutoText };

	enum Dock { DockUnmanaged, DockTornOff, DockTop, DockBottom, DockRight, DockLeft, DockMinimized, Unmanaged = DockUnmanaged, TornOff = DockTornOff, Top = DockTop, Bottom = DockBottom, Right = DockRight, Left = DockLeft, Minimized = DockMinimized };

	enum DateFormat { TextDate, ISODate, LocalDate };

	enum BackgroundMode { FixedColor, FixedPixmap, NoBackground, PaletteForeground, PaletteButton, PaletteLight, PaletteMidlight, PaletteDark, PaletteMid, PaletteText, PaletteBrightText, PaletteBase, PaletteBackground, PaletteShadow, PaletteHighlight, PaletteHighlightedText, PaletteButtonText, PaletteLink, PaletteLinkVisited, X11ParentRelative };

	enum StringComparisonMode { CaseSensitive = 0x00001, BeginsWith = 0x00002, EndsWith = 0x00004, Contains = 0x00008, ExactMatch = 0x00010 };
	
	enum GlobalColor
	{
		white		= 3,	// White (#ffffff)
		black		= 2,	// Black (#000000)
		red			= 7,	// Red (#ff0000)
		darkRed		= 13,	// Dark red (#800000)
		green		= 8,	// Green (#00ff00)
		darkGreen	= 14,	// Dark green (#008000)
		blue		= 9,	// Blue (#0000ff)
		darkBlue	= 15,	// Dark blue (#000080)
		cyan		= 10,	// Cyan (#00ffff)
		darkCyan	= 16,	// Dark cyan (#008080)
		magenta		= 11,	// Magenta (#ff00ff)
		darkMagenta	= 17,	// Dark magenta (#800080)
		yellow		= 12,	// Yellow (#ffff00)
		darkYellow	= 18,	// Dark yellow (#808000)
		gray		= 5,	// Gray (#a0a0a4)
		darkGray	= 4,	// Dark gray (#808080)
		lightGray	= 6,	// Light gray (#c0c0c0)
		transparent	= 19,	// a transparent black value (i.e., QColor(0, 0, 0, 0))
		color0		= 0,	// 0 pixel value (for bitmaps)
		color1		= 1		// 1 pixel value (for bitmaps)
	};

};

typedef void *		HANDLE;
typedef int		QCOORD;
#endif /*QNAMESPACE_H_*/
