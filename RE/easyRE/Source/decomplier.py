import binascii

rip = 0
f=open('opcode.bin','rb')
t=f.read()
opcode=[((t[i+3]<<24)|(t[i+2]<<16)|(t[i+1]<<8)|t[i]) for i in range(0,len(t),4)]

opcode_type_id = [0x1000000, 0x2000000, 0x3000000, 0x6000000, 0x5000000, 0x4000000,
                  0x7000000, 0x8000000, 0x9000000, 0x0B000000, 0x0C000000, 0x0A000000]

tot=0
tag=3

while rip != len(opcode):
    opcode_type = opcode[rip] & 0xF000000
    opcode_a1 = opcode[rip] & 0xFFF000
    opcode_a2 = opcode[rip] & 0xFFF
    arg1 = opcode[rip+1]
    arg2 = opcode[rip+2]
    
    if tag==2:
        print("LABLE_%d:"%tot)
        tot+=1

    if opcode_type == opcode_type_id[0]:
        if opcode_a1 == 0x800000:
            if opcode_a2==0x900:
                print('memory[ %s + 0x100 ] = %s;'%(hex(arg1),hex(arg2)))
            
            elif opcode_a2==0x100:
                print('reg_1 = %s;'%(hex(arg1)))
            
            elif opcode_a2==0x400:
                print('reg_3 = %s;'%(hex(arg1)))

        elif opcode_a1 == 0x900000:
            if opcode_a2==0x100:
                print('reg_1 = memory[ %s + 0x100 ];'%(hex(arg1)))
            
            elif opcode_a2==0x400:
                print('reg_3 = memory[ %s + 0x100 ];'%(hex(arg1)))

        elif opcode_a1 == 0x101000:
            if opcode_a2==0x900:
                print('memory[ %s + 0x100 ] = (unsigned char)reg_1;'%(hex(arg1)))
            
            elif opcode_a2==0x700:
                if arg1==1:
                    print('*(unsigned char *)reg_3 = (unsigned char)reg_1;')

                elif arg1==2:
                    print('*(unsigned char *)reg_1 = (unsigned char)reg_1;')

        elif opcode_a1 == 0x401000:
            if opcode_a2==0x700:
                if arg1==1:
                    print('*(unsigned char *)reg_3 = (unsigned char)reg_3;')
                
                elif arg1==2:
                    print('*(unsigned char *)reg_1 = (unsigned char)reg_3;')

        elif opcode_a1 == 0x400000:
            if opcode_a2==0x300:
                print('reg_2 = reg_3;')
            elif opcode_a2==0x100:
                print('reg_1 = reg_3;')

        elif opcode_a1 == 0xA00000:
            print('reg_3 = %s + reg_1;'%(hex(arg1)))

    elif opcode_type==opcode_type_id[1]:
        if opcode_a1==0x800000:
            if opcode_a2==0x100:
                print('reg_1 += %s;'%(hex(arg1)))
                
            elif opcode_a2==0x400:
                print('reg_3 += %s;'%(hex(arg1)))

        elif opcode_a1==0x100000:
            if opcode_a2==0x400:
                print('reg_3 += reg_1;')

        elif opcode_a1==0x400000:
            if opcode_a2==0x100:
                print('reg_1 += reg_3;')

    elif opcode_type==opcode_type_id[2]:
        if opcode_a1==0x100000:
            if opcode_a2==0x400:
                print('reg_3 -= reg_1;')

    elif opcode_type==opcode_type_id[3]:
        if opcode_a1==0x700000:
            if arg1==1:
                if opcode_a2==0x100:
                    print('reg_1 = *(unsigned char *)(reg_1 + %s);'%(hex(arg2)))
            elif arg1==2:
                if opcode_a2==0x400:
                    print('reg_3 = *(unsigned char *)reg_3;')
        
        elif opcode_a1==0x101000:
            if opcode_a2==0x400:
                print('reg_3 = (unsigned char)reg_1;')
            
            elif opcode_a2==0x100:
                print('reg_1 = (unsigned char)reg_1;')
            
        
        elif opcode_a1==0x401000:
            if opcode_a2==0x100:
                print('reg_1 = (unsigned char)reg_3;')
            elif opcode_a2==0x400:
                print('reg_3 = (unsigned char)reg_3;')


    elif opcode_type==opcode_type_id[4]:
        if opcode_a1==0x800000:
            if opcode_a2==0x401:
                print('tmp = (unsigned char*)&reg_3; *tmp >>= 4;')
    
    elif opcode_type==opcode_type_id[5]:
        if opcode_a1==0x800000:
            if opcode_a2==0x400:
                print('reg_3 <<= 4;')

    elif opcode_type==opcode_type_id[6]:
        if opcode_a1==0x300000:
            if opcode_a2==0x400:
                print('reg_3 |= reg_2;')

    elif opcode_type==opcode_type_id[7]:
        if opcode_a1==0x900000:
            if opcode_a2==0x101:
                print('tmp = (unsigned char*)&reg_1; *tmp ^= memory[ %s + 0x100 ];'%(hex(arg1)))
    
    elif opcode_type==opcode_type_id[8]:
        if opcode_a1==0x800000:
            if opcode_a2==0x100:
                print('eflag = reg_1 - %s;'%(hex(arg1)))
    
    elif opcode_type==opcode_type_id[9]:
        tmp = opcode_type_id[arg1]
        opcode_type_id[arg1] = opcode_type_id[arg2]
        opcode_type_id[arg2] = tmp

        #print('swap SCOPE_TABLE[ %d ] , SCOPE_TABLE[ %d ]'%(arg1,arg2))

    elif opcode_type==opcode_type_id[10]:
        if arg1==1:
            print('goto xxx')
        else:
            print('if(!eflag) goto LABLE_%d;'%tot)
        
        tag=0

    elif opcode_type==opcode_type_id[11]:
        print('ret reg_1 == 1;')

    rip += 3
    tag += 1
