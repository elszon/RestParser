#include <iostream>

#include "RestParser.h"

using namespace std;

int main()
{

    RestRequest r{RestRequest::Path{"p1","p2"},
                  RestRequest::Items{{"i1","iv1"},{"i2","iv2"}}};


    const auto& p = parseRest("root/request?item1=val1&item2=val2");
    p.getPath();
    cout << "Hello World!" << endl;
    return 0;
}
