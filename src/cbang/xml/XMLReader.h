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

#pragma once

#include "XMLProcessor.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>


namespace cb {
  class XMLHandlerFactory;
  class XIncludeHandler;

  /// Used to read the XML files.  Also handles <include> tags.
  class XMLReader : public XMLProcessor {
    bool skipRoot;
    unsigned depth;

    struct HandlerRecord;
    std::vector<HandlerRecord> handlers;

    XIncludeHandler *xIncludeHandler;

  public:
    XMLReader(bool skipRoot = true);
    virtual ~XMLReader();

    void read(const std::string &filename, XMLHandler *handler);
    void read(std::istream &stream, XMLHandler *handler);

    // From XMLProcessor
    void pushContext() override;

    // From XMLHandler
    void pushFile(const std::string &filename) override;
    void popFile() override;
    void startElement(
      const std::string &name, const XMLAttributes &attrs) override;
    void endElement(const std::string &name) override;
    void text(const std::string &text) override;
    void cdata(const std::string &data) override;

  protected:
    void push(XMLHandler *handler, XMLHandlerFactory *factory);
    bool pop();
    XMLHandler &get();
  };
}
