#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "tinyxml2.h"

using namespace tinyxml2;

struct Parameter
{
    struct A
    {
        int i;

        std::array<std::vector<int>, 5> a;

        std::vector<int> v;
    };

    struct B
    {
    };

    A a;
    B b;
};

void toVector(tinyxml2::XMLElement *e, std::vector<int> &v)
{
    if (e->GetText() == nullptr)
    {
        return;
    }

    std::stringstream ss(e->GetText());

    std::string s;

    while (std::getline(ss, s, ','))
    {
        v.push_back(std::stoi(s));
    }
}

void toArray(tinyxml2::XMLElement *e, std::array<std::vector<int>, 5> &a)
{
    for (int i = 0; i < a.size(); i++)
    {
        auto name = std::string("番号") + std::to_string(i);

        toVector(e->FirstChildElement(name.c_str()), a[i]);
    }
}

void parseA(tinyxml2::XMLElement *root, Parameter &p)
{
    p.a.i = root->FirstChildElement("要素0")->IntText();

    toArray(root->FirstChildElement("要素1"), p.a.a);

    toVector(root->FirstChildElement("要素2"), p.a.v);
}

void parseB(tinyxml2::XMLElement *root, Parameter &p)
{
}

int main(int argc, char *argv[])
{
    Parameter p;

    XMLDocument doc;
    doc.LoadFile("sample.xml");
    doc.Print();

    auto root = doc.RootElement();

    std::cout << root->Name() << std::endl;

    if (std::string(root->Name()) == "パラメータＡ")
    {
        parseA(root, p);
    }
    else if (std::string(root->Name()) == "パラメータＢ")
    {
        parseB(root, p);
    }

    return 0;
}
