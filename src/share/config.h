#ifndef SPINDULYS_CONFIG_H
#define SPINDULYS_CONFIG_H

/// \file share/config.h

#define SPINDULYS_MAJOR_VERSION 0
#define SPINDULYS_MINOR_VERSION 0
#define SPINDULYS_PATCH_VERSION 0

#define SPINDULYS_USE_NAMESPACES 1

#if SPINDULYS_USE_NAMESPACES

#define SPINDULYS_NS spindulys
#define SPINDULYS_FRONTEND_NS spindulysFrontend
#define SPINDULYS_BACKEND_CPU_NS spindulysBackendCPU
#define SPINDULYS_GUI_NS spindulysGUI

#define SPINDULYS_NAMESPACE_OPEN_SCOPE   namespace SPINDULYS_NS {
#define SPINDULYS_NAMESPACE_CLOSE_SCOPE  }

#else

#define SPINDULYS_NS 
#define SPINDULYS_FRONTEND_NS 
#define SPINDULYS_BACKEND_CPU_NS 
#define SPINDULYS_GUI_NS 

#define SPINDULYS_NAMESPACE_OPEN_SCOPE   
#define SPINDULYS_NAMESPACE_CLOSE_SCOPE 

#endif // SPINDULYS_USE_NAMESPACE

#endif //CONFIG_H
