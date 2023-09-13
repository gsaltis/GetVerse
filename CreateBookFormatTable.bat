sqlite3 NASB.db "DROP TABLE BookFormat;"
sqlite3 NASB.db "CREATE TABLE BookFormat (bookIndex number, GroupNumber number, TextColor string, BackgroundColor string, GroupEnd int);"
