SCREEN 7
n = 0

FOR i = ASC(" ") TO ASC("~")
  PRINT CHR$(i);
  n = n + 1
NEXT
PRINT

w = 8
h = 8
OPEN "ascii.txt" FOR OUTPUT AS #1
OPEN "ascii.h" FOR OUTPUT AS #2
PRINT #2, "//"; n * (w + 1)
PRINT #2, "char font["; n; "]["; w + 1; "]={";
FOR i = 0 TO n - 1
   REM PRINT #2, "font["; i; "]={";
   FOR j = 0 TO w
        x = 0
        FOR k = 0 TO h
                IF POINT(j + i * w MOD (40 * w) - 1, k + INT(i / 40) * h) > 0 THEN
                        x = x + 2 ^ k
                        PRINT #1, ".";
                ELSE
                        PRINT #1, " ";
                END IF
        NEXT
        PRINT #2, x; ", ";
        PRINT #1,
   NEXT
       PRINT #1, "-------------"; CHR$(i + ASC(" "))
       PRINT #2, "    //["; CHR$(i + ASC(" ")); "]"
NEXT
   PRINT #2, "};"
CLOSE #1
CLOSE #2

