// PF.H
// Copyright (c) A.Sobolev 2000-2002
//
// Definitions for remix of PlanFlex Project
//
#ifndef __PF_H
#define __PF_H

#ifndef __SLIB_H
	#include <slib.h>
#endif

#define FALSE       0
#define TRUE        1
#define RIGHT       0
#define LEFT        1
#define FULL        2
#define NOTNEEDED   0
#define CURR_TYPE   1
#define NEXT_TYPE   2
#define MAXMULT    20
#define PRECISION   5 // ��筮��� �।�⠢����� ������ ���祭��, �

typedef long PFID;
typedef long HEQUIP;
//
//
//
class  CDFile;
class  CuttDg;
struct CuttDgRec;
class  EquipVect;
class  LogSpcVect;
class  EquipRowVect;
class  BoardSpcVect;
class  TechLimitsVect;
class  CuttingDiagram;
class  HardCDCollection;
class  ProtoDiagramQueue;
class  CuttingDiagramCollection;
class  LogItem;
class  ProtoDiagram;
class  SzCluster;
class  CuttDgGenerator;
class  HardCDEntry;
class  ProtoDiagram;
class  BoardSpcVect;
struct GenExtra;
class  VisiLumber;
//
//
//
double SQ(double a) { return (a*a); }
double defVolumeFunc(PFID breedID, double, double);
char * cd2str(ProtoDiagram*, char*, int, int = 0);

typedef TSArray <double> RealArray;

DECL_CMPFUNC(double);
//
// Tokens
//
enum {                  // ���� �ࠢ�����
	rvEqual = 0x0001,
	rvLess  = 0x0002,
	rvGreat = 0x0004,
};
//
// ������� ��ࠡ�⪨ ᨭ⠪��᪨� ��ࠦ����
//
struct TokenVect {
	int    tCount;      // ������⢮ ���ᥬ
	int    nCount;      // ������⢮ �ᥫ
	int    tVect[64];   // ���᮪ ���ᥬ
	double nVect[32];   // ���᮪ �ᥫ
};
//
// ������� �஢�ન ���४⭮�� ��ࠦ����
//
struct ValidTokenTemplate {
	int  * vtokens;     // ���ᨢ �����⨬�� ���ᥬ
	int    numvtokens;  // ������⢮ �����⨬�� ���ᥬ
	RealRange bounds;   // �࠭��� �।�⠢����� �ᥫ
};

struct ErrLoc {         // ��������� �訡�� � ��ப� �����
	int    begChar;
	int    endChar;
};
//
// ���ᥬ�
//
enum {
	lexError = -1,       // �訡�筠� ���ᥬ�
	lexDelim =  0,       // �������⥫�
	lexAsterisk,         // ������窠 ( "*"  )
	lexDoubleDot,        // ��� �窨 ( ".." )
	lexLE,               // <=
	lexGE,               // >=
	lexEQ,               // =
	lexLT,               // <
	lexGT,               // >
	lexNum,              // ��᫮
	lexEOL,              // ����� ��ப� ( '\0' ��� '\n' )
	firstSign    = 0,    // ���� ����
	lastSign     = 7,    // ��᫥���� ����
	firstCmpSign = 2,    // ���� ���� �ࠢ�����
	lastCmpSign  = 7     // ��᫥���� ���� �ࠢ�����
};
//
// ���� ������� ���⠢�
//
const
	stMain     = 0x0100, // �᭮���� ��᪠
	stSide     = 0x0200, // ���᭮���� ��᪠
	stCenter   = 0x0500, // ����ࠫ쭮� ���� ���⠢�  (����砥� stMain)
	stPith     = 0x0800,
	stCntr     = 0x1000,
	stSawLog   = 0,      // �ॢ��
	stDETimber = 1,      // ���媠��� ����
	stSQBoard  = 2,      // ��१��� ��᪠
	stUEBoard  = 3,      // ����१��� ��᪠
	stSlab     = 4,      // �����
	stEdging   = 5,      // �����
	stChip     = 6,      // ����
	stNumber   = 7,      // ������⢮ ⨯�� ������⮢ ���⠢�
	bpNumber   = 3,      // ������⢮ ⨯�� ���� � ���⠢�
	MaxLevels  = 4;      // ���ᨬ��쭮� �᫮ �஢��� �ᯨ�����
//
//
//
class Sawlog {
public:
	SLAPI  Sawlog(PFID breedID, double aDiam, double aLen);
	SLAPI  Sawlog(const Sawlog &);
	void   SLAPI Init(PFID breedID, double aDiam, double aLen);
	void   SLAPI Init(double aDiam, double aLen);
	void   SLAPI SetVolumeFunc(double (*)(PFID,double,double));

	PFID   SLAPI GetBreedID() { return BreedID;  }
	double SLAPI GetDiameter() { return D0; }
	double SLAPI GetLength() { return L; }
	double SLAPI GetVolume() { return V; }

	double SLAPI Diameter(double len);
	double SLAPI Taper();
	double SLAPI MinPith();
	double SLAPI MinCntr();
protected:
	void   SLAPI Evaluate();
	double SLAPI ParaWidth(double A);
	double SLAPI ParaLen(double A);
	double SLAPI SqLen(double A, double width);
	double SLAPI SqWidth(double A, double len);

	PFID   BreedID;
	double D0;
	double L;
	double V;
	double P;

	static double (*volumeFunc)(PFID, double, double);
};
//
//
//
class AbstractLumber {
public:
	SLAPI  AbstractLumber();
	SLAPI  AbstractLumber(const AbstractLumber &);
	int    SLAPI IsBoard() const;
	int    SLAPI IsSawLog() const;
	int    SLAPI IsBadLumber() const;
	int    SLAPI IsGoodLumber() const;
	int    SLAPI IsCenter() const;

	ushort LumberKind; // ��� �������ਠ��
};
//
// ������� ��⮯��⠢�
//
struct ProtoDiagramItem : public AbstractLumber {
	SLAPI  ProtoDiagramItem();
	SLAPI ~ProtoDiagramItem();
	int    Item;      // ����� ᮮ⢥�����饣� ������� � ����ࠬ��
	double OuterCutt; // ���譨� �१
	double InnerCutt; // ����७��� �१
	double NmnlSize;  // ��������� ࠧ���
	uint16 SType;     // ��� ࠧ���
	ProtoDiagramQueue * P_Cluster; // ������騩 ��室
};
//
// ��।� ��⮯��⠢�� (����� �ᯮ�짮���� ��� ������ ��������)
//
class ProtoDiagramQueue : public SQueue {
public:
	SLAPI  ProtoDiagramQueue();
	int    SLAPI put(const ProtoDiagram *);
	ProtoDiagram * SLAPI get() const;
	ProtoDiagram * SLAPI peek() const;
private:
	virtual void SLAPI freeItem(void*);
};
//
// ��室�� ������� ��� �ᯨ�����
//
class SourceLumber : public AbstractLumber, public Sawlog {
public:
	SLAPI  SourceLumber(const Sawlog &);
	SLAPI  SourceLumber(const SourceLumber&, const ProtoDiagramItem&);
	double SLAPI Scope(double minLen, double minWidth);
	double SLAPI Width2length(double, RealRange&, double, double);
	void   SLAPI InscribedLengthes(RealRange&, double&, double&);
	int    SLAPI InscribedSizes(SArray&, SzCluster*, double);

	double Voc;  // ���⨪���� ���譨� �१
	double Vic;  // ���⨪���� ����७��� �१
	double Hrc;  // �ࠢ� �१
	double Hlc;  // ���� �१
	double Size; // ��������� ࠧ���
};
//
// ������� ��ࠬ���� �������� GenTemplateItem
//
struct SizeParams {
	double Sz;    // ��������� ࠧ���, �
	double RawSz; // ������ � �ਯ�᪮� �� �����, �
	double Scope; // ������� ���ᠭ�� �� 業�� �ॢ��, �
};

DECL_CMPFUNC(SizeParams); // �� �뢠��� SizeParams::Sz
//
// VisiLumber
//
const size_t
	maxSizeStr = 42,
	maxMultStr =  6;

class VisiLumber : public AbstractLumber {
public:
	SLAPI  VisiLumber();
	SLAPI  VisiLumber(const VisiLumber &);
	int    SLAPI Merge(VisiLumber *);
	int    SLAPI SizType(); // �����頥� �ନ�㥬� ࠧ��� ( szXXX )

	char   MultStr[maxMultStr]; // �����⥫�
	char   SizeStr[maxSizeStr]; // ���᮪ ���������� ࠧ��஢
	CuttDg * P_Owner; // ��������
	CuttDg * P_Diagr; // �奬� ����
};
//
// CuttDg
//
class CuttDg : public SCollection {
public:
	CuttDg(VisiLumber *);
	CuttDg(CuttDg &);
	VisiLumber * at(uint);
	int    FindCenter(uint &);
	int    IsSymmetric() const;

	HEQUIP EquipID;   // ��ᮯ���� �⠭��
	uint   Type;      // ���������, ����஢����
	short  MaxBoards; // ����. �᫮ ��᮪
	VisiLumber * P_Source; // ��室�� ��⨬���
	// ��ꥪ� CuttDg �� ���� �������楬 ��ꥪ�
	// �� ����� 㪠�뢠�� P_Source
private:
	virtual	void SLAPI freeItem(void *);
};
//
// ������� 蠡���� GenTemplate
//
struct GenTemplateItem : public AbstractLumber {
	SLAPI  GenTemplateItem();

	TSArray <SizeParams> Sizes;  // ������� ��ࠬ����
	IntRange Mults;  // �������� �����⨬�� �����⥫��
	int    SType;    // ��� ࠧ��� (�ਭ�/⮫騭�)
	int    DItem;    // ����� ��ꥪ� VisiLumber � ������樨 CuttDg
	int    Locked;   // ���� �����஢�� (��� ����७���� ���짮�����)
};
//
// ������ ��� �����஢���� ���㯮�⠢��
// �ᯮ������ ����ᮬ Tracker
//
typedef TSCollection <GenTemplateItem> GenTemplate;
//
// ����� ���� state �������� TrackerItem
//
enum {
	tiTerminal = 0x0001,  // ��ନ����� (����� ��⠢���� ��祣�)
	tiCenter   = 0x0002   // ����ࠫ��  (� 業�� �ॢ�� ��� ����)
};
//
// ������� �४��
//
struct TrackerItem {
	int    Item;        // ������ 蠡���� � ��ꥪ� GenTemplate
	int    SizePtr;     // ������ ⥪�饣� ࠧ��� � 蠡����
	double Offset;      // �����ﭨ� �� �窨 ����� �� ���㦭�� �����
	uint   State;       // ���� ���ﭨ�
};
//
// �४�� - ������� ���㯮�⠢��
//
class Tracker : public SArray {
public:
	SLAPI  Tracker(CuttDgGenerator*, SourceLumber*, CuttDg*, int);
	SLAPI ~Tracker();
	int    SLAPI GenNext();
	int    SLAPI Direction() const { return Dir; }
	int    SLAPI IsEven() const { return Even; }
	void   SLAPI Restart(int aDir);
	double SLAPI Size(int) const;
	double SLAPI Ssize(int) const;
	double SLAPI Scope(int) const;
	TrackerItem & SLAPI at(uint i) const
	{
		return *(TrackerItem *)SArray::at(i);
	}
	GenTemplateItem & SLAPI Lumber(uint i) const
	{
		return *GenTmpl.at(at(i).Item);
	}
protected:
	int    SLAPI Init();
	void   SLAPI InitSizes(VisiLumber&, GenTemplateItem&);
	void   SLAPI InitMults(VisiLumber&, GenTemplateItem&);
	void   SLAPI InitScope(VisiLumber&, GenTemplateItem&);
	void   SLAPI Recalc();
	void   SLAPI Terminal(int);
	int    SLAPI IsTerminal() const;
	int    SLAPI InsertItem(int);
	int    SLAPI InsertNext();
	int    SLAPI EnumSizes();
	int    SLAPI InsertingNeeded() const;
	int    SLAPI CheckLimits();
	int    SLAPI NumIdentItems() const;
	int    SLAPI IsTherePlace(const GenTemplateItem &) const;
	double SLAPI MinSize(const GenTemplateItem &);
	double SLAPI MaxHight(const GenTemplateItem &) const;
	double SLAPI MinHight(const GenTemplateItem &) const;
	GenTemplateItem * SLAPI NextLumber(int currentLumber) const;
	GenTemplateItem & SLAPI Lumber() const { return Lumber(Current); }
private:
	int    Dir;                  // ���ࠢ����� �� 蠡���� (RIGHT | LEFT)
	int    Even;                 // != 0 �᫨ ���⠢ ���
	int    NoEven;               // != 0 �᫨ ����饭� ��� ���⠢�
	int    Current;              // ����騩 ������� �४��
	double SawWidth;             // ��ਭ� �ய���, �
	CuttDg          * P_Diagram;   // ������ ����
	SourceLumber    * P_Source;    // ��஦���騩 ������� ���孥�� �஢��
	CuttDgGenerator * P_Generator; // ��஦���騩 �������
	GenTemplate       GenTmpl;
};
//
// ��⮯��⠢
//
class ProtoDiagram : public SArray {
public:
	SLAPI  ProtoDiagram();
	SLAPI ~ProtoDiagram();
	ProtoDiagramItem & SLAPI at(uint);
	virtual void   SLAPI atFree(int);
	void   SLAPI freeAll();
	int    SLAPI Make(Tracker&);
	int    SLAPI Make(HardCDEntry*, double);
	int    SLAPI Make(ProtoDiagram &left, ProtoDiagram &right);
	void   SLAPI SetSymm(int b) { x_symm = b ? TRUE : FALSE; }
	int    SLAPI IsSymm() const { return x_symm; }
	int    SLAPI IsEven() const { return x_even; }
	int    SLAPI IsFull() const { return x_full; }
	friend int SLAPI operator == (ProtoDiagram &a, ProtoDiagram&b);
	int    x_hard;     // �ਧ��� ���⪮�� ���⠢�
	char * P_HardMark; // ������祭�� ���⪮�� ���⠢�
private:
	int    x_symm;   // �ਧ��� ᨬ����筮��
	int    x_even;   // �ਧ��� �⭮��
	int    x_full;   // �ਧ��� ������� (�� ���㯮�⠢)
};
//
// ������� ࠧ��୮� ��㯯� �ॢ��
//
struct LogItem {
	int  D;    // �������, ��
	int  L;    // �����, ��
	int  p;    // ���� � ��㯯�, �஬���� (0.1 %)
	int  base; // �ਧ��� �������� ������� ��� ����
};
//
// ������� ������ ᯥ���஢����� ࠧ��஢
//
struct SzEntry {
	double Sz;    // ��������� ࠧ���, �
	double RawSz; // ������ � �ਯ�᪮� �� �����, �
};

DECL_CMPFUNC(SzEntry);
//
// ������ ᯥ���஢����� ࠧ��஢
// ����ন� ��������� ࠧ��� � ������⢮ ᮮ⢥�������
// ��� ࠧ��஢ ��㣮�� ����७�� ��� ��ꥪ�� ⨯� SzEntry
// (���ਬ��: ᮤ�ন� ⮫騭� 0.075 � � ᮮ�������騥 �ਭ�
// 0.100, 0.150, 0.175, 0.200).
// ��� ������ ���� ������⮬ ��ꥪ� SpcSizes
//
class SzCluster : public SArray { // Ordered CMPFUNC(SzEntry)
public:
	SLAPI  SzCluster();
	SLAPI  SzCluster(SzCluster&);
	SzEntry & SLAPI at(uint idx);

	double Sz;    // ��������� ࠧ���, �
	double RawSz; // ������ � �ਯ�᪮� �� �����, �
};

DECL_CMPFUNC(SzCluster);
//
// ����䨪��� ࠧ��஢ ��᮪
// ��������� �� �����樨, � �� �����襭�� ࠧ��蠥���
// ��室��� ��� ᮧ����� ��ꥪ� SpcSizes ���� ��������
// BoardSpcCollection (�. �㭪�� CuttDgGenerator::initSizes)
//
typedef TSCollection <SzCluster> SpcSizes; // Ordered CMPFNC(SzCluster)
//
// ����饭��, ��।������ �㭪樨 �� �����
// CuttDgGenerator::indicator
//
const
	cdgHalfDiagReady  = 1,  // ������஢�� ���㯮�⠢
	cdgProtoDiagReady = 2,  // ������஢�� ����� ��⮯��⠢
	cdgDiagReady      = 3,  // ������஢�� ��⮢� ���⠢
	cdgNextLevel      = 4,  // �����ᨢ�� ���室 �� ᫥���騩 ��室
	cdgPrevLevel      = 5,  // ������ �� ४��ᨨ � �।��饬� �஢��
	cdgNewEquipRow    = 6,  // ��砫��� ��ࠡ�⪠ ����� �����
	cdgNewLogGroup    = 7,  // ��砫��� ��ࠡ�⪠ ����� ��㯯� �ॢ��
	cdgMkProtoDiag    = 8,  // ��砫� �����樨 ��⮯��⠢��
	cdgMkDiag         = 9,  // ��砫� ����� ��⮢�� ���⠢��
	cdgFinish         = 10, // �����襭�� ࠡ��� �������
	cdgAvlMemory      = 11, // ����稥 ����㯭�� �����
	cdgUserBreak      = 12; // ���뢠��� ���짮��⥫��
//
// ��������� � �����
//
class CuttDgGenerator {
public:
	static void (*indicator)(int event, void *ptr = NULL);
	static void defIndicator(int, void*) {}

	SLAPI  CuttDgGenerator();
	SLAPI ~CuttDgGenerator();
	void   SLAPI ReleaseData();
	int    SLAPI LoadData();
	int    SLAPI Init();
	int    SLAPI Run();
	int    SLAPI Run(ProtoDiagramQueue*, SourceLumber*, CuttDg*);
	int    SLAPI Make(CuttingDiagram&, CDFile*, SourceLumber&,
		ProtoDiagramQueue&, int);
	int    SLAPI GlobalCheck(ProtoDiagram&, CuttDg&);
	int    SLAPI MakeLogItemList(RealRange &range);
	long   SLAPI DealTime(PFID equipRowID);
	void   SLAPI DeleteCDFile();

	int    NumLg;
	LogItem   * P_LogItem;
	SpcSizes  * P_Thicks;
	SpcSizes  * P_Widths;
	CuttDgRec * P_Scheme;
protected:
	int    SLAPI InitSizes(SArray*, SpcSizes*, SpcSizes*);
	int    SLAPI GlobalCheck(CuttingDiagram*);
	void   SLAPI SaveSpcSizes(SpcSizes*&, SpcSizes*&);
	void   SLAPI RestoreSpcSizes(SpcSizes*&, SpcSizes*&);
	void   SLAPI ProcessHards(HardCDCollection*, ProtoDiagramQueue&, RealRange&);
private:
	int    DataInited; // �᫨ 0, � ����� �� �᢮�������
};
//
// ��祭�� ��१��� ��᪨, ���஥ ����� ��������� �� ����१��� ��᪨
//
struct PossibleSQBoard {
	double Thick;        // ���騭�
	double Width;        // ��ਭ�
	double Length;       // �����
	double Probability;  // ����⭮���
};

class ProtoDiagramItem;
//
// ��ࠬ���� ��᪨, ����砥��� �� ���⠢�
//
struct CuttingDiagramItem {
	unsigned LType;  // ��� �������ਠ��
	int      Thick;  // ���騭�, ��
	int      Width;  // ��ਭ�,  ��
	int      Length; // �����,   ��
	float    Output; // ��室,   ��. �
};
//
// CuttingDiagram
//
const 
	cdfHard  = 0x0001,
	cdfInval = 0x8000;
//
// ������� ���ᠭ�� ���⠢�
//
class CuttingDiagram {
public:
	SLAPI  CuttingDiagram();
	SLAPI  CuttingDiagram(CuttingDiagram&);
	SLAPI ~CuttingDiagram();
	CuttingDiagramItem & SLAPI  at(uint i);
	int    SLAPI search(void *, int &);
	int    SLAPI insert(void *);
	int    SLAPI getCount();
	void   SLAPI atFree(int);
	void   SLAPI slVolume();
	void   SLAPI totals();
	void   SLAPI normalizeSections();
	void   SLAPI makeLogDiamRange(RealRange &);
	void   SLAPI makeLogDiamRange(IntRange &);
	char * SLAPI getString(char *, int maxLen, int level);
	// ***
	uint32 Flags;         // �����
	PFID   CD_ID;         // �����䨪�樮��� ����� ���⠢�
	PFID   Breed;
	PFID   EquipRow;
	long   DealTime;    // �६� �ண��� ������ �ॢ��, �
	double LogVolume;   // ��ꥬ �����, ��. �
	double TotalOutput; // ��騩 ��室 �������ਠ���, ��. �
	int16  TotalSects;  // ��饥 ������⢮ ࠧ����� �祭��
	uint16 NumLg;       // ������⢮ ࠧ����� ��㯯 �ॢ��
	uint16 Count;       // ������⢮ ������⮢
	// ***
	// ����� ����� �⬥⪠�� '// ***' ������� �- � ������ ��
	// ��⮪�� ��� �����뢭�� ������� ����� ࠧ��஬ 24 ����
	// ***
	CuttingDiagramItem * P_Items;
	uchar              * ExtData;
	static int           CdStyle;

	size_t SLAPI ExtSize();
	LogItem & SLAPI GetLogItem(int);
	int    SLAPI PutLogItems(LogItem*, int);
	int    SLAPI PutString(ProtoDiagram*, int level);
};
//
// CuttingDiagramCollection
//
class CuttingDiagram;

const
	sortByNumber = 0,
	sortByOutput = 1;
//
// ����� ���⠢��
//
// CuttingDiagramCollection
//
#endif /* __PF_H */
