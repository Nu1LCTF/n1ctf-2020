# VSS

## Description

Just a simple visual threshold scheme.

## Writeup

Predict python's random then recover the origin image.
```python
from PIL import Image
from randcrack import RandCrack
import random
share = Image.open('share2.png')
width = share.size[0]//2
res = Image.new('L', (width, width))
bits = ''
for idx in range(width*width-624*32, width*width):
    i, j = idx//width, idx % width
    if share.getpixel((2*j, 2*i)) == 255:
        bits += '0'
    else:
        bits += '1'
rc = RandCrack()
for i in range(len(bits), 0, -32):
    rc.submit(int(bits[i-32:i], 2))
flipped_coins = [int(bit)
                 for bit in bin(rc.predict_getrandbits(width*width-624*32))[2:].zfill(width*width-624*32)] + list(map(int, bits))

data = []

for idx in range(width*width):
    i, j = idx//width, idx % width
    if share.getpixel((2*j, 2*i)) == 255:
        data.append(0 if flipped_coins[idx] else 255)
    else:
        data.append(255 if flipped_coins[idx] else 0)

res.putdata(data)
res.save('ans.png')
```