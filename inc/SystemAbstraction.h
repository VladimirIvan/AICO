/*
 * SystemAbstraction.h
 *
 *  Created on: 14 Aug 2013
 *      Author: s0972326
 */

#ifndef SYSTEMABSTRACTION_H_
#define SYSTEMABSTRACTION_H_

#include "common.h"
#include "Eigen/Dense"

using namespace Eigen;

namespace SOC {

class _SymbolExport SystemAbstraction {
public:
	SystemAbstraction();
	virtual ~SystemAbstraction();
	virtual uint GetT();
	MatrixXd GetX0();
	virtual void GetX0(MatrixXd& x);
	virtual void SetX(const MatrixXd& x, uint t);
	virtual bool IsDynamic();
	virtual void GetPositionTrajectory(MatrixXd& q,const MatrixXd& x);
	virtual void GetQ(MatrixXd& x, uint t);
	virtual void GetWinv(MatrixXd& x, uint t);
	virtual void GetHinv(MatrixXd& x, uint t);
	virtual void GetProcess(MatrixXd& A, MatrixXd& a, MatrixXd& B, uint t, MatrixXd& Winv);
	virtual void GetProcess(MatrixXd& A, MatrixXd& a, MatrixXd& B, uint t);
	virtual void GetProcess(MatrixXd& A, MatrixXd& tA, MatrixXd& Ainv, MatrixXd& invtA, MatrixXd& a, MatrixXd& B, MatrixXd& Bt, uint t);
};

} /* namespace SOC */
#endif /* SYSTEMABSTRACTION_H_ */
