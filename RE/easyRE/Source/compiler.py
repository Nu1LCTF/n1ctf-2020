import struct
import random

eax_from = (0x100 << 12)
al_from = (0x101 << 12)
ebx_from = (0x200 << 12)
ecx_from = (0x300 << 12)
edx_from = (0x400 << 12)
dl_from = (0x401 << 12)
edi_from = (0x500 << 12)
esi_from = (0x600 << 12)
memery_from = (0x700 << 12)
imm_val_from = (0x800 << 12)
base_of_ebp_from = (0x900 << 12)
type_lea = (0xa00 << 12)

eax_to = (0x100)
al_to = (0x101)
ebx_to = (0x200)
ecx_to = (0x300)
edx_to = (0x400)
dl_to = (0x401)
edi_to = (0x500)
esi_to = (0x600)
memery_to = (0x700)
imm_val_to = (0x800)
base_of_ebp_to = (0x900)


f=open('opcode_swap.txt','r')
instruction=f.read()
instruction=instruction.split('\n')



fff=open('opcode.bin','wb')

code_type={'mov':0x1000000,'add':0x2000000,'sub':0x3000000,'shl':0x4000000,'shr':0x5000000,'movzx':0x6000000,'or':0x7000000,'xor':0x8000000,'cmp':0x9000000,'retn':0xa000000,'swap_handle':0xb000000,'jz':0xc000000}
code_name=['mov','add', 'sub','movzx','shr','shl','or','xor','cmp','swap_handle','jz','retn']

for i in instruction:
    code_val=0
    arg1=random.randint(0,0xfffffffe)
    arg2=random.randint(0,0xfffffffe)

    code_tp=i.split('     ')

    if code_tp[0]=='mov':
        code_val |= code_type['mov']
        operator_type=code_tp[1].split(', ')

        if '[' in operator_type[0]:
            if 'ebp-' in operator_type[0]:
                arg1=int(operator_type[0][5:operator_type[0].find(']')],16)
                code_val |= base_of_ebp_to

                if 'al' in operator_type[1]:
                    code_val |= al_from
                else:
                    code_val |= imm_val_from
                    operator_type[1]=operator_type[1].replace('h','')
                    arg2=int('0x'+operator_type[1],16)

            else:
                code_val |= memery_to

                if 'edx' in operator_type[0]:
                    arg1 = 1
                    if 'al' in operator_type[1]:
                        code_val |= al_from
                
                else:
                    arg1 = 2
                    if 'dl' in operator_type[1]:
                        code_val |= dl_from

        else:
            if '[' in operator_type[1]:
                if operator_type[1]=='[ebp+arg_0]':
                    #arg1=0x4001D830
                    arg1 = 0x40006660  #flag addr
                    code_val |= imm_val_from

                    if operator_type[0]=='eax':
                        code_val |= eax_to
                    
                    elif operator_type[0]=='edx':
                        code_val |= edx_to

                elif operator_type[1]=='[ebp-0x4]':
                    arg1=4
                    code_val |= base_of_ebp_from
                    code_val |= eax_to
            else:
                if operator_type[0]=='ecx':
                    if operator_type[1]=='edx':
                        code_val |= edx_from
                        code_val |= ecx_to

                elif operator_type[0]=='eax':
                    if operator_type[1]=='edx':
                        code_val |= edx_from
                        code_val |= eax_to


    elif code_tp[0]=='movzx':
        code_val |= code_type['movzx']
        operator_type=code_tp[1].split(', ')

        if 'byte ptr' in operator_type[1]:
            code_val |= memery_from 
            if '[eax+' in operator_type[1]:
                tmp=operator_type[1].replace('h','')
                arg2=int('0x'+tmp[14:tmp.index(']')],16)
                arg1=1
                code_val |= eax_to
                
            elif '[edx]' in operator_type[1]:
                arg1=2
                code_val |= edx_to

        else:
            if 'dl' in operator_type[1]:
                if 'edx' in operator_type[0]:
                    code_val |= dl_from
                    code_val |= edx_to
                
                elif 'eax' in operator_type[0]:
                    code_val |= dl_from
                    code_val |= eax_to


            elif 'al' in operator_type[1]:
                if 'edx' in operator_type[0]:
                    code_val |= al_from
                    code_val |= edx_to
                
                elif 'eax' in operator_type[0]:
                    code_val |=al_from
                    code_val |=eax_to



    elif code_tp[0]=='add':
            code_val |= code_type['add']
            operator_type=code_tp[1].split(', ')

            if operator_type[1]=='eax':
                if operator_type[0]=='edx':
                    code_val |= eax_from
                    code_val |= edx_to
            
            elif operator_type[1]=='edx':
                if operator_type[0]=='eax':
                    code_val |= edx_from
                    code_val |= eax_to
            
            else:
                code_val |= imm_val_from

                if operator_type[0]=='eax':
                    code_val |= eax_to
                    z=operator_type[1].replace('h','')
                    arg1 = int('0x'+z,16)
                
                elif operator_type[0]=='edx':
                    code_val |= edx_to
                    z=operator_type[1].replace('h','')
                    arg1 = int('0x'+z,16)
    
    elif code_tp[0]=='or':
        code_val |= code_type['or']
        operator_type=code_tp[1].split(', ')
        if operator_type[0]=='edx':
            if operator_type[1]=='ecx':
                code_val |= ecx_from
                code_val |= edx_to
    
    elif code_tp[0]=='cmp':
        code_val |= code_type['cmp']
        operator_type=code_tp[1].split(', ')
        if operator_type[0]=='eax':
            if 'h' in operator_type[1]:
                code_val |= eax_to
                code_val |= imm_val_from
                z=operator_type[1].replace('h','')
                arg1 = int('0x'+z,16)

    elif code_tp[0]=='sub':
        code_val |= code_type['sub']
        operator_type=code_tp[1].split(', ')

        if operator_type[0]=='edx':
            code_val |= edx_to

            if operator_type[1]=='eax':
                code_val |= eax_from

    elif code_tp[0]=='lea':
        code_val |= code_type['mov']
        operator_type=code_tp[1].split(', ')

        if operator_type[0]=='edx':
            code_val |= type_lea
            if '[eax+' in operator_type[1]:
                z=operator_type[1][5:]
                z=z.replace('h','')[:-1]
                arg1=int('0x'+z,16)
                
                
    elif code_tp[0]=='shl':
        code_val |= code_type['shl']
        operator_type=code_tp[1].split(', ')
        if operator_type[0]=='edx':
            code_val |= imm_val_from
            code_val |= edx_to
            z=operator_type[1].replace('h','')
            arg1=int('0x'+z,16)



    elif code_tp[0]=='shr':
        code_val |= code_type['shr']
        operator_type=code_tp[1].split(', ')
        if operator_type[0]=='dl':
            code_val |= imm_val_from
            code_val |= dl_to
            z=operator_type[1].replace('h','')
            arg1=int('0x'+z,16)

    elif code_tp[0]=='xor':
        code_val |= code_type['xor']
        operator_type=code_tp[1].split(', ')

        if operator_type[0]=='al':
            code_val |= al_to
            if '[ebp-' in operator_type[1]:
                code_val |= base_of_ebp_from
                z=operator_type[1][5:]
                z=z.replace('h','')[:-1]
                arg1=int(z,16)

    elif code_tp[0]=='jz':
        code_val |= code_type['jz']
        tmp=int(code_tp[1])
        if tmp>=0:
            arg1 = 0
            arg2 = tmp
        else:
            arg1 = 1
            arg2 = abs(tmp)

    elif code_tp[0]=='retn':
        code_val |= code_type['retn']

    elif code_tp[0]=='swap':
        code_val |= code_type['swap_handle']
        operator_type=code_tp[1].split(', ')
        arg1=int(operator_type[0])
        arg2=int(operator_type[1])
        tmp=code_type[code_name[arg1]]
        code_type[code_name[arg1]]=code_type[code_name[arg2]]
        code_type[code_name[arg2]]=tmp
        
        print(hex(code_val),end='   ')
        print(hex(arg1),end='   ')
        print(hex(arg2))




    # print(hex(code_val),end='   ')
    # print(hex(arg1),end='   ')
    # print(hex(arg2))
    tmp1=struct.pack('I',code_val)
    tmp2=struct.pack('I',arg1)
    tmp3=struct.pack('I',arg2)

    fff.write(tmp1)
    fff.write(tmp2)
    fff.write(tmp3)

fff.close()

