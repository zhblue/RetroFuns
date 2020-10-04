DECLARE SUB KLine (start AS LONG)
DECLARE SUB K1Line (current AS LONG, start AS LONG)
DECLARE SUB M1Line (total AS LONG, start AS LONG, mlen AS INTEGER, colour AS INTEGER)
DECLARE SUB MLine (start AS LONG, mlen AS INTEGER, colour AS INTEGER)
DECLARE SUB drawLine (start AS LONG, value() AS LONG, colour AS INTEGER)
DECLARE SUB loadGuoSendata (filepath AS STRING)
DECLARE FUNCTION inputCode$ ()
DECLARE SUB initSteps (start AS LONG)


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
DIM SHARED code$, total AS LONG, smax, smin, xstep, ystep, ybase, tkey AS STRING

REDIM SHARED sdate(1) AS LONG, sopen(1) AS LONG, sclose(1)  AS LONG, shigh(1) AS LONG, slow(1) AS LONG, svol(1)  AS LONG


code$ = inputCode + ".day"
loadGuoSendata (code$)
playlen = 250
PRINT code$; " Total:"; total
INPUT "How many days to play ?", playlen
IF playlen > total / 2 + 100 THEN playlen = total / 2 + 100
IF playlen <= 10 THEN playlen = 250


SCREEN 12



DIM start AS LONG
start = total - playlen - 100
initSteps (start)

realtotal = total
total = realtotal - playlen

CALL MLine(start, 1, 1)
CALL MLine(start, 5, 3)
CALL MLine(start, 20, 4)
CALL MLine(start, 60, 14)
CALL KLine(start)

'Start Playback

FOR total = total TO realtotal
   LOCATE 1, 1
   COLOR 15
   'PRINT code$; ":";
   COLOR 7
   PRINT sdate(total);
   COLOR 15
   PRINT "Open("; sopen(total) / 100; ")";
   COLOR 4
   PRINT "High("; shigh(total) / 100; ")";
   COLOR 14
   PRINT "Low("; slow(total) / 100; ")";
   COLOR 15
   PRINT "Close("; sclose(total) / 100; ")";


   CALL M1Line(total, start, 1, 1)
   CALL M1Line(total, start, 5, 3)
   CALL M1Line(total, start, 20, 4)
   CALL M1Line(total, start, 60, 14)
   CALL K1Line(total, start)

   PLAY "l8" + CHR$(65 + INT(sclose(total) MOD 7))
   tkey = INKEY$
   IF "q" = tkey THEN EXIT FOR


NEXT

PRINT "Press Esc to exit ..."
DO
LOOP UNTIL INKEY$ = CHR$(27)

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

SUB initSteps (start AS LONG)
   
    smax = shigh(start)
    smin = slow(start)

    FOR i = start TO total
 
        IF shigh(i) > smax THEN smax = shigh(i)
        IF slow(i) < smin THEN smin = slow(i)
   
    NEXT
   xstep = 630 / (total - start)
   ybase = 300
   ytop = 50
   ystep = (ybase - ytop) / (smax - smin)
 
END SUB

FUNCTION inputCode$
   
    INPUT "Code:", code$
    IF "" = code$ THEN code$ = "sh000001"
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
     LINE (x0, y3)-(x0, y4), c
     LINE (x1, y1)-(x2, y2), c, BF
     'LOCATE 20, 1
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
    PRINT USING "########"; sdate(total);

    CLOSE filenum
   
END SUB

SUB M1Line (total AS LONG, start AS LONG, mlen AS INTEGER, colour AS INTEGER)
   
      
      DIM value(2) AS LONG
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
       LINE (x1, y1)-(x2, y2), colour
       LOCATE 20, 1
'       PRINT x; "("; x1; ","; y1; ")-("; x2; ","; y2; ")"; colour
'       PLAY "c"

END SUB

SUB MLine (start AS LONG, mlen AS INTEGER, colour AS INTEGER)
   REDIM value(total) AS LONG
   IF start < mlen THEN start = mlen
  
   FOR i = start TO total
      sum = 0
      FOR j = i - mlen + 1 TO i
         sum = sum + sclose(j)
      NEXT
      value(i) = sum / mlen
   NEXT
   CALL drawLine(start, value(), colour)
END SUB
