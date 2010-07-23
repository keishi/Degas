//
//  Vector3.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "Vector3.h"

namespace Degas {
    std::ostream& operator<<(std::ostream& out, const Vector3& v)
    {
        out << "<";
        out << v.x();
        out << ",";
        out << v.y();
        out << ",";
        out << v.z();
        out << ">";
        return out;
    }
}
