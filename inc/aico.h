/*
 * aico.h
 *
 *  Created on: 13 Aug 2013
 *      Author: Vladimir Ivan
 */

#ifndef AICO_H_
#define AICO_H_

#include "common.h"
#include "Eigen/Dense"
#include "SystemAbstraction.h"

using namespace Eigen;
using namespace tinyxml2;

namespace SOC {

class _SymbolExport AICO {
public:
	enum AICOSweepMode
	{

		FORWARD = 0, ///< Relocate once on forward sweep, not on backward sweep.
		SYMMATRIC, ///< Relocate once on forward and backward sweep.
		LOCAL_GAUSS_NEWTON, ///< Relocate iteratively on forward and backward sweep.
		LOCAL_GAUSS_NEWTON_DAMPED ///< GaussNewton in forward and backward sweep.
	};

private:
	///@name Parameters
	double Damping; ///< Amount of damping.
	double Tolerance; ///< Cost tolerance defining termination criteria.
	uint MaxIterations; ///< Max number of AICO iterations.
	bool InitBwdMsg; ///< Use backward message initialisation.
	MatrixXd* BwdMsg_v; ///< Use backward mean initialisation.
	MatrixXd* BwdMsg_Vinv; ///< Use backward covariance initialisation.
	AICOSweepMode SweepMode; ///< Sweep mode used for iterations.

	///@name Messages
	///@{ Forward message.
	MatrixXd *s, *Sinv; ///@}
	///@{ Backward message.
	MatrixXd *v, *Vinv; ///@}
	///@{ Task message.
	MatrixXd *r, *R, *rhat; ///@}
	///@{ Task cost terms.
	Array<MatrixXd*, Dynamic,1> *phiBar, *JBar; ///@}
	MatrixXd *Psi; ///< All transition cost terms.
	///@{ Belief.
	MatrixXd *b, *Binv; ///@}
	///@{ q-trajectory (MAP), and point of linearization.
	MatrixXd *q, *xhat; ///@}
	///@{ Old message.
	MatrixXd *s_old, *Sinv_old, *v_old, *Vinv_old, *r_old, *R_old, *rhat_old, *b_old, *Binv_old, *q_old, *qhat_old; ///@}
	MatrixXd *DampingReference; ///< Damping reference.
	double Cost; ///< Cost of MAP trajectory.
	double Cost_old; ///< Old cost of MAP trajectory.
	double b_step; ///< Difference between old and new belief.

	///@{ Processes...
	SystemAbstraction* sys; ///< Reference to dynamic system abstraction class.
	MatrixXd *A, *tA, *Ainv, *invtA, *a, *B, *tB, *Winv, *Hinv, *Q, *Abar, *tAbar, *Vhatinv, *vhat; ///@}
	uint Sweep; ///< Number of sweeps so far.
	uint Scale; ///< Scale of this AICO in a multi-scale approach.
	bool Initialized; ///< True if Init() has been called succesfully.

public:
	AICO(); ///< Constructor
	virtual ~AICO(); ///< Destructor
	virtual bool Init(SystemAbstraction* _sys, XMLElement* Data);
	virtual void Reset();
	bool IterateToConvergence(MatrixXd *q_init=NULL);
	void InitTrajectory(MatrixXd *q_init);
	virtual double Step();

protected:
	virtual void InitMessages();
};

} /* namespace AICO */
#endif /* AICO_H_ */
