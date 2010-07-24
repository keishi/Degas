//
//  Color.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "Color.h"

namespace Degas {
    
    std::ostream& operator<<(std::ostream& out, const Color& c)
    {
        out << "Color(";
        out << c.red();
        out << ",";
        out << c.green();
        out << ",";
        out << c.blue();
        out << ")";
        return out;
    }
    
}
