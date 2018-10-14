# A password is considered strong if below conditions are all met:
# It has at least 6 characters and at most 20 characters.
# It must contain at least one lowercase letter, at least one uppercase letter, and at least one digit.
# It must NOT contain three repeating characters in a row("...aaa..." is weak, but "...aa...a..." is strong, assuming other conditions are met).
# Write a function strongPasswordChecker(s), that takes a string s as input, and return the MINIMUM change required to make s a strong password. If s is already strong, return 0.
# Insertion, deletion or replace of any one character are all considered as one change.
class Solution(object):
    def strongPasswordChecker(self, s):
        missing_type = 3
        if any('a' <= c <= 'z' for c in s): missing_type -= 1
        if any('A' <= c <= 'Z' for c in s): missing_type -= 1
        if any(c.isdigit() for c in s): missing_type -= 1

        change, one, two, p = 0, 0, 0, 2
        while p < len(s):
            if s[p] == s[p-1] == s[p-2]:
                length = 2
                while p < len(s) and s[p] == s[p-1]: length, p = length + 1, p + 1
                change += length // 3
                if length % 3 == 0: one += 1
                elif length % 3 == 1: two += 1
            else: p += 1
        
        if len(s) < 6: return int(max(missing_type, 6 - len(s)))
        elif len(s) <= 20: return int(max(missing_type, change))
        else:
            delete = len(s) - 20
            change -= min(delete, one)
            change -= min(max(delete - one, 0), two * 2) // 2
            change -= max(delete - one - 2 * two, 0) // 3
            return int(delete + max(missing_type, change))
