//
//  Matrix4.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "Matrix4.h"

namespace Degas {
    std::ostream& operator<<(std::ostream& out, const Matrix4& a)
    {
        out << "<<";
        out << a.m11();
        out << ",";
        out << a.m12();
        out << ",";
        out << a.m13();
        out << ",";
        out << a.m14();
        out << ">\n";
        out << " <";
        out << a.m21();
        out << ",";
        out << a.m22();
        out << ",";
        out << a.m23();
        out << ",";
        out << a.m24();
        out << ">\n";
        out << " <";
        out << a.m31();
        out << ",";
        out << a.m32();
        out << ",";
        out << a.m33();
        out << ",";
        out << a.m34();
        out << ">\n";
        out << " <";
        out << a.m41();
        out << ",";
        out << a.m42();
        out << ",";
        out << a.m43();
        out << ",";
        out << a.m44();
        out << ">>\n";
        return out;
    }
}
