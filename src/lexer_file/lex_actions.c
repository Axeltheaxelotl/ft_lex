#include "lexer_file.h"

bool split_rule_line(const char *line, char **regex_out, char **action_out)
{
    if (!line || !regex_out || !action_out)
        return false;

    int len = strlen(line);
    int regex_end = -1;
    bool in_quotes = false;
    bool in_brackets = false;
    bool escaped = false;

    for (int i = 0; i < len; i++)
    {
        if (escaped)
        {
            escaped = false;
            continue;
        }
        if (line[i] == '\\')
        {
            escaped = true;
            continue;
        }
        if (line[i] == '"')
        {
            in_quotes = !in_quotes;
            continue;
        }
        if (!in_quotes)
        {
            if (line[i] == '[')
                in_brackets = true;
            else if (line[i] == ']')
                in_brackets = false;
        }
        if (!in_quotes && !in_brackets)
        {
            if (line[i] == ' ' || line[i] == '\t')
            {
                regex_end = i;
                break;
            }
        }
    }

    if (regex_end == -1)
        return false;

    char *regex = malloc(regex_end + 1);
    if (!regex)
        return false;
    strncpy(regex, line, regex_end);
    regex[regex_end] = '\0';

    int action_start = regex_end;
    while (line[action_start] == ' ' || line[action_start] == '\t')
        action_start++;

    if (line[action_start] == '\0')
    {
        free(regex);
        return false;
    }

    char *action = strdup(&line[action_start]);
    if (!action)
    {
        free(regex);
        return false;
    }

    *regex_out = regex;
    *action_out = action;
    return true;
}

int count_braces(const char *str, int current_depth)
{
    if (!str)
        return current_depth;

    bool in_quotes = false;
    bool escaped = false;

    for (int i = 0; str[i]; i++)
    {
        if (escaped)
        {
            escaped = false;
            continue;
        }
        if (str[i] == '\\')
        {
            escaped = true;
            continue;
        }
        if (str[i] == '"')
        {
            in_quotes = !in_quotes;
            continue;
        }
        if (!in_quotes)
        {
            if (str[i] == '{')
                current_depth++;
            else if (str[i] == '}')
                current_depth--;
        }
    }
    return current_depth;
}