/******************************************************************************\

          This file is part of the C! library.  A.K.A the cbang library.

                Copyright (c) 2003-2023, Cauldron Development LLC
                               All rights reserved.

         The C! library is free software: you can redistribute it and/or
        modify it under the terms of the GNU Lesser General Public License
       as published by the Free Software Foundation, either version 2.1 of
               the License, or (at your option) any later version.

        The C! library is distributed in the hope that it will be useful,
          but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
                 Lesser General Public License for more details.

         You should have received a copy of the GNU Lesser General Public
                 License along with the C! library.  If not, see
                         <http://www.gnu.org/licenses/>.

        In addition, BSD licensing may be granted on a case by case basis
        by written permission from at least one of the copyright holders.
           You may request written permission by emailing the authors.

                  For information regarding this software email:
                                 Joseph Coffland
                          joseph@cauldrondevelopment.com

\******************************************************************************/

#include "Session.h"

#include <cbang/json/JSON.h>

using namespace std;
using namespace cb;


Session::Session() {if (!hasDict("group")) insertDict("group");}


Session::Session(const JSON::Value &value) {
  read(value);
  if (!hasDict("group")) insertDict("group");
}


Session::Session(const string &id, const IPAddress &ip) {
  setID(id);
  setCreationTime(Time::now());
  setLastUsed(Time::now());
  setIP(ip.getIP());
  insertDict("group");
}


uint64_t Session::getCreationTime() const {
  return Time::parse(getString("created"));
}


void Session::setCreationTime(uint64_t creationTime) {
  insert("created", Time(creationTime).toString());
}


uint64_t Session::getLastUsed() const {
  return Time::parse(getString("last_used"));
}


void Session::setLastUsed(uint64_t lastUsed) {
  insert("last_used", Time(lastUsed).toString());
}


void Session::matchIP(const IPAddress &ip) const {
  if (ip.getIP() != getIP().getIP())
    THROW("Session IP changed from " << getIP() << " to " << ip);
}


bool Session::hasGroup(const string &group) const {
  return get("group")->getBoolean(group, false);
}


void Session::addGroup(const string &group) {
  get("group")->insertBoolean(group, true);
}


vector<string> Session::getGroups() const {
  vector<string> groups;

  auto g = get("group");
  for (unsigned i = 0; i < g->size(); i++)
    if (g->getBoolean(i)) groups.push_back(g->keyAt(i));

  return groups;
}


void Session::read(const JSON::Value &value) {
  for (unsigned i = 0; i < value.size(); i++)
    insert(value.keyAt(i), value.get(i));
}
