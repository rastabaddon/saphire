/*
 * CSignal.h
 *
 *  Created on: 1 lut 2015
 *      Author: rast
 */

#ifndef CSIGNAL_H_
#define CSIGNAL_H_

#include "../include/inc.h"

namespace Saphire {
namespace Core {

class CSignal :public Saphire::IBaseObject {
public:
	CSignal(Saphire::Module::ICoreModule * core);
	virtual ~CSignal();

	void  setupSignalHandlers();
	static void _SIGINT(int _ignored);
	static void _SIGABRT(int _ignored);
	static void _SIGSEGV(int _ignored);
	static void _SIGTERM(int _ignored);
	static void _SIGILL(int _ignored);
	static void _SIGQUIT(int _ignored);
	static void _SIGKILL(int _ignored);

private:
	Saphire::Module::ICoreModule * SPTR_core;

};

extern  CSignal * signals;
extern  volatile std::sig_atomic_t gSignalStatus;

} /* namespace Core */
} /* namespace Saphire */

#endif /* CSIGNAL_H_ */
