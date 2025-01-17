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

#include "OptionMap.h"
#include "OptionCategory.h"

#include <cbang/json/Serializable.h>

#include <string>
#include <vector>
#include <map>


namespace cb {
  /// A container class for a set of configuration options
  class Options : public OptionMap, public JSON::Serializable {
    typedef std::map<const std::string, SmartPointer<Option> > map_t;
    map_t map;

    typedef std::map<const std::string, SmartPointer<OptionCategory> >
    categories_t;
    categories_t categories;

    typedef std::vector<SmartPointer<OptionCategory> > category_stack_t;
    category_stack_t categoryStack;

  public:
    static bool warnWhenInvalid;

    Options();
    virtual ~Options();

    typedef map_t::iterator iterator;
    typedef map_t::const_iterator const_iterator;

    virtual bool empty() const {return map.empty();}
    virtual iterator begin() {return map.begin();}
    virtual iterator end() {return map.end();}
    virtual const_iterator begin() const {return map.begin();}
    virtual const_iterator end() const {return map.end();}

    virtual std::ostream &print(std::ostream &stream) const;
    virtual void printHelp(std::ostream &stream, bool cmdLine = false) const;

    virtual void insert(JSON::Sink &sink, bool config = false,
                        const std::string &delims =
                        Option::DEFAULT_DELIMS) const;
    virtual void write(JSON::Sink &sink, bool config,
                       const std::string &delims =
                       Option::DEFAULT_DELIMS) const;
    virtual void write(XMLHandler &handler, uint32_t flags = 0) const;
    virtual void printHelpTOC(XMLHandler &handler,
                              const std::string &prefix = std::string()) const;
    virtual void printHelp(XMLHandler &handler,
                           const std::string &prefix = std::string()) const;
    virtual const char *getHelpStyle() const;
    virtual void printHelpPage(XMLHandler &handler) const;
    virtual SmartPointer<JSON::Value> getDict(bool defaults = false,
                                              bool all = false) const;

    virtual const SmartPointer<OptionCategory> &
    getCategory(const std::string &name);
    virtual const SmartPointer<OptionCategory> &
    pushCategory(const std::string &name);
    virtual void popCategory();

    // From OptionMap
    using OptionMap::add;
    void add(const std::string &name, SmartPointer<Option> option) override;
    bool remove(const std::string &key) override;
    bool has(const std::string &key) const override;
    const SmartPointer<Option> &get(const std::string &key) const override;
    void alias(const std::string &name, const std::string &alias) override;

    // From JSON::Serializable
    void read(const JSON::Value &value) override;
    void write(JSON::Sink &sink) const override {write(sink, false);}
    using JSON::Serializable::write;

    static std::string cleanKey(const std::string &key);
  };

  inline std::ostream &operator<<(std::ostream &stream, const Options &opts) {
    return opts.print(stream);
  }
};
