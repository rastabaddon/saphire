/*
 * XNAMESPACES.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */

#ifndef XNAMESPACES_H_
#define XNAMESPACES_H_

//! Core thing`s namespace
namespace Saphire {
	//! Core thing`s namespace
	namespace Boot {}
	//! Core thing`s namespace
	namespace Core {
	//! Types namespace
	namespace Types {

	}
	//! Core thing`s namespace
	namespace APlatformDepended {
		//! Platform specyfic namespace
			namespace Platforms {
				//! Android namespace
				namespace Android {}
				//! Apple namespace
				namespace Apple {}
				//! PlayStation 2 namespace
				namespace PS2 {}
				//! PlayStation 3 namespace
				namespace PS3 {}
				//! Windows namespace
				namespace Windows {}
				//! XBox360 namespace
				namespace XBox360 {}
				//! Linux namespace
				namespace Linux {}
			}
			//! Hardware specyfic namespace
				namespace Hardware {
					//! Memory namespace
					namespace Memory {}
					//! GPGPU namespace
					namespace GPGPU {
						//! CUDA namespace
						namespace CUDA {}
						//! OpenCL namespace
						namespace OpenCL {}
					}
					//! GPU namespace
					namespace GPU {
						//! Intel namespace
						namespace Intel {}
						//! Nvidia namespace
						namespace Nvidia {}
						//! AMD namespace
						namespace AMD {}
					}
					//! CPU namespace
					namespace CPU {
						//! Intel namespace
						namespace Intel {}
						//! AMD namespace
						namespace AMD {}
						//! ARM namespace
						namespace ARM {}
					}
					//! Network namespace
					namespace Network {

					}
					//! Workers namespace
					namespace Workers {

					}
				}
		}
		//! Debuger namespace
		namespace Debuger {

		}

		//! Workers namespace
		namespace Workers {

		}

		//! Scripts namespace
		namespace Scripts {
		//! LUA namespace
			namespace LUA {}
		}
		//! Graphics namespace
		namespace Graphics {
			//! OPENGL namespace
			namespace OpenGL {}
			//! DirectX namespace
			namespace DirectX {
				//! DirectX 9 namespace
				namespace dx9 {}
				//! DirectX 10 namespace
				namespace dx10 {}
				//! DirectX 11 namespace
				namespace dx11 {}
				//! DirectX 12 namespace
				namespace dx12 {}
			}
		}
		//! Video namespace
		namespace Video {
			//! Codecs namespace
			namespace Codecs {}
			//! Input namespace
			namespace Cameras {}
		}
		//! Sounds namespace
		namespace Sounds {
			//! Codecs namespace
			namespace Codecs {}
			//! Inputs namespace
			namespace Inputs {}
			//! Outputs namespace
			namespace Outputs {}
			//! Mixers namespace
			namespace Mixers {}
		}
		//! Files namespace
		namespace Files {
			//! Native namespace
			namespace Native {}
			//! VFS namespace
			namespace VFS {}
		}
		//! Controlers namespace
		namespace Controlers {
			//! Keyboard namespace
			namespace Keyboard {}
			//! Mouse namespace
			namespace Mouse {}
			//! Joystick namespace
			namespace Joystick {}
			//! Pad namespace
			namespace Pad {}
		}
		//! Physics namespace
		namespace Physics {
			//! Bullet namespace
			namespace Bullet {}
		}
		//! Network namespace
		namespace Network {

		}
	}

	namespace Managers {

	}

	namespace Modules {

	}

	namespace Helpers {}
}

#endif /*XNAMESPACES_H_ */
