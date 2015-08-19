/*
 * ModuleManager.cpp
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#include "CSaphireSound.h"


namespace Saphire {
namespace Module {

		CSaphireSound::CSaphireSound(Saphire::Module::ICoreModule*   core) {
			SPTR_core = core;

			if (!BASS_Init(-1,44100,0,0,NULL))
			{
				SPTR_core->Debug(this->getDebugName(),"Can't initialize device");

			} else {
				SPTR_core->Debug(this->getDebugName(),"Sukcess");

				HSAMPLE sample;
				HCHANNEL channel;

				SPTR_core->Debug(this->getDebugName(),"Try play");

				// load from disk
				if( sample = BASS_SampleLoad(FALSE,"foo.wav",0,0,1,BASS_SAMPLE_OVER_POS) ) {

				    // get playable channel
				    channel = BASS_SampleGetChannel( sample,FALSE);

				    // play
				    BASS_ChannelPlay(channel,TRUE);

				    SPTR_core->Debug(this->getDebugName()," play");

				    // wait for playback to finish
				    while( BASS_ChannelIsActive( channel ) )
				    {
				        //sleep(100);
				    }

				   BASS_SampleFree(sample);
				}

				// cleanup
				BASS_Free();

				SPTR_core->Debug(this->getDebugName(),"Done");
			}

		}

		CSaphireSound::~CSaphireSound() {

		}

		const Saphire::Core::Types::String CSaphireSound::getModuleName()
		{
			return Saphire::Core::Types::String("saphire-sound");
		}

		const Saphire::Core::Types::String CSaphireSound::getDebugName()
		{
					return Saphire::Core::Types::String("BASS");
		}

} /* namespace Manager */
} /* namespace Saphire */
