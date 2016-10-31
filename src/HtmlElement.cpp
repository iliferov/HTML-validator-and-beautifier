//
// Created by Liferov Ilia (liferili) on 6/5/16.
//
#include "HtmlElement.h"

using namespace std;

HtmlElement::HtmlElement(string name, bool block, set <string> &attributes) {this->name=name; this->block=block; this->attributes=attributes;}
