// MNCSHAPI.H
// (C) Harry V. Nikolayev, Micro Lana Ltd, 1995, 1996.
// Modified by A.Sobolev 1997
//
#ifndef __MNCSHAPI_H
#define __MNCSHAPI_H

#ifndef __SLIB_H
#	include <slib.h>
#endif

typedef struct {
	ulong l;                   /* ����襥 ᫮�� */
	ulong h;                   /* ���襥 ᫮�� */
} LONG64;
/*
	������ ����� ⮢��/�த����� �࠭���樨
*/
typedef struct {
	short GI_bank;             /* # ����� */
	uchar GI_user;             /* # ����� */
	LONG64 GI_code;            /* ��� ⮢�� */
	/* == 0 - ᢮������ 業�; != 0 - ����������p�� # */
	LONG64 GI_weight;          /* ��� ⮢�� */
	/* > 0 - �p�����/�p������ � ᥪ��; < 0 - ����p��/��p�� �� ᥪ樨 */
	LONG64 GI_price;           /* 業� ⮢�� (�ᥣ�� > 0) */
	LONG64 GI_rate;            /* ���� ������ �� ������ �த��� */
	uchar GI_sign;             /* ��-�� ⮢�� */
	uchar GI_division;         /* �⤥� */
	uchar GI_taxes;            /* # ��� */
	uchar GI_group;            /* ��㯯� ⮢�� */
	uchar GI_buflen;           /* ����� ���� ����� */
	uchar GI_name[52];         /* ������������ ⮢�� */
} GOODSINFO;

typedef struct {
	short RB_bank;             /* # ����� */
	uchar RB_user;             /* # ����� */
	ulong RB_data;             /* asciz ��p��� ��p���� */
} RAWBARCODE;
/*
	������ p����� � ᪨����� � ����������
*/
typedef struct {
	short RI_bank;             /* # ����� */
	uchar RI_user;             /* # ����� */
	uchar RI_subtotal;         /* �p����� <����. ����> */
	LONG64 RI_code;            /* ��� ⮢�p� */
	/* == 0 - ��� ᢮������ 業�� ��� <����. ����>   */
	/* != 0 - ��� 㪠����� ⮢�p��                  */
	LONG64 RI_value;           /* ���祭�� ᪨���/�������� */
} RAISEINFO;
/*
	������ ���p��樨 �� ����� 祪�
*/
typedef struct {
	short TI_bank;             /* # ����� */
	uchar TI_user;             /* # ����� */
	uchar TI_operation;        /* ⨯ ���p�樨 */
	short TI_ticket;           /* # 祪� */
	LONG64 TI_payment0;        /* ����� 0 */
	LONG64 TI_payment1;        /* ����� 1 */
	LONG64 TI_payment2;        /* ����� 2 */
	LONG64 TI_payment3;        /* ����� 3 */
	LONG64 TI_return0;         /* ����p�� 0 */
	LONG64 TI_return1;         /* ����p�� 1 */
	LONG64 TI_return2;         /* ����p�� 2 */
	LONG64 TI_return3;         /* ����p�� 3 */
} TICKETINFO;
/*
	Cash device keyboard codes
*/
#define _KEY_DIGIT0   0x0000
#define _KEY_DIGIT1   0x0001
#define _KEY_DIGIT2   0x0002
#define _KEY_DIGIT3   0x0003
#define _KEY_DIGIT4   0x0004
#define _KEY_DIGIT5   0x0005
#define _KEY_DIGIT6   0x0006
#define _KEY_DIGIT7   0x0007
#define _KEY_DIGIT8   0x0008
#define _KEY_DIGIT9   0x0009
#define _KEY_DIGIT00  0x000A
#define _KEY_PERIOD   0x000B
#define _KEY_PAPERUP  0x000C
#define _KEY_RESET    0x000D
#define _KEY_TOTAL    0x000E
#define _KEY_I        0x000F
#define _KEY_II       0x0010
#define _KEY_III      0x0011
#define _KEY_MUL      0x0012
#define _KEY_REPEAT   0x0013
#define _KEY_STORNO   0x0014
#define _KEY_TAXES    0x0015
#define _KEY_HOUR     0x0016
#define _KEY_SUBTOTAL 0x0017
#define _KEY_ARTICLE  0x0018
#define _KEY_BANKNUM  0x0019
#define _KEY_PLUS     0x001A
#define _KEY_MINUS    0x001B
#define _KEY_SECT1    0x001C
#define _KEY_SECT2    0x001D
#define _KEY_SECT3    0x001E
#define _KEY_SECT4    0x001F
#define _KEY_SECT5    0x0020
#define _KEY_SECT6    0x0021
#define _KEY_SECT7    0x0022
#define _KEY_SECT8    0x0023
#define _KEY_SECT9    0x0024
#define _KEY_SECT10   0x0025
/*
	Cash device keyboard key position
*/
#define _KEY_WORK     0x0000
#define _KEY_READ     0x0100
#define _KEY_ERASE    0x0200
#define _KEY_PROGRAMM 0x0300
/*
	����ﭨ� �믮������ �࠭���樨
*/
#define TR_UNKNOWN     0       /* ����।����� */
#define TR_RXREQUEST   1       /* �ਭ�� ����� �� ���ଠ�� �� ⮢��� */
#define TR_SENTACK     2       /* ����� ������� � ����稨 */
#define TR_SENTNAK     3       /* ����� ��������� */
#define TR_FINISHSALES 4       /* �࠭����� �த���/������ �����襭� */
#define TR_ENDOFTICKET 5       /* ����� 祪� */
/*
	���� ���⮢ � ��襭���
*/
typedef enum {
	DaylyReport = 1,           /* ������� 䨭��ᮢ� */
	OperatorsReport = 2,       /* ���� ����஢ */
	WareReport = 3             /* ���� �� ⮢�ࠬ */
} REPORT_TYPE;
/*
	���ଠ�� �� �ࠩ���� MnCash
*/
typedef struct {
	uchar mi_pid;              /* �����䨪��� ����� */
	uchar mi_major;            /* ����� ���ᨨ �ࠩ��� */
	uchar mi_minor;            /* ����� ���४樨 �ࠩ��� */
	uchar mi_usedIRQ;          /* ���-�� �ᯮ��㥬�� IRQ */
	uchar mi_maxIRQ;           /* ���ᨬ��쭮� ���-�� IRQ */
	uchar mi_usedChannels;     /* ���-�� �ᯮ��㥬�� ������� */
	uchar mi_maxChannels;      /* ���ᨬ��쭮� ���-�� ������� */
	uchar mi_connectAPI;       /* ������ ���墠� ����ᮢ ������祭� */
} MNCASH_INFO;
/*
	������� ���ᠭ�� 䨧��᪨� �ࠪ���⨪ ������
*/
typedef struct {
	ulong mp_baud;             /* ������� ������ */
	uchar mp_mode;             /* ����� ࠡ��� */
	uchar mp_sout;             /* ��室�� ᨣ���� */
	uchar mp_stxin;            /* �᫮��� ࠧ�襭�� ��।�� */
} MNCASH_PCHANNEL;
/*
	���ଠ�� �� ⥪�饬� ���ﭨ� ���ᮢ��� ������
*/
typedef struct {
	uchar mb_drvState;         /* ����ﭨ� �ࠩ��� */
	uchar mb_cmdState;         /* ����ﭨ� �믮��塞�� ������� */
	uint  mb_bank;             /* ����� ���ᮢ��� ������ */
	uchar mb_user;             /* ����� ⥪�饣� ����� */
	uchar mb_section;          /* ����� ⥪�饩 ᥪ樨 */
	ulong mb_rate;             /* ����騩 ���� ������ */
	ulong mb_goods;            /* ��� ��᫥����� ⮢�� */
	long  mb_price;            /* ���� ��᫥����� ⮢�� */
	long  mb_weight;           /* ���-�� ��᫥����� ⮢�� */
	long  mb_raise;            /* ��᫥���� ᪨��� ��� �������� */
	uint  mb_ticket;           /* ����� ��᫥����� �����⮣� 祪� */
	long  mb_payment[4];       /* ��᫥���� �ᯮ�짮����� ������ */
	long  mb_surrender;        /* ��᫥���� ���祭�� ᤠ� */
} MNCASH_BANKINFO;
/*
	������� ����⥫� ��ࠬ��஢ ᥪ樨

	�� ����� � �⮩ ������� ������ ���� � ���� �ନ������ ASCII-�����
	(��� ��ப - ��� �������饣� �㫥���� ᨬ���� � ���� ��ப�!).
	��� �����᪨� ���祭�� ��� '0' (30h) ����砥� "���", � ��� "1" (31h)
	����砥� "��". �� �᫮�� ���祭�� ������ ���� ⠪�� �।�⠢����
	� ���� ASCII-��ப, ����� ����樨 � ����� ��� ��ப� ������ ����
	��������� ����� "0" (30h). ���ਬ��, ��ப� "0123" (30h 31h 32h 33h)
	���� ��������⮬ �����筮�� �᫠ 123. �᫨ �᫮ �����
	�������� ��� (�� ������ �ᥣ�� 䨪�஢���), � ��� � ��
	�⠢����, � ���ࠧ㬥������ � ����ᨬ��� �� ⨯� ����. ���, ����
	������⢠ (���) ⮢�� �ᥣ�� ����� �� �������� ����� ��᫥
	�窨, ���⮬� ��ப� "123000" (31h 32h 33h 30h 30h 30h) ����砥�
	���� 123 ��㪨, ���� 123 �����ࠬ�� ⮢��.
*/
typedef struct {
	uchar s_taxes;             /* �ਧ��� ����� ���᫥��� ��� */
	uchar s_singleTransaction; /* �ਧ��� ࠧ�襭�� �����筮� �࠭���樨 */
	uchar s_duty;              /* �롮� �⠢�� ��� */
	uchar s_group;             /* ����� ⮢�୮� ��㯯� */
	uchar s_name[12];          /* ������������ ᥪ樨 */
	uchar s_cash[8];           /* ��������� 業� ᥪ樨 */
} SECTION;
/*
	������� ��易⥫쭮� ��� ��ࠬ��஢ ���ᮢ��� ������

	�� ����� � �⮩ ������� ������ ���� � ���� �ନ������ ASCII-�����
	(��� ��ப - ��� �������饣� �㫥���� ᨬ���� � ���� ��ப�!).
	��� �����᪨� ���祭�� ��� '0' (30h) ����砥� "���", � ��� "1" (31h)
	����砥� "��". �� �᫮�� ���祭�� ������ ���� ⠪�� �।�⠢����
	� ���� ASCII-��ப, ����� ����樨 � ����� ��� ��ப� ������ ����
	��������� ����� "0" (30h). ���ਬ��, ��ப� "0123" (30h 31h 32h 33h)
	���� ��������⮬ �����筮�� �᫠ 123. �᫨ �᫮ �����
	�������� ��� (�� ������ �ᥣ�� 䨪�஢���), � ��� � ��
	�⠢����, � ���ࠧ㬥������ � ����ᨬ��� �� ⨯� ����. ���, ����
	������⢠ (���) ⮢�� �ᥣ�� ����� �� �������� ����� ��᫥
	�窨, ���⮬� ��ப� "123000" (31h 32h 33h 30h 30h 30h) ����砥�
	���� 123 ��㪨, ���� 123 �����ࠬ�� ⮢��.
*/
typedef struct {
	ushort bp_actualSize;      /* ��騩 ࠧ��� ������ � ����� */
	uchar bp_p1;               /* ��䠢��: "0" - ���, "1"-���, "2" - ᬥ蠭�� */
	uchar bp_p2;               /* ���. ������ ����砭� ("1" = ��) */
	uchar bp_p3;               /* ����� (�.�. "0") */
	uchar bp_p4;               /* �������� 業� � ��� ("1" = ��) */
	uchar bp_p5;               /* ���᫥��� ��� ��� ᪨��� � �������� ("1" = ��) */
	uchar bp_p6;               /* ������ ����� ("1" = ��) */
	uchar bp_p7;               /* ��易⥫�� ���� ����祭��� ����� ("1" = ��) */
	uchar bp_p8;               /* ����� �஬����筮� �㬬� ����饭� ("1" = ��) */
	uchar bp_p9;               /* ������/�������� ��� �஬. �㬬�� ����饭� ("1" = ��) */
	uchar bp_p10;              /* ����஫� �����஢�� ᥩ� ("1" = ��) */
	uchar bp_p11;              /* ����� ⮢�஢ � �⤥��� ("0" - ���, "1" - ���) */
	uchar bp_p12;              /* ����� ���祭�� ��� ��᫥ ���� ࠧ�襭� ("1" = ��) */
	uchar bp_p13;              /* ��� ����䥩� ("0" - ��⮭��, "1" - ��, "2" - RS232) */
	uchar bp_p14;              /* ����� �裡 � ��� ("0" - ��� ����, "1" - �� �६�) */
	uchar bp_p15;              /* ����� ������ 祪�� ���㯠⥫� ࠧ�襭� ("1" = ��) */
	uchar bp_p16;              /* ����� ���� �� ����஫쭮� ���� ࠧ�襭� ("1" = ��) */
	uchar bp_p17;              /* ���-�� ��ப � ���� (�ᥣ�� "6") */
	uchar bp_p18;              /* ������ �����筮� �窨 � 業�� ("1" = "x", "2" = "x.y" "3" = "x.yy") */
	uchar bp_p19;              /* ��� �����஭��� ��ᮢ */
	uchar bp_p20;              /* ���뢠⥫� ���-����� ������祭 ("1" = ��) */
	uchar bp_p21a[3];          /* �᫮��� ���� ॣ���஢ �⤥��� � ⮢�஢ */
	uchar bp_p21b[8];          /* HALO - ����. ᢮������ 業� �⤥�� */
	uchar bp_p22[3];           /* ����� � �����襩 <��> */
	uchar bp_p23[23][2];       /* ����� � ��������ன */
	uchar bp_p24[2];           /* ����� � ����ࠬ� */
	uchar bp_p25[3][4];        /* �⠢�� ��� */
	uchar bp_p26[2][4];        /* ��業⭠� �⠢�� ᪨��� � �������� */
	uchar bp_p27[3][4];        /* ������ �����樥�� */
	uchar bp_p28[4][4];        /* ���� ����஢ */
	uchar bp_p29[8][8];        /* ��ᮢ� ��ਮ�� */
	uchar bp_p30[6][18];       /* ����� ���� */
	uchar bp_p31[4][8];        /* ����� ����஢ */
	uchar bp_p32[3][12];       /* ������������ ����� I, II � III */
	uchar bp_xz[12];           /* "���������   " */
	SECTION bp_p33[10];        /* ����⥫� ᥪ権 */
} BANKPARM;
/*
	����⥫� ����७��� (�ணࠬ���㥬��) ⮢�஢

	�� ����� � �⮩ ������� ������ ���� � ���� �ନ������ ASCII-�����
	(��� ��ப - ��� �������饣� �㫥���� ᨬ���� � ���� ��ப�!).
	��� �����᪨� ���祭�� ��� '0' (30h) ����砥� "���", � ��� "1" (31h)
	����砥� "��". �� �᫮�� ���祭�� ������ ���� ⠪�� �।�⠢����
	� ���� ASCII-��ப, ����� ����樨 � ����� ��� ��ப� ������ ����
	��������� ����� "0" (30h). ���ਬ��, ��ப� "0123" (30h 31h 32h 33h)
	���� ��������⮬ �����筮�� �᫠ 123. �᫨ �᫮ �����
	�������� ��� (�� ������ �ᥣ�� 䨪�஢���), � ��� � ��
	�⠢����, � ���ࠧ㬥������ � ����ᨬ��� �� ⨯� ����. ���, ����
	������⢠ (���) ⮢�� �ᥣ�� ����� �� �������� ����� ��᫥
	�窨, ���⮬� ��ப� "123000" (31h 32h 33h 30h 30h 30h) ����砥�
	���� 123 ��㪨, ���� 123 �����ࠬ�� ⮢��.
*/
typedef struct {
	uchar ig_code[4];          /* ��� ⮢�� ASCII */
	uchar ig_sign;             /* �p-�� ⮢�p� */
	uchar ig_division;         /* �⤥� */
	uchar ig_taxes;            /* N ��� */
	uchar ig_group;            /* �p㯯� ⮢�p� */
	uchar ig_name[12];         /* ASCII ��� ⮢�p� */
	uchar ig_price[8];         /* ASCII 業� ⮢�p� */
} INTERNALGOODS;
/*
	��p����p� ����p�樨 �p����p�
*/
#define DPG_ONLY_PRINTER 0x0080 /* ���쪮 祪��� �p���p */
#define DPG_NETWORK      0x0040 /* ��⥢�� ��p�� */
#define DPG_SYSDRIVER    0x0008 /* ���⥬�� �p����p ���p���⢠ */
/*
	��।������ ���⨯�� �㭪権
*/
#ifdef __cplusplus
extern "C" {
#endif

MNCASH_INFO* mcGetInfo(void);
int  mnUnload();
int  mcGetPhSettings(int cn,MNCASH_PCHANNEL far* p);
int  mcSetPhSettings(int cn,MNCASH_PCHANNEL far* p);
int  mcOpenChannel(int cn,ulong dollar);
int  mcCloseChannel(int cn);
int  mcRunChannel(int cn,int bank);
char far* mcCfgFile();
ulong mcGetCashIndex(int cn,uint* prec);
int  mcSetCashIndex(int cn,ulong dollar,uint prec);
int  mcGetBankInformation(int cn,MNCASH_BANKINFO* p);
int  mcGetBankState(int cn, uint* bnptr, uint* onptr, uint* tnptr, uint* dsptr, uint* tsptr);
int  mcGetCommandState(int cn);
int  mcSetDateAndTime(int cn);
int  mcReport(int cn, REPORT_TYPE report);
int  mcAccumulation(int cn,int sec,long cash);
int  mcPrintCheck(int cn,int ctype);
int  mcRequestSettings(int cn);
int  mcSetupParmBuffer(int cn, BANKPARM* buf, uint extra);
int  mcSetupBank(int cn);
void mcSetAlarm();
void mcResetAlarm();
int  mcSimulateKeyboard(int cn,int aKey);
int  mcConnectAPI();
int  mcDisconnectAPI();
int  mcWaitCmdFinished(int unit,ulong tmo);
int  mcSaleGoods(uint unit, ulong code, uint sec, long price, char* name);
int  mcIncasso(uint unit,long money,int type);
int  mcCloseTicket(uint unit, long payment0, long payment1, long payment2, long payment3);
void mcIdle(void);

#ifdef __cplusplus
}
#endif

#endif /* __MNCSHAPI_H */
