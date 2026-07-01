#include "lexer_file.h"

static void strip_newline(char *str)
{
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r'))
    {
        str[len - 1] = '\0';
        len--;
    }
}

static bool is_empty_line(const char *str)
{
    while (*str)
    {
        if (*str != ' ' && *str != '\t' && *str != '\r' && *str != '\n')
            return false;
        str++;
    }
    return true;
}

bool lex_file_parse(t_lex_file *lf, const char *filepath)
{
    if (!lf || !filepath)
        return false;

    FILE *file = fopen(filepath, "r");
    if (!file)
    {
        perror("fopen");
        return false;
    }

    char line_buf[1024];
    int section = 1; // 1: Header, 2: Rules, 3: Footer
    bool in_c_code = false;

    while (fgets(line_buf, sizeof(line_buf), file))
    {
        strip_newline(line_buf);

        char *trimmed = line_buf;
        while (*trimmed == ' ' || *trimmed == '\t')
            trimmed++;

        if (strcmp(trimmed, "%%") == 0)
        {
            if (section == 1)
            {
                section = 2;
                continue;
            }
            else if (section == 2)
            {
                section = 3;
                continue;
            }
        }

        if (section == 1)
        {
            if (strcmp(trimmed, "%{") == 0)
            {
                in_c_code = true;
                continue;
            }
            if (strcmp(trimmed, "%}") == 0)
            {
                in_c_code = false;
                continue;
            }
            if (in_c_code)
            {
                lex_file_append_header(lf, line_buf);
            }
        }
        else if (section == 2)
        {
            if (is_empty_line(line_buf))
                continue;

            char *regex = NULL;
            char *action = NULL;
            if (!split_rule_line(line_buf, &regex, &action))
            {
                fclose(file);
                return false;
            }

            int brace_depth = count_braces(action, 0);
            if (brace_depth > 0)
            {
                char action_buf[4096];
                strncpy(action_buf, action, sizeof(action_buf) - 1);
                action_buf[sizeof(action_buf) - 1] = '\0';
                free(action);

                char next_line[1024];
                while (brace_depth > 0 && fgets(next_line, sizeof(next_line), file))
                {
                    strip_newline(next_line);
                    size_t current_len = strlen(action_buf);
                    if (current_len + strlen(next_line) + 2 < sizeof(action_buf))
                    {
                        strcat(action_buf, "\n");
                        strcat(action_buf, next_line);
                    }
                    else
                    {
                        fprintf(stderr, "Error: Action block size limit exceeded.\n");
                        free(regex);
                        fclose(file);
                        return false;
                    }
                    brace_depth = count_braces(next_line, brace_depth);
                }
                action = strdup(action_buf);
            }

            if (!lex_file_add_rule(lf, regex, action))
            {
                free(regex);
                free(action);
                fclose(file);
                return false;
            }
            free(regex);
            free(action);
        }
        else if (section == 3)
        {
            lex_file_append_footer(lf, line_buf);
        }
    }

    fclose(file);
    return true;
}
