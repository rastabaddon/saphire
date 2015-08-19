/*
 * CSignal.cpp
 *
 *  Created on: 1 lut 2015
 *      Author: rast
 */

#include "CSignal.h"

namespace Saphire {
namespace Core {

  CSignal * signals = NULL;
  volatile std::sig_atomic_t gSignalStatus;

CSignal::CSignal(Saphire::Module::ICoreModule * core) {
	SPTR_core = core;
	signals = this;
	setupSignalHandlers();
}

CSignal::~CSignal() {
	// TODO Auto-generated destructor stub
}

void        CSignal::setupSignalHandlers(){

				//Interupt
				signal((int)SIGINT, Saphire::Core::CSignal::_SIGINT);

				//tERMINATE AND DUMP
				//SIGQUIT
				#ifdef LINUX
					signal((int)SIGQUIT, Saphire::Core::CSignal::_SIGQUIT);

				//Illegal instruction
				//SIGILL
					signal((int)SIGILL, Saphire::Core::CSignal::_SIGILL);

				//SIGKILL
					signal((int)SIGKILL, Saphire::Core::CSignal::_SIGKILL);

				#endif

				//ABORT
				signal((int)SIGABRT, Saphire::Core::CSignal::_SIGABRT);




				//MEMORY CORUPTION
				signal((int)SIGSEGV, Saphire::Core::CSignal::_SIGSEGV);

				//TERMINATE KILL
				signal((int)SIGTERM, Saphire::Core::CSignal::_SIGTERM);

				CSignal::SPTR_core->Debug("SIGNAL","%s","INSTALLED");
			}

#ifdef LINUX
			void CSignal::_SIGKILL(int _ignored){
				if(gSignalStatus) return;
				 gSignalStatus = _ignored;
				 signals->SPTR_core->Debug("SIGNAL","%s","Got siignal: SIGKILL");
				 signals->SPTR_core->Debug("SIGNAL","%s","KILL AND DUMP");
				 signals->SPTR_core->shutdown();
				 return;
			}

			void CSignal::_SIGQUIT(int _ignored){
				if(gSignalStatus) return;
				gSignalStatus = _ignored;
				 signals->SPTR_core->Debug("SIGNAL","%s","Got siignal: SIGILL");
				 signals->SPTR_core->Debug("SIGNAL","%s","tERMINATE AND DUMP");
				 signals->SPTR_core->shutdown();
				 signals->SPTR_core->Debug("SIGNAL","%s","SHUT GO DOWN");
				 return;
			}

			void CSignal::_SIGILL(int _ignored){
				if(gSignalStatus) return;
				gSignalStatus = _ignored;
				 signals->SPTR_core->Debug("SIGNAL","%s","Got siignal: SIGILL");
				 signals->SPTR_core->Debug("SIGNAL","%s","invalid program image, such as invalid instruction");
				 signals->SPTR_core->shutdown();
				 return;
			}
#endif

			 void CSignal::_SIGINT(int _ignored){
				 if(gSignalStatus) return;
				 gSignalStatus = _ignored;
				 signals->SPTR_core->Debug("SIGNAL","%s","Got siignal: SIGNIT");
				 signals->SPTR_core->Debug("SIGNAL","%s","external interrupt, usually initiated by the user");
				 signals->SPTR_core->shutdown();
				 return;
			}

			 void CSignal::_SIGABRT(int _ignored){
				 if(gSignalStatus) return;
				 gSignalStatus = _ignored;
				 signals->SPTR_core->Debug("SIGNAL","%s","Got siignal: _SIGABRT");
				 signals->SPTR_core->Debug("SIGNAL","%s","abnormal termination condition, as is e.g. initiated by std::abort()");
				 signals->SPTR_core->shutdown();
				 return;
			}

			 void CSignal::_SIGSEGV(int _ignored)
			{
				 if(gSignalStatus) return;
				 gSignalStatus = _ignored;
				 signals->SPTR_core->Debug("SIGNAL","%s","Got siignal: _SIGSEGV");
				 signals->SPTR_core->Debug("SIGNAL","%s","invalid memory access (segmentation fault)");
				 signals->SPTR_core->shutdown();
				 return;
			}

			 void CSignal::_SIGTERM(int _ignored)
			{
				 if(gSignalStatus) return;
				 gSignalStatus = _ignored;
				 signals->SPTR_core->Debug("SIGNAL","%s","Got siignal: _SIGTERM");
				 signals->SPTR_core->Debug("SIGNAL","%s","termination request, sent to the program");
				 signals->SPTR_core->shutdown();
				 return;
			}

} /* namespace Core */
} /* namespace Saphire */
