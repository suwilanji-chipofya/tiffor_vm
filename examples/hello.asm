#Tiffor assembly language 

.section data
STRING msg eq "Hello,World!\n"
INT len eq LEN(msg)
.section text
Mov r0, 0
Mov r1,len
Mov r2,msg
Mov r0,1
Mov r7,3
.end
