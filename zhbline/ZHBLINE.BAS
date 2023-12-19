DECLARE SUB Music ()
DECLARE SUB buy ()
DECLARE SUB sell ()
DECLARE SUB Music ()
DECLARE SUB display ()
DECLARE SUB KLine (start AS LONG)
DECLARE SUB K1Line (current AS LONG, start AS LONG)
DECLARE SUB M1Line (total AS LONG, start AS LONG, mlen AS INTEGER, colour AS INTEGER)
DECLARE SUB MLine (start AS LONG, mlen AS INTEGER, colour AS INTEGER)
DECLARE SUB drawLine (start AS LONG, value() AS LONG, colour AS INTEGER)
DECLARE SUB loadGuosenData (filepath AS STRING)
DECLARE FUNCTION inputCode$ ()
DECLARE SUB initsteps (start AS LONG)


TYPE guosen
    date AS LONG
    ope AS LONG
    high AS LONG
    low AS LONG
    clos AS LONG
    unknown0 AS LONG
    volume AS LONG
    unknown1 AS LONG
END TYPE
DIM SHARED CODE$, total AS LONG, smax, smin, xstep, ystep, vstep, ybase, tkey AS STRING
DIM SHARED startmoney AS CURRENCY, Money AS CURRENCY, stock AS CURRENCY
DIM SHARED mus(360) AS STRING, musStep AS INTEGER
DIM SHARED screenW AS LONG, screenH  AS LONG, realtotal AS LONG
DIM SHARED start AS LONG, m AS INTEGER, mode AS INTEGER
REDIM SHARED sdate(1) AS LONG, sopen(1) AS LONG, sclose(1) AS LONG, shigh(1) AS LONG, slow(1) AS LONG, svol(1)  AS LONG
mode = 9       '12 =vga   ,1 = cga
m = 0

CLS
SCREEN mode
IF mode > 8 THEN
        screenW = 640
        screenH = 384
END IF

IF mode = 1 THEN
        screenW = 320
        screenH = 240

END IF
xstep = 3


LOCATE screenH / 2 / 16, 1
IF mode > 8 THEN COLOR 14
IF COMMAND$ = "" THEN
        PRINT "Chinese Stock Market named as A Stock Market."
        PRINT "Here is a real history record of one stock."
        PRINT "You are going to trade with a million of fortune."
        PRINT "Press";
        COLOR 12: PRINT " B ";
        COLOR 14: PRINT "for Buy ,";
        COLOR 10: PRINT " S ";
        COLOR 14: PRINT "for Sell during the game."
        PRINT "Wish you good luck , cause you are going to need it."
        IF mode > 8 THEN COLOR 12
        PRINT "Press C to Continue..."
        IF mode > 8 THEN COLOR 15
 REM       DO
 REM       LOOP UNTIL INKEY$ = "c"

END IF

FOR i = 0 TO UBOUND(mus)
        READ mus(i)
NEXT

FILES "*.day"
IF COMMAND$ = "" THEN CODE$ = inputCode + ".day" ELSE CODE$ = COMMAND$

loadGuosenData (CODE$)
playlen = UBOUND(mus)
IF total = 0 THEN
   KILL CODE$
   END
END IF
PRINT CODE$; " Total:"; total; " days"
IF COMMAND$ = "" THEN INPUT "How many days to play ?", playlen
IF playlen > total / 2 + 100 THEN playlen = total / 2 + 100
IF playlen <= 10 THEN playlen = total - 250



start = total - playlen


realtotal = total

IF m = 1 THEN PLAY ON

DO

total = realtotal - playlen

startmoney = 100000000
stock = 0
Money = startmoney


CLS


CALL MLine(start, 1, 1)
CALL MLine(start, 5, 3)
CALL MLine(start, 20, 4)
CALL MLine(start, 60, 14)
CALL MLine(start, 240, 15)
CALL KLine(start)
IF m = 1 THEN
        ON PLAY(1) GOSUB subMusic
        CALL Music
        PLAY STOP
        PLAY ON
END IF
'Start Playback

FOR total = total TO realtotal

   IF INT((total - start) * xstep) MOD screenW < xstep THEN
      CLS
      initsteps (total)
      LOCATE 2, 1
      PRINT "Press Esc to Stop, Source: http://github.com/zhblue/RetroFuns   ";
      LOCATE 1, 66: PRINT CODE$
      FOR y = 32 TO screenH - 64 STEP screenH / 5
          LINE (0, y)-(screenW, y), 1, , &HF00
          IF mode > 8 THEN
             LOCATE INT(y / 14) + 1, INT(screenW / 8) - 5
             IF ystep <> 0 THEN PRINT INT(smin + (ybase - y) / ystep) / 100
          END IF
      NEXT

   END IF

   CALL display
   CALL M1Line(total, start, 1, 1)
   CALL M1Line(total, start, 5, 3)
   CALL M1Line(total, start, 20, 4)
   CALL M1Line(total, start, 60, 14)
   CALL M1Line(total, start, 240, 15)
   CALL K1Line(total, start)
REM   IF total MOD 10 = 0 THEN SOUND (sclose(total) * 10 MOD 3000) + 200, 1
   tkey = INKEY$
   IF CHR$(27) = tkey THEN EXIT FOR
   IF tkey = "b" THEN CALL buy
   IF tkey = "s" THEN CALL sell
   IF tkey = "m" THEN
        m = 1 - m
        IF m = 1 THEN
                PLAY ON
                CALL Music
        ELSE
                PLAY OFF
        END IF
   END IF
NEXT
REM PLAY "p4p4"

LOCATE screenH / 16 - 1, 1

IF COMMAND$ = "" THEN
        IF total > realtotal THEN total = realtotal
        PRINT "Score:";
        PRINT Money / startmoney * 100 + sclose(total) / startmoney * stock * 100;
        PRINT "%  Press C to Continue..."
        IF xstep <= 128 THEN xstep = xstep * 2
        DO
        LOOP UNTIL INKEY$ = "c"
ELSE
        END
END IF


LOOP UNTIL tkey = CHR$(27)

LOCATE screenH / 16 - 1, 1
PRINT "Press Esc to Exit..."


DO
LOOP UNTIL INKEY$ = CHR$(27)


END

subMusic:
  IF m = 1 THEN CALL Music
RETURN


DATA "t126O3L8ff","ff","o4aa","aa","o3gg","gg","o4cc","cc","dd","dd","dd","dd","o3gf","ec","dp8","do4a"
DATA "o3gp8", "fp8", "ep8", "ee", "gp8", "fe", "dp8", "do4f","ef","ef","o3dp8","do4f","ef","ef","o3dp8","do4a"
DATA "o3gp8", "fp8", "ep8", "ee", "gp8", "fe", "dp8", "do4f","ef","ef","o3dp8","do4f","ef","ef","o3ff","ff"
DATA "o4aa", "aa", "o3gg", "gg", "o4cc", "cc", "dd", "dd", "dd", "dd", "o3gf", "ec", "dp8", "do4a", "o3gp8", "fp8"
DATA "o3ep8", "ee", "gp8", "fe", "dp8", "do4f","ef","ef","o3dp8","do4f","ef","ef","o3dp8", "do4a", "o3gp8", "fp8"
DATA "o3ep8", "ee", "gp8", "fe", "dp8", "do4f","ef","ef","o3dp8","do4f","ef","ef","p4","p4"

DATA "t126O3L8ff","ff","o4aa","aa","o3gg","gg","o4cc","cc","dd","dd","dd","dd","o3gf","ec","dp8","do4a"
DATA "o3gp8", "fp8", "ep8", "ee", "gp8", "fe", "dp8", "do4f","ef","ef","o3dp8","do4f","ef","ef","o3dp8","do4a"
DATA "o3gp8", "fp8", "ep8", "ee", "gp8", "fe", "dp8", "do4f","ef","ef","o3dp8","do4f","ef","ef","o3ff","ff"
DATA "o4aa", "aa", "o3gg", "gg", "o4cc", "cc", "dd", "dd", "dd", "dd", "o3gf", "ec", "dp8", "do4a", "o3gp8", "fp8"
DATA "o3ep8", "ee", "gp8", "fe", "dp8", "do4f","ef","ef","o3dp8","do4f","ef","ef","o3dp8", "do4a", "o3gp8", "fp8"
DATA "o3ep8", "ee", "gp8", "fe", "dp8", "do4f","ef","ef","o3dp8","do4f","ef","ef","p4","p4"


DATA "p2"

DATA "T180L2O3EL4G", "L1O4DL2C", "O3L4GL1F", "L2E", "L4EE", "FG", "L1AG", "L2EL4G", "L1O4DL2C", "L4O3GL1F"
DATA "L2EL4G", "GA", "BL1O4C", "CL8D", "P8P8", "O3GL4G", "BA", "GL2EL4G", "L1O4CL2O3A", "L4O4CL2D", "L4CL1O3BG"
DATA "L2EL4G", "L1O4DL2C", "L4O3GL1F", "L2EL4G", "GA", "BO4L1C", "L2CP4"

DATA "p2"

DATA "o3l4ee", "fg", "gf", "ed", "cc", "de", "l3el8", "dl2d"
DATA "l4ee", "fg", "gf", "ed", "cc", "de", "l3dl8cl2c"
DATA "l4dd", "ec", "dl8e", "fl4e", "cd", "l8ef", "l4ed", "cd", "o2go3l2e"
DATA "l4ef", "gg", "fe", "l8fd", "l4cc", "de", "l3dl8c", "l2c"
DATA "o3l4ee", "fg", "gf", "ed", "cc", "de", "l3el8", "dl2d"
DATA "l4ee", "fg", "gf", "ed", "cc", "de", "l3dl8cl2c"
DATA "l4dd", "ec", "dl8e", "fl4e", "cd", "l8ef", "l4ed", "cd", "o2go3l2e"
DATA "l4ef", "gg", "fe", "l8fd", "l4cc", "de", "l3dl8c", "l2c"

DATA "p2"

DATA "O3L4AA", "L2BL4A", "AL2B", "L4AB", "O4CO3BA", "L8BA", "L2FL4E", "CE", "FE", "L8EC", "L2O2BL4O3A", "BO4C", "O3BA"
DATA "L8BA", "L2FL4E", "CE", "FE", "L8EC", "L2O2BL4O3A", "AL2B", "L4AA", "L2BL4E", "FL8B", "AL4F", "L1E"
DATA "O3L4AA", "L2BL4A", "AL2B", "L4AB", "O4CO3BA", "L8BA", "L2FL4E", "CE", "FE", "L8EC", "L2O2BL4O3A", "BO4C", "O3BA"
DATA "L8BA", "L2FL4E", "CE", "FE", "L8EC", "L2O2BL4O3A", "AL2B", "L4AA", "L2BL4E", "FL8B", "AL4F", "L1E"

DATA "p2"

DATA "O3L4AG", "L8GDE", "DL2E", "L4GF", "L8ED", "DO2A", "L2O3C"
DATA "L4EL8E", "GDCC", "O2GL2A", "L4AO3D", "P8L8DO2B", "AL2G"
DATA "O3L4AG", "L8GDE", "DL2E", "L4GF", "L8ED", "DO2A", "L2O3C"
DATA "L4EL8E", "GDCC", "O2GL2A", "L4AO3D", "P8L8DO2B", "AL2G"

DATA "p2"

SUB buy
   price = sclose(total)
   vol = INT(Money / price / 200) * 100
   IF (vol > 0) THEN
           Money = Money - vol * price
           stock = stock + vol
           x = total - start
           x0 = (x * xstep) MOD screenW
           y0 = ybase - (price - smin) * ystep
           CIRCLE (x0, y0), 5, 12
           IF mode > 8 THEN COLOR 12
           LOCATE INT(y0 / 16) + 1, INT(x0 / 8) + 1
           PRINT "Buy"

   END IF

END SUB

SUB display
   LINE (0, 0)-(screenW - 120, 16), 0, BF
   LOCATE 1, 1
   IF mode > 8 THEN COLOR 15
   'PRINT code$; ":";
   IF mode > 8 THEN COLOR 7
   PRINT sdate(total);
   IF mode > 8 THEN COLOR 15
   PRINT "Open("; sopen(total) / 100; ")";
   IF mode > 8 THEN COLOR 4
   PRINT "High("; shigh(total) / 100; ")";
   IF mode > 8 THEN COLOR 14
   PRINT "Low("; slow(total) / 100; ")";
   IF mode > 8 THEN COLOR 15
   PRINT "Close("; sclose(total) / 100; ")";
   REM LINE (0, 330)-(screenW, 350), 0, BF
   IF mode > 8 THEN LOCATE screenH / 16 + 1, 1
   Account$ = "Money:" + STR$(Money / 100) + "  Stock:" + STR$(stock) + "  Profit:"
   Account$ = Account$ + STR$(INT((Money / startmoney * 100 + sclose(total) / startmoney * stock * 100)) - 100) + "%"
   Account$ = Account$ + "  Per:" + STR$(INT(sclose(total) * stock / (sclose(total) * stock + Money) * 100)) + "%"
   IF (LEN(Account$) < 70) THEN Account$ = Account$ + SPACE$(70 - LEN(Account$))

   PRINT Account$;

   
   
END SUB

SUB drawLine (start AS LONG, value() AS LONG, colour AS INTEGER)
   


   'PRINT "s="; start, "t="; total, "max="; smax; " min="; smin; " xs="; xstep; "ys="; ystep

   FOR i = start TO total - 1
       x = i - start
       x1 = x * xstep
       y1 = ybase - (value(i) - smin) * ystep
       x2 = (x + 1) * xstep
       y2 = ybase - (value(i + 1) - smin) * ystep
       LINE (x1, y1)-(x2, y2), colour
       'PRINT "("; x1; ","; y1; ")-("; x2; ","; y2; ")"; colour

   NEXT
END SUB

SUB initsteps (startPoint AS LONG)
    vmax = svol(startPoint)
    smax = shigh(startPoint)
    smin = slow(startPoint)
    last = startPoint + screenW / xstep
    IF last > realtotal THEN last = realtotal
   
'    PRINT startPoint, last
'    SHELL ("pause")

    FOR i = startPoint TO last
 
        IF shigh(i) > smax THEN smax = shigh(i)
        IF slow(i) < smin THEN smin = slow(i)
        IF svol(i) > vmax THEN vmax = svol(i)
    NEXT
   'xstep = screenW / (total - startPoint)
   ybase = screenH - 16 * 3
   ytop = 16 * 2
   ystep = (ybase - ytop) / (smax - smin)
   vstep = (ybase - ytop) / vmax / 3
   'IF xstep < 10 THEN xstep = 10

END SUB

FUNCTION inputCode$
    PRINT "Tips: Press B to buy , Press S to Sell "
    DIM default AS STRING
    default = "600050"
    PRINT "Now input one stock Code (default:" + default + ") ";
    INPUT ":", CODE$
    IF "" = CODE$ THEN CODE$ = default
    DIM f AS STRING

    f = LEFT$(CODE$, 1)

    IF f = "6" THEN CODE$ = "sh" + CODE$
    IF f = "5" THEN CODE$ = "sh" + CODE$

    IF f = "0" THEN CODE$ = "sz" + CODE$
    IF f = "2" THEN CODE$ = "sz" + CODE$
    IF f = "3" THEN CODE$ = "sz" + CODE$


    inputCode$ = CODE$

END FUNCTION

SUB K1Line (current AS LONG, start AS LONG)

   
    c = 2
    IF sopen(current) < sclose(current) THEN c = 4
           
             x = current - start
             x0 = x * xstep
             x1 = x0 - xstep / 2 + 1
             y1 = ybase - (sopen(current) - smin) * ystep
             x2 = x0 + xstep / 2 - 1
             y2 = ybase - (sclose(current) - smin) * ystep
             y3 = ybase - (shigh(current) - smin) * ystep
             y4 = ybase - (slow(current) - smin) * ystep
             x0 = x0 MOD screenW
             x1 = x1 MOD screenW
             x2 = x2 MOD screenW
             IF x1 > x2 THEN x1 = x2 - 1
     y5 = ybase - svol(current) * vstep
     LINE (x1, ybase)-(x2, y5), 1, BF
     LINE (x0, y3)-(x0, y4), c
     LINE (x1, y1)-(x2, y2), c, BF
     'locate 20, 1
     'PRINT x1, y1

END SUB

SUB KLine (start AS LONG)
        DIM i AS LONG
        FOR i = start TO total
            
             CALL K1Line(i, start)

        NEXT
END SUB

SUB loadGuosenData (filepath AS STRING)
'PRINT code$

    DIM filenum AS LONG
    filenum = FREEFILE
    DIM c AS guosen
    DIM i AS LONG
    DIM xfix AS DOUBLE
    DIM autoshift AS LONG
    OPEN filepath FOR RANDOM AS filenum LEN = 32
  
    total = LOF(filenum) / LEN(c)
  
    REDIM sdate(total)  AS LONG
    REDIM sopen(total)  AS LONG
    REDIM sclose(total) AS LONG
    REDIM shigh(total) AS LONG
    REDIM slow(total) AS LONG
    REDIM svol(total) AS LONG
    autoshift = 0
    xfix = 1#
 
    FOR i = 1 TO total
        GET filenum, i, c
        REM pop up and down more than 10% means right distraction
        IF i > 1 THEN
           IF ABS(c.ope + autoshift - sclose(i - 1)) > sclose(i - 1) / 10 THEN
             autoshift = sclose(i - 1) - c.ope
           END IF
        END IF
        sdate(i) = c.date
        sopen(i) = c.ope + autoshift
        shigh(i) = c.high + autoshift
        slow(i) = c.low + autoshift
        sclose(i) = c.clos + autoshift
        svol(i) = c.volume
        IF i MOD 100 = 0 THEN PRINT ".";
    NEXT
'    PRINT USING "########"; sdate(total);

    CLOSE filenum
   
END SUB

SUB M1Line (total AS LONG, start AS LONG, mlen AS INTEGER, colour AS INTEGER)
   
      
      DIM value(2) AS LONG
      DIM sum AS LONG
      FOR i = 0 TO 1
              sum = 0
              FOR j = total - mlen + 1 - i TO total - i
                 sum = sum + sclose(j)
              NEXT
      
              value(i) = sum / mlen
      NEXT
       x = total - start - 1

       x1 = x * xstep
       y1 = ybase - (value(1) - smin) * ystep
       x2 = (x + 1) * xstep
       y2 = ybase - (value(0) - smin) * ystep
       
       x1 = x1 MOD screenW
       x2 = x2 MOD screenW
       IF x1 > x2 THEN x1 = x2 - 1

       LINE (x1, y1)-(x2, y2), colour
'       LOCATE 20, 1
'       PRINT x; "("; x1; ","; y1; ")-("; x2; ","; y2; ")"; colour
'       PLAY "c"

END SUB

SUB MLine (start AS LONG, mlen AS INTEGER, colour AS INTEGER)
   REDIM value(total) AS LONG
   IF start < mlen THEN start = mlen
   DIM sum AS DOUBLE
   FOR i = start TO total
      sum = 0
      FOR j = i - mlen + 1 TO i
         sum = sum + sclose(j)
      NEXT
      value(i) = sum / mlen
   NEXT
   CALL drawLine(start, value(), colour)
END SUB

SUB Music

    musStep = musStep MOD UBOUND(mus)
    PLAY "MB" + mus(musStep)
    musStep = musStep + 1

END SUB

SUB sell
   price = sclose(total)
   IF stock < 200 THEN vol = stock ELSE vol = INT(stock / 200) * 100
   Money = Money + vol * price
   stock = stock - vol
   IF vol > 0 THEN
           x = total - start
           x0 = (x * xstep) MOD screenW
           y0 = ybase - (price - smin) * ystep
           CIRCLE (x0, y0), 5, 10
           IF mode > 8 THEN COLOR 10
           LOCATE INT(y0 / 16) + 1, INT(x0 / 8) + 1
           PRINT "Sell"

   END IF
END SUB

