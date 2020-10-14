DECLARE SUB music ()
DECLARE SUB buy ()
DECLARE SUB sell ()
DECLARE SUB music ()
DECLARE SUB display ()
DECLARE SUB KLine (start AS LONG)
DECLARE SUB K1Line (current AS LONG, start AS LONG)
DECLARE SUB M1Line (total AS LONG, start AS LONG, mlen AS INTEGER, colour AS INTEGER)
DECLARE SUB MLine (start AS LONG, mlen AS INTEGER, colour AS INTEGER)
DECLARE SUB drawLine (start AS LONG, value() AS LONG, colour AS INTEGER)
DECLARE SUB loadGuoSendata (filepath AS STRING)
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
DIM SHARED code$, total AS LONG, smax, smin, xstep, ystep, vstep, ybase, tkey AS STRING
DIM SHARED startMoney AS LONG, Money AS LONG, stock AS LONG
DIM SHARED mus(360) AS STRING, musStep AS INTEGER
DIM SHARED screenW AS LONG, screenH  AS LONG, realtotal AS LONG
DIM SHARED start AS LONG, m AS INTEGER, mode AS INTEGER
REDIM SHARED sdate(1) AS LONG, sopen(1) AS LONG, sclose(1)  AS LONG, shigh(1) AS LONG, slow(1) AS LONG, svol(1)  AS LONG
mode = 12         '12 =vga   ,1 = cga
m = 1

CLS
SCREEN mode
IF mode = 12 THEN
        screenW = 640
        screenH = 480
END IF

IF mode = 1 THEN
        screenW = 320
        screenH = 240

END IF
xstep = 3


LOCATE screenH / 2 / 16, 1
IF mode = 12 THEN COLOR 14
IF COMMAND$ = "" THEN
        PRINT "Chinese Stock Market named as A Stock Market."
        PRINT "Here is a real history record of one stock."
        PRINT "You are going to trade with a million of fortune."
        PRINT "Press B for Buy ,S for Sell during the game."
        PRINT "Wish you good luck , cause you are going to need it."
        IF mode = 12 THEN COLOR 12
        PRINT "Press C to Continue..."
        IF mode = 12 THEN COLOR 15
        DO
        LOOP UNTIL INKEY$ = "c"

END IF

FOR i = 0 TO UBOUND(mus)
        READ mus(i)
NEXT






FILES "*.day"
IF COMMAND$ = "" THEN code$ = inputCode + ".day" ELSE code$ = COMMAND$

loadGuoSendata (code$)
playlen = UBOUND(mus)
IF total = 0 THEN END

PRINT code$; " Total:"; total; " days"
IF COMMAND$ = "" THEN INPUT "How many days to play ?", playlen
IF playlen > total / 2 + 100 THEN playlen = total / 2 + 100
IF playlen <= 10 THEN playlen = total - 250



start = total - playlen


realtotal = total

PLAY ON

DO

total = realtotal - playlen

startMoney = 100000000
stock = 0
Money = startMoney


CLS


CALL MLine(start, 1, 1)
CALL MLine(start, 5, 3)
CALL MLine(start, 20, 4)
CALL MLine(start, 60, 14)
CALL MLine(start, 240, 15)

CALL KLine(start)

'Start Playback

FOR total = total TO realtotal

   IF (total - start) MOD (screenW / xstep) = 1 THEN
      CLS
      initsteps (total)
      IF mode = 12 THEN LOCATE screenH / 16, 1
      PRINT "Press Esc to Stop, Source: http://github.com/zhblue/RetroFuns   ";
      PRINT code$
   END IF

   CALL display
   CALL M1Line(total, start, 1, 1)
   CALL M1Line(total, start, 5, 3)
   CALL M1Line(total, start, 20, 4)
   CALL M1Line(total, start, 60, 14)
   CALL M1Line(total, start, 240, 15)
   CALL K1Line(total, start)

   IF m = 1 THEN CALL music
   tkey = INKEY$
   IF CHR$(27) = tkey THEN EXIT FOR
   IF tkey = "b" THEN CALL buy
   IF tkey = "s" THEN CALL sell
   IF tkey = "m" THEN m = 1 - m
NEXT
PLAY "p4p4"

LOCATE screenH / 16 - 1, 1

IF COMMAND$ = "" THEN
        IF total > realtotal THEN total = realtotal
        PRINT "Score:";
        PRINT Money / startMoney * 100 + sclose(total) / startMoney * stock * 100;
        PRINT "%  Press C to Continue..."
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
   vol = INT(Money / price / 100) * 100
   IF (vol > 0) THEN
           Money = Money - vol * price
           stock = stock + vol
           x = total - start
           x0 = (x * xstep) MOD screenW
           y0 = ybase - (price - smin) * ystep
           CIRCLE (x0, y0), 5, 12
           IF mode = 12 THEN COLOR 12
           LOCATE INT(y0 / 16) + 1, INT(x0 / 8) + 1
           PRINT "Buy"

   END IF

END SUB

SUB display
   LOCATE 1, 1
   IF mode = 12 THEN COLOR 15
   'PRINT code$; ":";
   IF mode = 12 THEN COLOR 7
   PRINT sdate(total);
   IF mode = 12 THEN COLOR 15
   PRINT "Open("; sopen(total) / 100; ")";
   IF mode = 12 THEN COLOR 4
   PRINT "High("; shigh(total) / 100; ")";
   IF mode = 12 THEN COLOR 14
   PRINT "Low("; slow(total) / 100; ")";
   IF mode = 12 THEN COLOR 15
   PRINT "Close("; sclose(total) / 100; ")";
   LINE (0, screenH - 32)-(screenW, screenH - 16), 0, BF
   FOR y = 32 TO screenH - 32 STEP 60
       LINE (0, y)-(screenW, y), 1, , &HF00
   NEXT
   IF mode = 12 THEN LOCATE screenH / 16 - 1, 1
   PRINT "Money:"; Money / 100, "Stock:"; stock, "Percent:";
   PRINT Money / startMoney * 100 + sclose(total) / startMoney * stock * 100; "%";
   'PRINT "Ystep:"; ystep
   
   
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
    default = "300104"
    PRINT "Now input one stock Code (default:" + default + ") ";
    INPUT ":", code$
    IF "" = code$ THEN code$ = default
    DIM f AS STRING

    f = LEFT$(code$, 1)

    IF f = "6" THEN code$ = "sh" + code$
    IF f = "5" THEN code$ = "sh" + code$

    IF f = "0" THEN code$ = "sz" + code$
    IF f = "2" THEN code$ = "sz" + code$
    IF f = "3" THEN code$ = "sz" + code$


    inputCode$ = code$

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
     LINE (x1, ybase)-(x2, y5), 8, BF
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

SUB loadGuoSendata (filepath AS STRING)
'PRINT code$

    DIM filenum AS LONG
    filenum = FREEFILE
    DIM c AS guosen
    DIM i AS LONG
    DIM xfix AS DOUBLE
 
    OPEN filepath FOR RANDOM AS filenum LEN = 32
  
    total = LOF(filenum) / LEN(c)
  
    REDIM sdate(total)  AS LONG
    REDIM sopen(total)  AS LONG
    REDIM sclose(total) AS LONG
    REDIM shigh(total) AS LONG
    REDIM slow(total) AS LONG
    REDIM svol(total) AS LONG
  
    xfix = 1#
 
    FOR i = 1 TO total
        GET filenum, i, c

        sdate(i) = c.date
        sopen(i) = c.ope
        shigh(i) = c.high
        slow(i) = c.low
        sclose(i) = c.clos
        svol(i) = c.volume
     
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

SUB music

    musStep = musStep MOD UBOUND(mus)
    PLAY mus(musStep)
    musStep = musStep + 1
END SUB

SUB sell
   price = sclose(total)
   vol = stock
   Money = Money + vol * price
   stock = stock - vol
   IF vol > 0 THEN
           x = total - start
           x0 = (x * xstep) MOD screenW
           y0 = ybase - (price - smin) * ystep
           CIRCLE (x0, y0), 5, 10
           IF mode = 12 THEN COLOR 10
           LOCATE INT(y0 / 16) + 1, INT(x0 / 8) + 1
           PRINT "Sell"

   END IF
END SUB

