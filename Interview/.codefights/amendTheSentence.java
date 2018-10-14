String amendTheSentence(String s) {
    final StringBuilder text = new StringBuilder(s.length());
    for (int i = 0; i < s.length(); ++ i) {
        final char ch = s.charAt(i);
        if (ch >= 'A' && ch <= 'Z') {
            if (text.length() > 0) {
                text.append(' ');
            }
            text.append((char) ((ch - 'A') + 'a'));
        } else {
            text.append(ch);
        }
    }
    return text.toString();
}
