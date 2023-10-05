CLS
TYPE buf
dat AS STRING * 1
END TYPE
DIM b AS buf
OPEN "com1:19200,N,8,1,tb1024" FOR RANDOM AS #1
OPEN "intersvr.exe" FOR BINARY AS #2 LEN = 1
DIM flen AS LONG
flen = LOF(2)
 FOR i = 1 TO flen
 GET #2, , b
 PRINT #1, HEX$(ASC(b.dat))
 INPUT #1, n
 PRINT n; "/"; flen, INT(n * 100) / flen; "%"
 NEXT
PRINT #1, "end"
INPUT #1, n
PRINT n
CLOSE #1
CLOSE #2
