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

#include "Message.h"
#include "RequestMethod.h"

#include <cbang/net/URI.h>

#include <string>
#include <ostream>

namespace cb {
  namespace HTTP {
    class Request : public Message {
      RequestMethod method;
      URI uri;

    public:
      Request(RequestMethod method = RequestMethod::HTTP_UNKNOWN,
              const URI &uri = URI(), float version = 1.1);

      // From Message
      bool isResponse() const override {return false;}
      std::string getHeaderLine() const override;
      void readHeaderLine(const std::string &line) override;

      RequestMethod getMethod() const {return method;}
      void setMethod(RequestMethod method) {this->method = method;}

      const URI &getURI() const {return uri;}
      void setURI(const URI &uri) {this->uri = uri;}
    };

    inline std::ostream &operator<<(std::ostream &stream, const Request &r) {
      return r.write(stream);
    }
  }
}
