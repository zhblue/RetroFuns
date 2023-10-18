TYPE buf
dat AS STRING * 1
END TYPE
DIM b AS buf
DIM s AS STRING
OPEN "COM1: 19200,N,8,1,rb1024 " FOR RANDOM AS #1
OPEN "intersvr.exe" FOR BINARY AS #2 LEN = 1
   DO
     INPUT #1, s
     IF s = "end" THEN PRINT #1,-1:EXIT DO 
     b.dat = CHR$(VAL("&h" + s))
     PUT #2, , b
     c = c + 1
     PRINT #1, c
   WEND
CLOSE #1
CLOSE #2
