OUT 888, 0
OUT 890, 11
WHILE INKEY$ = ""
  OUT 890, 11
  FOR i = 0 TO 7
        PRINT i;
        x = 2 ^ i
        OUT 888, x
        PRINT INP(889)
        PLAY "p4"
        IF INKEY$ <> "" THEN EXIT FOR
  NEXT
  OUT 888, 0

  OUT 890, 10
  PLAY "p4"
  PRINT 8
  OUT 890, 9
  PLAY "p4"
  PRINT 9
  OUT 890, 15
  PLAY "p4"
  PRINT 10
  OUT 890, 3
  PLAY "p4"
  PRINT 11
WEND

