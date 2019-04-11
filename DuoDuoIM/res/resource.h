//stamp:107c529088f21f41
/*<------------------------------------------------------------------------------------------------->*/
/*该文件由uiresbuilder生成，请不要手动修改*/
/*<------------------------------------------------------------------------------------------------->*/
#pragma once
#include <res.mgr/snamedvalue.h>
#define ROBJ_IN_CPP \
namespace SOUI \
{\
    const _R R;\
    const _UIRES UIRES;\
}
namespace SOUI
{
	class _UIRES{
		public:
		class _UIDEF{
			public:
			_UIDEF(){
				XML_INIT = _T("UIDEF:XML_INIT");
			}
			const TCHAR * XML_INIT;
		}UIDEF;
		class _LAYOUT{
			public:
			_LAYOUT(){
				XML_MAINWND = _T("LAYOUT:XML_MAINWND");
				XML_DLG_SNAPSHOT = _T("LAYOUT:XML_DLG_SNAPSHOT");
				XML_PAGE_LASTTALK = _T("LAYOUT:XML_PAGE_LASTTALK");
				XML_PAGE_CONTACT = _T("LAYOUT:XML_PAGE_CONTACT");
				XML_PAGE_SEARCHRESULT = _T("LAYOUT:XML_PAGE_SEARCHRESULT");
			}
			const TCHAR * XML_MAINWND;
			const TCHAR * XML_DLG_SNAPSHOT;
			const TCHAR * XML_PAGE_LASTTALK;
			const TCHAR * XML_PAGE_CONTACT;
			const TCHAR * XML_PAGE_SEARCHRESULT;
		}LAYOUT;
		class _values{
			public:
			_values(){
				string = _T("values:string");
				color = _T("values:color");
				skin = _T("values:skin");
			}
			const TCHAR * string;
			const TCHAR * color;
			const TCHAR * skin;
		}values;
		class _IMG{
			public:
			_IMG(){
				traymenu_icons = _T("IMG:traymenu_icons");
			}
			const TCHAR * traymenu_icons;
		}IMG;
		class _PNG{
			public:
			_PNG(){
				PNG_SHADOW = _T("PNG:PNG_SHADOW");
				IDB_PNG_SB = _T("PNG:IDB_PNG_SB");
				PNG_VSCROLL = _T("PNG:PNG_VSCROLL");
				PNG_COMMON_CLOSE = _T("PNG:PNG_COMMON_CLOSE");
				PNG_COMMON_MIN = _T("PNG:PNG_COMMON_MIN");
				PNG_COMMON_MAX = _T("PNG:PNG_COMMON_MAX");
				PNG_COMMON_RESTORE = _T("PNG:PNG_COMMON_RESTORE");
				PNG_DEFAULELOGO_48 = _T("PNG:PNG_DEFAULELOGO_48");
				PNG_SEARCH = _T("PNG:PNG_SEARCH");
				PNG_SEARCHCANCEL = _T("PNG:PNG_SEARCHCANCEL");
				PNG_LASTTALK_NULL = _T("PNG:PNG_LASTTALK_NULL");
				PNG_SEARCH_NULL = _T("PNG:PNG_SEARCH_NULL");
				PNG_MALE32 = _T("PNG:PNG_MALE32");
				PNG_MALE48 = _T("PNG:PNG_MALE48");
				PNG_FEMALE32 = _T("PNG:PNG_FEMALE32");
				PNG_FEMALE48 = _T("PNG:PNG_FEMALE48");
			}
			const TCHAR * PNG_SHADOW;
			const TCHAR * IDB_PNG_SB;
			const TCHAR * PNG_VSCROLL;
			const TCHAR * PNG_COMMON_CLOSE;
			const TCHAR * PNG_COMMON_MIN;
			const TCHAR * PNG_COMMON_MAX;
			const TCHAR * PNG_COMMON_RESTORE;
			const TCHAR * PNG_DEFAULELOGO_48;
			const TCHAR * PNG_SEARCH;
			const TCHAR * PNG_SEARCHCANCEL;
			const TCHAR * PNG_LASTTALK_NULL;
			const TCHAR * PNG_SEARCH_NULL;
			const TCHAR * PNG_MALE32;
			const TCHAR * PNG_MALE48;
			const TCHAR * PNG_FEMALE32;
			const TCHAR * PNG_FEMALE48;
		}PNG;
		class _ICON{
			public:
			_ICON(){
				ICON_LOGO = _T("ICON:ICON_LOGO");
			}
			const TCHAR * ICON_LOGO;
		}ICON;
		class _SMENU{
			public:
			_SMENU(){
				menu_tray = _T("SMENU:menu_tray");
			}
			const TCHAR * menu_tray;
		}SMENU;
	};
	const SNamedID::NAMEDVALUE namedXmlID[]={
		{L"_name_start",65535},
		{L"attrbar",65558},
		{L"btn_arrow",65549},
		{L"btn_bigdot",65565},
		{L"btn_c1",65568},
		{L"btn_c10",65577},
		{L"btn_c11",65578},
		{L"btn_c12",65579},
		{L"btn_c13",65580},
		{L"btn_c14",65581},
		{L"btn_c15",65582},
		{L"btn_c16",65583},
		{L"btn_c17",65584},
		{L"btn_c18",65585},
		{L"btn_c19",65586},
		{L"btn_c2",65569},
		{L"btn_c20",65587},
		{L"btn_c3",65570},
		{L"btn_c4",65571},
		{L"btn_c5",65572},
		{L"btn_c6",65573},
		{L"btn_c7",65574},
		{L"btn_c8",65575},
		{L"btn_c9",65576},
		{L"btn_cancel",65556},
		{L"btn_close",65536},
		{L"btn_copy",65554},
		{L"btn_doodle",65550},
		{L"btn_ellipse",65548},
		{L"btn_finish",65557},
		{L"btn_mask",65551},
		{L"btn_max",65537},
		{L"btn_middledot",65564},
		{L"btn_min",65539},
		{L"btn_rect",65547},
		{L"btn_restore",65538},
		{L"btn_revoke",65553},
		{L"btn_save",65555},
		{L"btn_smalldot",65563},
		{L"btn_word",65552},
		{L"cbx_wordsize",65561},
		{L"face",65591},
		{L"hr",65589},
		{L"img_logo",65540},
		{L"left_tab",65543},
		{L"name",65590},
		{L"operate_bar",65546},
		{L"other_attrbar",65562},
		{L"search_cancel",65542},
		{L"search_edit",65541},
		{L"selected_color",65567},
		{L"selected_window",65566},
		{L"snapshot",65544},
		{L"text_title",65545},
		{L"tv_Friend",65588},
		{L"word_attrbar",65559},
		{L"word_sign",65560}		};
	class _R{
	public:
		class _name{
		public:
		_name(){
			_name_start = namedXmlID[0].strName;
			attrbar = namedXmlID[1].strName;
			btn_arrow = namedXmlID[2].strName;
			btn_bigdot = namedXmlID[3].strName;
			btn_c1 = namedXmlID[4].strName;
			btn_c10 = namedXmlID[5].strName;
			btn_c11 = namedXmlID[6].strName;
			btn_c12 = namedXmlID[7].strName;
			btn_c13 = namedXmlID[8].strName;
			btn_c14 = namedXmlID[9].strName;
			btn_c15 = namedXmlID[10].strName;
			btn_c16 = namedXmlID[11].strName;
			btn_c17 = namedXmlID[12].strName;
			btn_c18 = namedXmlID[13].strName;
			btn_c19 = namedXmlID[14].strName;
			btn_c2 = namedXmlID[15].strName;
			btn_c20 = namedXmlID[16].strName;
			btn_c3 = namedXmlID[17].strName;
			btn_c4 = namedXmlID[18].strName;
			btn_c5 = namedXmlID[19].strName;
			btn_c6 = namedXmlID[20].strName;
			btn_c7 = namedXmlID[21].strName;
			btn_c8 = namedXmlID[22].strName;
			btn_c9 = namedXmlID[23].strName;
			btn_cancel = namedXmlID[24].strName;
			btn_close = namedXmlID[25].strName;
			btn_copy = namedXmlID[26].strName;
			btn_doodle = namedXmlID[27].strName;
			btn_ellipse = namedXmlID[28].strName;
			btn_finish = namedXmlID[29].strName;
			btn_mask = namedXmlID[30].strName;
			btn_max = namedXmlID[31].strName;
			btn_middledot = namedXmlID[32].strName;
			btn_min = namedXmlID[33].strName;
			btn_rect = namedXmlID[34].strName;
			btn_restore = namedXmlID[35].strName;
			btn_revoke = namedXmlID[36].strName;
			btn_save = namedXmlID[37].strName;
			btn_smalldot = namedXmlID[38].strName;
			btn_word = namedXmlID[39].strName;
			cbx_wordsize = namedXmlID[40].strName;
			face = namedXmlID[41].strName;
			hr = namedXmlID[42].strName;
			img_logo = namedXmlID[43].strName;
			left_tab = namedXmlID[44].strName;
			name = namedXmlID[45].strName;
			operate_bar = namedXmlID[46].strName;
			other_attrbar = namedXmlID[47].strName;
			search_cancel = namedXmlID[48].strName;
			search_edit = namedXmlID[49].strName;
			selected_color = namedXmlID[50].strName;
			selected_window = namedXmlID[51].strName;
			snapshot = namedXmlID[52].strName;
			text_title = namedXmlID[53].strName;
			tv_Friend = namedXmlID[54].strName;
			word_attrbar = namedXmlID[55].strName;
			word_sign = namedXmlID[56].strName;
		}
		 const wchar_t * _name_start;
		 const wchar_t * attrbar;
		 const wchar_t * btn_arrow;
		 const wchar_t * btn_bigdot;
		 const wchar_t * btn_c1;
		 const wchar_t * btn_c10;
		 const wchar_t * btn_c11;
		 const wchar_t * btn_c12;
		 const wchar_t * btn_c13;
		 const wchar_t * btn_c14;
		 const wchar_t * btn_c15;
		 const wchar_t * btn_c16;
		 const wchar_t * btn_c17;
		 const wchar_t * btn_c18;
		 const wchar_t * btn_c19;
		 const wchar_t * btn_c2;
		 const wchar_t * btn_c20;
		 const wchar_t * btn_c3;
		 const wchar_t * btn_c4;
		 const wchar_t * btn_c5;
		 const wchar_t * btn_c6;
		 const wchar_t * btn_c7;
		 const wchar_t * btn_c8;
		 const wchar_t * btn_c9;
		 const wchar_t * btn_cancel;
		 const wchar_t * btn_close;
		 const wchar_t * btn_copy;
		 const wchar_t * btn_doodle;
		 const wchar_t * btn_ellipse;
		 const wchar_t * btn_finish;
		 const wchar_t * btn_mask;
		 const wchar_t * btn_max;
		 const wchar_t * btn_middledot;
		 const wchar_t * btn_min;
		 const wchar_t * btn_rect;
		 const wchar_t * btn_restore;
		 const wchar_t * btn_revoke;
		 const wchar_t * btn_save;
		 const wchar_t * btn_smalldot;
		 const wchar_t * btn_word;
		 const wchar_t * cbx_wordsize;
		 const wchar_t * face;
		 const wchar_t * hr;
		 const wchar_t * img_logo;
		 const wchar_t * left_tab;
		 const wchar_t * name;
		 const wchar_t * operate_bar;
		 const wchar_t * other_attrbar;
		 const wchar_t * search_cancel;
		 const wchar_t * search_edit;
		 const wchar_t * selected_color;
		 const wchar_t * selected_window;
		 const wchar_t * snapshot;
		 const wchar_t * text_title;
		 const wchar_t * tv_Friend;
		 const wchar_t * word_attrbar;
		 const wchar_t * word_sign;
		}name;

		class _id{
		public:
		const static int _name_start	=	65535;
		const static int attrbar	=	65558;
		const static int btn_arrow	=	65549;
		const static int btn_bigdot	=	65565;
		const static int btn_c1	=	65568;
		const static int btn_c10	=	65577;
		const static int btn_c11	=	65578;
		const static int btn_c12	=	65579;
		const static int btn_c13	=	65580;
		const static int btn_c14	=	65581;
		const static int btn_c15	=	65582;
		const static int btn_c16	=	65583;
		const static int btn_c17	=	65584;
		const static int btn_c18	=	65585;
		const static int btn_c19	=	65586;
		const static int btn_c2	=	65569;
		const static int btn_c20	=	65587;
		const static int btn_c3	=	65570;
		const static int btn_c4	=	65571;
		const static int btn_c5	=	65572;
		const static int btn_c6	=	65573;
		const static int btn_c7	=	65574;
		const static int btn_c8	=	65575;
		const static int btn_c9	=	65576;
		const static int btn_cancel	=	65556;
		const static int btn_close	=	65536;
		const static int btn_copy	=	65554;
		const static int btn_doodle	=	65550;
		const static int btn_ellipse	=	65548;
		const static int btn_finish	=	65557;
		const static int btn_mask	=	65551;
		const static int btn_max	=	65537;
		const static int btn_middledot	=	65564;
		const static int btn_min	=	65539;
		const static int btn_rect	=	65547;
		const static int btn_restore	=	65538;
		const static int btn_revoke	=	65553;
		const static int btn_save	=	65555;
		const static int btn_smalldot	=	65563;
		const static int btn_word	=	65552;
		const static int cbx_wordsize	=	65561;
		const static int face	=	65591;
		const static int hr	=	65589;
		const static int img_logo	=	65540;
		const static int left_tab	=	65543;
		const static int name	=	65590;
		const static int operate_bar	=	65546;
		const static int other_attrbar	=	65562;
		const static int search_cancel	=	65542;
		const static int search_edit	=	65541;
		const static int selected_color	=	65567;
		const static int selected_window	=	65566;
		const static int snapshot	=	65544;
		const static int text_title	=	65545;
		const static int tv_Friend	=	65588;
		const static int word_attrbar	=	65559;
		const static int word_sign	=	65560;
		}id;

		class _string{
		public:
		const static int title	=	0;
		const static int ver	=	1;
		}string;

		class _color{
		public:
		const static int blue	=	0;
		const static int gray	=	1;
		const static int green	=	2;
		const static int red	=	3;
		const static int white	=	4;
		}color;

	};

#ifdef R_IN_CPP
	 extern const _R R;
	 extern const _UIRES UIRES;
#else
	 extern const __declspec(selectany) _R & R = _R();
	 extern const __declspec(selectany) _UIRES & UIRES = _UIRES();
#endif//R_IN_CPP
}
