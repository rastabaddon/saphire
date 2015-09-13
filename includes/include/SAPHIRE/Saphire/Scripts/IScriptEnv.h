/*
 * IScriptEnv.h
 *
 *  Created on: 22 sie 2015
 *      Author: rast
 */

#ifndef INCLUDE_SAPHIRE_SAPHIRE_SCRIPTS_ISCRIPTENV_H_
#define INCLUDE_SAPHIRE_SAPHIRE_SCRIPTS_ISCRIPTENV_H_


namespace Saphire {
	namespace Module {
		class IScriptsModule;
	}
	namespace Core {

		namespace Scripts {

		typedef enum {
			T_SCRIPT_OK = 0,
			T_SCRIPT_ERROR = 1,
			T_SCRIPT_SYNTAX_ERROR=1000,
			T_SCRIPT_UNKNOWN = 9999,
		} T_SCRIPT_ERRORS;

			class IScriptEnv : public Saphire::IBaseObject {
				public:
					virtual Saphire::Module::IScriptsModule *  getScriptEngine()=0;
					virtual const Saphire::Core::Scripts::IScript &  getScript()=0;
					virtual T_SCRIPT_ERRORS execute()=0;
			};

		}
	}
}




#endif /* INCLUDE_SAPHIRE_SAPHIRE_SCRIPTS_ISCRIPTENV_H_ */
