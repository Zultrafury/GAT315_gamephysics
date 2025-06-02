#pragma once
#include <vector>
#include "contact.h"
using contacts_t = std::vector<Contact>;
using bodies_t = std::vector<Body*>;

void CreateContacts(const bodies_t& bodies, contacts_t& contacts);
void SeparateContacts(const contacts_t& contacts);
bool Intersects(const Body* bodyA, const Body* bodyB);
