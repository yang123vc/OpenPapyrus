// OBJACSHT.CPP
// Copyright (c) A.Sobolev 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2007, 2008, 2009, 2015, 2016
//
#include <pp.h>
#pragma hdrstop
//
// @ModuleDef(PPObjAccSheet)
//
class AccSheetDialog : public TDialog {
public:
	AccSheetDialog() : TDialog(DLG_ACCSHEET)
	{
		MEMSZERO(Data);
	}
	int    setDTS(const PPAccSheet * pData)
	{
		RVALUEPTR(Data, pData);
		setCtrlLong(CTL_ACCSHEET_ID, Data.ID);
		setCtrlData(CTL_ACCSHEET_NAME, Data.Name);
		setCtrlData(CTL_ACCSHEET_SYMB, Data.Symb);
		setupAssoc();
		checkLink();
		SetupPPObjCombo(this, CTLSEL_ACCSHEET_REGTYPE, PPOBJ_REGISTERTYPE, Data.CodeRegTypeID, 0, 0);
		return 1;
	}
	int    getDTS(PPAccSheet * pData)
	{
		int    ok = 1;
		getCtrlData(CTL_ACCSHEET_NAME, Data.Name);
		if(*strip(Data.Name) == 0)
			ok = PPErrorByDialog(this, CTL_ACCSHEET_NAME, PPERR_NAMENEEDED);
		else {
			getCtrlData(CTL_ACCSHEET_SYMB, Data.Symb);
			GetClusterData(CTL_ACCSHEET_ASSOC, &Data.Assoc);
			if(Data.Assoc == 0) {
				GetClusterData(CTL_ACCSHEET_FLAGS, &Data.Flags);
				Data.Flags &= ~ACSHF_AUTOCREATART;
			}
			else {
				if(Data.Assoc == PPOBJ_PERSON)
					Data.ObjGroup = getCtrlLong(CTLSEL_ACCSHEET_GROUP);
				else if(Data.Assoc == PPOBJ_LOCATION)
					Data.ObjGroup = LOCTYP_WAREHOUSE;
				else
					Data.ObjGroup = 0;
				GetClusterData(CTL_ACCSHEET_FLAGS, &Data.Flags);
				ushort v = getCtrlUInt16(CTL_ACCSHEET_AGTKIND);
				Data.Flags &= ~(ACSHF_USECLIAGT | ACSHF_USESUPPLAGT);
				if(v == 1)
					Data.Flags |= ACSHF_USECLIAGT;
				else if(v == 2)
					Data.Flags |= ACSHF_USESUPPLAGT;
			}
			getCtrlData(CTLSEL_ACCSHEET_REGTYPE, &Data.CodeRegTypeID);
			*pData = Data;
		}
		return ok;
	}
private:
	DECL_HANDLE_EVENT;
	int    setupAssoc();
	PPID   groupObjType() const
	{
		return (Data.Assoc == PPOBJ_PERSON) ? PPOBJ_PRSNKIND : 0;
	}
	void   getAssocData();
	void   checkLink();
	PPAccSheet Data;
};

IMPL_HANDLE_EVENT(AccSheetDialog)
{
	TDialog::handleEvent(event);
	if(event.isClusterClk(CTL_ACCSHEET_ASSOC)) {
		PPID   old_assoc = Data.Assoc;
		GetClusterData(CTL_ACCSHEET_ASSOC, &Data.Assoc);
		if(Data.Assoc != old_assoc) {
			SETFLAG(Data.Flags, ACSHF_AUTOCREATART, oneof2(Data.Assoc, PPOBJ_PERSON, PPOBJ_LOCATION));
			Data.ObjGroup = 0;
			setupAssoc();
		}
		clearEvent(event);
	}
}

void AccSheetDialog::checkLink()
{
	if(!DS.CheckExtFlag(ECF_AVERAGE) || !PPMaster) {
		int    r;
		PPID   tmp_id = 0;
		ArticleFilt ar_filt;
		ar_filt.AccSheetID = Data.ID;
		ar_filt.Ft_Closed = 0; 
		PPObjArticle arobj(&ar_filt/*(void *)Data.ID*/);
		if((r = arobj.GetFreeArticle(&tmp_id, Data.ID)) == 0)
			PPError();
		else {
			int has_link = (r < 0 || tmp_id == 1) ? 0 : 1;
			disableCtrl(CTLSEL_ACCSHEET_GROUP, has_link);
		}
	}
}

int AccSheetDialog::setupAssoc()
{
	if(Data.Assoc == PPOBJ_ACCOUNT_PRE9004)
		Data.Assoc = PPOBJ_ACCOUNT2;
	AddClusterAssoc(CTL_ACCSHEET_ASSOC,  0, 0);
	AddClusterAssoc(CTL_ACCSHEET_ASSOC, -1, 0);
	AddClusterAssoc(CTL_ACCSHEET_ASSOC,  1, PPOBJ_PERSON);
	AddClusterAssoc(CTL_ACCSHEET_ASSOC,  2, PPOBJ_LOCATION);
	AddClusterAssoc(CTL_ACCSHEET_ASSOC,  3, PPOBJ_ACCOUNT2);
	AddClusterAssoc(CTL_ACCSHEET_ASSOC,  4, PPOBJ_GLOBALUSERACC); // @v9.1.3
	SetClusterData(CTL_ACCSHEET_ASSOC, Data.Assoc);
	disableCtrl(CTLSEL_ACCSHEET_GROUP, !(Data.Assoc == PPOBJ_PERSON));
	if(Data.Assoc == PPOBJ_PERSON)
		SetupPPObjCombo(this, CTLSEL_ACCSHEET_GROUP, groupObjType(), Data.ObjGroup, OLW_CANINSERT, 0);
	else
		setCtrlLong(CTL_ACCSHEET_GROUP, 0);
	AddClusterAssoc(CTL_ACCSHEET_FLAGS, 0, ACSHF_AUTOCREATART);
	AddClusterAssoc(CTL_ACCSHEET_FLAGS, 1, ACSHF_USEALIASSUBST);
	SetClusterData(CTL_ACCSHEET_FLAGS, Data.Flags);
	ushort v = (Data.Flags & ACSHF_USECLIAGT) ? 1 : ((Data.Flags & ACSHF_USESUPPLAGT) ? 2 : 0);
	setCtrlData(CTL_ACCSHEET_AGTKIND, &v);
	return 1;
}
//
//
//
SLAPI PPObjAccSheet::PPObjAccSheet(void * extraPtr) : PPObjReference(PPOBJ_ACCSHEET, extraPtr)
{
	filt = 0;
}

int SLAPI PPObjAccSheet::IsAssoc(PPID acsID, PPID objType, PPAccSheet * pRec)
{
	int    ok = -1;
	PPAccSheet acs_rec;
	if(Fetch(acsID, &acs_rec) > 0) {
		ASSIGN_PTR(pRec, acs_rec);
		if(acs_rec.Assoc == objType)
			ok = 1;
	}
	return ok;
}

int SLAPI PPObjAccSheet::Edit(PPID * pID, void * extraPtr)
{
	int    ok = 1;
	int    r = cmCancel, valid_data = 0;
	PPAccSheet sheet;
	AccSheetDialog * dlg = 0;
	THROW(CheckRightsModByID(pID));
	if(*pID) {
		THROW(Search(*pID, &sheet) > 0);
	}
	else
		MEMSZERO(sheet);
	THROW(CheckDialogPtr(&(dlg = new AccSheetDialog)));
	dlg->setDTS(&sheet);
	while(!valid_data && (r = ExecView(dlg)) == cmOK) {
		if(dlg->getDTS(&sheet)) {
			if(*pID)
				*pID = sheet.ID;
			if(!CheckName(*pID, sheet.Name, 0))
				dlg->selectCtrl(CTL_ACCSHEET_NAME);
			else if(EditItem(Obj, *pID, &sheet, 1)) {
				Dirty(*pID);
				valid_data = 1;
			}
			else
				PPError();
		}
	}
	CATCHZOKPPERR
	delete dlg;
	return ok ? r : 0;
}

// virtual
void * SLAPI PPObjAccSheet::CreateObjListWin(uint flags, void * extraPtr)
{
	class PPObjAccSheetListWindow : public PPObjListWindow {
	public:
		PPObjAccSheetListWindow(PPObject * pObj, uint flags, void * extraPtr) : PPObjListWindow(pObj, flags, extraPtr)
		{
			DefaultCmd = cmaEdit;
			SetToolbar(TOOLBAR_LIST_ACCSHEET);
		}
	private:
		DECL_HANDLE_EVENT
		{
			int    update = 0;
			PPID   id = 0;
			PPObjListWindow::handleEvent(event);
			if(P_Obj) {
				getResult(&id);
				if(TVCOMMAND) {
					switch(TVCMD) {
						case cmaInsert:
							id = 0;
							if(Flags & OLW_CANINSERT && P_Obj->Edit(&id, ExtraPtr) == cmOK)
								update = 2;
							else
								::SetFocus(H());
							break;
						case cmaMore:
							if(id) {
								ArticleFilt filt;
								filt.AccSheetID = id;
								ViewArticle(&filt);
							}
							break;
					}
				}
				PostProcessHandleEvent(update, id);
			}
		}
		virtual int Transmit(PPID id)
		{
			int    ok = -1;
			ObjTransmitParam param;
			if(ObjTransmDialog(DLG_OBJTRANSM, &param) > 0) {
				PPObjAccSheet acs_obj;
				const PPIDArray & rary = param.DestDBDivList.Get();
				PPObjIDArray objid_ary;
				StrAssocArray * p_list = acs_obj.MakeStrAssocList(0);
				THROW(p_list);
				PPWait(1);
				for(uint i = 0; i < p_list->getCount(); i++) {
					THROW(objid_ary.Add(PPOBJ_ACCSHEET, p_list->at(i).Id));
				}
				THROW(PPObjectTransmit::Transmit(&rary, &objid_ary, &param));
				ok = 1;
			}
			CATCH
				ok = PPErrorZ();
			ENDCATCH
			PPWait(0);
			return ok;
		}
	};
	return /*0; */ new PPObjAccSheetListWindow(this, flags, extraPtr);
}

#if 0 // @v8.5.4 {
int SLAPI PPObjAccSheet::Browse(void * extraPtr)
{
	class AccSheetView : public ObjViewDialog {
	public:
		AccSheetView(PPObjAccSheet * _ppobj) : ObjViewDialog(DLG_ACCSHEETVIEW, _ppobj, 0)
		{
		}
	private:
		virtual void extraProc(long id)
		{
			if(id) {
				ArticleFilt filt;
				filt.AccSheetID = id;
				ViewArticle(&filt);
			}
		}
	};
	int    ok = 1;
	if(CheckRights(PPR_READ)) {
		TDialog * dlg = new AccSheetView(this);
		if(CheckDialogPtr(&dlg, 1))
			ExecViewAndDestroy(dlg);
		else
			ok = 0;
	}
	else
		ok = PPErrorZ();
	return ok;
}
#endif // } 0 @v8.5.4

int SLAPI PPObjAccSheet::HandleMsg(int msg, PPID _obj, PPID _id, void * extraPtr)
{
	int    ok = DBRPL_OK;
	if(msg == DBMSG_OBJDELETE && _obj == PPOBJ_PRSNKIND) {
		int    r;
		for(PPID acs_id = 0; (r = EnumItems(&acs_id)) > 0;)
			if(ref->data.Val1 == PPOBJ_PERSON && ref->data.Val2 == _id) {
				ok = RetRefsExistsErr(Obj, acs_id);
				break;
			}
		if(!r)
			ok = DBRPL_ERROR;
	}
	return ok;
}

int SLAPI PPObjAccSheet::Write(PPObjPack * p, PPID * pID, void * stream, ObjTransmContext * pCtx) // @srlz
{
	int    ok = 1;
	if(p && p->Data)
		if(stream == 0) {
			PPAccSheet * p_rec = (PPAccSheet*)p->Data;
			if(*pID == 0) {
				PPID   same_id = 0;
				if(ref->SearchSymb(Obj, &same_id, p_rec->Name, offsetof(PPAccSheet, Name)) > 0) {
					PPAccSheet same_rec;
					if(Search(same_id, &same_rec) > 0 && same_rec.Assoc == p_rec->Assoc) {
						if(same_rec.ObjGroup == p_rec->ObjGroup) {
							ASSIGN_PTR(pID, same_id);
						}
						else if(p_rec->Assoc == PPOBJ_LOCATION && (same_rec.ObjGroup == LOCTYP_WAREHOUSE || !same_rec.ObjGroup) &&
							(p_rec->ObjGroup == LOCTYP_WAREHOUSE || !p_rec->ObjGroup)) {
							ASSIGN_PTR(pID, same_id);
						}
						else
							same_id = 0;
					}
					else
						same_id = 0;
				}
				if(same_id == 0) {
					p_rec->ID = 0;
					if(EditItem(Obj, *pID, p_rec, 1)) {
						ASSIGN_PTR(pID, ref->data.ObjID);
					}
					else {
						pCtx->OutputAcceptObjErrMsg(Obj, p_rec->ID, p_rec->Name);
						ok = -1;
					}
				}
			}
			else {
				;
			}
		}
		else {
			THROW(Serialize_(+1, (ReferenceTbl::Rec *)p->Data, stream, pCtx));
		}
	CATCHZOK
	return ok;
}

int SLAPI PPObjAccSheet::ProcessObjRefs(PPObjPack * p, PPObjIDArray * ary, int replace, ObjTransmContext * pCtx)
{
	int    ok = 1;
	if(p && p->Data) {
		PPAccSheet * p_rec = (PPAccSheet*)p->Data;
		THROW(ProcessObjRefInArray(PPOBJ_REGISTERTYPE, &p_rec->CodeRegTypeID, ary, replace));
		if(p_rec->Assoc == PPOBJ_PERSON) {
			THROW(ProcessObjRefInArray(PPOBJ_PRSNKIND, &p_rec->ObjGroup, ary, replace));
		}
	}
	else
		ok = -1;
	CATCHZOK
	return ok;
}
//
//
//
class AccSheetCache : public ObjCache {
public:
	struct AccSheetData : public ObjCacheEntry {
		PPID   BinArID;       // ������ ��� ������ �������� �� ����������� �������
		PPID   CodeRegTypeID; // �� ���� ���������������� ���������, �����������������
			// ����������, ��������������� ������.
		long   Flags;         // ACSHF_XXX
		long   Assoc;         // @#{0L, PPOBJ_PERSON, PPOBJ_LOCATION, PPOBJ_ACCOUNT} ��������������� ������
		long   ObjGroup;      // ��������� ��������������� ��������
	};
	SLAPI AccSheetCache() : ObjCache(PPOBJ_ACCSHEET, sizeof(AccSheetData))
	{
	}
private:
	virtual int SLAPI FetchEntry(PPID, ObjCacheEntry * pEntry, long);
	virtual int SLAPI EntryToData(const ObjCacheEntry * pEntry, void * pDataRec) const;

};

int SLAPI AccSheetCache::FetchEntry(PPID id, ObjCacheEntry * pEntry, long)
{
	int    ok = 1;
	AccSheetData * p_cache_rec = (AccSheetData *)pEntry;
	PPObjAccSheet as_obj;
	PPAccSheet rec;
	if(as_obj.Search(id, &rec) > 0) {
		p_cache_rec->BinArID  = rec.BinArID;
		p_cache_rec->CodeRegTypeID = rec.CodeRegTypeID;
		p_cache_rec->Flags    = rec.Flags;
		p_cache_rec->Assoc    = rec.Assoc;
		p_cache_rec->ObjGroup = rec.ObjGroup;
		ok = PutName(rec.Name, p_cache_rec);
	}
	else
		ok = -1;
	return ok;
}

int SLAPI AccSheetCache::EntryToData(const ObjCacheEntry * pEntry, void * pDataRec) const
{
	PPAccSheet * p_data_rec = (PPAccSheet *)pDataRec;
	const AccSheetData * p_cache_rec = (const AccSheetData *)pEntry;
	memzero(p_data_rec, sizeof(*p_data_rec));
	p_data_rec->Tag   = PPOBJ_ACCSHEET;
	p_data_rec->ID    = p_cache_rec->ID;
	p_data_rec->BinArID = p_cache_rec->BinArID;
	p_data_rec->CodeRegTypeID = p_cache_rec->CodeRegTypeID;
	p_data_rec->Flags = p_cache_rec->Flags;
	p_data_rec->Assoc = p_cache_rec->Assoc;
	p_data_rec->ObjGroup = p_cache_rec->ObjGroup;
	GetName(pEntry, p_data_rec->Name, sizeof(p_data_rec->Name));
	return 1;
}
// }

IMPL_OBJ_FETCH(PPObjAccSheet, PPAccSheet, AccSheetCache);