DECLARE SUB pb (row AS INTEGER, col AS INTEGER)
DECLARE SUB po (row AS INTEGER, col AS INTEGER)
DECLARE SUB pk (row AS INTEGER, col AS INTEGER)
DECLARE SUB p8 (row AS INTEGER, col AS INTEGER)
DECLARE SUB p0 (row AS INTEGER, col AS INTEGER)
SCREEN 0
CLS

FOR i = 1 TO 25
  PRINT " ";
  FOR j = 1 TO 15
    IF j <> 8 AND j <> 7 THEN
    COLOR j, 0, 0
    PRINT CHR$(176); CHR$(177); CHR$(178);
    PRINT CHR$(219); CHR$(178); CHR$(177);
    END IF

  NEXT
  IF i < 25 THEN PRINT
NEXT

i = 0
WHILE INKEY$ <> CHR$(27)

COLOR 15, i

CALL pb(3, 28)

COLOR 15, (i + 1) MOD 16

CALL po(3, 36)

COLOR 15, (i + 2) MOD 16

CALL po(3, 44)

COLOR 15, (i + 3) MOD 16

CALL pk(3, 52)

COLOR 15, (i + 4) MOD 16

CALL p8(13, 28)

COLOR 15, (i + 1) MOD 16

CALL p0(13, 36)

COLOR 15, (i + 1) MOD 16

CALL p8(13, 44)

COLOR 15, (i + 1) MOD 16

CALL p8(13, 52)

i = i + 1
i = i MOD 16
WEND

COLOR 14, 1, 2
CLS

SUB p0 (row AS INTEGER, col AS INTEGER)

LOCATE row, col + 1
PRINT "   "

FOR i = 1 TO 7
LOCATE row + i, col
PRINT " "
LOCATE row + i, col + 4
PRINT " "
NEXT

LOCATE row + 8, col + 1
PRINT "   "

END SUB

SUB p8 (row AS INTEGER, col AS INTEGER)

LOCATE row, col + 1
PRINT "   "

FOR i = 1 TO 3
LOCATE row + i, col
PRINT " "
LOCATE row + i, col + 4
PRINT " "
NEXT
LOCATE row + 4, col + 1
PRINT "   "
FOR i = 5 TO 7
LOCATE row + i, col
PRINT " "
LOCATE row + i, col + 4
PRINT " "
NEXT
LOCATE row + 8, col + 1
PRINT "   "

END SUB

SUB pb (row AS INTEGER, col AS INTEGER)

LOCATE row, col
PRINT "    ";
FOR i = 1 TO 3
LOCATE row + i, col + 1: PRINT " "
LOCATE row + i, col + 4: PRINT " "
NEXT
LOCATE row + i, col + 1: PRINT "   "

FOR i = 5 TO 7
LOCATE row + i, col + 1: PRINT " "
LOCATE row + i, col + 4: PRINT " "
NEXT
LOCATE row + i, col: PRINT "    "

END SUB

SUB pk (row AS INTEGER, col AS INTEGER)


LOCATE row, col
PRINT "  ";
FOR i = 1 TO 7
LOCATE row + i, col + 1: PRINT " "
NEXT

'LOCATE row + 4, col + 2: PRINT "  "

FOR i = 3 TO 6
LOCATE row + i - 1, col + 8 - i: PRINT " "
LOCATE row + i + 1, col - 2 + i: PRINT " "
NEXT

LOCATE row + 8, col: PRINT "  "
LOCATE row + 8, col + 4: PRINT "  "


END SUB

SUB po (row AS INTEGER, col AS INTEGER)

LOCATE row + 4, col + 2
PRINT "  ";

FOR i = 5 TO 7
LOCATE row + i, col + 1: PRINT " "
LOCATE row + i, col + 4: PRINT " "
NEXT
LOCATE row + i, col + 2: PRINT "  "

END SUB

