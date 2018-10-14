
void generate(
    int pos, String buttons, StringBuilder comb, 
    String [] ime, List<String> result) {
    
    if (pos == comb.length()) {
        result.add(comb.toString());
        return;
    }
    
    int button = buttons.charAt(pos) - '0';
    for (int i = 0; i < ime [button].length(); ++ i) {
        comb.setCharAt(pos, ime [button].charAt(i));
        generate(pos + 1, buttons, comb, ime, result);
    }
}
    
String[] pressingButtons(String buttons) {
    if (buttons.isEmpty()) return new String [0];
    final String [] ime = {
        "", "", "abc", "def", "ghi", "jkl", 
        "mno", "pqrs", "tuv", "wxyz"};
    final StringBuilder comb = new StringBuilder();
    comb.setLength(buttons.length());
    List<String> result = new ArrayList<>();
    generate(0, buttons, comb, ime, result);
    return result.toArray(new String [0]);
}
