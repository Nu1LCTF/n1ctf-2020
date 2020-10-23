## Intro

The core part of this challenge is to craft a file's CRC to an arbitrary value(zero) by modifying some specified bytes of the same bit size as the CRC value. 

As for the binary `n1vault`, it uses SHA256 to digest all the bytes inside the file(`credencial.png`) except for the even bytes in the last 25 bytes(some twists were added to the *sha256_update* function, paving the way for the backdoor), once the file's CRC has been faked to 0, a secret logic(backdoor) will be triggered by an exception *FPE_INTDIV*, since the verification inside function `main` has an unnecessary comparison `4764888639493207598 / (crc32_result | crc64_result) == 1`, which will trigger an *FPE_INTDIV* when both crc32_result and crc64_result are zero, and will be evaluated to *true* when given the original `credential.png`. Players' job is to to construct an input to trigger the backdoor, send the constructed bytes to the judging bot and receive the flag.

## Solution

The reverse engineering part of the binary program is quite easy, some junks with fixed patterns are inserted into the main logic, which can be bypassed by simple searching & replacing. After that the program logic is really straightforward, we only have to solve the math problem left.

CRC has a property that the final result can be viewed as the linear combination of the influence of each bit in the message and an initial bias, based on $GF(2)$, which can be described as:
$$
f(x)=f(0) + \sum_{i=0}^{CRC\_SIZE-1} x_i \cdot \mbox{influence}(i),
$$
where $f(0)$ is the initial bias, specifically for this challenge, is the CRC of the credential with all the even bytes in the last 25 bytes set to zero. Given this property, if we have enough $x_i$ to control, we can easily construct a matrix and solve each $x_i$ using gauss elimination. The twist here is that we have to ensure both $f(x)=CRC32(credential)$ and $g(x)=CRC64(credential)$ are equal to zero. Actually if we let $h(x)=(f(x)<<64)+g(x)$ and focus our attention on making $h(x)=0$, it has the same effect as making both $f(x)$ and $g(x)$ zero.

I write a tool based on this interesting property of CRC, allowing us to arbitrarily craft a file's CRC by specifying certain bits available for modification. It can output all the available solutions and allows for fewer available bits than the bit size of the CRC result. You can check the tool here: 

https://github.com/yype/crcollider

Using this tool we can easily solve the problem using the following Python code:

```python
from crcollider import collcrc
from crc_funcs import crc64, crc32

def crc96(m):
    return (crc32(m) << 64) + crc64(m)

def solve_chal():
    with open('credential.png', 'rb') as f:
        org_img = f.read()

    rg = list(range(len(org_img)*8))
    available_bits = []
    for i in range(12):
        # even bytes in the last 25 bytes
        available_bits += rg[len(rg)-16*i-16:len(rg)-16*i-8]

    sol_num, sols = collcrc(crc96, 96, org_img, available_bits, 0x0)
    
    print(f'{sol_num} solution(s) found')

    for i, each in enumerate(sols):
        file_out = f'credential_sol{i}.png'
        print(f'Outputting sol{i} to {file_out}...')
        with open(file_out, 'wb') as f:
            f.write(each)

if __name__ == '__main__':
    solve_chal()

```

There are totally 4 solutions available for this challenge. One of them contains only visible characters, which is `n1vaultadmin`(intentionally crafted), while others are not.

```
solution> python3 .\main.py
4 solution(s) found
Outputting sol0 to credential_sol0.png...
Outputting sol1 to credential_sol1.png...
Outputting sol2 to credential_sol2.png...
Outputting sol3 to credential_sol3.png...
```

You can also check the awesome write-up from team *Super Guesser* who got the first blood of this challenge here:

https://gist.github.com/jhs7jhs/cb5fedc1ffb6138b73420cb8567357bb#n1vault