PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE Words (text string, book number, chapter number, verse number, base number, id number);
COMMIT;
