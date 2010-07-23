//
//  Vector4.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "Vector4.h"

namespace Degas {
    std::ostream& operator<<(std::ostream& out, const Vector4& v)
    {
        out << "<";
        out << v.x();
        out << ",";
        out << v.y();
        out << ",";
        out << v.z();
        out << ",";
        out << v.w();
        out << ">";
        return out;
    }
}
