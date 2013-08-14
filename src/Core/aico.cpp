/*
 * aico.cpp
 *
 *  Created on: 13 Aug 2013
 *      Author: Vladimir Ivan
 */

#include "aico.h"

#define DELNULL(X) if(X!=NULL) delete X; X=NULL;
#define GET_ATTRIBUTE(X,Y) XML_NO_ERROR

namespace SOC {

AICO::AICO() {
	BwdMsg_v=BwdMsg_Vinv=s=Sinv=v=Vinv=r=R=rhat=NULL;
	phiBar=JBar=NULL;
	Psi=b=Binv=q=xhat=NULL;
	s_old=Sinv_old=v_old=Vinv_old=r_old=R_old=rhat_old=b_old=Binv_old=q_old=qhat_old=NULL;
	DampingReference=A=tA=Ainv=invtA=a=B=tB=Winv=Hinv=Q=Abar=tAbar=Vhatinv=vhat=NULL;
	Damping=Tolerance=Cost=Cost_old=b_step=0;
	MaxIterations=Sweep=Scale=0;
	InitBwdMsg=Initialized=false;
	SweepMode = FORWARD;
}

AICO::~AICO() {
	Reset();
}

void AICO::Reset()
{
	DELNULL(BwdMsg_v);
	DELNULL(BwdMsg_Vinv);
	DELNULL(s);
	DELNULL(Sinv);
	DELNULL(v);
	DELNULL(Vinv);
	DELNULL(r);
	DELNULL(R);
	DELNULL(rhat);
	DELNULL(phiBar);
	DELNULL(JBar);
	DELNULL(Psi);
	DELNULL(b);
	DELNULL(Binv);
	DELNULL(q);
	DELNULL(xhat);
	DELNULL(s_old);
	DELNULL(Sinv_old);
	DELNULL(v_old);
	DELNULL(Vinv_old);
	DELNULL(r_old);
	DELNULL(R_old);
	DELNULL(rhat_old);
	DELNULL(b_old);
	DELNULL(Binv_old);
	DELNULL(q_old);
	DELNULL(qhat_old);
	DELNULL(DampingReference);
	DELNULL(A);
	DELNULL(tA);
	DELNULL(Ainv);
	DELNULL(invtA);
	DELNULL(a);
	DELNULL(B);
	DELNULL(tB);
	DELNULL(Winv);
	DELNULL(Hinv);
	DELNULL(Q);
	DELNULL(Abar);
	DELNULL(tAbar);
	DELNULL(Vhatinv);
	DELNULL(vhat);
	Damping=Tolerance=Cost=Cost_old=b_step=0;
	MaxIterations=Sweep=Scale=0;
	InitBwdMsg=false;
	SweepMode = FORWARD;
	Initialized=false;
}

bool AICO::Init(SystemAbstraction* _sys, XMLElement* Data)
{
	Reset();
	uint Mode;
	if(!GetParam(Data, "SweepMode", Mode)) return false; SweepMode=(AICOSweepMode)Mode;
	if(!GetParam(Data, "MaxIterations", MaxIterations)) return false;
	if(!GetParam(Data, "Tolerance", Tolerance)) return false;
	if(!GetParam(Data, "Damping", Damping)) return false;
	if(!GetParam(Data, "InitBwdMsg", InitBwdMsg)) return false;
	InitMessages();
	Initialized=true;
}

void AICO::InitMessages()
{

}

bool AICO::IterateToConvergence(MatrixXd *q_init=NULL)
{
	if(!Initialized) return false;
	if(q_init) InitTrajectory(q_init);
	for(uint k=0; k<MaxIterations; k++)
	{
		double d=Step();
		if(k && d<Tolerance) return true;
	}
	return false;
}

void AICO::InitTrajectory(MatrixXd *q_init)
{

}

double AICO::Step()
{
	return 0;
}

} /* namespace AICO */
