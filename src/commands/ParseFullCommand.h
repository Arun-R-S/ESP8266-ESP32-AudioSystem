#pragma once

#include "ParsedCommand.h"
#include <vector>

class ParseFullCommand {
public:
    static std::vector<ParsedCommand> Parse(const String& input) {
        std::vector<ParsedCommand> commands;

        // Split input by ';'
        int start = 0;
        while (start < input.length()) {
            int sep = input.indexOf(';', start);
            String segment = input.substring(start, sep == -1 ? input.length() : sep);

            int eq = segment.indexOf('=');
            if (eq > 0) {
                commands.emplace_back(segment.substring(0, eq), segment.substring(eq + 1));
            } else {
                commands.emplace_back(segment, "");
            }

            if (sep == -1) break;
            start = sep + 1;
        }

        return commands;
    }
};
