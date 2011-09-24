#include "EditorUI.h"
#include "EditorRes.h"
#include "../DES_GOBSTG/DES_GOBSTG/Header/Data.h"
#include "../DES_GOBSTG/DES_GOBSTG/Header/Export.h"

EditorUI ui;

EditorUI::EditorUI()
{
	timer = 0;
}

EditorUI::~EditorUI()
{
}

void EditorUI::SetupInit()
{
	for(int i=UIITEM_ITEMBEGIN; i<UIITEMMAX; i++)
	{
		eres.iteminfo[i].state = 0;
	}
}

void EditorUI::SetupEB(bool updateList)
{
	editmode = UIEDITMODE_EB;
	if(eres.eff[ebnum])
	{
		char buffer[M_STRMAX];

		eres.iteminfo[UIITEM_EB_NLIFETIME].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EB_NLIFETIME].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EB_NLIFETIME].info, "nLifeTime");
		eres.iteminfo[UIITEM_EB_NLIFETIME_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EB_NLIFETIME_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EB_NLIFETIME_VALUE].info, hge->Math_itoa(eres.eff[ebnum]->ebi.nLifeTime, buffer));

		eres.iteminfo[UIITEM_EB_NREPEATDELAY].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EB_NREPEATDELAY].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EB_NREPEATDELAY].info, "nRpDelay");
		eres.iteminfo[UIITEM_EB_NREPEATDELAY_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EB_NREPEATDELAY_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EB_NREPEATDELAY_VALUE].info, hge->Math_itoa(eres.eff[ebnum]->ebi.nRepeatDelay, buffer));

		eres.iteminfo[UIITEM_EB_TEX].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EB_TEX].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EB_TEX].info, "Texure");
		eres.iteminfo[UIITEM_EB_TEX_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EB_TEX_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EB_TEX_VALUE].info, hge->Math_itoa(eres.texnum[ebnum], buffer));

		if(updateList)
		{
			eres.eff[ebnum]->Stop(true);
			eres.eff[ebnum]->MoveTo(mx, my, true);
			eres.eff[ebnum]->Fire();

			emitterItem = eres.eff[ebnum]->eiList;
			if(emitterItem)
			{
				emitter = &(emitterItem->emitter);
			}
			else
			{
				emitter = NULL;
			}
			if(emitter)
			{
				affectorItem = emitter->eaiList;
				if(affectorItem)
				{
					affector = &(emitter->eaiList->affector);
				}
			}
			else
			{
				affector = NULL;
			}
		}
	}
	else
	{
		for(int i=UIITEM_ITEMBEGIN; i<UIITEM_EB_END; i++)
		{
			eres.iteminfo[i].state = 0;
		}
		emitterItem = NULL;
		emitter = NULL;
		affectorItem = NULL;
		affector = NULL;
	}
	for(int i=UIITEM_EB_END; i<UIITEMMAX; i++)
	{
		eres.iteminfo[i].state = 0;
	}
}

void EditorUI::SetupEE(bool updateList)
{
	editmode = UIEDITMODE_EE;
	if(emitter)
	{
		char buffer[M_STRMAX];

		eres.iteminfo[UIITEM_EE_NSTARTTIME].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_NSTARTTIME].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EE_NSTARTTIME].info, "nStartTime");
		eres.iteminfo[UIITEM_EE_NSTARTTIME_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_NSTARTTIME_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EE_NSTARTTIME_VALUE].info, hge->Math_itoa(emitter->eei.nStartTime, buffer));

		eres.iteminfo[UIITEM_EE_NENDTIME].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_NENDTIME].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EE_NENDTIME].info, "nEndTime");
		eres.iteminfo[UIITEM_EE_NENDTIME_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_NENDTIME_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EE_NENDTIME_VALUE].info, hge->Math_itoa(emitter->eei.nEndTime, buffer));

		eres.iteminfo[UIITEM_EE_NLIFETIMEMIN].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_NLIFETIMEMIN].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EE_NLIFETIMEMIN].info, "nLifeMin");
		eres.iteminfo[UIITEM_EE_NLIFETIMEMIN_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_NLIFETIMEMIN_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EE_NLIFETIMEMIN_VALUE].info, hge->Math_itoa(emitter->eei.nLfieTimeMin, buffer));

		eres.iteminfo[UIITEM_EE_NLIFETIMEMAX].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_NLIFETIMEMAX].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EE_NLIFETIMEMAX].info, "nLifeMax");
		eres.iteminfo[UIITEM_EE_NLIFETIMEMAX_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_NLIFETIMEMAX_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EE_NLIFETIMEMAX_VALUE].info, hge->Math_itoa(emitter->eei.nLifeTimeMax, buffer));


		eres.iteminfo[UIITEM_EE_FEMITNUM].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FEMITNUM].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EE_FEMITNUM].info, "fEmitNum");
		eres.iteminfo[UIITEM_EE_FEMITNUM_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FEMITNUM_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", emitter->eei.fEmitNum);
		strcpy(eres.iteminfo[UIITEM_EE_FEMITNUM_VALUE].info, buffer);

		eres.iteminfo[UIITEM_EE_FROTATIONX].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FROTATIONX].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EE_FROTATIONX].info, "fRotationX");
		eres.iteminfo[UIITEM_EE_FROTATIONX_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FROTATIONX_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", emitter->eei.fRotationX);
		strcpy(eres.iteminfo[UIITEM_EE_FROTATIONX_VALUE].info, buffer);

		eres.iteminfo[UIITEM_EE_FROTATIONY].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FROTATIONY].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EE_FROTATIONY].info, "fRotationY");
		eres.iteminfo[UIITEM_EE_FROTATIONY_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FROTATIONY_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", emitter->eei.fRotationY);
		strcpy(eres.iteminfo[UIITEM_EE_FROTATIONY_VALUE].info, buffer);

		eres.iteminfo[UIITEM_EE_FRADIUS].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FRADIUS].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EE_FRADIUS].info, "fRadius");
		eres.iteminfo[UIITEM_EE_FRADIUS_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FRADIUS_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", emitter->eei.fRadius);
		strcpy(eres.iteminfo[UIITEM_EE_FRADIUS_VALUE].info, buffer);

		eres.iteminfo[UIITEM_EE_FRADIUSINNER].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FRADIUSINNER].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EE_FRADIUSINNER].info, "fRInner");
		eres.iteminfo[UIITEM_EE_FRADIUSINNER_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FRADIUSINNER_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", emitter->eei.fRadiusInner);
		strcpy(eres.iteminfo[UIITEM_EE_FRADIUSINNER_VALUE].info, buffer);

		eres.iteminfo[UIITEM_EE_FTHETASTART].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FTHETASTART].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EE_FTHETASTART].info, "fThetaStart");
		eres.iteminfo[UIITEM_EE_FTHETASTART_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FTHETASTART_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", emitter->eei.fThetaStart);
		strcpy(eres.iteminfo[UIITEM_EE_FTHETASTART_VALUE].info, buffer);

		eres.iteminfo[UIITEM_EE_FTHETASTEP].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FTHETASTEP].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EE_FTHETASTEP].info, "fThetaStep");
		eres.iteminfo[UIITEM_EE_FTHETASTEP_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FTHETASTEP_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", emitter->eei.fThetaStep);
		strcpy(eres.iteminfo[UIITEM_EE_FTHETASTEP_VALUE].info, buffer);

		eres.iteminfo[UIITEM_EE_FTRACERESISTANCE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FTRACERESISTANCE].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EE_FTRACERESISTANCE].info, "fTraceResist");
		eres.iteminfo[UIITEM_EE_FTRACERESISTANCE_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FTRACERESISTANCE_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", emitter->eei.fTraceResistance);
		strcpy(eres.iteminfo[UIITEM_EE_FTRACERESISTANCE_VALUE].info, buffer);

		eres.iteminfo[UIITEM_EE_FTEXTUREX].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FTEXTUREX].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EE_FTEXTUREX].info, "fTextureX");
		eres.iteminfo[UIITEM_EE_FTEXTUREX_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FTEXTUREX_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", emitter->eei.fTextureX);
		strcpy(eres.iteminfo[UIITEM_EE_FTEXTUREX_VALUE].info, buffer);

		eres.iteminfo[UIITEM_EE_FTEXTUREY].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FTEXTUREY].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EE_FTEXTUREY].info, "fTextureY");
		eres.iteminfo[UIITEM_EE_FTEXTUREY_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FTEXTUREY_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", emitter->eei.fTextureY);
		strcpy(eres.iteminfo[UIITEM_EE_FTEXTUREY_VALUE].info, buffer);

		eres.iteminfo[UIITEM_EE_FTEXTUREW].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FTEXTUREW].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EE_FTEXTUREW].info, "fTextureW");
		eres.iteminfo[UIITEM_EE_FTEXTUREW_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FTEXTUREW_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", emitter->eei.fTextureW);
		strcpy(eres.iteminfo[UIITEM_EE_FTEXTUREW_VALUE].info, buffer);

		eres.iteminfo[UIITEM_EE_FTEXTUREH].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FTEXTUREH].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EE_FTEXTUREH].info, "fTextureH");
		eres.iteminfo[UIITEM_EE_FTEXTUREH_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FTEXTUREH_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", emitter->eei.fTextureH);
		strcpy(eres.iteminfo[UIITEM_EE_FTEXTUREH_VALUE].info, buffer);
		
		eres.iteminfo[UIITEM_EE_FHOTX].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FHOTX].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EE_FHOTX].info, "fHotX");
		eres.iteminfo[UIITEM_EE_FHOTX_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FHOTX_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", emitter->eei.fHotX);
		strcpy(eres.iteminfo[UIITEM_EE_FHOTX_VALUE].info, buffer);
		
		eres.iteminfo[UIITEM_EE_FHOTY].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FHOTY].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EE_FHOTY].info, "fHotY");
		eres.iteminfo[UIITEM_EE_FHOTY_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_FHOTY_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", emitter->eei.fHotY);
		strcpy(eres.iteminfo[UIITEM_EE_FHOTY_VALUE].info, buffer);

		
		eres.iteminfo[UIITEM_EE_BLEND].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_BLEND].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EE_BLEND].info, "Blend");
		eres.iteminfo[UIITEM_EE_BLEND_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_BLEND_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EE_BLEND_VALUE].info, hge->Math_itoa(emitter->eei.blend, buffer));
		
		eres.iteminfo[UIITEM_EE_BTRACE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_BTRACE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EE_BTRACE].info, "bTrace");
		eres.iteminfo[UIITEM_EE_BTRACE_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_BTRACE_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EE_BTRACE_VALUE].info, hge->Math_itoa(emitter->eei.bTrace, buffer));
		
		eres.iteminfo[UIITEM_EE_BADJUSTDIRECTION].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_BADJUSTDIRECTION].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EE_BADJUSTDIRECTION].info, "bAdjustDir");
		eres.iteminfo[UIITEM_EE_BADJUSTDIRECTION_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EE_BADJUSTDIRECTION_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EE_BADJUSTDIRECTION_VALUE].info, hge->Math_itoa(emitter->eei.bAdjustDirection, buffer));

		if(updateList)
		{
			affectorItem = emitter->eaiList;
			if(affectorItem)
			{
				affector = &(affectorItem->affector);
			}
			else
			{
				affector = NULL;
			}
		}
	}
	else
	{
		for(int i=UIITEM_ITEMBEGIN; i<UIITEM_EE_END; i++)
		{
			eres.iteminfo[i].state = 0;
		}
		affectorItem = NULL;
		affector = NULL;
	}
	for(int i=UIITEM_EE_END; i<UIITEMMAX; i++)
	{
		eres.iteminfo[i].state = 0;
	}
}

void EditorUI::SetupEA()
{
	editmode = UIEDITMODE_EA;
	if(affector)
	{
		bool dwordmode = false;
		if(affector->eai.type == HGEEFFECT_AFFECTORTYPE_COLOR)
			dwordmode = true;

		char buffer[M_STRMAX];

		eres.iteminfo[UIITEM_EA_NAFFECTORSTARTTIME].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EA_NAFFECTORSTARTTIME].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EA_NAFFECTORSTARTTIME].info, "nStartTime");
		eres.iteminfo[UIITEM_EA_NAFFECTORSTARTTIME_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EA_NAFFECTORSTARTTIME_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EA_NAFFECTORSTARTTIME_VALUE].info, hge->Math_itoa(affector->eai.nAffectorStartTime, buffer));

		eres.iteminfo[UIITEM_EA_NAFFECTORENDTIME].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EA_NAFFECTORENDTIME].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EA_NAFFECTORENDTIME].info, "nEndTime");
		eres.iteminfo[UIITEM_EA_NAFFECTORENDTIME_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EA_NAFFECTORENDTIME_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EA_NAFFECTORENDTIME_VALUE].info, hge->Math_itoa(affector->eai.nAffectorEndTime, buffer));

		eres.iteminfo[UIITEM_EA_NRANDOMPICKINTERVAL].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EA_NRANDOMPICKINTERVAL].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EA_NRANDOMPICKINTERVAL].info, "nPickInter");
		eres.iteminfo[UIITEM_EA_NRANDOMPICKINTERVAL_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EA_NRANDOMPICKINTERVAL_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EA_NRANDOMPICKINTERVAL_VALUE].info, hge->Math_itoa(affector->eai.nRandomPickInterval, buffer));


		eres.iteminfo[UIITEM_EA_FSTARTVALUEMIN].state = UIITEM_STATE_NORMAL;
		if(dwordmode)
		{
			eres.iteminfo[UIITEM_EA_FSTARTVALUEMIN].inputtype = UIINPUTTYPE_DWORD;
			strcpy(eres.iteminfo[UIITEM_EA_FSTARTVALUEMIN].info, "uStartValMin");
		}
		else
		{
			eres.iteminfo[UIITEM_EA_FSTARTVALUEMIN].inputtype = UIINPUTTYPE_FLOAT;
			strcpy(eres.iteminfo[UIITEM_EA_FSTARTVALUEMIN].info, "fStartValMin");
		}
		eres.iteminfo[UIITEM_EA_FSTARTVALUEMIN_VALUE].state = UIITEM_STATE_NORMAL;
		if(dwordmode)
			eres.iteminfo[UIITEM_EA_FSTARTVALUEMIN_VALUE].inputtype = UIINPUTTYPE_DWORD;
		else
			eres.iteminfo[UIITEM_EA_FSTARTVALUEMIN_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		if(dwordmode)
			sprintf(buffer, "%08x", *(DWORD *)&(affector->eai.fStartValueMin));
		else
			sprintf(buffer, "%f", affector->eai.fStartValueMin);
		strcpy(eres.iteminfo[UIITEM_EA_FSTARTVALUEMIN_VALUE].info, buffer);
		

		eres.iteminfo[UIITEM_EA_FSTARTVALUEMAX].state = UIITEM_STATE_NORMAL;
		if(dwordmode)
		{
			eres.iteminfo[UIITEM_EA_FSTARTVALUEMAX].inputtype = UIINPUTTYPE_DWORD;
			strcpy(eres.iteminfo[UIITEM_EA_FSTARTVALUEMAX].info, "uStartValMax");
		}
		else
		{
			eres.iteminfo[UIITEM_EA_FSTARTVALUEMAX].inputtype = UIINPUTTYPE_FLOAT;
			strcpy(eres.iteminfo[UIITEM_EA_FSTARTVALUEMAX].info, "fStartValMax");
		}
		eres.iteminfo[UIITEM_EA_FSTARTVALUEMAX_VALUE].state = UIITEM_STATE_NORMAL;
		if(dwordmode)
			eres.iteminfo[UIITEM_EA_FSTARTVALUEMAX_VALUE].inputtype = UIINPUTTYPE_DWORD;
		else
			eres.iteminfo[UIITEM_EA_FSTARTVALUEMAX_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		if(dwordmode)
			sprintf(buffer, "%08x", *(DWORD *)&(affector->eai.fStartValueMax));
		else
			sprintf(buffer, "%f", affector->eai.fStartValueMax);
		strcpy(eres.iteminfo[UIITEM_EA_FSTARTVALUEMAX_VALUE].info, buffer);
		

		eres.iteminfo[UIITEM_EA_FENDVALUEMIN].state = UIITEM_STATE_NORMAL;
		if(dwordmode)
		{
			eres.iteminfo[UIITEM_EA_FENDVALUEMIN].inputtype = UIINPUTTYPE_DWORD;
			strcpy(eres.iteminfo[UIITEM_EA_FENDVALUEMIN].info, "uEndValMin");
		}
		else
		{
			eres.iteminfo[UIITEM_EA_FENDVALUEMIN].inputtype = UIINPUTTYPE_FLOAT;
			strcpy(eres.iteminfo[UIITEM_EA_FENDVALUEMIN].info, "fEndValMin");
		}
		eres.iteminfo[UIITEM_EA_FENDVALUEMIN_VALUE].state = UIITEM_STATE_NORMAL;
		if(dwordmode)
			eres.iteminfo[UIITEM_EA_FENDVALUEMIN_VALUE].inputtype = UIINPUTTYPE_DWORD;
		else
			eres.iteminfo[UIITEM_EA_FENDVALUEMIN_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		if(dwordmode)
			sprintf(buffer, "%08x", *(DWORD *)&(affector->eai.fEndValueMin));
		else
			sprintf(buffer, "%f", affector->eai.fEndValueMin);
		strcpy(eres.iteminfo[UIITEM_EA_FENDVALUEMIN_VALUE].info, buffer);
		

		eres.iteminfo[UIITEM_EA_FENDVALUEMAX].state = UIITEM_STATE_NORMAL;
		if(dwordmode)
		{
			eres.iteminfo[UIITEM_EA_FENDVALUEMAX].inputtype = UIINPUTTYPE_DWORD;
			strcpy(eres.iteminfo[UIITEM_EA_FENDVALUEMAX].info, "uEndValMax");
		}
		else
		{
			eres.iteminfo[UIITEM_EA_FENDVALUEMAX].inputtype = UIINPUTTYPE_FLOAT;
			strcpy(eres.iteminfo[UIITEM_EA_FENDVALUEMAX].info, "fEndValMax");
		}
		eres.iteminfo[UIITEM_EA_FENDVALUEMAX_VALUE].state = UIITEM_STATE_NORMAL;
		if(dwordmode)
			eres.iteminfo[UIITEM_EA_FENDVALUEMAX_VALUE].inputtype = UIINPUTTYPE_DWORD;
		else
			eres.iteminfo[UIITEM_EA_FENDVALUEMAX_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		if(dwordmode)
			sprintf(buffer, "%08x", *(DWORD *)&(affector->eai.fEndValueMax));
		else
			sprintf(buffer, "%f", affector->eai.fEndValueMax);
		strcpy(eres.iteminfo[UIITEM_EA_FENDVALUEMAX_VALUE].info, buffer);
		

		eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMIN].state = UIITEM_STATE_NORMAL;
		if(dwordmode)
		{
			eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMIN].inputtype = UIINPUTTYPE_DWORD;
			strcpy(eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMIN].info, "uIncMin");
		}
		else
		{
			eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMIN].inputtype = UIINPUTTYPE_FLOAT;
			strcpy(eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMIN].info, "fIncMin");
		}
		eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMIN_VALUE].state = UIITEM_STATE_NORMAL;
		if(dwordmode)
			eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMIN_VALUE].inputtype = UIINPUTTYPE_DWORD;
		else
			eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMIN_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		if(dwordmode)
			sprintf(buffer, "%08x", *(DWORD *)&(affector->eai.fIncrementValueMin));
		else
			sprintf(buffer, "%f", affector->eai.fIncrementValueMin);
		strcpy(eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMIN_VALUE].info, buffer);


		eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMAX].state = UIITEM_STATE_NORMAL;
		if(dwordmode)
		{
			eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMAX].inputtype = UIINPUTTYPE_DWORD;
			strcpy(eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMAX].info, "uIncMax");
		}
		else
		{
			eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMAX].inputtype = UIINPUTTYPE_FLOAT;
			strcpy(eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMAX].info, "fIncMax");
		}
		eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMAX_VALUE].state = UIITEM_STATE_NORMAL;
		if(dwordmode)
			eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMAX_VALUE].inputtype = UIINPUTTYPE_DWORD;
		else
			eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMAX_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		if(dwordmode)
			sprintf(buffer, "%08x", *(DWORD *)&(affector->eai.fIncrementValueMax));
		else
			sprintf(buffer, "%f", affector->eai.fIncrementValueMax);
		strcpy(eres.iteminfo[UIITEM_EA_FINCREMENTVALUEMAX_VALUE].info, buffer);
		

		eres.iteminfo[UIITEM_EA_FINCREMENTSCALE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EA_FINCREMENTSCALE].inputtype = UIINPUTTYPE_FLOAT;
		strcpy(eres.iteminfo[UIITEM_EA_FINCREMENTSCALE].info, "fIncScale");
		eres.iteminfo[UIITEM_EA_FINCREMENTSCALE_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EA_FINCREMENTSCALE_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		sprintf(buffer, "%f", affector->eai.fIncrementScale);
		strcpy(eres.iteminfo[UIITEM_EA_FINCREMENTSCALE_VALUE].info, buffer);

		eres.iteminfo[UIITEM_EA_FACCELERATION].state = UIITEM_STATE_NORMAL;
		if(dwordmode)
		{
			eres.iteminfo[UIITEM_EA_FACCELERATION].inputtype = UIINPUTTYPE_DWORD;
			strcpy(eres.iteminfo[UIITEM_EA_FACCELERATION].info, "uAccel");
		}
		else
		{
			eres.iteminfo[UIITEM_EA_FACCELERATION].inputtype = UIINPUTTYPE_FLOAT;
			strcpy(eres.iteminfo[UIITEM_EA_FACCELERATION].info, "fAccel");
		}
		eres.iteminfo[UIITEM_EA_FACCELERATION_VALUE].state = UIITEM_STATE_NORMAL;
		if(dwordmode)
			eres.iteminfo[UIITEM_EA_FACCELERATION_VALUE].inputtype = UIINPUTTYPE_DWORD;
		else
			eres.iteminfo[UIITEM_EA_FACCELERATION_VALUE].inputtype = UIINPUTTYPE_FLOAT;
		if(dwordmode)
			sprintf(buffer, "%08x", *(DWORD *)&(affector->eai.fAcceleration));
		else
			sprintf(buffer, "%f", affector->eai.fAcceleration);
		strcpy(eres.iteminfo[UIITEM_EA_FACCELERATION_VALUE].info, buffer);

		eres.iteminfo[UIITEM_EA_BUSESTARTVALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EA_BUSESTARTVALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EA_BUSESTARTVALUE].info, "bUseStart");
		eres.iteminfo[UIITEM_EA_BUSESTARTVALUE_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EA_BUSESTARTVALUE_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EA_BUSESTARTVALUE_VALUE].info, hge->Math_itoa(affector->eai.bUseStartValue, buffer));

		eres.iteminfo[UIITEM_EA_BUSEENDVALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EA_BUSEENDVALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EA_BUSEENDVALUE].info, "bUseEnd");
		eres.iteminfo[UIITEM_EA_BUSEENDVALUE_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EA_BUSEENDVALUE_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EA_BUSEENDVALUE_VALUE].info, hge->Math_itoa(affector->eai.bUseEndValue, buffer));
		
		eres.iteminfo[UIITEM_EA_TYPE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EA_TYPE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EA_TYPE].info, "Type");
		eres.iteminfo[UIITEM_EA_TYPE_VALUE].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EA_TYPE_VALUE].inputtype = UIINPUTTYPE_INT;
		strcpy(eres.iteminfo[UIITEM_EA_TYPE_VALUE].info, hge->Math_itoa(affector->eai.type, buffer));
	}
	else
	{
		for(int i=UIITEM_ITEMBEGIN; i<UIITEM_EA_END; i++)
		{
			eres.iteminfo[i].state = 0;
		}
	}
	for(int i=UIITEM_EA_END; i<UIITEMMAX; i++)
	{
		eres.iteminfo[i].state = 0;
	}
}

void EditorUI::PageUp()
{
	if(editmode == UIEDITMODE_EB)
	{
		bool bFound = false;
		for(int i=ebnum-1; i>=0; i--)
		{
			if(eres.eff[i])
			{
				ebnum = i;
				bFound = true;
				break;
			}
		}
		if(!bFound)
		{
			for(int i=EFFECTSYSTYPEMAX-1; i> ebnum; i--)
			{
				if(eres.eff[i])
				{
					ebnum = i;
					bFound = true;
					break;
				}
			}
		}
		if(bFound)
			SetupEB(true);
	}
	else if(editmode == UIEDITMODE_EE)
	{
		if(eres.eff[ebnum])
		{
			if(emitter && emitterItem)
			{
				emitterItem = emitterItem->next;
			}
			if(!emitterItem)
			{
				emitterItem = eres.eff[ebnum]->eiList;
			}

			if(emitterItem)
			{
				emitter = &(emitterItem->emitter);
				SetupEE(true);
			}
			else
				emitter = NULL;
		}
	}
	else if(editmode == UIEDITMODE_EA)
	{
		if(eres.eff[ebnum] && emitter && emitterItem)
		{
			if(affector && affectorItem)
			{
				affectorItem = affectorItem->next;
			}
			if(!affectorItem)
			{
				affectorItem = emitter->eaiList;
			}

			if(affectorItem)
			{
				affector = &(affectorItem->affector);
				SetupEA();
			}
			else
				affector = NULL;
		}
	}
}

void EditorUI::PageDown()
{
	if(editmode == UIEDITMODE_EB)
	{
		bool bFound = false;
		for(int i=ebnum+1; i<EFFECTSYSTYPEMAX; i++)
		{
			if(eres.eff[i])
			{
				ebnum = i;
				bFound = true;
				break;
			}
		}
		if(!bFound)
		{
			for(int i=0; i<ebnum; i++)
			{
				if(eres.eff[i])
				{
					ebnum = i;
					bFound = true;
					break;
				}
			}
		}
		if(bFound)
			SetupEB(true);
	}
	else if(editmode == UIEDITMODE_EE)
	{
		if(eres.eff[ebnum])
		{
			CEmitterList * _emitterItem = eres.eff[ebnum]->eiList;

			bool bFirst = false;
			if(emitterItem == _emitterItem)
				bFirst = true;

			while(_emitterItem)
			{
				if(_emitterItem->next == emitterItem)
				{
					emitterItem = _emitterItem;
					break;
				}
				if(bFirst && _emitterItem->next == NULL)
				{
					emitterItem = _emitterItem;
					break;
				}
				_emitterItem = _emitterItem->next;
			}
			if(emitterItem)
			{
				emitter = &(emitterItem->emitter);
				SetupEE(true);
			}
			else
				emitter = NULL;
		}
	}
	else if(editmode == UIEDITMODE_EA)
	{
		if(eres.eff[ebnum] && emitter && emitterItem)
		{
			CAffectorList * _affectorItem = emitter->eaiList;

			bool bFirst = false;
			if(affectorItem == _affectorItem)
				bFirst = true;

			while(_affectorItem)
			{
				if(_affectorItem->next == affectorItem)
				{
					affectorItem = _affectorItem;
					break;
				}
				if(bFirst && _affectorItem->next == NULL)
				{
					affectorItem = _affectorItem;
					break;
				}
				_affectorItem = _affectorItem->next;
			}
			if(affectorItem)
			{
				affector = &(affectorItem->affector);
				SetupEA();
			}
			else
				affector = NULL;
		}
	}
}

void EditorUI::Refresh()
{
	if(eres.eff[ebnum])
	{
		eres.eff[ebnum]->Fire();
	}
	zpos = 0;
}

void EditorUI::ChangePanel(BYTE info)
{
	switch(info)
	{
	case UIITEM_EBINFO:
		eres.iteminfo[UIITEM_EBINFO].state = UIITEM_STATE_SELECTED;
		eres.iteminfo[UIITEM_EEINFO].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EAINFO].state = UIITEM_STATE_NORMAL;
		SetupEB();
		break;
	case UIITEM_EEINFO:
		eres.iteminfo[UIITEM_EEINFO].state = UIITEM_STATE_SELECTED;
		eres.iteminfo[UIITEM_EBINFO].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EAINFO].state = UIITEM_STATE_NORMAL;
		SetupEE();
		break;
	case UIITEM_EAINFO:
		eres.iteminfo[UIITEM_EAINFO].state = UIITEM_STATE_SELECTED;
		eres.iteminfo[UIITEM_EBINFO].state = UIITEM_STATE_NORMAL;
		eres.iteminfo[UIITEM_EEINFO].state = UIITEM_STATE_NORMAL;
		SetupEA();
		break;
	}
}

void EditorUI::Operate()
{
	if(!editmode)
		return;
	eres.iteminfo[oper].state = UIITEM_STATE_SELECTED;
	eres.iteminfo[UIITEM_INPUTINFO].state = UIITEM_STATE_SELECTED;
	strcpy(input, "");
}

bool EditorUI::Save()
{
	if(!eres.eff[ebnum])
		return false;
	bool bret = eres.Save(ebnum);
	if (bret)
	{
		SetupEB(true);
		BYTE _info = 0;
		switch(editmode)
		{
		case UIEDITMODE_EB:
			_info = UIITEM_EBINFO;
			break;
		case UIEDITMODE_EE:
			_info = UIITEM_EEINFO;
			break;
		case UIEDITMODE_EA:
			_info = UIITEM_EAINFO;
			break;
		}
		ChangePanel(_info);
	}
	return bret;
}

bool EditorUI::isListNull()
{
	if(!editmode)
		return true;
	switch(editmode)
	{
	case UIEDITMODE_EA:
		if(!affector || !affectorItem)
			return true;
	case UIEDITMODE_EE:
		if(!emitter || !emitterItem)
			return true;
	case UIEDITMODE_EB:
		if(!eres.eff[ebnum])
			return true;
	}
	return false;
}

void EditorUI::Update()
{
	timer++;
	if(timer == 1)
	{
		eres.Init();
		SetupInit();
		input = eres.iteminfo[UIITEM_INPUTINFO].info;
		title = eres.iteminfo[UIITEM_TITLEINFO].info;
		addinfo = eres.iteminfo[UIITEM_ADDINFO].info;
		oper = -1;
		ebnum = 0;
		zpos = 0;
		emitter = NULL;
		affector = NULL;
		editmode = UIEDITMODE_EB;
		ChangePanel(UIITEM_EBINFO);
		SetupEB(true);
	}
	hge->Input_GetMousePos(&mx, &my);
	wheel = 0;
	clickdown = false;
	clickup = false;
	while(hge->Input_GetEvent(&inputevent))
	{
		if(inputevent.type == INPUT_MBUTTONDOWN)
		{
			clickdown = true;
		}
		else if(inputevent.type == INPUT_MBUTTONUP)
		{
			clickup = true;
		}
		else if(inputevent.type == INPUT_MOUSEWHEEL)
		{
			wheel = inputevent.wheel;
			if(wheel)
			{
				if(hge->Input_GetDIKey(DIK_RSHIFT))
				{
					zpos += wheel;
				}
				else
				{
					zpos += wheel * 10;
				}
			}
		}
	}
	if(mx < M_ACTIVECLIENT_RIGHT)
		hge->System_SetState(HGE_HIDEMOUSE, true);
	else
		hge->System_SetState(HGE_HIDEMOUSE, false);

	if(hge->Input_GetDIKey(DIK_RCONTROL) && hge->Input_GetDIKey(DIK_NEXT, DIKEY_DOWN))
	{
		ChangeBGTex();
	}
	if(hge->Input_GetDIKey(DIK_RCONTROL) && hge->Input_GetDIKey(DIK_PRIOR, DIKEY_DOWN))
	{
		bool bFound = false;
		if(eres.bgtex == -1)
			eres.bgtex = TEXMAX;
		int i;
		for(i=eres.bgtex-1; i>=0; i--)
		{
			if(eres.tex[i].tex)
			{
				bFound = true;
				break;
			}
		}
		if(!bFound)
		{
			for(i=TEXMAX-1; i>eres.bgtex; i--)
			{
				if(eres.tex[i].tex)
				{
					bFound = true;
					break;
				}
			}
		}
		if(bFound)
			ChangeBGTex(i);
	}

	for(int i=0; i<UIITEMMAX; i++)
	{
		if(eres.iteminfo[i].state)
		{
			if(eres.iteminfo[i].state != UIITEM_STATE_SELECTED)
			{
				if(mx > eres.iteminfo[i].x &&
					mx < eres.iteminfo[i].x + eres.iteminfo[i].w &&
					my > eres.iteminfo[i].y &&
					my < eres.iteminfo[i].y + eres.iteminfo[i].h)
				{
					if(clickdown && oper == -1)
					{
						ChangePanel(i);
					}
					if(clickup && oper == -1)
					{
						if(i == UIITEM_REFRESHINFO)
						{
							Refresh();
						}
						else if(i == UIITEM_PAGEUPINFO)
						{
							PageUp();
						}
						else if(i == UIITEM_PAGEDOWNINFO)
						{
							PageDown();
						}
						else if(i == UIITEM_SAVEINFO)
						{
							Save();
						}
						else if(i == UIITEM_ADDINFO)
						{
							if(hge->Input_GetDIKey(DIK_RCONTROL))
								Delete();
							else
								Add();
						}
						else if(i == UIITEM_BGINFO)
						{
							ChangeBGTex();
						}
						if(oper < 0)
						{
							if(i >= UIITEM_ITEMBEGIN)
							{
								eres.iteminfo[i].state = UIITEM_STATE_SELECTED;
								eres.iteminfo[UIITEM_INPUTINFO].state = UIITEM_STATE_SELECTED;
								oper = i;
								if(oper >= UIITEM_ITEMBEGIN)
								{
									oper = ((oper>>1)<<1)+1;
									eres.iteminfo[oper].state = UIITEM_STATE_SELECTED;
									eres.iteminfo[oper-1].state = UIITEM_STATE_NORMAL;
								}
								strcpy(input, "");
							}
						}
					}
					else if(eres.iteminfo[i].state != UIITEM_STATE_SELECTED)
						eres.iteminfo[i].state = UIITEM_STATE_OVER;
				}
				else
				{
					eres.iteminfo[i].state = UIITEM_STATE_NORMAL;
				}
			}
		}
	}

	if(oper >= 0)
	{
		if(UpdateInput())
		{
			if(UpdateValue())
			{
				eres.iteminfo[oper].state = UIITEM_STATE_NORMAL;
				eres.iteminfo[UIITEM_INPUTINFO].state = UIITEM_STATE_NORMAL;
				strcpy(eres.iteminfo[UIITEM_INPUTINFO].info, "Input");
				if(oper >= UIITEM_ITEMBEGIN)
				{
					if(hge->Input_GetDIKey(DIK_UP, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_UP) && pushtimer == M_PUSH_FIRST)
					{
						oper -= 2;
						if(oper < UIITEM_ITEMBEGIN)
						{
							switch(editmode)
							{
							case UIEDITMODE_EB:
								oper = UIITEM_EB_END - 1;
								break;
							case UIEDITMODE_EE:
								oper = UIITEM_EE_END - 1;
								break;
							case UIEDITMODE_EA:
								oper = UIITEM_EA_END - 1;
								break;
							default:
								oper = -1;
								break;
							}
						}
					}
					else if(hge->Input_GetDIKey(DIK_DOWN, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_DOWN) && pushtimer == M_PUSH_FIRST)
					{
						oper += 2;
						switch(editmode)
						{
						case UIEDITMODE_EB:
							if(oper > UIITEM_EB_END)
								oper = UIITEM_ITEMBEGIN + 1;
							break;
						case UIEDITMODE_EE:
							if(oper > UIITEM_EE_END)
								oper = UIITEM_ITEMBEGIN + 1;
							break;
						case UIEDITMODE_EA:
							if(oper > UIITEM_EA_END)
								oper = UIITEM_ITEMBEGIN + 1;
							break;
						default:
							oper = -1;
							break;
						}
					}
					else
						oper = -1;
				}
				else
					oper = -1;

				if(oper >= 0)
				{
					Operate();
				}
			}
			else
			{
				strcpy(input, "");
			}
		}
	}

	char buff[M_STRITOAMAX];
	switch(editmode)
	{
	case 0:
		strcpy(title, "Title");
		break;
	case UIEDITMODE_EB:
		if(eres.eff[ebnum])
		{
			sprintf(title, "EffectSystem_%03d", ebnum);
		}
		else
		{
			strcpy(title, "Title");
		}
		break;
	case UIEDITMODE_EE:
		if(emitter)
		{
			strcpy(title, "Emitter_");
			strcat(title, hge->Math_itoa(ebnum, buff));
			strcat(title, "_");
			strcat(title, hge->Math_itoa(emitter->ID, buff));
		}
		else
		{
			strcpy(title, "Title");
		}
		break;
	case UIEDITMODE_EA:
		if(affector)
		{
			strcpy(title, eres.GetAffectorName(affector->eai.type));
			strcat(title, "_");
			strcat(title, hge->Math_itoa(ebnum, buff));
			strcat(title, "_");
			strcat(title, hge->Math_itoa(emitter->ID, buff));
			strcat(title, "_");
			strcat(title, hge->Math_itoa(affector->ID, buff));
		}
		else
		{
			strcpy(title, "Title");
		}
		break;
	}

	nlives = 0;
	nobj = 0;
	if(eres.eff[ebnum])
	{
		if(mx < M_ACTIVECLIENT_RIGHT)
			eres.eff[ebnum]->MoveTo(mx, my, zpos);
		eres.eff[ebnum]->Update();

		nlives = eres.eff[ebnum]->GetEffectObjectAlive(0, &nobj);
	}

	if(hge->Input_GetDIKey(DIK_RCONTROL))
	{
		strcpy(addinfo, "Delete");
	}
	else
	{
		strcpy(addinfo, "Add");
	}

	if(oper == -1)
	{
		if(hge->Input_GetDIKey(DIK_LEFT) || hge->Input_GetDIKey(DIK_RIGHT))
		{
			if(pushtimer < M_PUSH_FIRST)
				pushtimer++;
			else if(pushtimer == M_PUSH_FIRST)
				pushtimer = M_PUSH_FIRST - M_PUSH_SKIP;
		}
		else
			pushtimer = 0;

		if(!hge->Input_GetDIKey(DIK_RCONTROL) && hge->Input_GetDIKey(DIK_PRIOR, DIKEY_DOWN))
			PageUp();
		else if(!hge->Input_GetDIKey(DIK_RCONTROL) && hge->Input_GetDIKey(DIK_NEXT, DIKEY_DOWN))
			PageDown();
		else if(hge->Input_GetDIKey(DIK_TAB, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_RIGHT, DIKEY_DOWN) || pushtimer == M_PUSH_FIRST)
		{
			BYTE _info = 0;
			switch(editmode)
			{
			case UIEDITMODE_EB:
				_info = UIITEM_EEINFO;
				break;
			case UIEDITMODE_EE:
				_info = UIITEM_EAINFO;
				break;
			case UIEDITMODE_EA:
				_info = UIITEM_EBINFO;
				break;
			}
			ChangePanel(_info);
		}
		else if(hge->Input_GetDIKey(DIK_LEFT, DIKEY_DOWN) || pushtimer == M_PUSH_FIRST)
		{
			BYTE _info = 0;
			switch(editmode)
			{
			case UIEDITMODE_EB:
				_info = UIITEM_EAINFO;
				break;
			case UIEDITMODE_EE:
				_info = UIITEM_EBINFO;
				break;
			case UIEDITMODE_EA:
				_info = UIITEM_EEINFO;
				break;
			}
			ChangePanel(_info);
		}
		else if(hge->Input_GetDIKey(DIK_END, DIKEY_DOWN) && !hge->Input_GetDIKey(DIK_RCONTROL) || 
			isListNull() && (hge->Input_GetDIKey(DIK_UP, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_DOWN, DIKEY_DOWN)))
		{
			Add();
		}
		else if(hge->Input_GetDIKey(DIK_END, DIKEY_DOWN) && hge->Input_GetDIKey(DIK_RCONTROL))
		{
			Delete();
		}

		else if(hge->Input_GetDIKey(DIK_UP ,DIKEY_DOWN) || pushtimer == M_PUSH_FIRST)
		{
			if(editmode && oper == -1)
			{
				switch(editmode)
				{
				case UIEDITMODE_EB:
					if(eres.eff[ebnum])
						oper = UIITEM_EB_END - 1;
					break;
				case UIEDITMODE_EE:
					if(eres.eff[ebnum] && emitter && emitterItem)
						oper = UIITEM_EE_END - 1;
					break;
				case UIEDITMODE_EA:
					if(eres.eff[ebnum] && emitter && emitterItem && affector && affectorItem)
						oper = UIITEM_EA_END - 1;
					break;
				}
			}
			if(oper >= 0)
				Operate();
		}
		else if(hge->Input_GetDIKey(DIK_DOWN, DIKEY_DOWN))
		{
			if(editmode && oper == -1)
			{
				switch(editmode)
				{
				case UIEDITMODE_EB:
					if(eres.eff[ebnum])
						oper = UIITEM_ITEMBEGIN + 1;
					break;
				case UIEDITMODE_EE:
					if(eres.eff[ebnum] && emitter && emitterItem)
						oper = UIITEM_ITEMBEGIN + 1;
					break;
				case UIEDITMODE_EA:
					if(eres.eff[ebnum] && emitter && emitterItem && affector && affectorItem)
						oper = UIITEM_ITEMBEGIN + 1;
					break;
				}
			}
			if(oper >= 0)
				Operate();
		}
		else if(hge->Input_GetDIKey(DIK_RCONTROL) && hge->Input_GetDIKey(DIK_DELETE, DIKEY_DOWN))
		{
			Delete();
		}
		else if(hge->Input_GetDIKey(DIK_HOME, DIKEY_DOWN))
		{
			Refresh();
		}
		else if(hge->Input_GetDIKey(DIK_INSERT, DIKEY_DOWN))
		{
			Save();
		}
	}
}

bool EditorUI::UpdateInput()
{
	if(hge->Input_GetDIKey(DIK_UP) || hge->Input_GetDIKey(DIK_DOWN))
	{
		if(pushtimer < M_PUSH_FIRST)
			pushtimer++;
		else if(pushtimer == M_PUSH_FIRST)
			pushtimer = M_PUSH_FIRST - M_PUSH_SKIP;
	}
	else
		pushtimer = 0;
	if(hge->Input_GetDIKey(DIK_RETURN, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPADENTER, DIKEY_DOWN))
	{
		return true;
	}
	if(oper >= UIITEM_ITEMBEGIN && (hge->Input_GetDIKey(DIK_UP, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_DOWN, DIKEY_DOWN) || pushtimer == M_PUSH_FIRST))
	{
		return true;
	}
	if(hge->Input_GetDIKey(DIK_0, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD0, DIKEY_DOWN))
	{
		bool link = true;
		if(eres.iteminfo[oper].inputtype != UIINPUTTYPE_DWORD && 
			(input[0] == '0' || input[0] == '-' && (eres.iteminfo[oper].inputtype == UIINPUTTYPE_INT && strlen(input) < 2 || input[1] == '0')))
		{
			link = false;
			if(eres.iteminfo[oper].inputtype == UIINPUTTYPE_FLOAT)
			{
				for(int i=0; i<strlen(input); i++)
				{
					if(input[i] == '.')
					{
						link = true;
						break;
					}
				}
			}
		}
		if(link)
			strcat(input, "0");
	}
	else if(hge->Input_GetDIKey(DIK_1, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD1, DIKEY_DOWN))
	{
		input[UIEDITINPUT_MAX] = 0;
		strcat(input, "1");
	}
	else if(hge->Input_GetDIKey(DIK_2, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD2, DIKEY_DOWN))
	{
		input[UIEDITINPUT_MAX] = 0;
		strcat(input, "2");
	}
	else if(hge->Input_GetDIKey(DIK_3, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD3, DIKEY_DOWN))
	{
		input[UIEDITINPUT_MAX] = 0;
		strcat(input, "3");
	}
	else if(hge->Input_GetDIKey(DIK_4, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD4, DIKEY_DOWN))
	{
		input[UIEDITINPUT_MAX] = 0;
		strcat(input, "4");
	}
	else if(hge->Input_GetDIKey(DIK_5, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD5, DIKEY_DOWN))
	{
		input[UIEDITINPUT_MAX] = 0;
		strcat(input, "5");
	}
	else if(hge->Input_GetDIKey(DIK_6, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD6, DIKEY_DOWN))
	{
		input[UIEDITINPUT_MAX] = 0;
		strcat(input, "6");
	}
	else if(hge->Input_GetDIKey(DIK_7, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD7, DIKEY_DOWN))
	{
		input[UIEDITINPUT_MAX] = 0;
		strcat(input, "7");
	}
	else if(hge->Input_GetDIKey(DIK_8, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD8, DIKEY_DOWN))
	{
		input[UIEDITINPUT_MAX] = 0;
		strcat(input, "8");
	}
	else if(hge->Input_GetDIKey(DIK_9, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD9, DIKEY_DOWN))
	{
		input[UIEDITINPUT_MAX] = 0;
		strcat(input, "9");
	}
	else if(hge->Input_GetDIKey(DIK_MINUS, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_SUBTRACT, DIKEY_DOWN))
	{
		bool link = true;
		if(strlen(input) != 0 || eres.iteminfo[oper].inputtype == UIINPUTTYPE_DWORD)
		{
			link = false;
		}
		if(link)
			strcat(input, "-");
	}
	else if(hge->Input_GetDIKey(DIK_PERIOD, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_DECIMAL, DIKEY_DOWN))
	{
		if(eres.iteminfo[oper].inputtype == UIINPUTTYPE_FLOAT)
		{
			bool link = true;
			for(int i=0; i<strlen(input); i++)
			{
				if(input[i] == '.')
				{
					link = false;
					break;
				}
			}
			if(link)
				strcat(input, ".");
		}
	}
	else if(hge->Input_GetDIKey(DIK_A, DIKEY_DOWN))
	{
		if(eres.iteminfo[oper].inputtype == UIINPUTTYPE_DWORD)
			strcat(input, "A");
	}
	else if(hge->Input_GetDIKey(DIK_B, DIKEY_DOWN))
	{
		if(eres.iteminfo[oper].inputtype == UIINPUTTYPE_DWORD)
			strcat(input, "B");
	}
	else if(hge->Input_GetDIKey(DIK_C, DIKEY_DOWN))
	{
		if(eres.iteminfo[oper].inputtype == UIINPUTTYPE_DWORD)
			strcat(input, "C");
	}
	else if(hge->Input_GetDIKey(DIK_D, DIKEY_DOWN))
	{
		if(eres.iteminfo[oper].inputtype == UIINPUTTYPE_DWORD)
			strcat(input, "D");
	}
	else if(hge->Input_GetDIKey(DIK_E, DIKEY_DOWN))
	{
		if(eres.iteminfo[oper].inputtype == UIINPUTTYPE_DWORD)
			strcat(input, "E");
	}
	else if(hge->Input_GetDIKey(DIK_F, DIKEY_DOWN))
	{
		if(eres.iteminfo[oper].inputtype == UIINPUTTYPE_DWORD)
			strcat(input, "F");
	}

	if(eres.iteminfo[oper].inputtype == UIINPUTTYPE_DWORD)
	{
		input[8] = 0;
	}
	else
	{
		input[UIEDITINPUT_MAX + 1] = 0;
	}

	if(eres.iteminfo[oper].inputtype == UIINPUTTYPE_FLOAT)
	{
		char buffer[M_STRITOAMAX];
		strcpy(buffer, input);
		fval = (float)atof(buffer);
	}
	else if(eres.iteminfo[oper].inputtype == UIINPUTTYPE_INT)
	{
		if(input[0] == '0' && strlen(input) > 1)
		{
			strcpy(input, &input[1]);
		}

		char buffer[M_STRITOAMAX];
		strcpy(buffer, input);
		ival = atoi(buffer);
	}
	else if(eres.iteminfo[oper].inputtype == UIINPUTTYPE_DWORD)
	{
		sscanf(input, "%x", &uval);
	}
	return false;
}

bool EditorUI::Delete()
{
	if(editmode == 0)
		return false;
	if(editmode == UIEDITMODE_EB)
	{
		char buffer[M_STRMAX];
		strcpy(buffer, "Delete ");
		strcat(buffer, eres.GetFullFilename(ebnum));
		strcat(buffer, " ?");
		if(hge->System_MessageBox(buffer, "", MB_OKCANCEL) == IDOK)
		{
			Data::data.SetEffectSystemResourceName(ebnum, "");
			hge->Resource_DeleteFile(hge->Resource_MakePath(eres.fullfilename));
			delete eres.eff[ebnum];
			eres.eff[ebnum] = NULL;
			eres.texnum[ebnum] = -1;
			PageDown();
		}
		SetupEB(true);
		return true;
	}
	if(editmode == UIEDITMODE_EE)
	{
		if(!eres.eff[ebnum])
			return false;
		if(emitter && emitterItem)
		{
			char buffer[M_STRMAX];
			strcpy(buffer, "Delete ");
			strcat(buffer, title);
			strcat(buffer, " ? (");
			strcat(buffer, eres.GetFullFilename(ebnum));
			strcat(buffer, ")");
			if(hge->System_MessageBox(buffer, "", MB_OKCANCEL) == IDOK)
			{
				int delID = emitter->ID;

				eres.eff[ebnum]->DeleteEmitter(delID);
				emitterItem = eres.eff[ebnum]->eiList;

				CEmitterList * _emitterItem = emitterItem;
				while (_emitterItem)
				{
					if (_emitterItem->emitter.ID > delID)
					{
						_emitterItem->emitter.ID--;
					}
					_emitterItem = _emitterItem->next;
				}

				if(emitterItem)
					emitter = &(emitterItem->emitter);
				else
					emitter = NULL;

			}
			SetupEE(true);
		}
		return true;
	}
	if(editmode == UIEDITMODE_EA)
	{
		if(!eres.eff[ebnum] || !emitter || !emitterItem)
			return false;
		if(affector && affectorItem)
		{
			char buffer[M_STRMAX];
			strcpy(buffer, "Delete ");
			strcat(buffer, title);
			strcat(buffer, " ? (");
			strcat(buffer, eres.GetFullFilename(ebnum));
			strcat(buffer, ")");
			if(hge->System_MessageBox(buffer, "", MB_OKCANCEL) == IDOK)
			{
				int delID = affector->ID;

				eres.eff[ebnum]->DeleteAffector(emitter->ID, delID);
				affectorItem = emitter->eaiList;

				CAffectorList * _affectorItem = affectorItem;
				while (_affectorItem)
				{
					if (_affectorItem->affector.ID > delID)
					{
						_affectorItem->affector.ID--;
					}
					_affectorItem = _affectorItem->next;
				}

				if(affectorItem)
					affector = &(affectorItem->affector);
				else
					affector = NULL;
			}
			SetupEA();
		}
		return true;
	}
	return false;
}

bool EditorUI::Add()
{
	if(editmode == 0)
		return false;
	if(editmode == UIEDITMODE_EB)
	{
		int i = 0;
		for(; i<EFFECTSYSTYPEMAX; i++)
		{
			if(!eres.eff[i])
				break;
		}
		if(i >= 0 && i < EFFECTSYSTYPEMAX)
		{
			if(!eres.eff[i])
			{
				char buffer[M_STRMAX];
				char buff[M_STRITOAMAX];
				sprintf(buffer, "EffectSystem_%03d.effect", i);
				Data::data.SetEffectSystemResourceName(i, buffer);
				eres.eff[i] = new hgeEffectSystem;
				ZeroMemory(eres.eff[i], sizeof(hgeEffectSystem));
				ebnum = i;
				SetupEB(true);
				return true;
			}
		}
		return false;
	}
	if(editmode == UIEDITMODE_EE)
	{
		if(!eres.eff[ebnum])
			return false;
		int i = 1;

		CEmitterList * _emitterItem = eres.eff[ebnum]->eiList;
		while(_emitterItem)
		{
			i++;
			_emitterItem = _emitterItem->next;
		}

		if(i > 0 && i < HGEEFFECT_EMITTERMAX)
		{
			_emitterItem = eres.eff[ebnum]->eiList;

			hgeEffectEmitterInfo _eei;
			ZeroMemory(&_eei, sizeof(hgeEffectEmitterInfo));
			eres.eff[ebnum]->AddEmitter(i, &_eei);

			emitterItem = NULL;
			emitter = NULL;
			_emitterItem = eres.eff[ebnum]->eiList;
			while(_emitterItem)
			{
				if(_emitterItem->emitter.ID == i)
				{
					emitterItem = _emitterItem;
					emitter = &(emitterItem->emitter);
					break;
				}
				_emitterItem = _emitterItem->next;
			}
			emitter->sprite->SetTexture(eres.eff[ebnum]->ebi.tex);
			SetupEE(true);
			return true;
		}
		return false;
	}
	if(editmode == UIEDITMODE_EA)
	{
		if(!eres.eff[ebnum] || !emitter || !emitterItem)
			return false;
		int i = 1;

		CAffectorList * _affectorItem = emitter->eaiList;
		while(_affectorItem)
		{
			i++;
			_affectorItem = _affectorItem->next;
		}

		if(i > 0 && i < HGEEFFECT_AFFECTORMAX)
		{
			_affectorItem = emitter->eaiList;
			hgeEffectAffectorInfo _eai;
			ZeroMemory(&_eai, sizeof(hgeEffectAffectorInfo));
			eres.eff[ebnum]->AddAffector(emitter->ID, i, &_eai);

			affectorItem = NULL;
			affector = NULL;
			_affectorItem = emitter->eaiList;
			while(_affectorItem)
			{
				if(_affectorItem->affector.ID == i)
				{
					affectorItem = _affectorItem;
					affector = &(affectorItem->affector);
					break;
				}
				_affectorItem = _affectorItem->next;
			}
			SetupEA();
			return true;
		}
		return false;
	}
	return false;
}

bool EditorUI::ChangeBGTex(int texnum)
{
	if(texnum == -1)
	{
		bool bFound = false;
		int i;
		for(i=eres.bgtex+1; i<TEXMAX; i++)
		{
			if(eres.tex[i].tex)
			{
				bFound = true;
				break;
			}
		}
		if(!bFound)
		{
			for(i=0; i<eres.bgtex; i++)
			{
				if(eres.tex[i].tex)
				{
					bFound = true;
					break;
				}
			}
		}
		if(bFound)
			texnum = i;
	}

	if(eres.tex[texnum].tex)
	{
		eres.bg->SetTexture(eres.tex[texnum]);
		eres.bg->SetTextureRect(0, 0, hge->Texture_GetWidth(eres.tex[texnum]), hge->Texture_GetHeight(eres.tex[texnum]));
		eres.bgtex = texnum;
		return true;
	}
	return false;
}

bool EditorUI::UpdateValue()
{
	if(!strlen(input))
		return true;
	if(oper > UIITEM_ITEMBEGIN)
	{
		if(editmode == UIEDITMODE_EB)
		{
			return EditEB();
		}
		if(editmode == UIEDITMODE_EE)
		{
			return EditEE();
		}
		if(editmode == UIEDITMODE_EA)
		{
			return EditEA();
		}
		return true;
	}
	return false;
}

bool EditorUI::EditEB()
{
	if(isListNull())
		return true;
	if(oper == UIITEM_EB_NLIFETIME_VALUE)
	{
		if(ival >= 0)
		{
			eres.eff[ebnum]->ebi.nLifeTime = ival;
			SetupEB();
			return true;
		}
	}
	else if(oper == UIITEM_EB_NREPEATDELAY_VALUE)
	{
		if(ival >= 0)
		{
			eres.eff[ebnum]->ebi.nRepeatDelay = ival;
			SetupEB();
			return true;
		}
	}
	else if(oper == UIITEM_EB_TEX_VALUE)
	{
		if(ival >= 0 && ival < TEXMAX)
		{
			if(eres.tex[ival].tex)
			{
				eres.eff[ebnum]->ebi.tex = eres.tex[ival];
				eres.texnum[ebnum] = ival;

				CEmitterList * _emitterItem = eres.eff[ebnum]->eiList;
				while(_emitterItem)
				{
					_emitterItem->emitter.sprite->SetTexture(eres.tex[ival]);
					_emitterItem = _emitterItem->next;
				}
				SetupEB();
				return true;
			}
		}
	}
	return false;
}

bool EditorUI::EditEE()
{
	if(isListNull())
		return true;
	if(oper == UIITEM_EE_NSTARTTIME_VALUE)
	{
		if(ival >= 0)
		{
			emitter->eei.nStartTime = ival;
			if(emitter->eei.nEndTime < ival)
				emitter->eei.nEndTime = ival;
			SetupEE();
			return true;
		}
	}
	else if(oper == UIITEM_EE_NENDTIME_VALUE)
	{
		if(ival >= 0)
		{
			emitter->eei.nEndTime = ival;
			if(emitter->eei.nStartTime > ival)
				emitter->eei.nStartTime = ival;
			SetupEE();
			return true;
		}
	}
	else if(oper == UIITEM_EE_NLIFETIMEMIN_VALUE)
	{
		if(ival >= 0)
		{
			emitter->eei.nLfieTimeMin = ival;
			if(emitter->eei.nLifeTimeMax < ival)
				emitter->eei.nLifeTimeMax = ival;
			SetupEE();
			return true;
		}
	}
	else if(oper == UIITEM_EE_NLIFETIMEMAX_VALUE)
	{
		if(ival >= 0)
		{
			emitter->eei.nLifeTimeMax = ival;
			if(emitter->eei.nLfieTimeMin > ival)
				emitter->eei.nLfieTimeMin = ival;
			SetupEE();
			return true;
		}
	}
	else if(oper == UIITEM_EE_FEMITNUM_VALUE)
	{
		if(fval >= 0)
		{
			emitter->eei.fEmitNum = fval;
			SetupEE();
			return true;
		}
	}
	else if(oper == UIITEM_EE_FROTATIONX_VALUE)
	{
		emitter->eei.fRotationX = fval;
		SetupEE();
		return true;
	}
	else if(oper == UIITEM_EE_FROTATIONY_VALUE)
	{
		emitter->eei.fRotationY = fval;
		SetupEE();
		return true;
	}
	else if(oper == UIITEM_EE_FRADIUS_VALUE)
	{
		if(fval >= 0)
		{
			emitter->eei.fRadius = fval;
			if(emitter->eei.fRadiusInner > fval)
				emitter->eei.fRadiusInner = fval;
			SetupEE();
			return true;
		}
	}
	else if(oper == UIITEM_EE_FRADIUSINNER_VALUE)
	{
		if(fval >= 0)
		{
			emitter->eei.fRadiusInner = fval;
			if(emitter->eei.fRadius < fval)
				emitter->eei.fRadius = fval;
			SetupEE();
			return true;
		}
	}
	else if(oper == UIITEM_EE_FTHETASTART_VALUE)
	{
		emitter->eei.fThetaStart = fval;
		SetupEE();
		return true;
	}
	else if(oper == UIITEM_EE_FTHETASTEP_VALUE)
	{
		emitter->eei.fThetaStep = fval;
		SetupEE();
		return true;
	}
	else if(oper == UIITEM_EE_FTRACERESISTANCE_VALUE)
	{
		emitter->eei.fTraceResistance = fval;
		SetupEE();
		return true;
	}
	else if(oper == UIITEM_EE_FTEXTUREX_VALUE)
	{
		emitter->eei.fTextureX = fval;
		emitter->sprite->SetTextureRect(emitter->eei.fTextureX, emitter->eei.fTextureY, emitter->eei.fTextureW, emitter->eei.fTextureH);
		SetupEE();
		return true;
	}
	else if(oper == UIITEM_EE_FTEXTUREY_VALUE)
	{
		emitter->eei.fTextureY = fval;
		emitter->sprite->SetTextureRect(emitter->eei.fTextureX, emitter->eei.fTextureY, emitter->eei.fTextureW, emitter->eei.fTextureH);
		SetupEE();
		return true;
	}
	else if(oper == UIITEM_EE_FTEXTUREW_VALUE)
	{
		emitter->eei.fTextureW = fval;
		emitter->sprite->SetTextureRect(emitter->eei.fTextureX, emitter->eei.fTextureY, emitter->eei.fTextureW, emitter->eei.fTextureH);
		SetupEE();
		return true;
	}
	else if(oper == UIITEM_EE_FTEXTUREH_VALUE)
	{
		emitter->eei.fTextureH = fval;
		emitter->sprite->SetTextureRect(emitter->eei.fTextureX, emitter->eei.fTextureY, emitter->eei.fTextureW, emitter->eei.fTextureH);
		SetupEE();
		return true;
	}
	else if(oper == UIITEM_EE_FHOTX_VALUE)
	{
		emitter->eei.fHotX = fval;
		emitter->sprite->SetHotSpot(emitter->eei.fHotX, emitter->eei.fHotY);
		SetupEE();
		return true;
	}
	else if(oper == UIITEM_EE_FHOTY_VALUE)
	{
		emitter->eei.fHotY = fval;
		emitter->sprite->SetHotSpot(emitter->eei.fHotX, emitter->eei.fHotY);
		SetupEE();
		return true;
	}
	else if(oper == UIITEM_EE_BLEND_VALUE)
	{
		if(ival >= 0 && ival < 8)
		{
			emitter->eei.blend = ival;
			emitter->sprite->SetBlendMode(ival);
			SetupEE();
			return true;
		}
	}
	else if(oper == UIITEM_EE_BTRACE_VALUE)
	{
		if(ival)
			emitter->eei.bTrace = 1;
		else
			emitter->eei.bTrace = 0;
		SetupEE();
		return true;
	}
	else if(oper == UIITEM_EE_BADJUSTDIRECTION_VALUE)
	{
		if(ival)
			emitter->eei.bAdjustDirection = 1;
		else
			emitter->eei.bAdjustDirection = 0;
		SetupEE();
		return true;
	}
	return false;
}

bool EditorUI::EditEA()
{
	if(isListNull())
		return true;

	bool dwordmode = false;
	if(affector->eai.type == HGEEFFECT_AFFECTORTYPE_COLOR)
		dwordmode = true;

	if(oper == UIITEM_EA_NAFFECTORSTARTTIME_VALUE)
	{
		if(ival >= 0)
		{
			affector->eai.nAffectorStartTime = ival;
			if(affector->eai.nAffectorEndTime < ival)
				affector->eai.nAffectorEndTime = ival;
			SetupEA();
			return true;
		}
	}
	else if(oper == UIITEM_EA_NAFFECTORENDTIME_VALUE)
	{
		if(ival >= 0)
		{
			affector->eai.nAffectorEndTime = ival;
			if(affector->eai.nAffectorStartTime > ival)
				affector->eai.nAffectorStartTime = ival;
			SetupEA();
			return true;
		}
	}
	else if(oper == UIITEM_EA_NRANDOMPICKINTERVAL_VALUE)
	{
		if(ival >= 0)
		{
			affector->eai.nRandomPickInterval = ival;
			SetupEA();
			return true;
		}
	}
	else if(oper == UIITEM_EA_FSTARTVALUEMIN_VALUE)
	{
		if(dwordmode)
		{
			affector->eai.fStartValueMin = *(float *)&uval;
			DWORD maxval = *(DWORD *)(&(affector->eai.fStartValueMax));
			if(GETA(maxval) < GETA(uval) ||
				GETR(maxval) < GETR(uval) ||
				GETG(maxval) < GETG(uval) ||
				GETB(maxval) < GETB(uval))
				affector->eai.fStartValueMax = *(float *)&uval;
		}
		else
		{
			affector->eai.fStartValueMin = fval;
			if(affector->eai.fStartValueMax < fval)
				affector->eai.fStartValueMax = fval;
		}
		SetupEA();
		return true;
	}
	else if(oper == UIITEM_EA_FSTARTVALUEMAX_VALUE)
	{
		if(dwordmode)
		{
			affector->eai.fStartValueMax = *(float *)&uval;
			DWORD minval = *(DWORD *)(&(affector->eai.fStartValueMin));
			if(GETA(minval) > GETA(uval) ||
				GETR(minval) > GETR(uval) ||
				GETG(minval) > GETG(uval) ||
				GETB(minval) > GETB(uval))
				affector->eai.fStartValueMin = *(float *)&uval;
		}
		else
		{
			affector->eai.fStartValueMax = fval;
			if(affector->eai.fStartValueMin > fval)
				affector->eai.fStartValueMin = fval;
		}
		SetupEA();
		return true;
	}
	else if(oper == UIITEM_EA_FENDVALUEMIN_VALUE)
	{
		if(dwordmode)
		{
			affector->eai.fEndValueMin = *(float *)&uval;
			DWORD maxval = *(DWORD *)(&(affector->eai.fEndValueMax));
			if(GETA(maxval) < GETA(uval) ||
				GETR(maxval) < GETR(uval) ||
				GETG(maxval) < GETG(uval) ||
				GETB(maxval) < GETB(uval))
				affector->eai.fEndValueMax = *(float *)&uval;
		}
		else
		{
			affector->eai.fEndValueMin = fval;
			if(affector->eai.fEndValueMax < fval)
				affector->eai.fEndValueMax = fval;
		}
		SetupEA();
		return true;
	}
	else if(oper == UIITEM_EA_FENDVALUEMAX_VALUE)
	{
		if(dwordmode)
		{
			affector->eai.fEndValueMax = *(float *)&uval;
			DWORD minval = *(DWORD *)(&(affector->eai.fEndValueMin));
			if(GETA(minval) > GETA(uval) ||
				GETR(minval) > GETR(uval) ||
				GETG(minval) > GETG(uval) ||
				GETB(minval) > GETB(uval))
				affector->eai.fEndValueMin = *(float *)&uval;
		}
		else
		{
			affector->eai.fEndValueMax = fval;
			if(affector->eai.fEndValueMin > fval)
				affector->eai.fEndValueMin = fval;
		}
		SetupEA();
		return true;
	}
	else if(oper == UIITEM_EA_FINCREMENTVALUEMIN_VALUE)
	{
		if(dwordmode)
		{
			affector->eai.fIncrementValueMin = *(float *)&uval;
			DWORD maxval = *(DWORD *)(&(affector->eai.fIncrementValueMax));
			if(GETA(maxval) < GETA(uval) ||
				GETR(maxval) < GETR(uval) ||
				GETG(maxval) < GETG(uval) ||
				GETB(maxval) < GETB(uval))
				affector->eai.fIncrementValueMax = *(float *)&uval;
		}
		else
		{
			affector->eai.fIncrementValueMin = fval;
			if(affector->eai.fIncrementValueMax < fval)
				affector->eai.fIncrementValueMax = fval;
		}
		SetupEA();
		return true;
	}
	else if(oper == UIITEM_EA_FINCREMENTVALUEMAX_VALUE)
	{
		if(dwordmode)
		{
			affector->eai.fIncrementValueMax = *(float *)&uval;
			DWORD minval = *(DWORD *)(&(affector->eai.fIncrementValueMin));
			if(GETA(minval) > GETA(uval) ||
				GETR(minval) > GETR(uval) ||
				GETG(minval) > GETG(uval) ||
				GETB(minval) > GETB(uval))
				affector->eai.fIncrementValueMin = *(float *)&uval;
		}
		else
		{
			affector->eai.fIncrementValueMax = fval;
			if(affector->eai.fIncrementValueMin > fval)
				affector->eai.fIncrementValueMin = fval;
		}
		SetupEA();
		return true;
	}
	else if(oper == UIITEM_EA_FINCREMENTSCALE_VALUE)
	{
		affector->eai.fIncrementScale = fval;
		SetupEA();
		return true;
	}
	else if (oper == UIITEM_EA_FACCELERATION_VALUE)
	{
		if(dwordmode)
		{
			affector->eai.fAcceleration = *(float *)&uval;
			DWORD minval = *(DWORD *)(&(affector->eai.fAcceleration));
			if(GETA(minval) > GETA(uval) ||
				GETR(minval) > GETR(uval) ||
				GETG(minval) > GETG(uval) ||
				GETB(minval) > GETB(uval))
				affector->eai.fAcceleration = *(float *)&uval;
		}
		else
		{
			affector->eai.fAcceleration = fval;
			if(affector->eai.fAcceleration > fval)
				affector->eai.fAcceleration = fval;
		}
		SetupEA();
		return true;
	}
	else if(oper == UIITEM_EA_BUSESTARTVALUE_VALUE)
	{
		if(ival)
			affector->eai.bUseStartValue = 1;
		else
			affector->eai.bUseStartValue = 0;
		SetupEA();
		return true;
	}
	else if(oper == UIITEM_EA_BUSEENDVALUE_VALUE)
	{
		if(ival)
			affector->eai.bUseEndValue = 1;
		else
			affector->eai.bUseEndValue = 0;
		SetupEA();
		return true;
	}
	else if(oper == UIITEM_EA_TYPE_VALUE)
	{
		if(ival >= HGEEFFECT_AFFECTORTYPE_NONE && ival < HGEEFFECT_AFFECTORTYPE_END)
		{
			ZeroMemory(&(affector->eai), sizeof(hgeEffectAffectorInfo));
			affector->eai.type = ival;
			SetupEA();
			return true;
		}
	}
	return false;
}

void EditorUI::Render()
{
	if(eres.bg)
	{
//		eres.bg->SetZ(0);
		eres.bg->RenderStretch(M_ACTIVECLIENT_LEFT, M_ACTIVECLIENT_TOP, M_ACTIVECLIENT_RIGHT, M_ACTIVECLIENT_BOTTOM);
	}
	hge->Gfx_RenderLine(mx-5, my, mx+5, my, 0xffffffff, zpos > 0 ? 0 : zpos);
	hge->Gfx_RenderLine(mx, my-5, mx, my+5, 0xffffffff, zpos > 0 ? 0 : zpos);
	if(eres.eff[ebnum])
	{
		eres.eff[ebnum]->Render(Export::GetFarPoint(M_RENDER_NULL));
	}
	if(eres.panel)
	{
		eres.panel->RenderStretch(M_ACTIVECLIENT_RIGHT, M_ACTIVECLIENT_TOP, M_CLIENT_RIGHT, M_ACTIVECLIENT_BOTTOM);
	}
	if(eres.button)
	{
		for(int i=0; i<UIITEMMAX; i++)
		{
			if(eres.iteminfo[i].state)
			{
				if(eres.iteminfo[i].state == UIITEM_STATE_NORMAL)
					eres.button->SetColor(0xff0000aa);
				else if(eres.iteminfo[i].state == UIITEM_STATE_SELECTED)
					eres.button->SetColor(0xff00aaaa);
				else if(eres.iteminfo[i].state == UIITEM_STATE_OVER)
					eres.button->SetColor(0xffaaaa00);
				eres.button->RenderStretch(
					eres.iteminfo[i].x + UIITEM_EDGE,
					eres.iteminfo[i].y + UIITEM_EDGE,
					eres.iteminfo[i].x + eres.iteminfo[i].w - UIITEM_EDGE,
					eres.iteminfo[i].y + eres.iteminfo[i].h - UIITEM_EDGE);
			}
		}
	}
	for(int i=0; i<UIITEMMAX; i++)
	{
		if(eres.iteminfo[i].state)
		{
			eres.font->printfb(eres.iteminfo[i].x, eres.iteminfo[i].y, eres.iteminfo[i].w, eres.iteminfo[i].h, HGETEXT_MIDDLE | HGETEXT_CENTER, eres.iteminfo[i].info);
		}
	}

	if(eres.font)
	{
		char tbuff[M_STRMAX];
		sprintf(tbuff, "%f", hge->Timer_GetFPS(35));
		eres.font->printf(M_ACTIVECLIENT_RIGHT, M_ACTIVECLIENT_BOTTOM - UIITEM_FONT, HGETEXT_RIGHT, tbuff);
		sprintf(tbuff, "(%d, %d, %d) nLives=%d (%d)", (int)mx, (int)my, (int)zpos, nlives, nobj);
		eres.font->printf(M_ACTIVECLIENT_LEFT, M_ACTIVECLIENT_BOTTOM - UIITEM_FONT, HGETEXT_LEFT, tbuff);
	}
}
