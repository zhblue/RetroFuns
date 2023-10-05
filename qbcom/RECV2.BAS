CLS
TYPE buf
dat AS STRING * 1
END TYPE
DIM b AS buf
DIM s AS STRING
c = 0
OPEN "COM1: 19200,N,8,1,rb16384 " FOR RANDOM AS #1
KILL "data.out"
OPEN "data.out" FOR BINARY AS #2 LEN = 1
   WHILE s <> "end"
     INPUT #1, s
      b.dat = CHR$(VAL("&h" + s))
      PUT #2, , b
     c = c + 1
     PRINT #1, c
     PRINT ".";
   WEND
CLOSE #1
CLOSE #2

