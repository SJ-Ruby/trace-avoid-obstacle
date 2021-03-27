#include "sys.h"
#include "pid.h"

void Pid_Init(PID* pid,double kp,double ki,double kd) {
	pid->kp=kp;
	pid->ki=ki;
	pid->kd=kd;
}

double Pid_Position(double err,const PID * const pid) {
	static double pre_err=0,sum=0;
	double dif,rate;
	sum+=err;
	dif=err-pre_err;
	pre_err=err;
	rate=err*pid->kp+sum*pid->ki+dif*pid->kd;
	return rate;
}

