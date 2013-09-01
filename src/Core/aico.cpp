/*
 * aico.cpp
 *
 *  Created on: 13 Aug 2013
 *      Author: Vladimir Ivan
 */

#include "aico.h"
#include <iostream>

#define GET_ATTRIBUTE(X,Y) XML_NO_ERROR

using namespace std;

namespace SOC {

AICO::AICO()
{
	sys=NULL;
	Sinv=Vinv=R=NULL;
	BwdMsg_Vinv=BwdMsg_v=s=v=r=rhat=NULL;
	phiBar=JBar=Binv=Sinv_old=Vinv_old=R_old=Binv_old=B=invtA=A=tA=Ainv=tB=Winv=Hinv=Q=Abar=tAbar=NULL;
	b=q=xhat=NULL;
	s_old=v_old=r_old=rhat_old=b_old=q_old=qhat_old=NULL;
	DampingReference=a=vhat=NULL;
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
	if(_sys) {sys=_sys;} else {return false;}
	InitMessages();
	Initialized=true;
	return true;
}

void AICO::InitMessages()
{
	T=sys->GetT();
    MatrixXd x0;
    sys->GetX0(x0);
	uint n=x0.size();
	s = new MatrixXd(T+1,n); s->setZero(); s->row(0)=x0;
	v = new MatrixXd(T+1,n); v->setZero(); if(InitBwdMsg) {v->row(T)=*BwdMsg_v;}
	b = new MatrixXd(T+1,n); b->setZero(); b->row(0)=x0;
	r = new MatrixXd(T+1,n); r->setZero();
	a = new MatrixXd(T+1,n); r->setZero();
	rhat = new MatrixXd(T+1,1); rhat->setZero();
	xhat = new MatrixXd(T+1,n); xhat->setZero(); xhat->row(0) = x0;

	Sinv = new Array<MatrixXd, Dynamic,1>(T+1);
	Vinv = new Array<MatrixXd, Dynamic,1>(T+1);
	Binv = new Array<MatrixXd, Dynamic,1>(T+1);
	R = new Array<MatrixXd, Dynamic,1>(T+1);
	A = new Array<MatrixXd, Dynamic,1>(T+1);
	tA = new Array<MatrixXd, Dynamic,1>(T+1);
	Ainv = new Array<MatrixXd, Dynamic,1>(T+1);
	invtA = new Array<MatrixXd, Dynamic,1>(T+1);
	B = new Array<MatrixXd, Dynamic,1>(T+1);
	Hinv = new Array<MatrixXd, Dynamic,1>(T+1);
	Winv = new Array<MatrixXd, Dynamic,1>(T+1);
	Q = new Array<MatrixXd, Dynamic,1>(T+1);
	phiBar = new Array<MatrixXd, Dynamic,1>(T+1);
	JBar = new Array<MatrixXd, Dynamic,1>(T+1);
	for(uint i=0;i<T+1;i++)
	{
		Sinv->coeffRef(i).resize(n,n); Sinv->coeffRef(i).setZero();
		Vinv->coeffRef(i).resize(n,n); Vinv->coeffRef(i).setZero();
		Binv->coeffRef(i).resize(n,n); Binv->coeffRef(i).setZero();
		R->coeffRef(i).resize(n,n); R->coeffRef(i).setZero();
		A->coeffRef(i).resize(n,n); A->coeffRef(i).setZero();
		tA->coeffRef(i).resize(n,n); tA->coeffRef(i).setZero();
		Ainv->coeffRef(i).resize(n,n); Ainv->coeffRef(i).setZero();
		invtA->coeffRef(i).resize(n,n); invtA->coeffRef(i).setZero();
		Q->coeffRef(i).resize(n,n); Q->coeffRef(i).setZero();
		if(sys->IsDynamic())
		{
			B->coeffRef(i).resize(n,n/2); tB->coeffRef(i).resize(n/2,n);
			Hinv->coeffRef(i).resize(n/2,n/2);
			Winv->coeffRef(i).resize(n/2,n/2);
		}
		else
		{
			B->coeffRef(i).resize(n,n); tB->coeffRef(i).resize(n,n);
			Hinv->coeffRef(i).resize(n,n);
			Winv->coeffRef(i).resize(n,n);
		}
	}
	Sinv->coeffRef(0) = MatrixXd::Identity(n, n) * 1e10;
	Binv->coeffRef(0) = MatrixXd::Identity(n, n) * 1e10;
	if(InitBwdMsg) {Vinv->coeffRef(T)=*BwdMsg_Vinv;}
	
    if(sys->IsDynamic()) sys->GetPositionTrajectory(*q, *b); else *q=*b;
	DampingReference = new MatrixXd(T+1,n); DampingReference->setZero();

    //Initialize system matrices at time 0
    sys->SetX(x0, 0);
    sys->GetQ(Q->coeffRef(0), 0);
    sys->GetHinv(Hinv->coeffRef(0), 0);
    if(!sys->IsDynamic()) sys->GetWinv(Winv->coeffRef(0), 0);
    sys->GetProcess(A->coeffRef(0), tA->coeffRef(0), Ainv->coeffRef(0), invtA->coeffRef(0), (MatrixXd)a->row(0), B->coeffRef(0), tB->coeffRef(0),0);

    RememberOldState();
}

void AICO::RememberOldState()
{

}

bool AICO::IterateToConvergence(MatrixXd *q_init)
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
