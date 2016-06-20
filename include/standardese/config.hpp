// Copyright (C) 2016 Jonathan Müller <jonathanmueller.dev@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#ifndef STANDARDESE_CONFIG_HPP_INCLUDED
#define STANDARDESE_CONFIG_HPP_INCLUDED

#include <map>
#include <string>
#include <vector>

#include <standardese/noexcept.hpp>
#include <standardese/string.hpp>
#include <standardese/synopsis.hpp>

namespace standardese
{
    /// C++ standard to be used
    enum class cpp_standard
    {
        cpp_98,
        cpp_03,
        cpp_11,
        cpp_14,
        count
    };

    class compile_config
    {
    public:
        compile_config(cpp_standard standard, string commands_dir = "");

        void add_macro_definition(string def);

        void remove_macro_definition(string def);

        void add_include(string path);

        std::vector<const char*> get_flags() const;

    private:
        std::vector<string> flags_;
    };

    enum class section_type : unsigned;

    class comment_config
    {
    public:
        comment_config();

        void set_command_character(char c) STANDARDESE_NOEXCEPT
        {
            cmd_char_ = c;
        }

        char get_command_character() const STANDARDESE_NOEXCEPT
        {
            return cmd_char_;
        }

        void set_section_command(section_type t, std::string command);

        section_type get_section(const std::string& command) const;

        section_type try_get_section(const std::string& command) const STANDARDESE_NOEXCEPT;

    private:
        std::map<std::string, unsigned> section_commands_;
        char cmd_char_;
    };

    class output_config
    {
    public:
        output_config();

        void set_section_name(section_type t, std::string name)
        {
            section_names_[unsigned(t)] = std::move(name);
        }

        const std::string& get_section_name(section_type t) const STANDARDESE_NOEXCEPT
        {
            return section_names_[unsigned(t)];
        }

        entity_blacklist& get_blacklist() STANDARDESE_NOEXCEPT
        {
            return blacklist_;
        }

        const entity_blacklist& get_blacklist() const STANDARDESE_NOEXCEPT
        {
            return blacklist_;
        }

        void set_tab_width(unsigned w) STANDARDESE_NOEXCEPT
        {
            tab_width_ = w;
        }

        unsigned get_tab_width() const STANDARDESE_NOEXCEPT
        {
            return tab_width_;
        }

        void set_hidden_name(std::string name)
        {
            hidden_name_ = std::move(name);
        }

        const std::string& get_hidden_name() const STANDARDESE_NOEXCEPT
        {
            return hidden_name_;
        }

    private:
        entity_blacklist         blacklist_;
        std::vector<std::string> section_names_;
        std::string              hidden_name_;
        unsigned                 tab_width_;
    };
} // namespace standardese

#endif // STANDARDESE_CONFIG_HPP_INCLUDED
