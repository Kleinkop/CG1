//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//

// The main file of the plugin. It defines a global register variable
// "global_exercise2" that is initialized when the plugin is loaded.
// The initializer of this variable calls the constructor of "exercise2"
// and thus creates a new view in the viewer.
#include <cgv/base/register.h>
#include "exercise2.h"

using namespace cgv::base;

extern cgv::base::object_registration<exercise2> global_exercise2(""); 
