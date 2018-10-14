public class Solution {
    public String pretty(final int extraTabs, final String text) {
        final StringBuilder tabs = new StringBuilder(extraTabs + text.length());
        for (int i = 0; i < extraTabs; ++ i) {
            tabs.append("\t");
        }
        tabs.append(text);
        return tabs.toString();
    }
    
    public ArrayList<String> prettyJSON(String json) {
        final ArrayList<String> prettyJson = new ArrayList<>();
        int extraTabs = 0;
        final int length = json.length();
        int i = 0;
        while (i < length) {
            if (Character.isWhitespace(json.charAt(i))) {
                ++ i;
                continue;
            } else if ('{' == json.charAt(i) || '[' == json.charAt(i)) {
                final String pCh = String.valueOf(json.charAt(i ++));
                while (i < length && Character.isWhitespace(json.charAt(i))) ++ i;
                String cCh = "";
                if (i < length && ',' == json.charAt(i)) {
                    cCh = ",";
                    ++ i;
                }
                prettyJson.add(pretty(extraTabs, pCh + cCh));
                ++ extraTabs;
                continue;
            } else if ('}' == json.charAt(i) || ']' == json.charAt(i)) {
                final String pCh = String.valueOf(json.charAt(i ++));
                while (i < length && Character.isWhitespace(json.charAt(i))) ++ i;
                String cCh = "";
                if (i < length && ',' == json.charAt(i)) {
                    cCh = ",";
                    ++ i;
                }
                -- extraTabs;
                prettyJson.add(pretty(extraTabs, pCh + cCh));
                continue;
            }

            int j = i;
            final StringBuilder item = new StringBuilder();
            while (j < length) {
                 if (Character.isWhitespace(json.charAt(j))) {
                     ++ j;
                     continue;
                 } else if ('}' == json.charAt(j) || ']' == json.charAt(j)) {
                     break;
                 } else if ('{' == json.charAt(j) || '[' == json.charAt(j)) {
                     break;
                 }
                 
                 item.append(json.charAt(j ++));
                 if (',' == json.charAt(j - 1)) {
                     break;
                 }
            }
            
            prettyJson.add(pretty(extraTabs, item.toString()));
            i = j;
        }
        return prettyJson;
    }
}
