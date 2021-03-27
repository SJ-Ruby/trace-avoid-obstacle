#ifndef __PID_H_
#define __PID_H_

typedef struct pid_control{
	double kp;
	double ki;
	double kd;
}PID;

void Pid_Init(PID* pid,double kp,double ki,double kd);
double Pid_Position(double err,const PID * const pid);   //���Ч�� ��Լ�ڴ�ռ�

#endif