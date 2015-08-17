/*
 * ModuleManager.cpp
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#include "CSaphirePhysics.h"
#include <btBulletDynamicsCommon.h>

namespace Saphire {
namespace Module {

		CSaphirePhysics::CSaphirePhysics(Saphire::Module::ICoreModule * core) {
			SPTR_core = core;
			btBroadphaseInterface* broadphase = new btDbvtBroadphase();
			btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
			        btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
		}

		CSaphirePhysics::~CSaphirePhysics() {

		}

		const Saphire::Core::Types::String CSaphirePhysics::getModuleName()
		{
			return Saphire::Core::Types::String("saphire-physics");
		}

} /* namespace Manager */
} /* namespace Saphire */

